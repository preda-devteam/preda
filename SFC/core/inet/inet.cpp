#include "inet.h"
#include <string.h>
#include <ctype.h>


#ifdef PLATFORM_WIN
#include <Iphlpapi.h>
#include <Ipifcons.h>
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#else
#include <netdb.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>

#if defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
#include <sys/sockio.h>
#include <net/if_dl.h>
#if defined(PLATFORM_IOS)
#include <CoreFoundation/CoreFoundation.h>
#include <notify_keys.h>
#else
#include <sys/kern_event.h>
#endif // #if defined(PLATFORM_IOS)
#else
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <signal.h>
#endif

#endif

namespace inet
{

#ifdef PLATFORM_WIN
struct _w32_socket_init
{	
	_w32_socket_init()
	{	WORD wVersionRequested = MAKEWORD(2,2);
		WSADATA wsaData;
		WSAStartup(wVersionRequested, &wsaData);
	}
	~_w32_socket_init(){ WSACleanup(); }
};

_w32_socket_init _w32_socket_init_obj;

#else

bool IN6_ADDR_EQUAL(LPCVOID x, LPCVOID y)
{
	return ((const LONGLONG*)x)[0] == ((const LONGLONG*)y)[0]
		&& ((const LONGLONG*)x)[1] == ((const LONGLONG*)y)[1];
}

#endif

void GetHostName(rt::String& name_out)
{
	char name[1024];
	if(0 == gethostname(name, sizeof(name)))
	{	
		LPSTR end = strchr(name, '.');
		if(end)
		{	name_out = rt::String(name, end);
		}
		else
		{	name_out = name;
		}
	}
	else
	{	name_out.Empty();
	}
}

template<typename t_ADDR>
UINT GetLocalAddressT(t_ADDR* pOut, UINT OutSize, bool no_loopback, t_ADDR* broadcast_addr = nullptr, DWORD* subnet_mask = nullptr, LPCSTR interface_prefix = nullptr, rt::String* if_names = nullptr)
{
	typedef _details::InetAddrT_Op<typename t_ADDR::ADDRESS_TYPE>	OP;
	ASSERT(OutSize);
    
	UINT nextAddr = 0;
#if defined(PLATFORM_WIN)
    ASSERT(interface_prefix == nullptr); // not supported on Windows
	ASSERT(if_names == nullptr); // not supported on Windows
	if(OP::SIN_FAMILY == AF_INET)
	{	// IP v4
		ULONG buflen = sizeof(MIB_IPADDRROW)*128;
		MIB_IPADDRTABLE* ipaddrtable = (MIB_IPADDRTABLE*)_alloca(buflen);
		if(NO_ERROR == GetIpAddrTable(ipaddrtable, &buflen, false))
		{
			for(UINT i=0; i<(UINT)ipaddrtable->dwNumEntries; i++)
			{
				MIB_IPADDRROW& ipt = ipaddrtable->table[i];
				pOut[nextAddr].SetBinaryAddress(&ipt.dwAddr);
				if(	!OP::IsAddressNone(pOut[nextAddr]) &&
					!OP::IsAddressLoopback(pOut[nextAddr]) &&
					!OP::IsAddressAny(pOut[nextAddr]) &&
					!OP::IsAddressGhost(pOut[nextAddr])
				)
				{
                    if(broadcast_addr)
					{	DWORD bcast = ipt.dwAddr|~ipt.dwMask;
						broadcast_addr[nextAddr].SetBinaryAddress(&bcast);
					}
					if(subnet_mask)
					{	subnet_mask[nextAddr] = ipt.dwMask;
					}
					nextAddr++;
					if(nextAddr >= OutSize)break;
				}
			}
		}
	}
	else
	{	// AF_INET6
		ASSERT(broadcast_addr == nullptr);
		ASSERT(subnet_mask == nullptr);

		char szHostname[256];
		gethostname(szHostname, sizeof(szHostname));

		struct addrinfo aiHints;
		struct addrinfo *aiList = nullptr;
		//memset(&aiHints, 0, sizeof(aiHints));
		rt::Zero(aiHints);
		aiHints.ai_family = OP::SIN_FAMILY;
		int ret = false;
		if(0 == getaddrinfo(szHostname, NULL, &aiHints, &aiList) && aiList)
		{	
			struct addrinfo *p = aiList;
			while(p)
			{
				if(	p->ai_addrlen == sizeof(t_ADDR) &&
					!OP::IsAddressNone((t_ADDR&)*p->ai_addr) &&
					!OP::IsAddressLoopback((t_ADDR&)*p->ai_addr) &&
					!OP::IsAddressAny((t_ADDR&)*p->ai_addr) &&
					!OP::IsAddressGhost((t_ADDR&)*p->ai_addr)
				)
				{	OP::CopyAddress(OP::GetAddressPtr(pOut[nextAddr]), (t_ADDR&)*p->ai_addr);
					nextAddr++;
					if(nextAddr >= OutSize)break;
				}
				p = p->ai_next;
			}
		}
		if(aiList)freeaddrinfo(aiList);
	}
#else

    rt::String_Ref nic_prefix[64];
    int nic_prefix_co = rt::String_Ref(interface_prefix).Split(nic_prefix, sizeofArray(nic_prefix), ",;");
    int top_nic_idx = 100;

    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if(!ifa->ifa_addr)continue;
        if(ifa->ifa_addr->sa_family != OP::SIN_FAMILY)continue;
        if((ifa->ifa_flags & IFF_UP) == 0)continue;  // ignore if interface not up
/*
        if(ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
             // is a valid IP4 Address
             tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
             char addressBuffer[INET_ADDRSTRLEN];
             inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
             printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
             // is a valid IP6 Address
             tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
             char addressBuffer[INET6_ADDRSTRLEN];
             inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
             printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
*/
        int prefix_idx = -1;
        if(nic_prefix_co)
        {
            for(int i=0; i<nic_prefix_co; i++)
                if(rt::String_Ref(ifa->ifa_name).StartsWith(nic_prefix[i]))
                {   prefix_idx = i;
                    goto GET_LISTED;
                }
            
            continue;
        }
        
GET_LISTED:
        t_ADDR& addr = *(t_ADDR*)ifa->ifa_addr;
        if( !OP::IsAddressNone(addr) &&
            !OP::IsAddressLoopback(addr) &&
            !OP::IsAddressAny(addr) &&
            !OP::IsAddressGhost(addr)
        )
        {   UINT add_idx = nextAddr;
            if(prefix_idx <= top_nic_idx)  // take the last IP for a weird scenario that the real IPv6 IP of dpd_ip on iOS is the last one.
            {   // add in front if a preferred NIC found
                add_idx = 0;
                top_nic_idx = prefix_idx;
        
                pOut[nextAddr] = pOut[0];
                if(if_names)if_names[nextAddr] = if_names[0];
                if(subnet_mask)subnet_mask[nextAddr] = subnet_mask[0];
                if(broadcast_addr)broadcast_addr[nextAddr] = broadcast_addr[0];
            }
                          
            pOut[add_idx] = addr;
            if(if_names)if_names[add_idx] = ifa->ifa_name;
            if(broadcast_addr)broadcast_addr[add_idx] = *(t_ADDR*)ifa->ifa_broadaddr;
            if(subnet_mask)
            {
                ASSERT(ifa->ifa_addr->sa_family == AF_INET);
                subnet_mask[add_idx] = *(DWORD*)(ifa->ifa_netmask->sa_data+2);
            }

            nextAddr++;
            if(nextAddr >= OutSize)break;
        }
     }
     if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
#endif

