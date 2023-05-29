#include "http_client.h"
#pragma warning(disable:4312)

namespace inet
{

UrlEncoding::UrlEncoding(const rt::String_Ref& url_before_encoding)
{
	static const rt::CharacterSet_AlphabetDigits _url_safe;

	for(UINT i=0;i<url_before_encoding.GetLength();i++)
	{
		int c = (BYTE&)url_before_encoding[i];
		if(_url_safe.Has(c))
		{	_encoded += (char)c;
		}
		else
		{	static const char num[] = "0123456789ABCDEF";
			_encoded += '%';
			_encoded += num[(c&0xf0)>>4];
			_encoded += num[(c&0xf)];
		}
	}
}

//////////////////////////////////////////////////
// HttpSession
bool HttpSession::Request_Get(LPCSTR pURL, LPCSTR additional_header, UINT additional_header_len)
{
	return SendRequest(pURL, HTTP_VERB_GET, additional_header, additional_header_len);
}

bool HttpSession::Request_GetPartial(LPCSTR pURL, int start, int length, LPCSTR additional_header, UINT additional_header_len)
{
	ASSERT(length != 0 && length >=-1);

	char range_header[64];
	int  range_header_len = 
		 (UINT)(rt::String_Ref("Range: bytes=") + start + '-' + ((length>=0)?rt::tos::Number(length):rt::String_Ref()) + '\r' + '\n')
		 .CopyTo(range_header);

	if(additional_header_len)
	{
		LPSTR p = (LPSTR)alloca(range_header_len + additional_header_len + 1);
		memcpy(p, range_header, range_header_len);
		memcpy(p + range_header_len, additional_header, additional_header_len);
		p[range_header_len + additional_header_len] = 0;

		return SendRequest(pURL, HTTP_VERB_GET, p, range_header_len + additional_header_len);
	}
	else
	{	return SendRequest(pURL, HTTP_VERB_GET, range_header, range_header_len);
	}
}


bool HttpSession::Request_Post(LPCSTR pURL, LPCBYTE data, UINT sz, LPCSTR data_type, LPCSTR charset, bool keep_alive)
{
	DataBuf bufs = { data, sz };
	return Request_Post(pURL, &bufs, 1, data_type, charset, nullptr, 0 , keep_alive);
}

bool HttpSession::Request_Post(LPCSTR pURL, const HttpSession::DataBuf* pBufs, UINT BufCount, LPCSTR data_type, LPCSTR charset, bool keep_alive)
{
	return Request_Post(pURL, pBufs, BufCount, data_type, charset, nullptr, 0, keep_alive);
}



bool HttpSession::Request_Post(LPCSTR pURL, const HttpSession::DataBuf* pBufs, UINT BufCount, LPCSTR data_type, LPCSTR charset,  LPCSTR additional_header, UINT additional_header_len, bool keep_alive)
{
	UINT tot_len = 0;
	for (UINT i = 0; i < BufCount; i++)
		tot_len += pBufs[i].Length;
	rt::String_Ref header;
	if (additional_header_len == 0)
	{
		auto x =
			rt::SS("Content-Type: ") + data_type + rt::SS("; charset=\"") + charset + rt::SS("\"\r\n") +
			rt::SS("Content-Length: ") + tot_len + rt::SS("\r\n");
		header = ALLOCA_C_STRING(x);
	}
	else {
		auto x =
			rt::SS("Content-Type: ") + data_type + rt::SS("; charset=\"") + charset + rt::SS("\"\r\n") +
			rt::SS("Content-Length: ") + tot_len + rt::SS("\r\n") + additional_header;
		header = ALLOCA_C_STRING(x);
	}
	
	//if (SendRequest(pURL, HTTP_VERB_POST, additional_header, additional_header_len))
	if (SendRequest(pURL, HTTP_VERB_POST, header.Begin(), (UINT)header.GetLength()))
	{
		for (UINT i = 0; i < BufCount; i++)
		{
			LPCBYTE data = (LPCBYTE)pBufs[i].Data;
			UINT sz = pBufs[i].Length;

			for (; sz > 1024; sz -= 1024, data += 1024)
				if (!_Send(data, 1024))
					return false;

			if (!_Send(data, sz))return false;
		}
		return true;
	}

	return false;

}

bool HttpSession::Request_PostFile(LPCSTR pURL, LPCBYTE data, UINT sz, LPCSTR local_filename, bool keep_alive) // as multipart/form-data
{
	DataBuf bufs[3];
	
	auto x = 
		rt::SS("----WebFormBoundary\r\nContent-Disposition: form-data; name=\"file\"; filename=\"") + 
		local_filename + rt::SS("\"\r\nContent-Type: application/octet-stream\r\n\r\n");

	rt::String_Ref head = ALLOCA_C_STRING(x);

	bufs[0].Data = head.Begin();
	bufs[0].Length = (UINT)head.GetLength();

	bufs[1].Data = data;
	bufs[1].Length = sz;

	static const rt::SS tail("\r\n----WebFormBoundary--\r\n");
	bufs[2].Data = tail.Begin();
	bufs[2].Length = (UINT)tail.GetLength();

	return Request_Post(pURL, bufs, 3, "multipart/form-data; boundary=----WebFormBoundary", "utf-8", keep_alive);
}


void HttpSession::CancelResponseWaiting() // supposed to be called from other thread
{
	CloseSocket();
	if(m_pEventCallback)m_pEventCallback(NULL,HTTPCLIENT_EVENT_CANCELLED,m_pEventCallbackCookie);
}

void HttpSession::CloseSocket()
{
	_SecureConn.Destroy();
	_TcpConn.Close();
}

namespace _details
{

bool _HttpSession_TLS_SocketRecv_CB(LPVOID buf, UINT buf_size, UINT&read, LPVOID cookie)
{
	return ((HttpSession::SOCKET_TYPE*)cookie)->Recv(buf, buf_size, read) && read;
}

bool _HttpSession_TLS_SocketSend_CB(LPCVOID buf, UINT buf_size, LPVOID cookie)
{
	return ((HttpSession::SOCKET_TYPE*)cookie)->Send(buf, buf_size);
}

} // namespace _details

void HttpSession::ResetConnection()
{
	CloseSocket();
	m_ServerName.Empty();
	m_Port = 0;
}

bool HttpSession::SendRequest(LPCSTR pURL, DWORD verb, LPCSTR additional_header, UINT additional_header_len, LPCSTR optional, UINT optional_len)
{
	rt::Zero(m_ResponseHeader);

	m_pEventCallback = m_pEventCallbackSaved;
	_ResponseStart = 0;
	_RecvBuffer_Used = 0;
	_RecvBuffer_Parsed = 0;
	_RecvBuffer_Removed = 0;

	ASSERT(verb < HTTP_VERB_MAX);
	
	LPCSTR p = pURL;
	for(;*p;p++)
		if(*p>' ')break;

	bool Secure = false;

	// parse scheme, handles http only
	{	LPCSTR t = strstr(p,"://");
		if(t)
		{
			if(	(pURL<=t-4) &&
				(t[-1] == 'p' || t[-1] == 'P') &&
				(t[-2] == 't' || t[-2] == 'T') &&
				(t[-3] == 't' || t[-3] == 'T') &&
				(t[-4] == 'h' || t[-4] == 'H') 
			){}
			else if(
				(pURL<=t-5) &&
				(t[-1] == 's' || t[-1] == 'S') &&
				(t[-2] == 'p' || t[-2] == 'P') &&
				(t[-3] == 't' || t[-3] == 'T') &&
				(t[-4] == 't' || t[-4] == 'T') &&
				(t[-5] == 'h' || t[-5] == 'H') 
			)
			{	Secure = true;
			}
			else return false;
			p = t+3;
		}
	}

	m_Timing_DNS = 
	m_Timing_Connection = 
	m_Timing_Wait = 
	m_Timing_Transmission = 0;

	// parse site domain
	bool reconnect = false;
	LPCSTR	path="/";
	{	LPCSTR	host=p;
		UINT	port=Secure?443:80;
		UINT	host_len;
		LPCSTR t = strchr(p,'/');
		if(t)
		{	host_len = (UINT)(t-host);
			path=t; 
		}
		else{ host_len = (UINT)strlen(p); }

		UINT i=0;
		for(;i<host_len;i++)
			if(host[i]==':')
			{	char buf[6];
				for(UINT j=0;j<5;j++)
					if(i+j+1<host_len)buf[j] = host[i+j+1];
					else buf[j] = 0;
				buf[5] = 0;
				port = atoi(buf);
				break;
			}
		host_len = i;

		bool IsHostSame = true;
		if(m_ServerName.GetLength() != host_len)
			IsHostSame = false;
		else
			for(i=0;i<host_len;i++)
				if(m_ServerName[i] == host[i] || m_ServerName[i] == host[i] - ('a'-'A')){}
				else{ IsHostSame = false; break; }

		if(port != m_Port || m_ServerName.GetLength() != host_len || !IsHostSame || !m_Keepalive)
		{	
			m_Port = port;
			m_ServerName = rt::String_Ref(host,host_len) + ':' + m_Port;
			reconnect = !HasProxy();
		}
	}

	if(m_pEventCallback)m_pEventCallback((LPVOID)p,HTTPCLIENT_EVENT_URL_PARSED,m_pEventCallbackCookie);
	m_LastResponseStage = HTTPCLIENT_EVENT_URL_PARSED;

	_Timing.LoadCurrentTick();
	
	if(reconnect || !_TcpConn.IsConnected())
	{	
		CloseSocket();
		if(!_TcpConn.Create(m_BindingAddress))return false;

		InetAddr target = HasProxy()?m_ProxyServer:InetAddr(m_ServerName, m_Port);
		if(m_pEventCallback)m_pEventCallback(0,HTTPCLIENT_EVENT_DNS_RESOLVED,m_pEventCallbackCookie);
		m_LastResponseStage = HTTPCLIENT_EVENT_DNS_RESOLVED;

		m_Timing_DNS = _Timing.TimeLapse();

		if(!_TcpConn.ConnectTo(target))
		{
			if(_TcpConn.IsLastOperationTimeout() && m_pEventCallback)
				m_pEventCallback(NULL,HTTPCLIENT_EVENT_TIMEOUT,m_pEventCallbackCookie);
			return false;
		}

		if(m_pEventCallback)m_pEventCallback(m_ServerName.Begin(),HTTPCLIENT_EVENT_CONNECTED,m_pEventCallbackCookie);
		m_LastResponseStage = HTTPCLIENT_EVENT_CONNECTED;

        // RequestProxyTunnel for both http and https.
		if (HasProxy())
		{	// send CONNECT request first
			if (!RequestProxyTunnel())return false;
		}

		if(Secure)
		{
			if(!_SecureConn.Create(m_ServerName))
			{
				if(_TcpConn.IsLastOperationTimeout() && m_pEventCallback)
					m_pEventCallback(NULL,HTTPCLIENT_EVENT_TIMEOUT,m_pEventCallbackCookie);
				return false;
			}

			if(m_pEventCallback)m_pEventCallback(m_ServerName.Begin(),HTTPCLIENT_EVENT_TLS_CONNECTED,m_pEventCallbackCookie);
			m_LastResponseStage = HTTPCLIENT_EVENT_TLS_CONNECTED;
		}

		m_Timing_Connection = _Timing.TimeLapse() - m_Timing_DNS;
	}
	else if(m_pEventCallback)
	{
		m_pEventCallback(0,HTTPCLIENT_EVENT_DNS_RESOLVED,m_pEventCallbackCookie);
		m_pEventCallback(m_ServerName.Begin(),HTTPCLIENT_EVENT_CONNECTED,m_pEventCallbackCookie);
		m_LastResponseStage = HTTPCLIENT_EVENT_CONNECTED;
	}

	rt::String_Ref verb_header;
	if(HTTP_VERB_POST == verb)
		verb_header = rt::String_Ref("POST ",5);
	else if(HTTP_VERB_GET == verb)
		verb_header = rt::String_Ref("GET ",4);
	else if(HTTP_VERB_PROPFIND == verb)
		verb_header = rt::String_Ref("PROPFIND ",9);
	else if(HTTP_VERB_REPORT == verb)
		verb_header = rt::String_Ref("REPORT ",7);
	else if(HTTP_VERB_DELETE == verb)
		verb_header = rt::String_Ref("DELETE ",7);
	else if(HTTP_VERB_PUT == verb)
		verb_header = rt::String_Ref("PUT ",4);
	else ASSERT(0);

	rt::String_Ref host[2];
	if(m_ServerName.Split(host, 2, ':') == 2)
	{	if(	(Secure && host[1] == rt::SS("443")) || 
			(!Secure && host[1] == rt::SS("80"))
		){}
		else host[0] = m_ServerName;
	}

	_RequestHeader = verb_header + 
					rt::String_Ref(path,(UINT)strlen(path)) + 
					rt::String_Ref(" HTTP/1.1\r\n",11) + 
					rt::String_Ref("Host: ",6) + 
					host[0] +
					rt::String_Ref("\r\n",2) + 
					rt::String_Ref(additional_header, additional_header_len) + 
					_CommonFields;
	_SendBuffer = _RequestHeader + rt::String_Ref(optional, optional_len);

	//_LOG(_SendBuffer);
	return _Send(_SendBuffer,(UINT)_SendBuffer.GetLength());
}

HttpSession::HttpSession()
	:_SecureConn(_details::_HttpSession_TLS_SocketRecv_CB, _details::_HttpSession_TLS_SocketSend_CB, &_TcpConn)
{
	m_Port = 0;
	_RecvBufferPool.SetSize(16);
	_Timeout = rt::TypeTraits<int>::MaxVal();
	m_pEventCallback = nullptr;
	m_pEventCallbackSaved = nullptr;
	m_pDataCallback = nullptr;
	SetCommonHeaders(nullptr);
	m_LastResponseStage = HTTPCLIENT_EVENT_NONE;

	m_BindingAddress.SetAsAny().SetPort(0);
	m_ProxyServer.SetAsAny().SetPort(0);
}

HttpSession::~HttpSession()
{
	CloseSocket();
}


bool HttpSession::RequestProxyTunnel()
{
	//  CONNECT server.example.com:80 HTTP/1.1
	//  Host: server.example.com:80
	char buf[1024];
	int len = (int)
	(	rt::SS("CONNECT ") + m_ServerName + 
		rt::SS(" HTTP/1.1\r\nHost: ") +	m_ServerName + rt::SS("\r\n") + 
		rt::SS(	"Proxy-Connection: Keep-Alive\r\n"
				"Connection: Keep-Alive\r\n"
				"\r\n"
		)
	).CopyTo(buf);

	if(!_TcpConn.Send(buf,len))
	{
		if(_TcpConn.IsLastOperationTimeout() && m_pEventCallback)
			m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);
		return false;
	}

