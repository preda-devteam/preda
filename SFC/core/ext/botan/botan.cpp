#pragma warning(disable:4267)
#pragma warning(disable:4244)
#pragma warning(disable:4297)
#pragma warning(disable:4996)
#pragma warning(disable:4250)
#pragma warning(disable:4146)
#pragma warning(disable:4334)

#include "botan.h"

#if defined(PLATFORM_WIN)
	#ifdef PLATFORM_64BIT
		#include "./platforms/win_x64/botan_all.cpp"
	#else
		#include "./platforms/win_x86/botan_all.cpp"
	#endif
#elif defined(PLATFORM_ANDROID)
	#if defined (__mips__)
		#include "./platforms/botan_ndk_mips.cpp"
	#elif defined (__arm__)
		#include "./platforms/android_arm/botan_all.cpp"
	#elif defined (__aarch64__)
		#include "./platforms/android_arm64/botan_all.cpp"
		#include "./platforms/android_arm64/openssl_crypto.cpp"
	#elif defined (__i386__)
		#include "./platforms/botan_ndk_x86.cpp"
	#else
		#error unknown andriod platform
	#endif
#elif defined(PLATFORM_MAC)
	#ifdef PLATFORM_64BIT
        #include "./platforms/mac_x64/botan_all.cpp"
	#else
        #error 32-bit is not supported on MacOS
    #endif
#elif defined(PLATFORM_IOS)
    #ifdef PLATFORM_64BIT
        #include "./platforms/ios_arm64/botan_all.cpp"
    #else
        #error 32-bit is not supported on iOS
    #endif
#elif defined(PLATFORM_LINUX)	
	#ifdef PLATFORM_64BIT
		#include "./platforms/linux_x64/botan_all.cpp"
	#else
		#include "./platforms/linux_x86/botan_all.cpp"
	#endif
#else
	#error unknown platform
#endif


