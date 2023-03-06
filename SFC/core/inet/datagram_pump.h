#pragma once
/**
 * @file datagram_pump.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-04-30
 * 
 * @copyright  
 * System Foundation Classes(SFC)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *      * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *      * Neither the name of SFC.  nor the names of its
 *        contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
/** \defgroup inet inet 
 * @ingroup SFC
 *  @{
 */

#include "inet.h"

namespace inet
{
/** \defgroup datagram_pump datagram_pump
 * @ingroup inet
 *  @{
 */

/**
 * @brief IOCP has recv buffer per-socket, it is paralellizing multiple RecvFrom calls epoll/kqueue has recv buffer pre-thread, 
 * it is waiting for event from multiple socket before making RecvFrom calls 
 */
class AsyncDatagramCoreBase
{
public:
#if defined(PLATFORM_WIN)
	typedef	HANDLE	    IOCORE;
	static const SIZE_T IOCORE_INVALID = (SIZE_T)INVALID_HANDLE_VALUE;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    static const int    EVENT_BATCH_SIZE = 8;  // for Linux only
    typedef	int		    IOCORE;
	static const int 	IOCORE_INVALID = -1;
#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
	static const int    EVENT_BATCH_SIZE = 1020; // less than the recursive template instantiation depth
	typedef	int		    IOCORE;  // highest-numbered file descriptor
	static const int 	IOCORE_INVALID = -2;
	typedef rt::hash_map<SOCKET, LPVOID>	t_Socket2Cookie;
	
	pthread_rwlock_t fdslock;
	t_Socket2Cookie	Socket2Cookies;
	fd_set allfds;
#else
	#error AsyncIOCore Unsupported Platform
#endif

protected:
	IOCORE					_Core = (IOCORE)IOCORE_INVALID;
	rt::Buffer<os::Thread>	_IOWorkers;

public:
	struct Event
	{
#if defined(PLATFORM_WIN)
		DWORD	bytes_transferred;
        LPVOID  cookie;
		WSAOVERLAPPED* overlapped;
#else
        int     count;
        LPVOID  cookies[EVENT_BATCH_SIZE];
#endif
	};

protected:
	bool _Init(os::FUNC_THREAD_ROUTINE io_pump, UINT concurrency = 0, UINT stack_size = 0);
	bool _AddObject(SOCKET obj, LPVOID cookie);
	void _RemoveObject(SOCKET obj);
	bool _PickUpEvent(Event& e);

public:
	bool IsRunning() const { return _Core != (IOCORE)IOCORE_INVALID; }
	void Term();
	~AsyncDatagramCoreBase(){ Term(); }
};

#pragma pack(push, 1)
struct Datagram
{
    LPBYTE		RecvBuf;
	DWORD		RecvBufSize;	///< MTU
    DWORD		RecvSize;		///< Last recv
    socklen_t	PeerAddressSize;
    union {
        WORD        PeerAddressFamily; ///< AF_INET, AF_INET6
        InetAddr    PeerAddressV4;
        InetAddrV6  PeerAddressV6;
    };

    bool        IsIPv4() const { return PeerAddressFamily == AF_INET && PeerAddressSize>=sizeof(InetAddr); }
    bool        IsIPv6() const { return PeerAddressFamily == AF_INET6 && PeerAddressSize>=sizeof(InetAddrV6); }
};
#pragma pack(pop)

/**
 * @brief Non-blocking I/O is used, the # of UDP packet is not equal to # of events by epoll/kevent.
 * 
 */
class DatagramSocket: public Socket
{
    template<typename SocketObject>
    friend class DatagramPump;
    