	int bufused = 0;
	UINT recv = 0;
	while(bufused < sizeof(buf) && _TcpConn.Recv(&buf[bufused], sizeof(buf) - bufused, recv))
	{
		if(!recv)return false;
		//if(!recv && (!_TcpConn.IsValid() || (!_TcpConn.IsConnected())))return false;
		bufused += recv;
		if(bufused>12 && *((DWORD*)&buf[bufused-4]) == 0x0a0d0a0d)
		{	// header received
			int status;
			rt::String_Ref(&buf[8], 4).ToNumber(status);
			rt::String_Ref(buf,4).MakeUpper();
			if(status/100 == 2 && *((DWORD*)buf) == 0x50545448)
				return true;
			else
			{
				if(m_pEventCallback)
					m_pEventCallback(nullptr, HTTPCLIENT_EVENT_PROTOCAL_ERROR, m_pEventCallbackCookie);
				return false;
			}
		}
	}

	if(_TcpConn.IsLastOperationTimeout() && m_pEventCallback)
		m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);

	return false;
}

bool HttpSession::_Send(LPCVOID pData, UINT len)
{
	return _SecureConn.IsCreate()?_SecureConn.Send(pData, len):_TcpConn.Send(pData, len);
}

bool HttpSession::_Recv(LPVOID pData, UINT len, UINT& len_out)
{
	return _SecureConn.IsCreate()?_SecureConn.Recv(pData, len, len_out):_TcpConn.Recv(pData, len, len_out);
}

