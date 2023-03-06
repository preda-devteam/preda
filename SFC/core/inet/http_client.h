#pragma once
/**
 * @file http_client.h
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
#include "../../core/ext/botan/botan.h"

namespace inet
{
/** \defgroup http_client http_client
 * @ingroup inet
 *  @{
 */
class UrlEncoding
{
    rt::String	_encoded;
public:
    UrlEncoding(const rt::String_Ref& url_before_encoding);
    operator const rt::String&(){ return _encoded; }
};
//////////////////////////////////////////////
// HTTP client
/**
 * @brief values provided in msg of FUNC_EVENT_CALLBACK, return 0 for cancel
 * 
 */
enum	
{	
    HTTPCLIENT_EVENT_NONE = 0,
    HTTPCLIENT_EVENT_URL_PARSED = 1,		///< (LPCSTR)param is url with "http://" removed
    HTTPCLIENT_EVENT_DNS_RESOLVED,
    HTTPCLIENT_EVENT_CONNECTED,				///< (LPCSTR)param is the server name
    HTTPCLIENT_EVENT_TLS_CONNECTED,			///< (LPCSTR)param is the server name

    HTTPCLIENT_EVENT_START_RECEIVING,		///< WaitResponse being called
    HTTPCLIENT_EVENT_FIRSTBYTE,				///< first byte received after connected
    HTTPCLIENT_EVENT_HEADER_RECEIVED,		///< (ResponseHeader*)param is the parsed header
    HTTPCLIENT_EVENT_CONTENT_RECEIVING,		///< (int)param is bytes received so far
    HTTPCLIENT_EVENT_PROTOCAL_ERROR,		///< error in HTTP protocol
    HTTPCLIENT_EVENT_DONE,					///< (int)param is the length of content downloaded

    HTTPCLIENT_EVENT_TIMEOUT,				///< this one will not be recorded in m_LastResponseStage
    HTTPCLIENT_EVENT_CANCELLED,

    HTTPCLIENT_EVENT_REDIRECT = 100			///< (LPCSTR)param is the target url (Issued by HttpNavigator only)
};

class HttpSession
{
    sec::TLS			_SecureConn;
    SocketTimed			_TcpConn;
    bool				_Send(LPCVOID pData, UINT len);
    bool				_Recv(LPVOID pData, UINT len, UINT& len_out);

    static const int RECV_BUFFER_EXTSIZE = 2048;
    friend class HttpNavigator;
    rt::String			_CommonFields;
    rt::String			_SendBuffer;
	rt::String			_RequestHeader;
    rt::Buffer<char>	_RecvBufferPool;
    CHAR&				_RecvBuffer(UINT i=0){ ASSERT(i >= _RecvBuffer_Removed); return *(_RecvBufferPool.Begin() + i - _RecvBuffer_Removed); }
    UINT				_GetRecvBufferSize() const { return (UINT)(_RecvBufferPool.GetSize() + _RecvBuffer_Removed); }
    bool				_ChangeRecvBufferSize(UINT sz);
    UINT				_RecvBuffer_Used;
    UINT				_RecvBuffer_Parsed;
    UINT				_RecvBuffer_Removed;
    UINT				_RecvUntil(LPCSTR end_token, bool remove_parsed = false);  ///< return the index of first token character in _RecvBuffer
    bool				_RecvUntilClose();
    bool				_RecvUpTo(UINT size_byte);  ///< fill _RecvBuffer up to size_byte bytes, make size_byte == _RecvBuffer_Used
    UINT				_RecvOneChunk();  ///< return the size of the chunk, or INFINITE for error, 0 for end
    UINT				_ResponseStart;
    os::TickCount		_Timing;
    int					_Timeout;

public:
    DWORD				m_Timing_DNS;
    DWORD				m_Timing_Connection;
    DWORD				m_Timing_Wait;
    DWORD				m_Timing_Transmission;

public:
    typedef	bool (*FUNC_EVENT_CALLBACK)(LPVOID param, UINT event, LPVOID cookie);
    typedef	int (*FUNC_DATA_CALLBACK)(LPCBYTE data, UINT data_len, UINT start_pos, bool fin, LPVOID cookie);	///< return >0 to remove exiting response data from internal buffer, -1 for stopping downloading
    bool				SendRequest(LPCSTR pURL, DWORD verb = HTTP_VERB_GET, LPCSTR additional_header = nullptr, UINT additional_header_len = 0, LPCSTR optional = nullptr, UINT optional_len = 0);
    void				SetExpectedServerPublicKey(LPCVOID data = nullptr, UINT data_size = 0){ _SecureConn.SetExpectedServerPublicKey(data, data_size); }
    bool				HasCertificateError(){ return _SecureConn.HasCertificateError(); }

protected:
    rt::String			m_ServerName;
    InetAddr			m_ProxyServer;