	bool RecvFrom(LPVOID pData, UINT len, UINT& len_out, InetAddr &target);
	bool RecvFrom(LPVOID pData, UINT len, UINT& len_out, InetAddrV6 &target);
	bool Recv(LPVOID pData, UINT len, UINT& len_out, bool Peek);
    void EnableNonblockingIO(bool enable = true);
    bool Create(const InetAddrV6 &BindTo,int nSocketType, bool reuse_addr);
    bool Create(const InetAddr &BindTo,int nSocketType, bool reuse_addr);
    bool Send(LPCVOID pData, UINT len, bool drop_if_busy = false);
    
protected:
#if defined(PLATFORM_WIN)
	struct RecvBlock
	{
		TYPETRAITS_DECLARE_NON_POD;
		int				Index;
		SOCKET			hSocket;		///< just a copy of DatagramSocket
		Datagram		Packet;
		WSAOVERLAPPED	Overlapped;
		BYTE			DataBuf[1];	///< MTU
		UINT			GetSize() const { return offsetof(RecvBlock, DataBuf) + Packet.RecvBufSize; }
		bool			PumpNext();
		bool			IsErrorNeglectable(int err) const {return (WSAENETRESET == err || WSAECONNRESET == err || WSAEMSGSIZE == err);}
	};
    rt::BufferEx<BYTE>	_ConcurrentRecvBuf; ///< MTU + sizeof(inet::Datagram) + sizeof(WSAOVERLAPPED)
	UINT				_Concurrency = 0;
	UINT				_RecvBlockSize = 0;
	volatile int32_t	_RecvBlockCounter = 0;
	void				_InitBuf(UINT mtu, UINT concurrency);
	RecvBlock&			_GetRecvBlock(UINT i){ return *(RecvBlock*)(_ConcurrentRecvBuf.Begin() + i*_RecvBlockSize); }
	RecvBlock&			_GetRecvBlockFromOverlapped(WSAOVERLAPPED* overlapped) const 
						{	ASSERT((LPCBYTE)overlapped > _ConcurrentRecvBuf.Begin() && (LPCBYTE)overlapped < _ConcurrentRecvBuf.End());
							return *(RecvBlock*)(((LPCBYTE)overlapped) - offsetof(RecvBlock, Overlapped));
						}
	void				_ClearOverlapped()
						{	for(UINT i=0; i<_Concurrency; i++)
								_GetRecvBlock(i).Overlapped.hEvent = INVALID_HANDLE_VALUE;
						}
	void				_LockBuffer() { os::AtomicIncrement(&_RecvBlockCounter); }
	void				_UnlockBuffer() { os::AtomicDecrement(&_RecvBlockCounter); }
	void				_Shutdown();
#endif // #if defined(PLATFORM_WIN)

	bool	__SendTo(LPCVOID pData, UINT len, LPCVOID addr, int addr_len, bool drop_if_busy = false);

public:
	SOCKET	GetHandle() const { return _hSocket; }
    bool    Create(const InetAddrV6 &bind_to, bool reuse_addr = false);
    bool    Create(const InetAddr &bind_to, bool reuse_addr = false);

public:   
    static void     OnRecv(Datagram* g){ ASSERT(0); } ///< should be overrided