void HttpSession::SetProxy(const InetAddr& addr)
{
	if(addr.GetPort())
	{
		if(addr != m_ProxyServer)
		{
			m_ProxyServer = addr;
			CloseSocket();
		}
	}
	else
	{
		m_ProxyServer = addr;
	}
}

void HttpSession::SetCommonHeaders(LPCSTR agent, bool keepalive)
{
	if(!agent)agent = "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.64 Safari/537.31";

	if(keepalive)
	{
		_CommonFields = rt::String_Ref("User-Agent: ") + agent + "\r\n"
						"Accept: */*\r\n"
						"Cache-Control: no-cache\r\n"
						"Proxy-Connection: Keep-Alive\r\n"
						"Connection: Keep-Alive\r\n"
						"\r\n";
	}
	else
	{
		_CommonFields = rt::String_Ref("User-Agent: ") + agent + "\r\n"
						"Accept: */*\r\n"
						"Cache-Control: no-cache\r\n"
						"Proxy-Connection: Close\r\n"
						"Connection: Close\r\n"
						"\r\n";
	}
	m_Keepalive = keepalive;
}


UINT HttpSession::_RecvOneChunk()
{
	ASSERT(_RecvBuffer_Used <= _GetRecvBufferSize());

	UINT head = _RecvBuffer_Parsed;
	UINT tail = _RecvUntil("\r\n");

	if(tail != INFINITE)
	{
		_RecvBuffer(tail) = 0;
		UINT chunk_size = 0;
		rt::String_Ref(&_RecvBuffer(head), &_RecvBuffer(tail)).MakeLower();
		if(sscanf(&_RecvBuffer(head),"%x",&chunk_size)==1)
		{
			if(chunk_size)
			{
				{	//remove chunk size tag
					UINT tag_len = tail-head+2;
					_RecvBuffer_Parsed = head;
					_RecvBuffer_Used -= tag_len;
					memmove(&_RecvBuffer(head), &_RecvBuffer(tail+2), _RecvBuffer_Used - _RecvBuffer_Parsed);
				}

				if(_RecvUpTo(_RecvBuffer_Parsed + chunk_size + 2))
				{
					memmove(&_RecvBuffer(_RecvBuffer_Parsed-2), &_RecvBuffer(_RecvBuffer_Parsed), _RecvBuffer_Used - _RecvBuffer_Parsed);
					_RecvBuffer_Parsed -= 2;
					_RecvBuffer_Used -= 2;
					if(!ProbeDataCB())return INFINITE;
					return chunk_size;
				}
				else
					return INFINITE;
			}
			else
			{
				_RecvBuffer_Parsed -= 3;
			}
		}

		ASSERT(_RecvBuffer_Used <= _GetRecvBufferSize());

		return 0;
	}
	else
	{	
		return 0;
	}
}

bool HttpSession::_ChangeRecvBufferSize(UINT sz)
{	
	sz = rt::max((int)sz - (int)_RecvBuffer_Removed, (int)_RecvBufferPool.GetSize()*2);
	bool ret = _RecvBufferPool.ChangeSize(sz);
	//_LOG("RCBUF: "<<_RecvBufferPool.GetSize()<<" Used: "<<(_RecvBuffer_Used - _RecvBuffer_Removed)<<" Parsed: "<<(_RecvBuffer_Parsed - _RecvBuffer_Removed));
	return ret;
}