    UINT				m_Port;
    bool				m_Keepalive;
    InetAddr			m_BindingAddress;
    FUNC_EVENT_CALLBACK	m_pEventCallback;
    FUNC_EVENT_CALLBACK	m_pEventCallbackSaved;
    LPVOID				m_pEventCallbackCookie;
    FUNC_DATA_CALLBACK	m_pDataCallback;
    LPVOID				m_pDataCallbackCookie;
    DWORD				m_LastResponseStage;

    void				RemovePartialResponse(UINT sz);		///< response header will not be removed
    bool				ProbeDataCB(bool fin = false);		///< false for cancel
    bool				RequestProxyTunnel();
    void				CloseSocket();

public:

    struct HeaderField
    {
        rt::String_Ref name;
        rt::String_Ref value;
    };

    struct ResponseHeader
    {
        UINT			m_StateCode;
        UINT			m_VersionMajor;
        UINT			m_VersionMinor;
        bool			m_ConnectPersisent;
        UINT			m_ContentLength;
        bool			m_ChunkedTransfer;
        rt::String_Ref	m_ContentCharset;
        rt::String_Ref	m_ContentType;
        rt::String_Ref	m_ContentSubtype[2];
        rt::String_Ref	m_Redirected;
        rt::String_Ref	m_SuggestedFilename;
        rt::String		m_RawHeader;
        // partial content
        UINT			m_ContentPartial_Start;
        UINT			m_ContentPartial_Total;	///< total size of the object, NOT the content would received
        rt::BufferEx<HeaderField> m_fields;

        void	ParseHeader(LPCSTR header_text);
        bool	GetHeaderField(rt::String_Ref &outValue, LPCSTR headerField) const;
        bool	IsParsedOk() const { return m_StateCode != 0xffffffff; }
        bool	IsContentLengthKnown() const { return m_ContentLength != 0xffffffff; }
        bool	IsPartialContent() const { return m_ContentPartial_Start != 0xffffffff; }
        UINT	GetStartPosition() const { return m_ContentPartial_Start != 0xffffffff?m_ContentPartial_Start:0; }
    };

public:
    ResponseHeader		m_ResponseHeader;
    enum _tagHttpVerb
    {	HTTP_VERB_GET = 0,
        HTTP_VERB_POST,
        HTTP_VERB_PROPFIND,
        HTTP_VERB_REPORT,
        HTTP_VERB_DELETE,
        HTTP_VERB_PUT,
        HTTP_VERB_MAX
    };

    HttpSession();
    ~HttpSession();
/** @name Proxy
*/
///@{
    void			SetProxy(const InetAddr& addr);	///< SetProxy(InetAddr()); to disable proxy
    bool			HasProxy() const { return m_ProxyServer.GetPort(); }
    auto&			GetProxy() const { return m_ProxyServer; }
	auto&			GetResponseParsedHeader() const { return m_ResponseHeader; }
///@}
/** @name Request
*/
///@{
    void			SetItemEventCallback(FUNC_EVENT_CALLBACK cb, LPVOID cookie){ m_pEventCallbackSaved = cb; m_pEventCallbackCookie = cookie; }
    bool			Request_Get(LPCSTR pURL, LPCSTR additional_header = nullptr, UINT additional_header_len = 0);	///< no automatic redirection (3xx) handling
    bool			Request_Post(LPCSTR pURL, LPCBYTE data, UINT sz=0, LPCSTR data_type = "text/plain", LPCSTR charset = "utf-8", bool keep_alive = true);
    bool			Request_PostFile(LPCSTR pURL, LPCBYTE data, UINT sz, LPCSTR local_filename, bool keep_alive = true); // as multipart/form-data
   