	// blocking call
	bool	        SendTo(LPCVOID pData, UINT len,const InetAddr &target, bool drop_if_busy = false){ return __SendTo(pData, len, &target, sizeof(InetAddr), drop_if_busy); }
	bool	        SendTo(LPCVOID pData, UINT len,const InetAddrV6 &target, bool drop_if_busy = false){ return __SendTo(pData, len, &target, sizeof(InetAddrV6), drop_if_busy); }
};

template<typename t_IOObject> ///< IOObjectDatagram or IOObjectStream
class RecvPump;

#if !defined(PLATFORM_WIN)
namespace _details
{
template<typename T>
inline bool OnRecv(T* obj, rt::Buffer<BYTE>& buf)
{	
	Datagram g;
	g.RecvBuf = buf.Begin();
	g.PeerAddressSize = sizeof(inet::InetAddrV6);
	int len = 0;
	do
	{
		len = ::recvfrom(obj->GetHandle(), g.RecvBuf, buf.GetSize(), 0, (sockaddr*)&g.PeerAddressFamily, &g.PeerAddressSize);
		if(len>=0){ g.RecvSize = len; obj->OnRecv(&g);}
		else { break; }
	} while(true);
	return len != 0 && (errno == EAGAIN || errno == EINTR);
}
template<typename T_OBJ, int SIZE, int ITER = 0, bool STOP = ITER == SIZE>
struct OnRecvAll
{
    static void Call(const AsyncDatagramCoreBase::Event& evt, rt::Buffer<BYTE>& buf)
    {   if(ITER < evt.count)
        {   if(!OnRecv((T_OBJ*)evt.cookies[ITER], buf))
                ((T_OBJ*)evt.cookies[ITER])->OnRecv(nullptr); // indicate error
            OnRecvAll<T_OBJ,SIZE,ITER+1>::Call(evt, buf);
        }
    }
};
    template<typename T_OBJ, int SIZE, int ITER>
    struct OnRecvAll<T_OBJ, SIZE, ITER, true>
    {
        static void Call(const AsyncDatagramCoreBase::Event& evt, rt::Buffer<BYTE>& buf){}
    };
} // namespace _details
#endif
/**
 * @brief Datagram Pump
 * 
 * @tparam SocketObject 
 * IOObjectDatagram or IOObjectStream
 */
template<typename SocketObject> 
class DatagramPump: public AsyncDatagramCoreBase
{
#if defined(PLATFORM_WIN)
public:
	volatile int _PendingRecvCall = 0;
#endif
protected:
	UINT _MTU;
	void _IOPump()
	{
#if !defined(PLATFORM_WIN)
        rt::Buffer<BYTE> buf;
        VERIFY(buf.SetSize(_MTU));  // per-thread recv buffer
#endif
		Event evt;
		while(IsRunning() && !_IOWorkers[0].WantExit())
		{
			if(AsyncDatagramCoreBase::_PickUpEvent(evt))
			{
#if defined(PLATFORM_WIN)
				auto so = (SocketObject*)evt.cookie;
				so->_LockBuffer();
				if(!so->IsValid()) 
				{
					so->_UnlockBuffer();
					continue;
				}
				auto& rb = so->_GetRecvBlockFromOverlapped(evt.overlapped);
				rb.Packet.RecvSize = evt.bytes_transferred;
				so->OnRecv(&rb.Packet);
				so->_UnlockBuffer();
				if(!rb.PumpNext())
				{	os::AtomicDecrement(&_PendingRecvCall);
					if(rb.Index == 0)
					{	so->OnRecv(nullptr);  // indicate error
						_LOGC_WARNING("[NET]: DatagramPump: IOCP Concurrency Dropped");
					}
				}
#else
                _details::OnRecvAll<SocketObject, sizeofArray(evt.cookies)>::Call(evt, buf);
#endif
			}
		}
	}

public:
	bool Init(UINT concurrency = 0, UINT mtu = UDP_Optimal_Size, UINT stack_size = 0)
	{
        _MTU = mtu;
		struct _call
		{	static DWORD _func(LPVOID p)
			{	((DatagramPump*)p)->_IOPump();
				return 0;
			}
		};
		return _Init(_call::_func, concurrency, stack_size);
	}
	/**
	 * @brief lifecycle is **not** maintained by RecvPump
	 * 
	 * @param obj 
	 * @return true 
	 * @return false 
	 */
	bool AddObject(SocketObject* obj) 
	{	
		if(!IsRunning())return false;

		((Socket*)obj)->EnableNonblockingIO(true);
		if(!_AddObject(obj->GetHandle(), obj))return false;
#if defined(PLATFORM_WIN)
		UINT cocurrency = (UINT)_IOWorkers.GetSize()*10;
        obj->_InitBuf(_MTU, cocurrency);
		for(UINT i=0; i<cocurrency; i++)
			if(!obj->_GetRecvBlock(i).PumpNext())
			{	RemoveObject(obj);
				_LOG_POS_WARNING;
				return false;
			}
		os::AtomicAdd(cocurrency, &_PendingRecvCall);
#endif
		return true;
	}

	void RemoveObject(SocketObject* obj)
	{	
#if defined(PLATFORM_WIN)
		obj->_Shutdown();
#endif
		_RemoveObject(obj->GetHandle());
	}
};
/** @}*/

} // namespace inet
/** @}*/