UINT HttpSession::_RecvUntil(LPCSTR end_token, bool remove_parsed)
{
	ASSERT(_RecvBuffer_Used <= _GetRecvBufferSize());

	UINT token_len = (UINT)strlen(end_token);

	UINT head = 0xffffffff;
	for(;;)
	{	int remain_len = _RecvBuffer_Used - _RecvBuffer_Parsed;
		if(remain_len >= (int)token_len)
		{
			LPCSTR p = strstr(&_RecvBuffer(_RecvBuffer_Parsed),end_token);
			if(p)
			{	head = (UINT)(p-(LPCSTR)&_RecvBuffer(_RecvBuffer_Parsed)) + _RecvBuffer_Parsed;
				_RecvBuffer_Parsed = head + token_len;
				break;
			}
			else{ _RecvBuffer_Parsed = _RecvBuffer_Used-token_len+1; }
		}

		if(_GetRecvBufferSize() <= _RecvBuffer_Used+1)_ChangeRecvBufferSize(_RecvBuffer_Used + RECV_BUFFER_EXTSIZE);
		UINT recv_len = 0;

		if(_Timing.TimeLapse() > _Timeout)
		{	
			if(m_pEventCallback)
			{	m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);
				m_pEventCallback = nullptr;
			}
			return INFINITE;
		}

		if(!_Recv(&_RecvBuffer(_RecvBuffer_Used),(UINT)(_GetRecvBufferSize()-_RecvBuffer_Used-1),recv_len)
		   || recv_len == 0
		)
		{	CloseSocket();
			if(_TcpConn.IsLastOperationTimeout() && m_pEventCallback)
			{	m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);
				m_pEventCallback = nullptr;
			}
			return INFINITE;
		}
		_RecvBuffer_Used += recv_len;
		_RecvBuffer(_RecvBuffer_Used) = '\0';
	}

	ASSERT(head != INFINITE);
	if(remove_parsed)
	{	
		memmove(&_RecvBuffer(),&_RecvBuffer(head),_RecvBuffer_Used - head);
		_RecvBuffer_Used -= head;
		_RecvBuffer_Parsed -= head;
		head = 0;
	}

	ASSERT(_RecvBuffer_Used <= _GetRecvBufferSize());

	return head;
}

bool HttpSession::ProbeDataCB(bool fin)
{
	if(m_ResponseHeader.m_StateCode/100 == 2 && m_pDataCallback)
	{	
		int remove = m_pDataCallback(GetResponse(), GetResponseLength(), m_ResponseHeader.GetStartPosition() + _RecvBuffer_Removed, fin, m_pDataCallbackCookie);
		if(remove>0)RemovePartialResponse(remove);
		if(remove == -1)
		{	if(m_pEventCallback)m_pEventCallback(0, HTTPCLIENT_EVENT_CANCELLED, m_pEventCallbackCookie);
			return false;
		}
	}
	return true;
}

LPBYTE HttpSession::GetResponse()
{
	if(_RecvBuffer_Parsed > _ResponseStart)
	{
		ASSERT(_GetRecvBufferSize() >= _RecvBuffer_Parsed);
		return (LPBYTE)&_RecvBuffer(_ResponseStart + _RecvBuffer_Removed);
	}
	else
		return nullptr;
}

UINT HttpSession::GetResponseLength() const
{
	ASSERT(_RecvBuffer_Parsed >= (_ResponseStart + _RecvBuffer_Removed));
	return _RecvBuffer_Parsed - _ResponseStart - _RecvBuffer_Removed;
}

void HttpSession::RemovePartialResponse(UINT sz)
{
	ASSERT(sz <= GetResponseLength());

	if(_RecvBuffer_Used != sz)
	{	memmove(GetResponse(), GetResponse() + sz, _RecvBuffer_Used - sz - _RecvBuffer_Removed - _ResponseStart);
		_RecvBuffer_Removed += sz;
		//_LOG("Removed: "<<sz);
	}
}

UINT HttpSession::GetResponseLengthTotal() const
{
	return _RecvBuffer_Parsed - _ResponseStart;
}



bool HttpSession::_RecvUpTo(UINT size_byte)
{	
	ASSERT(_RecvBuffer_Used <= _GetRecvBufferSize());

	//if(size_byte+1>_GetRecvBufferSize())
	//	_ChangeRecvBufferSize(size_byte+1);

	while(_RecvBuffer_Used < size_byte)
	{
		UINT recv_len = 0;
		
		if(_Timing.TimeLapse() > _Timeout)
		{
			if(m_pEventCallback)
			{	m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);
				m_pEventCallback = nullptr;
			}
			return false;
		}

		if(_GetRecvBufferSize() <= _RecvBuffer_Used+1)_ChangeRecvBufferSize(_RecvBuffer_Used + RECV_BUFFER_EXTSIZE);
		if(!_Recv(&_RecvBuffer(_RecvBuffer_Used),(UINT)(_GetRecvBufferSize()-1-_RecvBuffer_Used),recv_len)
		   || recv_len == 0
		)
		{	CloseSocket();
			if(_TcpConn.IsLastOperationTimeout() && m_pEventCallback)
			{	m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);
				m_pEventCallback = nullptr;
			}
			return false; 
		}

		_RecvBuffer_Used += recv_len;
		_RecvBuffer_Parsed = rt::min(_RecvBuffer_Used, size_byte);

		m_LastResponseStage = HTTPCLIENT_EVENT_CONTENT_RECEIVING;
		if(!m_ResponseHeader.m_ChunkedTransfer)
			if(!ProbeDataCB())return false;
		if(m_pEventCallback && !m_pEventCallback((LPVOID)(SIZE_T)(_RecvBuffer_Used - _ResponseStart),HTTPCLIENT_EVENT_CONTENT_RECEIVING,m_pEventCallbackCookie))
			return false;
	}

	_RecvBuffer(_RecvBuffer_Used) = 0;
	ASSERT(_RecvBuffer_Parsed <= size_byte);
	_RecvBuffer_Parsed = size_byte;
	ASSERT(_RecvBuffer_Used <= _GetRecvBufferSize());

	return true;
}

bool HttpSession::_RecvUntilClose()
{
	ASSERT(_RecvBuffer_Used <= _GetRecvBufferSize());

	for(;;)
	{
		//if(_RecvBuffer_Used + chunk_size >= _GetRecvBufferSize())
		//	_ChangeRecvBufferSize(rt::max(SIZE_T(_RecvBuffer_Used + chunk_size),_GetRecvBufferSize()*2));

		UINT recv_len = 0;
		
		if(_Timing.TimeLapse() > _Timeout)
		{
			if(m_pEventCallback)
			{	m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);
				m_pEventCallback = nullptr;
			}
			return false;
		}

		if(_GetRecvBufferSize() <= _RecvBuffer_Used+1)_ChangeRecvBufferSize(_RecvBuffer_Used + RECV_BUFFER_EXTSIZE);
		if(!_Recv(&_RecvBuffer(_RecvBuffer_Used),(UINT)(_GetRecvBufferSize()-1-_RecvBuffer_Used),recv_len)
		   || recv_len == 0
		)
		{	CloseSocket();
			if(_TcpConn.IsLastOperationTimeout() && m_pEventCallback)
			{	m_pEventCallback(nullptr, HTTPCLIENT_EVENT_TIMEOUT, m_pEventCallbackCookie);
				m_pEventCallback = nullptr;
			}
			break;
		}

		if(recv_len)
		{	_RecvBuffer_Used += recv_len;
			_RecvBuffer_Parsed = _RecvBuffer_Used;
		}
		else
			break;

		m_LastResponseStage = HTTPCLIENT_EVENT_CONTENT_RECEIVING;
		if(!ProbeDataCB())return false;
		if(m_pEventCallback && !m_pEventCallback((LPVOID)(SIZE_T)(_RecvBuffer_Used - _ResponseStart),HTTPCLIENT_EVENT_CONTENT_RECEIVING,m_pEventCallbackCookie))
			break;
	}

	//_RecvBuffer_Parsed = _RecvBuffer_Used;
	_RecvBuffer(_RecvBuffer_Used) = 0;
	return true;
}


