#include "rocksdb_serving.h"
#include "../../rt/json.h"


namespace ext
{

void RocksDBServe::RocksMap(RocksDB* pDB, const rt::String_Ref& L1_path, KeyFormat key_format, LPCSTR mime)
{
	auto* handle = _New(RocksDBHandler(pDB));
	handle->L1_Path = L1_path;
	handle->Mime = mime;
	handle->KeyDisplayFormat = key_format;
	handle->SetEndPoint(handle->L1_Path);
	AddEndpoint(handle);

	_Endpoints.push_back(handle);
}

RocksDBServe::~RocksDBServe()
{
	Stop();

	for(UINT i=0; i<_Endpoints.GetSize(); i++)
	{
		_SafeDel(_Endpoints[i]);
	}
}

rt::String_Ref RocksDBServe::RocksDBHandler::GetKey(inet::HttpResponse& resp, const rt::String_Ref& varname, rt::String& ws)
{
	switch(KeyDisplayFormat)
	{
	case ext::RocksDBServe::KF_STRING:
		return resp.GetQueryParam(varname);
	case ext::RocksDBServe::KF_BIN_BASE64:
		os::Base64Decode(resp.GetQueryParam(varname), ws);
		return ws;
	case ext::RocksDBServe::KF_BIN_BASE16:
		os::Base16Decode(resp.GetQueryParam(varname), ws);
		return ws;
	default:
		ASSERT(0);
		return nullptr;
	}
}

void RocksDBServe::RocksDBHandler::SendKey(inet::HttpResponse& resp, const rt::String_Ref& key, rt::String& ws)
{
	switch(KeyDisplayFormat)
	{
	case ext::RocksDBServe::KF_STRING:
		resp.SendChuncked(key);
		break;
	case ext::RocksDBServe::KF_BIN_BASE64:
		os::Base64Encode(key, ws);
		resp.SendChuncked(ws);
		break;
	case ext::RocksDBServe::KF_BIN_BASE16:
		os::Base16Encode(key, ws);
		resp.SendChuncked(ws);
		break;
	}
}

bool RocksDBServe::RocksDBHandler::OnRequestList(inet::HttpResponse& resp, bool no_val)
{
	thread_local rt::String bk,be;
	rt::String_Ref k = GetKey(resp, "begin", bk);
	rt::String_Ref e = GetKey(resp, "end", be);

	int n = resp.GetQueryParam<int>(rt::SS("count"), rt::TypeTraits<int>::MaxVal());

	resp.SendChuncked_Begin(inet::TinyHttpd::MIME_STRING_JSON);
	resp.SendChuncked(no_val?"[":"{");
	ext::RocksCursor c = k.IsEmpty()?pDB->First():pDB->Seek(SliceValue(k));
	for(int i=0; i<n && c.IsValid(); i++)
	{
		auto key = c.Key().ToString();
		if(!e.IsEmpty() && e <= key)break;

		if(no_val)
		{
			resp.SendChuncked(i==0?"\"":",\"");
			SendKey(resp, key, bk);
			resp.SendChuncked("\"");
		}
		else
		{
			resp.SendChuncked(i==0?"\"":",\"");
			SendKey(resp, key, bk);
			resp.SendChuncked("\":");

			auto v = c.Value().ToString();

			if(v[0] == '{' || v[0] == '[')
			{
				resp.SendChuncked(v);
			}
			else
			{	resp.SendChuncked("\"");
				resp.SendChuncked(rt::JsonEscapeString(v));
				resp.SendChuncked("\"");
			}
		}

		c.Next();
	}
	resp.SendChuncked(no_val?"]":"}");
	resp.SendChuncked_End();

	return true;
}

bool RocksDBServe::RocksDBHandler::OnRequest(inet::HttpResponse& resp)
{
	static const rt::CharacterSet keycheck("\" {}':");

	if(pDB == nullptr || pDB->IsEmpty())
	{
		resp.SendHttpError(503);
		return true;
	}

	thread_local std::string  val;
	thread_local rt::String ws;
	rt::String_Ref q = resp.GetLnPath(this);

	if(resp.Body.IsEmpty())
	{
		
		if(q == rt::SS("/get"))
		{
			rt::String_Ref k = GetKey(resp, "key", ws);

			if(k.IsEmpty())return false;
			if(k.FindCharacter(keycheck)>=0)return false;

			if(pDB->Get(k, val))
			{	resp.Send(val.c_str(), (int)val.size(), Mime);
			}
			else
			{	resp.SendHttpError(inet::HTTP_NOT_FOUND);
			}

			return true;
		}
		else if(q == rt::SS("/set"))
		{
			rt::String_Ref k = GetKey(resp, "key", ws);

			rt::String_Ref v = resp.GetQueryParam(rt::SS("val")).TrimSpace();
			if(k.IsEmpty())return false;
			if(k.FindCharacter(keycheck)>=0)return false;

			if(pDB->Set(k, v))
			{	resp.Send("true", 4, inet::TinyHttpd::MIME_STRING_JSON);
			}
			else
			{	resp.SendHttpError(500);
			}
			
			return true;
		}
		else if(q == rt::SS("/delete"))
		{
			rt::String_Ref k = GetKey(resp, "key", ws);
			if(pDB->Has(k))
			{
				pDB->Delete(k);
				resp.Send("true", 4, inet::TinyHttpd::MIME_STRING_JSON);
			}
			else
			{	resp.SendHttpError(inet::HTTP_NOT_FOUND);
			}
		}
		else if(q == rt::SS("/list"))
		{
			return OnRequestList(resp, false);
		}
		else if(q == rt::SS("/listkey"))
		{
			return OnRequestList(resp, true);
		}
		else if(q.GetLength() < 2)
		{
			if(pDB && !pDB->IsEmpty())
			{
				resp.Send("true", 4, inet::TinyHttpd::MIME_STRING_JSON);
			}
			else
			{	resp.SendHttpError(inet::HTTP_UNAVAILABLE);
			}
			return true;
		}
		else return false;
	}
	else
	{
		if(q == rt::SS("/set"))
		{
			rt::String_Ref k = GetKey(resp, "key", ws);
			if(k.IsEmpty())return false;

			if(pDB->Set(k, resp.Body))
			{	resp.Send("true", 12, inet::TinyHttpd::MIME_STRING_JSON);
			}
			else
			{	resp.SendHttpError(500);
			}
			
			return true;
		}

		return false;
	}

	return true;
}

} // namespace rocksdb