    struct DataBuf
    {	LPCVOID Data;
        UINT	Length;	
    };
    bool			Request_Post(LPCSTR pURL, const DataBuf* pBufs, UINT BufCount, LPCSTR data_type = "text/plain", LPCSTR charset = "utf-8", bool keep_alive = true);
     bool			Request_Post(LPCSTR pURL, const DataBuf* pBufs, UINT BufCount, LPCSTR data_type = "text/plain", LPCSTR charset = "utf-8",  LPCSTR additional_header = nullptr, UINT additional_header_len = 0, bool keep_alive = true);

///@}
    void			SetDataCallback(FUNC_DATA_CALLBACK cb, LPVOID cookie){ m_pDataCallback = cb; m_pDataCallbackCookie = cookie; }
    bool			Request_GetPartial(LPCSTR pURL, int start, int length = -1, LPCSTR additional_header = nullptr, UINT additional_header_len = 0);
/** @name BindingAddress
*/
///@{
    bool			SetBindingAddress(LPCSTR dotted_ip);	///< return false if the address is not available
    bool			SetBindingAddress(const InetAddr& addr);
///@}
/** @name Response
*/
///@{
    bool			WaitResponse();
    rt::String_Ref	GetResponseAsString(){ return rt::String_Ref((LPCSTR)GetResponse(), GetResponseLength()); }
    LPBYTE			GetResponse();	///< the remaining response if some data has been removed by FUNC_DATA_CALLBACK
    UINT			GetResponseLength() const; ///< the remaining length of the response if some data has been removed by FUNC_DATA_CALLBACK
    UINT			GetResponseLengthTotal() const; ///< the total length of the response regardless data has been removed or not
    LPCSTR			GetResponseHeader(){ return &_RecvBuffer(); }
    UINT			GetResponseHeaderLength();
    void			SetCommonHeaders(LPCSTR agent, bool keepalive = false);
    DWORD			GetLastServerEvent() const { return m_LastResponseStage; }
    UINT			GetInternalBufferSize() const { return (UINT)_RecvBufferPool.GetSize(); }
	rt::String_Ref	GetRequestHeader() { return _RequestHeader; }
///@}
    void			CancelResponseWaiting(); ///< supposed to be called from other thread
    void			ResetConnection();

    void			SetHangingTimeout(DWORD msec){ _TcpConn.SetTimeout(msec); }	///< limit the maximum time of server not responding
    void			SetResponseTimeout(DWORD msec){ _Timeout = msec; }				///< limit the total time of fulfilling the request 

    static bool		ResolveRelativeURL(rt::String& out, const rt::String_Ref& tobe_resolved, const rt::String_Ref& refer);
    static bool		IsCompleteURL(const rt::String_Ref& url); ///< no component missing, no relative path
};

class HttpRequestAsync
{
    os::Thread	_thread;
    HttpSession	_http;
public:
    HttpRequestAsync(LPCSTR url = nullptr);
    ~HttpRequestAsync();
    bool Request(LPCSTR url);
    void Wait(DWORD timeout = INFINITE);
    rt::String_Ref GetResponse();
    DWORD		   GetHttpStatus() const;
};

/**
 * @brief HTTP Downloadable content
 * 
 * 1. HTTP 3xx redirection with Location
 * 2. resuming downloading if possible (HTTP Range Content)
 */
enum
{	HTTP_DLC_EMPTY = 0,
    HTTP_DLC_STARTING,
    HTTP_DLC_DOWNLOADING,
    HTTP_DLC_INACTIVED,
    HTTP_DLC_STOPPED,
    HTTP_DLC_DONE,

    HTTP_DLC_ERROR = 100,
    HTTP_DLC_ERROR_FILEOPEN,
    HTTP_DLC_ERROR_SERVERCONNECT,
    HTTP_DLC_ERROR_SERVEROPEN,
    HTTP_DLC_ERROR_FILEIO,
};

class HttpDownloader
{
    static const int DOWNLOAD_BUFFER_SIZE = 128*1024;
    static const int REDIRECTION_COUNT_MAX = 16;

    HttpSession		_Http;
    os::Thread		_Worker;
    DWORD			_WorkerState;
    bool			_WantStop;
    int				_OnDataReceived(LPCBYTE data, UINT data_len, UINT start_pos, bool fin);