void HttpSession::ResponseHeader::ParseHeader(LPCSTR header_text)
{
	m_StateCode = m_VersionMajor = m_VersionMinor = m_ConnectPersisent = m_ContentLength = m_ChunkedTransfer = m_ContentPartial_Start = m_ContentPartial_Total = 0xffffffff;

	m_RawHeader = header_text;

	rt::String_Ref line;
	m_RawHeader.GetNextLine(line);

	//FILE *fp = fopen("c:/a.txt","w");
	//fprintf(fp, "%s", m_RawHeader.GetSafeString());
	//fclose(fp);

	if(3!=sscanf(line.Begin(),"HTTP/%d.%d %d",&m_VersionMajor,&m_VersionMinor,&m_StateCode))
	{
		m_StateCode = 0xffffffff;
		return;
	}

	while (m_RawHeader.GetNextLine(line))
	{
		SSIZE_T colon_pos = line.FindCharacter(':');
		if (colon_pos == -1)
			continue;
		HeaderField &field = m_fields.push_back();
		field.name = line.SubStrHead(colon_pos);
		field.name.MakeLower();
		field.value = line.SubStrTail(line.GetLength() - colon_pos - 1).TrimLeftSpace();
	}
	
	// connect
	{
		m_ConnectPersisent = false;
		rt::String_Ref value;
		if (GetHeaderField(value, "connection") && value.GetLength() > 0)
			m_ConnectPersisent = (value[0] != 'C' && value[0] != 'c');
	}

	// content length
	{
		rt::String_Ref value;
		if (GetHeaderField(value, "content-length") && value.GetLength() > 0)
		{
			LPCSTR msglen_entry = value.Begin();
			while(!isdigit(*msglen_entry))msglen_entry++;

			char numb[20];
			UINT l;
			for(l=0;l<19;l++,msglen_entry++)
				if(isdigit(*msglen_entry))
					numb[l] = *msglen_entry;
				else
					break;

			numb[l] = 0;
			m_ContentLength = atoi(numb);
		}
	}

	// chunked transfer
	{
		m_ChunkedTransfer = false;
		rt::String_Ref value;
		if (GetHeaderField(value, "transfer-encoding") && value.GetLength() > 0)
		{
			LPCSTR te_entry = value.Begin();
			while(!isalpha(*te_entry))te_entry++;
			m_ChunkedTransfer = (*te_entry == 'c') || (*te_entry == 'C');
		}
	}

	// partial content
	{
		rt::String_Ref value;
		if (GetHeaderField(value, "content-range") && value.FindString("bytes ") == 0)
		{
			LPCSTR te_entry = &value[6];
			rt::String_Ref range = rt::String_Ref(te_entry).TrimAfter('\r');
			rt::String_Ref partial[2];
			rt::String_Ref start_end[2];
			if(	range.Split(partial, 2, '/') > 0 &&
				partial[0].Split(start_end,2,'-') > 0 &&
				!start_end[0].IsEmpty()
			)
			{	start_end[0].ToNumber(m_ContentPartial_Start);
			}
			if(!partial[1].IsEmpty())
				partial[1].ToNumber(m_ContentPartial_Total);
		}
	}

	// Disposition
	m_SuggestedFilename.Empty();
	if(m_StateCode/100 == 2)
	{
		rt::String_Ref value;
		if (GetHeaderField(value, "content-disposition") && value.GetLength() > 0)
		{
			LPCSTR dispos = value.Begin();
			LPCSTR end = nullptr;
			int fn_end, fn_start;
			if(	dispos && (end = strstr(dispos, "\r\n")) &&
				(fn_start = (int)rt::String_Ref(dispos, end).FindString("filename=")) > 0 &&
				(fn_end = (int)rt::String_Ref(dispos + fn_start + 9, end).FindCharacter(';')) > 0
			)
			{	m_SuggestedFilename = rt::String_Ref(dispos + fn_start + 9, fn_end);
			}
		}
	}

	// content type
	{
		m_ContentCharset.Empty();
		m_ContentType.Empty();
		m_ContentSubtype[0].Empty();
		m_ContentSubtype[1].Empty();

		rt::String_Ref value;
		if (GetHeaderField(value, "content-type") && value.GetLength() > 0)
		{
			rt::String_Ref f[4];
			UINT co = value.Split(f,4,';');
			m_ContentType = f[0];
			m_ContentType.Split(m_ContentSubtype,2,'/');

			for(UINT i=1;i<co;i++)
			{
				if(f[i].TrimSpace().StartsWith(rt::SS("charset=")))
				{	m_ContentCharset = f[i].SubStr(9);
					m_ContentCharset.MakeLower();
					break;
				}
			}
		}
	}

	// redirection
	m_Redirected.Empty();
	if(m_StateCode/100 == 3)
	{
		rt::String_Ref value;
		if (GetHeaderField(value, "location") && value.GetLength() > 0)
		{
			LPCSTR redirect = value.Begin();
			while(*redirect ==' ')redirect++;
			LPCSTR end = redirect;
			while(*end>' ')end++;
			m_Redirected = rt::String_Ref(redirect, end);
		}
	}
}

bool HttpSession::ResponseHeader::GetHeaderField(rt::String_Ref &outValue, LPCSTR headerField) const
{
	if (!IsParsedOk())
		return false;

	rt::String fieldName = headerField;
	fieldName.MakeLower();

	for (int i = 0; i < (int)m_fields.GetSize(); i++)
		if (m_fields[i].name == fieldName)
		{
			outValue = m_fields[i].value;
			return true;
		}

	return false;
}

bool HttpSession::SetBindingAddress(LPCSTR dotted_ip)
{
    if (dotted_ip)
    {
    	m_BindingAddress.SetAddress(dotted_ip);
    }
    else
    {
        m_BindingAddress = InetAddr();
    }
	Socket _test;
	return _test.Create(m_BindingAddress);
}

bool HttpSession::SetBindingAddress(const InetAddr& addr)
{
    m_BindingAddress = addr;
	Socket _test;
	return _test.Create(m_BindingAddress);
}