	if(!no_loopback && OutSize>(UINT)nextAddr)
	{	pOut[nextAddr++].SetAsLoopback();
	}

	return nextAddr;
}

extern UINT GetLocalAddresses(InetAddrT<sockaddr_in>* pOut, UINT Size_InOut, bool no_loopback, InetAddrT<sockaddr_in>* pOut_Broadcast, DWORD* subnet_mask, LPCSTR interface_prefix, rt::String* if_names)
{
	UINT co = GetLocalAddressT<InetAddrT<sockaddr_in>>(pOut, Size_InOut, no_loopback, pOut_Broadcast, subnet_mask, interface_prefix, if_names);
	return co;
}

extern UINT GetLocalAddresses(InetAddrV6* pOut, UINT Size_InOut, bool no_loopback, InetAddrV6* pOut_Broadcast, LPCSTR interface_prefix, rt::String* if_names)
{
	UINT co = GetLocalAddressT<InetAddrV6>(pOut, Size_InOut, no_loopback, pOut_Broadcast, nullptr, interface_prefix, if_names);
	return co;
}

////////////////////////////////////////////////////////////
// Socket

int Socket::GetBindPort() const
{
	BYTE addr[sizeof(InetAddrV6)];
	socklen_t addrlen = sizeof(addr);
	if(getsockname(_hSocket, (sockaddr*)addr, &addrlen)==0)
	{
		if(((sockaddr*)addr)->sa_family == AF_INET)
			return ((InetAddr*)addr)->GetPort();
		else if(((sockaddr*)addr)->sa_family == AF_INET6)
			return ((InetAddrV6*)addr)->GetPort();
	}
	
	return 0;
}

int Socket::GetLastError()
{
#ifdef PLATFORM_WIN
	return WSAGetLastError();
#else
	return errno;
#endif
}

bool Socket::IsErrorUnrecoverable(int err)
{
#if defined(PLATFORM_WIN)
	switch(err)
	{	case WSA_INVALID_HANDLE:
		case WSA_OPERATION_ABORTED:
		case WSAEBADF:
		case WSAEACCES:
		case WSAENOTSOCK:
		case WSAENETDOWN:
		case WSAESHUTDOWN:
		case WSASYSNOTREADY:
		case WSANOTINITIALISED:
			return true;
		default: return false;
	}
#else
	return true;
#endif
}

bool Socket::IsLastErrorOpPending()
{
	int e = GetLastError();
#if defined(PLATFORM_WIN)
	return e == WSAEWOULDBLOCK || e == WSAEINPROGRESS;
#else
	return e == EINPROGRESS || e == EWOULDBLOCK;
#endif
}

bool Socket::IsLastErrorDisconnected()
{
	int e = GetLastError();
#if defined(PLATFORM_WIN)
	return e == WSAECONNABORTED || e == WSAECONNRESET;
#else
	return e == ECONNABORTED || e == ECONNRESET;
#endif
}

Socket::Socket()
{
	_hSocket = INVALID_SOCKET;
}

Socket::Socket(SOCKET s)
{
	_hSocket = s;
}