    float			_BPS;
    UINT			_DownloadedSize;
    UINT			_ReceivedSize;
    os::TickCount	_DownloadTimer;
    bool			_bExpectPartialData;

protected:
    rt::String		_URL_Resolved;
    rt::String		_URL;
    rt::String		_Cookie;
    rt::String		_Filename;
    rt::String		_AddtionalHeader;
    bool			_TryToResume;
    void			_WorkingThread();
    os::Event		_Wakeup;
    os::File		_File;
    
public:
    HttpDownloader();
    ~HttpDownloader();
    void	SetHangingTimeout(DWORD msec){ _Http.SetHangingTimeout(msec); }
    void	SetResponseTimeout(DWORD msec){ _Http.SetResponseTimeout(msec); }
    void	SetItemEventCallback(HttpSession::FUNC_EVENT_CALLBACK cb, LPVOID cookie){ _Http.SetItemEventCallback(cb, cookie); }
	void	SetTask(LPCSTR url, LPCSTR filepath, LPCSTR cookie = nullptr, bool resume = true);
	void	SetProxy(LPCSTR url);
	void	SetAddtionalHeader(LPCSTR header, UINT header_len) { _AddtionalHeader = header; }
    void	Start(bool async = false);
    void	Stop(bool async = false);
    DWORD	GetState() const { return _WorkerState; }
    void	WaitForFinish() const;
    bool	IsDownloading() const;

    float	GetBandwidth() const;
    UINT	GetProgress() const;	///< 10x precentage
    UINT	GetTotalSize() const;
    UINT	GetDownloadedSize() const;
};


//////////////////////////////////////////////////////////
// What has been handled:
// 1. HTTP 3xx redirection with Location
// 2. HTML http-equiv="refresh" redirection
//
/**
 * @brief a simple web navigator with redirection and cookie
 */
class HttpNavigator	
{
    HttpNavigator(const HttpNavigator& x);
    rt::BufferEx<HttpSession::HeaderField>	_AdditionalHeaders;
    //rt::String				_AdditionalHeader;
    //rt::String				_Refer;
    //void						_UpdateAdditionalHeader();
    void						_ComposeAddtionalHeaderString(rt::String &outString);

protected:
    rt::String			_NavigatedDestination;
    HttpSession			_HttpSession;

protected:
    void				SetRedirected(const rt::String_Ref& url);

public:
    void				SetHangingTimeout(DWORD msec){ _HttpSession.SetHangingTimeout(msec); }		///< limit the maximum time of server not responding
    void				SetResponseTimeout(DWORD msec){ _HttpSession.SetResponseTimeout(msec); }	///< limit the total time of fulfilling the request 
    void				CancelResponseWaiting(){ _HttpSession.CancelResponseWaiting(); }
    // automatic redirection (3xx) handling, cookie storage
    bool				NavigateTo(LPCSTR pURL, int max_redirection_times = 8, const char *pPostData = nullptr, int postDataLen = 0, HttpSession::_tagHttpVerb customVerb_for_post = HttpSession::HTTP_VERB_POST, bool bWaitResponse = true);
    rt::String_Ref		GetNavigateDestination() const { return _NavigatedDestination; };	///< final redirected URL
    HttpNavigator(){}

public:
    LPBYTE				GetResponse(){ return _HttpSession.GetResponse(); }
    HttpSession&		GetHttpSession() { return _HttpSession; }
    UINT				GetResponseLength(){ return _HttpSession.GetResponseLength(); }
    rt::String_Ref		GetDocument(){ return rt::String_Ref((LPCSTR)GetResponse(),GetResponseLength()); }
 
    bool	SetBindingAddress(LPCSTR dotted_ip);
    bool	SetBindingAddress(const InetAddr& addr);

    void	SetProxy(const InetAddr& addr) { _HttpSession.SetProxy(addr); }     ///< SetProxy(inet::InetAddr()); to disable proxy
    bool	HasProxy() const { return _HttpSession.HasProxy(); }

    void	SetCommonHeaders(LPCSTR agent, bool keepalive = false){ _HttpSession.SetCommonHeaders(agent,keepalive); }
    void	SetReferer(LPCSTR referer);
    void	AddAdditionalHeader(LPCSTR key, LPCSTR value);
    void	SetItemEventCallback(HttpSession::FUNC_EVENT_CALLBACK cb, LPVOID cookie){ _HttpSession.SetItemEventCallback(cb, cookie); }
        
    LPCSTR	GetResponseHeader(){ return _HttpSession.GetResponseHeader(); }
    UINT	GetResponseHeaderLength(){ return _HttpSession.GetResponseHeaderLength(); }
    UINT	GetResponseStatusCode(){ return _HttpSession.GetResponseParsedHeader().m_StateCode; }
    bool	IsResponseSuccess() const { return _HttpSession.GetResponseParsedHeader().m_StateCode/100 == 2; }
    const HttpSession::ResponseHeader& GetResponseParsedHeader() const {return _HttpSession.GetResponseParsedHeader();}
};
/** @}*/
} // namespace inet
/** @}*/