bool HttpSession::WaitResponse()
{
	m_LastResponseStage = HTTPCLIENT_EVENT_START_RECEIVING;

	_ResponseStart = 0;
	_RecvBuffer_Used = 0;
	_RecvBuffer_Parsed = 0;

	if(0!=_RecvUntil("HTTP/", true))
	{
		if(m_pEventCallback)m_pEventCallback(0,HTTPCLIENT_EVENT_PROTOCAL_ERROR,m_pEventCallbackCookie);
		m_LastResponseStage = HTTPCLIENT_EVENT_PROTOCAL_ERROR;
		CloseSocket();
		return false;
	}
	m_Timing_Wait = _Timing.TimeLapse() - m_Timing_Connection - m_Timing_DNS;

	if(m_pEventCallback)m_pEventCallback(0,HTTPCLIENT_EVENT_FIRSTBYTE,m_pEventCallbackCookie);
	m_LastResponseStage = HTTPCLIENT_EVENT_FIRSTBYTE;

	UINT	header_len = _RecvUntil("\r\n\r\n");
	if(header_len==0xffffffff)
	{	
		if(m_pEventCallback)m_pEventCallback(0,HTTPCLIENT_EVENT_PROTOCAL_ERROR,m_pEventCallbackCookie);
		m_LastResponseStage = HTTPCLIENT_EVENT_PROTOCAL_ERROR;
		CloseSocket();
		return false;
	}

	header_len += 2;
	char tt = _RecvBuffer(header_len);
	_RecvBuffer(header_len) = 0;

	m_ResponseHeader.ParseHeader(_RecvBufferPool.Begin());
	if(m_pEventCallback)m_pEventCallback(&m_ResponseHeader,HTTPCLIENT_EVENT_HEADER_RECEIVED,m_pEventCallbackCookie);
	m_LastResponseStage = HTTPCLIENT_EVENT_HEADER_RECEIVED;

	_RecvBuffer(header_len) = tt;
	_ResponseStart = header_len+2;

	if(m_ResponseHeader.m_ChunkedTransfer)
	{	UINT ret;
		while((ret = _RecvOneChunk()))
			if(ret == INFINITE)
			{	CloseSocket();
				if(m_pEventCallback)m_pEventCallback(0,HTTPCLIENT_EVENT_PROTOCAL_ERROR,m_pEventCallbackCookie);
				m_LastResponseStage = HTTPCLIENT_EVENT_HEADER_RECEIVED;
				return false;
			}
	}
	else if(m_ResponseHeader.IsContentLengthKnown())
	{
		if(_RecvUpTo(header_len + 2 + m_ResponseHeader.m_ContentLength))
		{	_RecvBuffer(header_len + 2 + m_ResponseHeader.m_ContentLength) = 0;	}
		else
		{
			if(m_pEventCallback)m_pEventCallback(0,HTTPCLIENT_EVENT_PROTOCAL_ERROR,m_pEventCallbackCookie);
			m_LastResponseStage = HTTPCLIENT_EVENT_HEADER_RECEIVED;
			CloseSocket();
			return false;
		}
	}
	else if(m_ResponseHeader.m_ConnectPersisent == false)
	{	
		if(_RecvUntilClose()){}
		else
		{	if(m_pEventCallback)m_pEventCallback(0,HTTPCLIENT_EVENT_PROTOCAL_ERROR,m_pEventCallbackCookie);
			m_LastResponseStage = HTTPCLIENT_EVENT_PROTOCAL_ERROR;
			CloseSocket();
			return false;
		}
	}

	if(GetResponseLength())ProbeDataCB(true);

	m_LastResponseStage = HTTPCLIENT_EVENT_DONE;
	if(m_pEventCallback)m_pEventCallback((LPVOID)(SIZE_T)GetResponseLength(),HTTPCLIENT_EVENT_DONE,m_pEventCallbackCookie);
	if(!m_Keepalive)CloseSocket();

	m_Timing_Transmission = _Timing.TimeLapse() - m_Timing_Wait - m_Timing_Connection - m_Timing_DNS;

	return true;
}

UINT HttpSession::GetResponseHeaderLength()
{
	return _ResponseStart;
}

bool HttpSession::ResolveRelativeURL(rt::String& out, const rt::String_Ref& tobe_resolved, const rt::String_Ref& refer)
{
	rt::String_Ref _protocal, _host, _path;
	tobe_resolved.SplitURL(_protocal, _host, _path);

	rt::String_Ref p,h,pth;
	refer.SplitURL(p,h,pth);

	if(_protocal.IsEmpty())_protocal = p;
	if(_protocal.IsEmpty())_protocal = rt::SS("http");

	if(_host.IsEmpty())_host = h;
	if(_host.IsEmpty())return false;
	
	if(_path.IsEmpty()){ out = _protocal + rt::SS("://") + _host + '/'; return true; }
	if(_path[0] == '/'){ out = _protocal + rt::SS("://") + _host + _path; return true; }

	if(pth.IsEmpty())
	{	pth = rt::SS("/");
	}
	else
	{	if(pth[0] != '/')return false;
	}

	out = _host + pth.GetDirectoryName() + _path;
	out.ResolveRelativePath();
	out = _protocal + rt::SS("://") + out;

	return true;
}

bool HttpSession::IsCompleteURL(const rt::String_Ref& url)
{
	rt::String_Ref _protocal, _host, _path;
	url.SplitURL(_protocal, _host, _path);
	if(_protocal.IsEmpty() || _host.IsEmpty() || _path.IsEmpty())return false;
	return _path.FindString(rt::SS("../")) == -1;
}

HttpRequestAsync::HttpRequestAsync(LPCSTR url)
{
	Request(url);
}

HttpRequestAsync::~HttpRequestAsync()
{
	Wait();
}

bool HttpRequestAsync::Request(LPCSTR url)
{
	struct _call
	{
		static DWORD _func(LPVOID p)
		{
			((HttpRequestAsync*)p)->_http.WaitResponse();
			return 0;
		}
	};

	ASSERT(!_thread.IsRunning());
	if(_http.Request_Get(url))
	{	_thread.Create(_call::_func, this);
		return true;
	}
	else
	{	return false;
	}
}

void HttpRequestAsync::Wait(DWORD timeout)
{
	_thread.WaitForEnding(timeout);
}

rt::String_Ref HttpRequestAsync::GetResponse()
{
	return rt::String_Ref((LPCSTR)_http.GetResponse(), _http.GetResponseLength());
}

DWORD HttpRequestAsync::GetHttpStatus() const
{
	return _http.GetResponseParsedHeader().m_StateCode;
}


/////////////////////////////////////////////////////////////////////////////////////
// HttpDownloader
inet::HttpDownloader::HttpDownloader()
{
	struct _call
	{	static DWORD _func(LPVOID p)
		{	((HttpDownloader*)p)->_WorkingThread();
			return 0;
		}
	};

	_WorkerState = HTTP_DLC_EMPTY;
	_WantStop = false;
	_Wakeup.Reset();
	_Worker.Create(_call::_func, this);

	_bExpectPartialData = false;
}

inet::HttpDownloader::~HttpDownloader()
{
	_Worker.WantExit() = true;
	Stop(false);
	_Wakeup.Set();
	_Worker.WaitForEnding();
}