bool Socket::__Create(const struct sockaddr &BindTo, int addr_len, int nSocketType, bool reuse_addr, int AF)
{
	ASSERT(_hSocket == INVALID_SOCKET);
	_hSocket = socket(AF, nSocketType, 0);

	if(INVALID_SOCKET != _hSocket)
	{
		int on = 1;
		if(SOCK_STREAM == nSocketType)
		{	linger l = {1,0};
			VERIFY(0==::setsockopt(_hSocket,SOL_SOCKET,SO_LINGER,(char*)&l,sizeof(linger)));
#if defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
			VERIFY(0==::setsockopt(_hSocket,SOL_SOCKET,SO_NOSIGPIPE,(void *)&on, sizeof(on)));
#endif
		}
		else if(SOCK_DGRAM == nSocketType)
		{
			VERIFY(0==::setsockopt(_hSocket,SOL_SOCKET,SO_BROADCAST,(LPCSTR)&on, sizeof(on)));

#if defined(PLATFORM_WIN) // prevent 10054 error on UDP (https://stackoverflow.com/questions/34242622/windows-udp-sockets-recvfrom-fails-with-error-10054)
			#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
			BOOL bNewBehavior = FALSE;
			DWORD dwBytesReturned = 0;
			::WSAIoctl(_hSocket, SIO_UDP_CONNRESET, &bNewBehavior, sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL);
#endif
		}

		if(reuse_addr)
		{
			VERIFY(0==setsockopt(_hSocket,SOL_SOCKET,SO_REUSEADDR,(char*)&on,sizeof(on)));
			//VERIFY(0==::setsockopt(_hSocket,SOL_SOCKET,SO_REUSEPORT,(char *)&on, sizeof(on)));
		}
		
		if(0==bind(_hSocket,&BindTo,addr_len))
		{
			return true;
		}
	}
	
	_LOGC_WARNING("[NET]: Socket Creation Error = "<<GetLastError());
	Close();
	return false;
}

void Socket::Attach(SOCKET hSocket)
{
	ASSERT(_hSocket == INVALID_SOCKET);
	_hSocket = hSocket;
	ASSERT(_hSocket != INVALID_SOCKET);
}

SOCKET Socket::Detach()
{
	SOCKET s;
	s = _hSocket;
	_hSocket = INVALID_SOCKET;
	return s;
}

void Socket::Close()
{
	if(_hSocket != INVALID_SOCKET)
	{
		SOCKET tmp = _hSocket;
		_hSocket = INVALID_SOCKET;

#if !defined(PLATFORM_LINUX) && !defined(PLATFORM_ANDROID)
		int val;
		SOCKET_SIZE_T len = sizeof(val);
		if(	(getsockopt(tmp,SOL_SOCKET,SO_TYPE,(char*)&val,&len) == 0) &&
			(val == SOCK_STREAM)	// cause deadlock with RecvFrom on SOCK_DGRAM socket
		)
#endif
		{	shutdown(tmp,2);	 // SD_BOTH == 2
		}

#ifdef PLATFORM_WIN
		closesocket(tmp);
#else
		close(tmp);
#endif
	}
}

bool Socket::__GetPeerName(struct sockaddr &ConnectedTo, int addr_len) const
{
	ASSERT(_hSocket != INVALID_SOCKET);
	SOCKET_SIZE_T size = addr_len;
	return getpeername(_hSocket,&ConnectedTo,&size)==0 && (int)size == addr_len;
}

bool Socket::__GetBindName(struct sockaddr &bind, int addr_len)	const	// address of this socket
{
	ASSERT(_hSocket != INVALID_SOCKET);
	SOCKET_SIZE_T size = addr_len;
	return getsockname(_hSocket,&bind,&size)==0;
}

bool Socket::__ConnectTo(const struct sockaddr &target, int addr_len)
{
	return connect(_hSocket,&target,addr_len)==0;
}

bool Socket::IsValid() const
{
    if(INVALID_SOCKET == _hSocket)return false;

	int val;
	SOCKET_SIZE_T len = sizeof(val);
	return getsockopt(_hSocket,SOL_SOCKET,SO_TYPE,(char*)&val,&len) == 0;
}

bool Socket::IsConnected() const
{
	if(!IsValid())return false;

	InetAddrV6 peeraddr;
	SOCKET_SIZE_T size = sizeof(InetAddrV6);
	return getpeername(_hSocket,peeraddr,&size)==0;
}

bool Socket::Send(LPCVOID pData, UINT len)
{
	if(len==send(_hSocket,(const char*)pData,len,0))return true;
	if(IsLastErrorDisconnected())Close();
	return false;
}

bool Socket::__SendTo(LPCVOID pData, UINT len,const struct sockaddr &target, int addr_len)
{
	return len==sendto(_hSocket,(const char*)pData,len,0,&target,addr_len);
}

bool Socket::Recv(LPVOID pData, UINT len, UINT& len_out, bool Peek)
{
	UINT l = (UINT)recv(_hSocket,(char*)pData,len,Peek?MSG_PEEK:0);
    if(l==(UINT)SOCKET_ERROR)
    {   len_out = 0;
        return false;
    }
	len_out = l;
	return true;
}

bool Socket::__RecvFrom(LPVOID pData, UINT len, UINT& len_out, struct sockaddr &target, int addr_len, bool Peek)
{
	SOCKET_SIZE_T la = addr_len;
	int l = (int)recvfrom(_hSocket,(char*)pData,len,Peek?MSG_PEEK:0,&target,&la);
    if(l==SOCKET_ERROR)
    {   len_out = 0;
        return false;
    }
	len_out = l;
	return (int)la == addr_len;
}

bool Socket::SetBufferSize(int reserved_size, bool receiving_sending)
{
	return 0 == setsockopt(_hSocket,SOL_SOCKET,receiving_sending?SO_RCVBUF:SO_SNDBUF,(char*)&reserved_size,sizeof(int));
}

bool Socket::Listen(UINT pending_size)
{
	return 0 == listen(_hSocket,pending_size);
}
	