namespace sec
{

struct HttpsPolicy: public Botan::TLS::Policy
{
	std::vector<std::string> allowed_key_exchange_methods() const override
	{
		std::vector<std::string> ke = Botan::TLS::Policy::allowed_key_exchange_methods();
		ke.push_back("RSA");
		return ke;
	}
};

Botan::TLS::Session_Manager_Noop	g_TlsSessionManager;
Botan::Credentials_Manager			g_TlsCredentialsManager;
HttpsPolicy							g_TlsPolicy;

TLS::TLS(TLS_SocketRecv_CB recv_cb, TLS_SocketSend_CB send_cb, LPVOID cookie)
{
	_RecvCB = recv_cb;
	_SendCB = send_cb;
	_CB_Cookie = cookie;
	_Init = false;
	_NoErrorOccurred = true;
	_CertificateError = false;
	__RecvAteSize = 0;
}

TLS::~TLS()
{
	Destroy();
}

void TLS::tls_emit_data(const uint8_t data[], size_t size)
{
	if(_NoErrorOccurred)
		_NoErrorOccurred = _SendCB(data, (UINT)size, _CB_Cookie);
}

void TLS::tls_record_received(Botan::u64bit seq_no, const uint8_t data[], size_t size)
{
	if(_NoErrorOccurred)
		__RecvBuf.push_back(data, size);
}

bool TLS::tls_session_established(const Botan::TLS::Session& session)
{
	return false;
}

void TLS::tls_verify_cert_chain(	const std::vector<Botan::X509_Certificate>& cert_chain,
									const std::vector<std::shared_ptr<const Botan::OCSP::Response>>& ocsp_responses,
									const std::vector<Botan::Certificate_Store*>& trusted_roots,
									Botan::Usage_Type usage,
									const std::string& hostname,
									const Botan::TLS::Policy& policy
)
{	
	if(_ExpectedPubKey.GetSize())
	{
		rt::Buffer_Ref<BYTE> pk(cert_chain[cert_chain.size()-1].subject_public_key_bits().data(), cert_chain[cert_chain.size()-1].subject_public_key_bits().size());
		if(_ExpectedPubKey != pk)
		{	_NoErrorOccurred = false;
			_CertificateError = true;
		}
	}
}


bool TLS::Recv(LPVOID buf, UINT buf_size, UINT&read)
{
	ASSERT(_Init);

	if(__RecvBuf.GetSize())
	{
		read = rt::min(buf_size, (UINT)(__RecvBuf.GetSize() - __RecvAteSize));
		memcpy(buf, &__RecvBuf[__RecvAteSize], read);
		__RecvAteSize += read;
		if(__RecvAteSize == __RecvBuf.GetSize())
		{	__RecvBuf.ShrinkSize(0);
			__RecvAteSize = 0;
		}
		return true;
	}
	
	BYTE recv_buf[2048];

	while(__RecvBuf.GetSize() == 0)
	{
		UINT recv_size = 0;
		if(!_RecvCB(recv_buf, sizeof(recv_buf), recv_size, _CB_Cookie))
			return _NoErrorOccurred = false;

		try
		{	((Botan::TLS::Client*)_BotanTLSObject)->received_data((Botan::byte*)recv_buf, recv_size);
		}
		catch(...){ return false; }
	}

	VERIFY(Recv(buf, buf_size, read));
	return true;
}


bool TLS::Send(LPCVOID buf, UINT buf_size)
{
	ASSERT(_Init);
	if(_NoErrorOccurred)
	{	try
		{	((Botan::TLS::Client*)_BotanTLSObject)->send((const Botan::byte*)buf, buf_size);
		}
		catch(...){ return false; }
	}
	return _NoErrorOccurred;
}

void TLS::SetExpectedServerPublicKey(LPCVOID data, UINT data_size)
{
	_ExpectedPubKey.SetSize(data_size);
	if(data_size)
		_ExpectedPubKey.CopyFrom((LPCBYTE)data);
}

bool TLS::Create(const rt::String_Ref& hostname)
{
	ASSERT(_Init == false);

	_NoErrorOccurred = true;
	_CertificateError = false;

	try
	{
		new (_BotanRngObject)Botan::AutoSeeded_RNG();
		new (_BotanTLSObject)Botan::TLS::Client(*this, 
												g_TlsSessionManager, 
												g_TlsCredentialsManager, 
												g_TlsPolicy, 
												*((Botan::AutoSeeded_RNG*)_BotanRngObject),
												Botan::TLS::Server_Information(ALLOCA_C_STRING(hostname)));
		
		_Init = true;

		// Start hand-shaking
		{	BYTE recv_buf[2048];
			UINT recv_size = 0;

			try
			{	
				for(;;)
				{
					if(!_RecvCB(recv_buf, sizeof(recv_buf), recv_size, _CB_Cookie))
						return _NoErrorOccurred = false;

					if(	((Botan::TLS::Client*)_BotanTLSObject)->received_data((Botan::byte*)recv_buf, recv_size) == 0 &&
						((Botan::TLS::Client*)_BotanTLSObject)->is_active()
					)break;
				}
			}
			catch(...){ return false; }
		}

		return true;
	}
	catch(Botan::Stream_IO_Error &e)
	{
#if defined PLATFORM_ANDROID
#else
		if(strstr(e.what(), "Server certificate is not valid") != nullptr)
#endif
			_CertificateError = true;
	}
	catch(...){}

	return false;
}

void TLS::Destroy()
{
	if(_Init)
	{	try
		{	((Botan::TLS::Client*)_BotanTLSObject)->~Client();
			((Botan::AutoSeeded_RNG*)_BotanRngObject)->~AutoSeeded_RNG();
		}
		catch(...){}
		_Init = false;
		__RecvBuf.ShrinkSize(0);
		__RecvAteSize = 0;
	}
}
} // namespace sec