void inet::HttpDownloader::SetProxy(LPCSTR url)
{
	_Http.SetProxy(url);
}

void inet::HttpDownloader::SetTask(LPCSTR url, LPCSTR filepath, LPCSTR cookie, bool resume)
{
	if(url && filepath)
	{
		_WantStop = false;
		ASSERT(_WorkerState != HTTP_DLC_DOWNLOADING);

		_URL = url;
		_Cookie = cookie;
		_Filename = filepath;
		_TryToResume = resume;
	}
	else
	{	_WorkerState = HTTP_DLC_EMPTY;
	}
}

void inet::HttpDownloader::WaitForFinish() const
{
	while(IsDownloading())
		os::Sleep(250);
}

bool inet::HttpDownloader::IsDownloading() const
{
	return GetState() < HTTP_DLC_STOPPED && GetState() != 0;
}

void inet::HttpDownloader::Start(bool async)
{
	ASSERT(_WorkerState != HTTP_DLC_DOWNLOADING);

	_WantStop = false;
	_WorkerState = HTTP_DLC_STARTING;
	_Wakeup.Set();
	if(!async)	do
				{	os::Sleep(100);
				}while(_WorkerState == HTTP_DLC_STARTING);
}

void inet::HttpDownloader::Stop(bool async)
{
	_WantStop = true;
	if(!async)	do
				{	os::Sleep(100);
				}while(_WorkerState < HTTP_DLC_STOPPED && _WorkerState != 0);
}

void inet::HttpDownloader::_WorkingThread()
{
	struct _call
	{	static int _OnDataReceived(LPCBYTE data, UINT data_len, UINT start_pos, bool fin, LPVOID cookie)
		{	return ((HttpDownloader*)cookie)->_OnDataReceived(data, data_len, start_pos, fin);
		}
	};

	_Http.SetDataCallback(_call::_OnDataReceived, this);

	while(_Wakeup.WaitSignal() && !_Worker.WantExit())
	{
		_bExpectPartialData = false;
		_BPS = 0;
		_DownloadedSize = 0;
		_ReceivedSize = 0;

		_Wakeup.Reset();
		_WorkerState = HTTP_DLC_DOWNLOADING;

		// start a downloading
		int start = 0;
		if(_TryToResume)
		{	if(_File.Open(_Filename, os::File::Normal_ReadWrite, false))
			{	_File.SeekToEnd();
				start = (int)_File.GetCurrentPosition();
			}
		}
		
		if(!_File.IsOpen())_File.Open(_Filename, os::File::Normal_Write, true);
		if(!_File.IsOpen())
		{	_WorkerState = HTTP_DLC_ERROR_FILEOPEN;
			continue;
		}

		int redirection_count = 0;
		bool sopen;
		_URL_Resolved = _URL;

		rt::String header;
		header = _Cookie + _AddtionalHeader;

RETRY_DIFFERENT_CONFIG:
		sopen = start?	_Http.Request_GetPartial(_URL_Resolved, start, -1, header.Begin(), (UINT)header.GetLength()):
						_Http.Request_Get(_URL_Resolved, header.Begin(), (UINT)header.GetLength());

		_bExpectPartialData = start!=0;
		_DownloadedSize = start;
		if(sopen)
		{
			_DownloadTimer.LoadCurrentTick();

			bool ret = _Http.WaitResponse();
			int httpstatus = _Http.GetResponseParsedHeader().m_StateCode;
			if(httpstatus/100 == 2)
			{	
				_File.Close();
				if(_WorkerState == HTTP_DLC_DOWNLOADING)
					_WorkerState = ret?HTTP_DLC_DONE:HTTP_DLC_STOPPED;
			}
			else if(httpstatus == 416 && _Http.GetResponseParsedHeader().m_ContentPartial_Total == start)
			{
				_WorkerState = HTTP_DLC_DONE;
			}
			else if(httpstatus/100 == 3 && !_Http.GetResponseParsedHeader().m_Redirected.IsEmpty() && redirection_count<REDIRECTION_COUNT_MAX)
			{
				_URL_Resolved = _Http.GetResponseParsedHeader().m_Redirected;
				redirection_count++;
				goto RETRY_DIFFERENT_CONFIG;
			}
			else if(start)
			{	start = 0;
				_File.Close();
				_File.Open(_Filename, os::File::Normal_Write);
				goto RETRY_DIFFERENT_CONFIG;
			}
			else
			{	_WorkerState = HTTP_DLC_ERROR_SERVEROPEN;
				_File.Close();
				continue;
			}
		}
		else
		{	_WorkerState = HTTP_DLC_ERROR_SERVERCONNECT;
			_File.Close();
			continue;
		}
	}

	_WorkerState = rt::max((DWORD)HTTP_DLC_STOPPED, _WorkerState);
}

int inet::HttpDownloader::_OnDataReceived(LPCBYTE data, UINT data_len, UINT start_pos, bool fin)
{
	int ret = 0;
	if(data_len)
	{
		if(_bExpectPartialData && start_pos != (UINT)_File.GetCurrentPosition() && start_pos == 0)
		{	_bExpectPartialData = false;
			// Fall back to re-download
			_File.Close();
			if(!_File.Open(rt::tos::StringOnStack<1024>(_File.GetFilename()), os::File::Normal_Write))
				return -1;
		}

		ASSERT(start_pos == (UINT)_File.GetCurrentPosition());
		if(data_len >= DOWNLOAD_BUFFER_SIZE || fin)
		{	_DownloadedSize = start_pos + data_len;
			_ReceivedSize += data_len;
			os::Sleep(10);
			ret = _File.Write(data, data_len) == data_len?data_len:-1;
			if(ret == -1)_WorkerState = HTTP_DLC_ERROR_FILEIO;
		}
	}
	
	if(_WantStop)return -1;
	return ret;
}

float inet::HttpDownloader::GetBandwidth() const
{
	if(GetState() == HTTP_DLC_DOWNLOADING)
		rt::_CastToNonconst(this)->_BPS = _ReceivedSize*1000.f/(1 + _DownloadTimer.TimeLapse());
	return _BPS;
}

UINT inet::HttpDownloader::GetDownloadedSize() const
{
	return _DownloadedSize;
}

UINT inet::HttpDownloader::GetProgress() const
{
	if(_Http.GetResponseParsedHeader().m_ContentPartial_Total != 0xffffffff)
	{	
		if(_Http.GetResponseParsedHeader().m_ContentPartial_Total)
			return (UINT)(_DownloadedSize*1000LL / _Http.GetResponseParsedHeader().m_ContentPartial_Total);
	}
	else if(_Http.GetResponseParsedHeader().m_ContentLength != 0xffffffff)
	{
		if(_Http.GetResponseParsedHeader().m_ContentLength)
			return (UINT)(_DownloadedSize*1000LL / _Http.GetResponseParsedHeader().m_ContentLength);
	}
	
	return 0;
}