bool Socket::__Accept(Socket& connected_out, struct sockaddr& peer_addr, int addr_len)
{
	SOCKET_SIZE_T la = addr_len;
	SOCKET sock = accept(_hSocket,&peer_addr,&la);
	if(INVALID_SOCKET != sock)
	{
		connected_out.Attach(sock);
		return (int)la == addr_len;
	}
	else
	{
		return false;
	}
}

void Socket::EnableNonblockingIO(bool enable)
{
#if defined(PLATFORM_WIN)
	u_long flag = enable;
	ioctlsocket(_hSocket, FIONBIO, &flag);
#else
	u_long flag = enable;
	ioctl(_hSocket, FIONBIO, &flag);
#endif
}

void Socket::EnableDatagramBroadcast(bool enable)
{
#if !defined(PLATFORM_WIN)
	int option = enable;
    if(-1 == setsockopt(_hSocket, SOL_SOCKET, SO_BROADCAST, (char *)&option, sizeof(option)))
        _LOG_WARNING("[NET]: failed to enable broadcast (err:"<<strerror(errno)<<')');
#endif
}

SocketTimed::_FD::_FD(SOCKET s)
{
	FD_ZERO(&_fd);
	FD_SET(s, &_fd);
}

SocketTimed::SocketTimed()
{
	SetSendTimeout(5000);
	SetRecvTimeout(30*1000);
}


void SocketTimed::SetRecvTimeout(DWORD msec)
{
	_timeout_recv.tv_sec = msec/1000;
	_timeout_recv.tv_usec = (msec%1000)*1000;
}

void SocketTimed::SetSendTimeout(DWORD msec)
{
	_timeout_send.tv_sec = msec/1000;
	_timeout_send.tv_usec = (msec%1000)*1000;
}

bool SocketTimed::__Create(const struct sockaddr &BindTo, int addr_len, int nSocketType, bool reuse_addr, int AF)
{
	_LastSelectRet = 1;
	if(Socket::__Create(BindTo, addr_len, nSocketType, reuse_addr, AF))
	{	Socket::EnableNonblockingIO(true);
		return true;
	}
	else
		return false;
}

bool SocketTimed::__ConnectTo(const struct sockaddr &target, int addr_len)
{
	timeval timeout = _timeout_send;
	_LastSelectRet = 1;
	int ret = connect(_hSocket,&target,addr_len);
	
	return	ret == 0 ||
			(	ret < 0 &&
				IsLastErrorOpPending() &&
				(_LastSelectRet = select(1 + (int)_hSocket, NULL, _FD(_hSocket), NULL, &timeout)) == 1
			);
}

bool SocketTimed::__Accept(Socket& connected_out, struct sockaddr& peer_addr, int addr_len)
{
	timeval timeout = _timeout_recv;
	return	(_LastSelectRet = select(1 + (int)_hSocket, _FD(_hSocket), NULL, NULL, &timeout)) == 1 &&
			Socket::__Accept(connected_out, peer_addr, addr_len);
}

bool SocketTimed::Recv(LPVOID pData, UINT len, UINT& len_out, bool Peek)
{
	timeval timeout = _timeout_recv;
	ASSERT(Peek == false);
	_LastSelectRet = select(1 + (int)_hSocket, _FD(_hSocket), NULL, NULL, &timeout);
	if(_LastSelectRet == 1)
		return Socket::Recv(pData, len, len_out, false);
	else
	{
		if(GetLastError())return false;
		if(Socket::Recv(pData, len, len_out, false))return true;
		return IsLastErrorOpPending();
	}
}

bool SocketTimed::__RecvFrom(LPVOID pData, UINT len, UINT& len_out, struct sockaddr &target, int addr_len, bool Peek )
{
	timeval timeout = _timeout_recv;

	ASSERT(Peek == false);
	return	(_LastSelectRet = select(1 + (int)_hSocket, _FD(_hSocket), NULL, NULL, &timeout)) == 1 &&
			Socket::__RecvFrom(pData, len, len_out, target, addr_len, false);
}

bool SocketTimed::Send(LPCVOID pData, UINT len, bool drop_if_busy, UINT* len_sent)
{
	ASSERT(len);
	if(len_sent)*len_sent = 0;

	int ret = 0;
	LPCSTR d = (LPCSTR)pData;
	while(len>0)
	{	
		ret = (int)send(_hSocket,d,rt::min(32*1024U, len),0);
		if(ret>0)
		{	len -= ret;
			d += ret;
			if(len_sent)*len_sent += ret;
			continue;
		}

		if(!IsLastErrorOpPending())
		{
			if(IsLastErrorDisconnected())Close();
			return false;
		}
		if(drop_if_busy)return true;

		ASSERT(ret == -1);
		timeval timeout = _timeout_send;

		// wait to death
		while((_LastSelectRet = select(1 + (int)_hSocket, NULL, _FD(_hSocket), NULL, &timeout)) == 0);
		if(_LastSelectRet == 1)
			continue;
		else
			return false;
	}
	
	return true;
}