UINT inet::HttpDownloader::GetTotalSize() const
{
	if(_Http.GetResponseParsedHeader().m_ContentPartial_Total != 0xffffffff)
	{	
		return _Http.GetResponseParsedHeader().m_ContentPartial_Total;
	}
	else if(_Http.GetResponseParsedHeader().m_ContentLength != 0xffffffff)
	{
		return _Http.GetResponseParsedHeader().m_ContentLength;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////
// HttpNavigator
void HttpNavigator::_ComposeAddtionalHeaderString(rt::String &outString)
{
	static const rt::SS BR("\r\n");

	outString.Empty();
	for (int i = 0; i < (int)_AdditionalHeaders.GetSize(); i++)
		outString +=  _AdditionalHeaders[i].name + ": " + _AdditionalHeaders[i].value + BR;
}

void HttpNavigator::SetReferer(LPCSTR referer)
{
	AddAdditionalHeader("Referer", referer);
}

void HttpNavigator::AddAdditionalHeader(LPCSTR key, LPCSTR value)
{
	for (int i = 0; i < (int)_AdditionalHeaders.GetSize(); i++)
		if (_AdditionalHeaders[i].name == key)
		{
			_AdditionalHeaders[i].value = value;
			return;
		}

	HttpSession::HeaderField &item = _AdditionalHeaders.push_back();
	item.name = key;
	item.value = value;
}

void HttpNavigator::SetRedirected(const rt::String_Ref& url)
{
	int i = (int)url.FindCharacter(':');

	if(_NavigatedDestination.IsEmpty() || (i>0 && url[i+1] == '/' && url[i+2] == '/'))
	{
		_NavigatedDestination = url;
	}
	else
	{	
		LPSTR begin = _NavigatedDestination.Begin() + _NavigatedDestination.FindString("://") + 3;

		if(url[0] == '/')
		{
			LPSTR p = strchr(begin,'/');
			if(p)
				_NavigatedDestination = rt::String_Ref(_NavigatedDestination, p) + url;
			else
				_NavigatedDestination += url;
		}
		else
		{
			LPSTR pdir = strrchr(begin,'/');
			if(!pdir)
			{	_NavigatedDestination += '/';
				pdir = _NavigatedDestination.Begin() + (_NavigatedDestination.GetLength()-1);
			}

			LPCSTR path = url.Begin();
			for(;;)
			{	
				if(path[0] == '.' && path[1] == '/')
					path += 2;
				else if(path[0] == '.' && path[1] == '.' && path[2] == '/')
				{
					path += 3;
					LPSTR p = pdir;
					for(;p>begin;p--)
						if(*p == '/')
						{	pdir = p;
							break;
						}
				}
				else break;
			}

			_NavigatedDestination = rt::String_Ref(_NavigatedDestination, pdir + 1) + rt::String_Ref(path,url.End());
		}
	}
}

bool HttpNavigator::SetBindingAddress(LPCSTR dotted_ip)
{
    return _HttpSession.SetBindingAddress(dotted_ip);
}

bool HttpNavigator::SetBindingAddress(const inet::InetAddr& addr)
{
    return _HttpSession.SetBindingAddress(addr);
}


bool HttpNavigator::NavigateTo(LPCSTR pURL, int max_redirection_times, const char *pPostData, int postDataLen, HttpSession::_tagHttpVerb customVerb, bool bWaitResponse)
{
	static const rt::String_Ref content_type_html("text/html",9);

	if(strstr(pURL,"://"))
		_NavigatedDestination = pURL;
	else
		_NavigatedDestination = rt::String_Ref("http://",7) + pURL;

	bool bIsPost = pPostData != nullptr;

	rt::String addtionalHeaderString;
	if (bIsPost)
		AddAdditionalHeader("Content-Length", rt::tos::Number(postDataLen).Begin());
	_ComposeAddtionalHeaderString(addtionalHeaderString);

	while(	max_redirection_times >= 0 &&
			(bIsPost ?
			_HttpSession.SendRequest(_NavigatedDestination, customVerb, addtionalHeaderString, (UINT)addtionalHeaderString.GetLength(), pPostData, postDataLen)
			:
			_HttpSession.Request_Get(_NavigatedDestination, addtionalHeaderString, (UINT)addtionalHeaderString.GetLength())
			))
	{
		if (bWaitResponse)
		{
			if (!_HttpSession.WaitResponse())
				break;
		}
		else
			return true;
		max_redirection_times--;
		if(	_HttpSession.GetResponseParsedHeader().m_StateCode/100 == 3 && 
			!_HttpSession.GetResponseParsedHeader().m_Redirected.IsEmpty()
		)
		{	SetRedirected(_HttpSession.GetResponseParsedHeader().m_Redirected);
			if(_HttpSession.m_pEventCallback)
				_HttpSession.m_pEventCallback(_NavigatedDestination.Begin(),HTTPCLIENT_EVENT_REDIRECT,_HttpSession.m_pEventCallbackCookie);
		}
		else if(_HttpSession.GetResponseParsedHeader().m_StateCode/100 == 2 && 
				_HttpSession.GetResponseLength()
		)
		{	if(_HttpSession.GetResponseParsedHeader().m_ContentType == content_type_html)
			{
				// analysis HTML content
				rt::String doc = (LPSTR)_HttpSession.GetResponse();
				doc.MakeLower();
				LPSTR pdoc = doc;

				LPSTR pend = strstr(pdoc,"<body");
				if(pend)*pend = '\0';
				bool redirected = false;
			
				while(pdoc && (pdoc = strstr(pdoc,"http-equiv")))
				{
					LPSTR next = pdoc+10;
					LPSTR pclose = nullptr;
					LPSTR pUrl = nullptr;
					LPSTR pEndUrl = nullptr;

					if( (pclose = strchr(pdoc, '>')) &&
						(*pclose = '\0', true) &&
						(pdoc = strstr(pdoc+10,"refresh")) &&
						(pdoc = strstr(pdoc+8,"content")) &&
						(pdoc = strchr(pdoc+8,'"')) &&
						(pdoc = strstr(pdoc+1,"url")) &&
						(pUrl = strchr(pdoc+3,'=')) &&
						(	(pEndUrl = strchr(pUrl,'"')) ||
							(pEndUrl = strchr(pUrl,'\''))
						)
					)
					{	SIZE_T len = pEndUrl - (pUrl+1);
						SetRedirected(rt::String_Ref(((LPSTR)_HttpSession.GetResponse()) + (pUrl+1-pdoc),len));
						*pclose = '>';
						redirected = true;
						break;
					}

					if(pclose)*pclose = '>';
					pdoc = next;
				}

				if(!redirected)
				{
					LPSTR p = (LPSTR)_HttpSession.GetResponse();
					p[_HttpSession.GetResponseLength()] = '\0';

					return true;
				}
			}
			else return true;
		}
		else break;
	}

	return false;
}


} // namespace inet