bool SocketTimed::__SendTo(LPCVOID pData, UINT len,const struct sockaddr &target, int addr_len, bool drop_if_busy)
{
	int ret = 0;
	timeval timeout;

	do
	{	timeout = _timeout_send;
		ret = (int)sendto(_hSocket,(const char*)pData,len,0,&target,addr_len);
		if(ret == (int)len)return true;
	}while(	!drop_if_busy &&
			ret < 0 &&
			IsLastErrorOpPending() &&
			(_LastSelectRet = select(1 + (int)_hSocket, NULL, _FD(_hSocket), NULL, &timeout)) == 1
		  );

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////
// SocketEvent

SocketEvent::SocketEvent(DWORD signal_type)
#if !defined(PLATFORM_WIN)
	:fd_set_read(_Sockets)
	,fd_set_write(_Sockets)
	,fd_set_exception(_Sockets)
#endif
{
#if !defined(PLATFORM_WIN)
	_FD_Max = 0;
#endif
	if(signal_type&SEVT_ReadIsReady)fd_set_read.alloc();
	if(signal_type&SEVT_WriteIsReady)fd_set_write.alloc();
	if(signal_type&SEVT_Exception)fd_set_exception.alloc();
}

void SocketEvent::my_fd_set::assign_socket(const rt::BufferEx<SOCKET>& _Sockets)
{
#if defined(PLATFORM_WIN)
	_fd_set->fd_count = (u_int)_Sockets.GetSize();
	memcpy(_fd_set->fd_array,_Sockets.Begin(),_Sockets.GetSize()*sizeof(SOCKET));
#else
	for(UINT i=0;i<_Sockets.GetSize();i++)
		FD_SET(_Sockets[i], _fd_set);
#endif
}

int SocketEvent::WaitForEvents(UINT timeout)
{
	if(GetCount() == 0)return 0;

	if(fd_set_read.is_allocated()){ fd_set_read.assign_socket(_Sockets); fd_set_read.clear_event(); }
	if(fd_set_write.is_allocated()){ fd_set_write.assign_socket(_Sockets); fd_set_write.clear_event(); }
	if(fd_set_exception.is_allocated()){ fd_set_exception.assign_socket(_Sockets); fd_set_exception.clear_event(); }

	timeval		tm;
	timeval*	ptm = 0;
	if(timeout != INFINITE)
	{	ptm = &tm;
		tm.tv_sec = timeout/1000;
		tm.tv_usec = (timeout%1000)*1000000;
	}

#if defined(PLATFORM_WIN)
	int ret = select(0, fd_set_read, fd_set_write, fd_set_exception, ptm);
#else
	int ret = select(_FD_Max+1, fd_set_read, fd_set_write, fd_set_exception, ptm);
#endif
	
	return ret;
}

void SocketEvent::Add(SOCKET s)
{
	for(UINT i=0;i<_Sockets.GetSize();i++)
		if(s == _Sockets[i])return;

	_Sockets.push_back(s);
#if !defined(PLATFORM_WIN)
	_FD_Max = rt::max(_FD_Max, s);
#endif
}

void SocketEvent::Assign(SOCKET* p, UINT co)
{
	_Sockets.SetSize(co);
	memcpy(_Sockets, p, co*sizeof(SOCKET));

#if !defined(PLATFORM_WIN)
	if(fd_set_read._fd_set)rt::Zero(fd_set_read._fd_set); // memset(fd_set_read._fd_set, 0, sizeof(fd_set));
	if(fd_set_write._fd_set)rt::Zero(fd_set_write._fd_set); // memset(fd_set_write._fd_set, 0, sizeof(fd_set));
	if(fd_set_exception._fd_set)rt::Zero(fd_set_exception._fd_set); //memset(fd_set_exception._fd_set, 0, sizeof(fd_set));
	_UpdateFDMax();
#endif
}

#if !defined(PLATFORM_WIN)
void SocketEvent::_UpdateFDMax()
{
	_FD_Max = 0;
	for(UINT i=0;i<_Sockets.GetSize();i++)
		_FD_Max = rt::max(_FD_Max, _Sockets[i]);
}
#endif

void SocketEvent::Remove(SOCKET s)
{
	for(UINT i=0;i<_Sockets.GetSize();i++)
		if(s == _Sockets[i])_Sockets.erase(i);

#if !defined(PLATFORM_WIN)
	if(fd_set_read._fd_set)FD_CLR(s, fd_set_read._fd_set);
	if(fd_set_write._fd_set)FD_CLR(s, fd_set_write._fd_set);
	if(fd_set_exception._fd_set)FD_CLR(s, fd_set_exception._fd_set);
	_UpdateFDMax();
#endif
}

void SocketEvent::RemoveAll()
{
	_Sockets.SetSize(0);
}

UINT SocketEvent::GetCount()
{
	return (UINT)_Sockets.GetSize();
}

SOCKET SocketEvent::my_fd_set::get_next_event()
{
	if(_fd_set == nullptr)return INVALID_SOCKET;

#if defined(PLATFORM_WIN)
	_last_getevent++;
	if(_last_getevent < (int)_fd_set->fd_count)
		return _fd_set->fd_array[_last_getevent];
#else
	for(;;)
	{	_last_getevent++;
		if(_last_getevent >= (int)_Sockets.GetSize())break;
		if(FD_ISSET(_Sockets[_last_getevent], _fd_set))return _Sockets[_last_getevent];
	}
#endif

	return INVALID_SOCKET;
}

namespace _details
{
#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID)
static const UINT _NetworkInterfacesReconfigClaimDown = 2500; // msec
#else
static const UINT _NetworkInterfacesReconfigClaimDown = 1500; // msec
#endif

#if defined(PLATFORM_IOS)
CFStringRef _NotifySCNetworkChange = CFSTR(kNotifySCNetworkChange);
#endif
}

NetworkInterfaces::NetworkInterfaces()
{
#if defined(PLATFORM_WIN)
	struct _call
	{	static void NETIOAPI_API_ func(PVOID CallerContext, PMIB_UNICASTIPADDRESS_ROW Row, MIB_NOTIFICATION_TYPE NotificationType)
		{
            ((NetworkInterfaces*)CallerContext)->_LastEventFired = os::Timestamp::Get();
		}
	};

	ASSERT(_CallbackHandle == INVALID_HANDLE_VALUE);
	if(NO_ERROR != ::NotifyUnicastIpAddressChange(AF_UNSPEC, _call::func, this, false, &_CallbackHandle))
		_LOG_WARNING("[NET]: NotifyIpInterfaceChange failed");
#elif defined(PLATFORM_IOS)
    struct _call
    {
        static void func(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo)
        {
            if(CFStringCompare(name, _details::_NotifySCNetworkChange, 0) == kCFCompareEqualTo)
                *((LONGLONG*)observer) = os::Timestamp::Get();
        }
    };

    CFNotificationCenterAddObserver(CFNotificationCenterGetDarwinNotifyCenter(), //center
                                        &_LastEventFired, // observer
                                        _call::func, // callback
                                        _details::_NotifySCNetworkChange, // event name
                                        NULL, // object
                                        CFNotificationSuspensionBehaviorDeliverImmediately
    );
#else
	_WaitingThread.Create(this, &NetworkInterfaces::_WaitingFunc);
#endif
}

NetworkInterfaces::~NetworkInterfaces()
{
#if defined(PLATFORM_WIN)
    if(_CallbackHandle != INVALID_HANDLE_VALUE)
        ::CancelMibChangeNotify2(_CallbackHandle);
#elif defined(PLATFORM_IOS)
    CFNotificationCenterRemoveObserver(CFNotificationCenterGetDarwinNotifyCenter(), &_LastEventFired, NULL, NULL);
#else
    auto t = _NetLinkSocket;
    _NetLinkSocket = -1;
	_WaitingThread.WantExit() = true;
    ::close(t);
#if defined(PLATFORM_LINUX)
	pthread_kill(_WaitingThread.GetId(), SIGUSR1);
#endif
    _WaitingThread.WaitForEnding();
#endif
}

#if !defined(PLATFORM_WIN) && !defined(PLATFORM_IOS)
void NetworkInterfaces::_WaitingFunc()
{
#if defined(PLATFORM_LINUX)
	struct _thread_call
	{	static void thread_exit_handler(int sig) {}	
	};

	struct sigaction actions;
	memset(&actions, 0, sizeof(actions)); 
	sigemptyset(&actions.sa_mask);
	actions.sa_flags = 0; 
	actions.sa_handler = _thread_call::thread_exit_handler;
	sigaction(SIGUSR1,&actions,NULL);
#endif
	while(!_WaitingThread.WantExit())
	{
#if defined(PLATFORM_MAC)
        _NetLinkSocket = socket(PF_SYSTEM, SOCK_RAW, SYSPROTO_EVENT);
        
        kev_request key;
        key.vendor_code = KEV_VENDOR_APPLE;
        key.kev_class = KEV_NETWORK_CLASS;
        key.kev_subclass = KEV_ANY_SUBCLASS;
        
        int code = ioctl(_NetLinkSocket, SIOCSKEVFILT, &key);
        kern_event_msg msg;
        while(_NetLinkSocket>=0)
        {
            code = recv(_NetLinkSocket, &msg, sizeof(msg), 0);
            if(code<sizeof(kern_event_msg))break;
            // check type of event
            if(msg.event_code == KEV_DL_IF_DETACHED || msg.event_code == KEV_DL_IF_ATTACHED ||
               msg.event_code == KEV_DL_LINK_OFF || msg.event_code == KEV_DL_LINK_ON ||
               msg.event_code == KEV_DL_LINK_ADDRESS_CHANGED
            )
            {  _LastEventFired = os::Timestamp::Get(); }
        }
#elif defined(PLATFORM_ANDROID) // NETLINK_ROUTE socket binding is deprecated since Android 11+
		struct ifaddrs *ifaddr, *ifa;
		if(getifaddrs(&ifaddr) == -1)
		{
			os::Sleep(2000);
			continue;
		}

		std::unordered_set<rt::String> current;
		char host[NI_MAXHOST];
		for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) 
		{
			if (ifa->ifa_addr == nullptr)
				continue;
			
			uint32_t family = ifa->ifa_addr->sa_family;
			if (family == AF_INET || family == AF_INET6)
			{
				getnameinfo(ifa->ifa_addr,
							(family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
							host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
				current.insert(host);
			}
		}

		if(_InterfaceIps != current)
		{
			_LastEventFired = os::Timestamp::Get();
			_InterfaceIps.swap(current);
		}
		
		freeifaddrs(ifaddr);
		os::Sleep(1000);
#else
		struct sockaddr_nl addr;
		rt::Zero(addr);
		addr.nl_family = AF_NETLINK;
		addr.nl_pid = getpid();
		addr.nl_groups = /*RTMGRP_LINK|*/RTMGRP_IPV4_IFADDR|RTMGRP_IPV6_IFADDR;

		_NetLinkSocket = socket(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
		if(_NetLinkSocket<-1 || bind(_NetLinkSocket,(struct sockaddr *)&addr,sizeof(addr))<0)
		{
			::close(_NetLinkSocket);
			os::Sleep(1000);
			continue;
		}

		while(_NetLinkSocket>=0)
		{
			int status;
			char buf[4096];
			struct iovec iov = { buf, sizeof buf };
			struct sockaddr_nl snl;
			struct msghdr msg = { (void*)&snl, sizeof snl, &iov, 1, NULL, 0, 0};
			struct nlmsghdr *h;

			status = recvmsg(_NetLinkSocket, &msg, 0);

			if(status < 0)
			{
				/* Socket non-blocking so bail out once we have read everything */
				if(errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)
					continue;

				break;
			}

			if(status == 0)break;

			for(h = (struct nlmsghdr *)buf; NLMSG_OK(h, (unsigned int)status); h = NLMSG_NEXT (h, status))
			{
				auto type = h->nlmsg_type;
				if(type == NLMSG_DONE || type == NLMSG_ERROR)
					break;
					
				if(type == RTM_NEWADDR || type == RTM_DELADDR)
                {
                    _LastEventFired = os::Timestamp::Get();
					break;
				}
			}
		}
#endif // #if defined(PLATFORM_MAC)
		
		os::Sleep(1000);
	}
}
#endif // #if !defined(PLATFORM_WIN) && !defined(PLATFORM_IOS)

NetworkInterfaces::ConfigState NetworkInterfaces::GetState() const
{
    if(_LastEventFired)
    {
        if(os::Timestamp::Get() - _LastEventFired > _details::_NetworkInterfacesReconfigClaimDown)
        {
            _LastEventFired = 0;
            return Reconfigured;
        }
        else return Reconfiguring;
    }
    else return Unchanged;
}

bool NetworkInterfaces::_IsIPv6AddressTrivial(LPCBYTE ipv6)
{
	if(ipv6[0] == 0xfe && (ipv6[1]&0xc0) == 0x80)return true;  // link-local, maybe multicast? https://menandmice.com/blog/ipv6-reference-multicast

	return false;
}

bool NetworkInterfaces::_IsIPv4AddressTrivial(LPCBYTE ipv4)
{
	if(ipv4[0] == 169 && ipv4[1] == 254)return true;	// link-local

	return false;
}

bool NetworkInterfaces::Populate(rt::BufferEx<NetworkInterface>& list, bool only_up, bool skip_trivial)
{
	list.ShrinkSize(0);

#if defined(PLATFORM_WIN)
	rt::Buffer<BYTE> data_buf;
	data_buf.SetSize(40960);

	ULONG outBufLen = (ULONG)data_buf.GetSize();
	DWORD gaa = GAA_FLAG_SKIP_ANYCAST|GAA_FLAG_INCLUDE_PREFIX|GAA_FLAG_SKIP_DNS_SERVER;

	auto dwRetVal = GetAdaptersAddresses(AF_UNSPEC, gaa, NULL, (IP_ADAPTER_ADDRESSES *)data_buf.Begin(), &outBufLen);
	if(dwRetVal == ERROR_BUFFER_OVERFLOW)
	{
		data_buf.SetSize(outBufLen + 1024);
		outBufLen = (ULONG)data_buf.GetSize();
		dwRetVal = GetAdaptersAddresses(AF_UNSPEC, gaa, NULL, (IP_ADAPTER_ADDRESSES *)data_buf.Begin(), &outBufLen);
	}
	if(dwRetVal != NO_ERROR)return false;

	auto* nic = (IP_ADAPTER_ADDRESSES *)data_buf.Begin();
    for(; nic; nic = nic->Next)
	{
		if(only_up && nic->OperStatus != IfOperStatusUp)continue;

		bool is_tunnel = wcsstr(nic->FriendlyName,L"6TO4") || wcsstr(nic->FriendlyName,L"4TO6") || wcsstr(nic->FriendlyName,L"Teredo") ||
						 wcsstr(nic->FriendlyName,L"isatap");

		if(skip_trivial && (is_tunnel || (nic->IfType == IF_TYPE_SOFTWARE_LOOPBACK)))continue;

		auto& itm = list.push_back();
		rt::Zero(itm);

		{	auto len = os::__UTF8(nic->FriendlyName).SubStrHead(sizeof(itm.Name)-1).CopyTo(itm.Name);
			if(len < sizeof(itm.Name)-1)
				itm.Name[len++] = ':';
			os::__UTF8(nic->Description).SubStrHead(sizeof(itm.Name)-1-len).CopyTo(&itm.Name[len]);
		}

		if(nic->ReceiveLinkSpeed != 0xffffffffffffffff && nic->ReceiveLinkSpeed != 0xffffffffffffffff)
			itm.LinkSpeed = (nic->ReceiveLinkSpeed + nic->TransmitLinkSpeed)/2;

		itm.MTU = nic->Mtu;

		switch(nic->IfType)
		{
		case IF_TYPE_SOFTWARE_LOOPBACK:	itm.Type = NITYPE_LOOPBACK; 	break;
		case IF_TYPE_IEEE80211:
		case IF_TYPE_IEEE8023AD_LAG:
		case IF_TYPE_IEEE802154:		
		case IF_TYPE_ETHERNET_CSMACD:	
		case IF_TYPE_IEEE80216_WMAN:	itm.Type = NITYPE_LAN; 		    break;
		case IF_TYPE_USB:				itm.Type = NITYPE_USB; 		    break;
		case IF_TYPE_WWANPP:			
		case IF_TYPE_WWANPP2:			itm.Type = NITYPE_CELLULAR; 	break;
		default: if(is_tunnel)itm.Type = NITYPE_TUNNEL;					break;
		}

        if(!(nic->Flags&IP_ADAPTER_NO_MULTICAST))
            itm.Type |= NITYPE_MULTICAST;

		//if(nic->TunnelType != TUNNEL_TYPE_NONE)

		if(nic->OperStatus == IfOperStatusUp)itm.Type |= NITYPE_ONLINE;
		
		// copy first address per-AF
		auto* addr = nic->FirstUnicastAddress;
		while(addr && itm.v4Count < sizeofArray(NetworkInterface::v4) && itm.v6Count < sizeofArray(NetworkInterface::v6))
		{
			if(addr->Address.lpSockaddr->sa_family == AF_INET)
			{
				auto& ip = itm.v4[itm.v4Count++];
					
				ip.Local = *(DWORD*)(((InetAddr*)addr->Address.lpSockaddr)->GetBinaryAddress());
				ConvertLengthToIpv4Mask(addr->OnLinkPrefixLength, (PULONG)&ip.SubnetMask);
				ip.Boardcast = ip.Local|~ip.SubnetMask;
			}
			else if(addr->Address.lpSockaddr->sa_family == AF_INET6)
			{
				auto* bin = ((InetAddrV6*)addr->Address.lpSockaddr)->GetBinaryAddress();
				if(!skip_trivial || ((*(WORD*)bin)& 0xc0ff ) != 0x80fe)
					rt::CopyByteTo<16>(bin, itm.v6[itm.v6Count++].Local);
			}

			addr = addr->Next;
		}
	}
#else
	struct ifaddrs * ifaps = nullptr;
	if(getifaddrs(&ifaps))return false;
	
	auto* ifap = ifaps;
	for(; ifap; ifap = ifap->ifa_next)
	{
		auto flag = ifap->ifa_flags;
        bool online = (flag&IFF_UP) &&
                      ifap->ifa_addr &&
                      (ifap->ifa_addr->sa_family == AF_INET || ifap->ifa_addr->sa_family == AF_INET6);
                      
        
		if(only_up && (flag&IFF_UP) == 0)continue;
		if(skip_trivial && (flag&IFF_LOOPBACK))continue;

		rt::String_Ref name(ifap->ifa_name);
		name = name.SubStrHead(sizeof(NetworkInterface::Name)-1);

		NetworkInterface* pitm = nullptr;
		for(UINT i=0; i<list.GetSize(); i++)
		{
			if(!pitm && memcmp(name.Begin(), list[i].Name, name.GetLength()+1) == 0)
            {	pitm = &list[i];
                break;
            }
		}
        
		if(pitm == nullptr)
		{
            UINT if_type;
			if(flag&IFF_LOOPBACK){ if_type = NITYPE_LOOPBACK; }
			else if(flag&IFF_POINTOPOINT){ if_type = NITYPE_ADHOC; }
			{
				// sadly to guess type based on interface name, which is not reliable
				if(name.StartsWith("bridge") || name.StartsWith("ap") || name.StartsWith("swlan")){ if_type = NITYPE_HOTSPOT; }
				else if(name.StartsWith("awdl") || name.StartsWith("p2p")){ if_type = NITYPE_ADHOC; }  // Apple Wireless Direct Link (AirDrop,AirPlay), can be bluetooth
				else if(name.StartsWith("llw") || name.FindString("wlan")>=0 || name.StartsWith("eth") || name.StartsWith("wlp") || name.StartsWith("en")|| name.StartsWith("em")){ if_type = NITYPE_LAN; }
				else if(name.StartsWith("XHC") || name.StartsWith("usb")){ if_type = NITYPE_USB; }
				else if(name.StartsWith("pdp_ip") || name.StartsWith("rmnet")){ if_type = NITYPE_CELLULAR; }
				else if(name.StartsWith("utun") || name.StartsWith("vpn") || name.StartsWith("tun")){ if_type = NITYPE_VPN; }
				else if(name.StartsWith("gif") || name.StartsWith("stf") || name.StartsWith("sit") || name.StartsWith("ipsec")){ if_type = NITYPE_TUNNEL; }
			}
            
            if(skip_trivial && if_type == NITYPE_TUNNEL)continue;
            
            pitm = &list.push_back();
            auto& itm = *pitm;

            rt::Zero(itm);
            name.CopyTo(itm.Name);

            itm.Type = if_type;
            if(online)itm.Type |= NITYPE_ONLINE;
            if(flag&IFF_MULTICAST)itm.Type |= NITYPE_MULTICAST;
		}
        else
        {
            if(online)pitm->Type |= NITYPE_ONLINE;
        }

        if(online)
        {
            auto& itm = *pitm;
            if(ifap->ifa_addr->sa_family == AF_INET && itm.v4Count < sizeofArray(NetworkInterface::v4)) // ipv4
            {
				auto& ip = itm.v4[itm.v4Count++];
                ip.Local = *(DWORD*)(((InetAddr*)ifap->ifa_addr)->GetBinaryAddress());
                
                if(ifap->ifa_netmask)
                    ip.SubnetMask = *(DWORD*)(((InetAddr*)ifap->ifa_netmask)->GetBinaryAddress());
                    
                if(ifap->ifa_broadaddr)
                    ip.Boardcast = *(DWORD*)(((InetAddr*)ifap->ifa_broadaddr)->GetBinaryAddress());
                else if(ifap->ifa_netmask)
                    ip.Boardcast = ip.Local|~ip.SubnetMask;
            }
            
            if(ifap->ifa_addr->sa_family == AF_INET6 && itm.v6Count < sizeofArray(NetworkInterface::v6)) // ipv6
            {       
				auto* bin = ((InetAddrV6*)ifap->ifa_addr)->GetBinaryAddress();
				if(!skip_trivial || ((*(WORD*)bin)& 0xc0ff ) != 0x80fe)
	                rt::CopyByteTo<16>(bin, itm.v6[itm.v6Count++].Local);
            }
        }
	}
	
	freeifaddrs(ifaps);
	
#endif // #if defined(PLATFORM_WIN)
	return true;
}


} // namespace inet
