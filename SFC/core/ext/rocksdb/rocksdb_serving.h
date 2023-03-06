#pragma once
/**
 * @file rocksdb_serving.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-05-08
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
/** \defgroup rocksdb rocksdb
 * @ingroup ext
 *  @{
 */
#include "rocksdb.h"
#include "../../inet/tinyhttpd.h"


namespace ext
{
	/** \defgroup rocksdb_serving rocksdb_serving
 * @ingroup rocksdb
 *  @{
 */
class RocksDB;

class RocksDBServe: public inet::TinyHttpd
{
public:
	enum KeyFormat
	{
		KF_STRING = 0,
		KF_BIN_BASE64,
		KF_BIN_BASE16,
	};

protected:
	struct RocksDBHandler:public inet::HttpHandler<RocksDBHandler>
	{
		rt::String		Mime;
		rt::String		L1_Path;
		RocksDB*		pDB;
		KeyFormat		KeyDisplayFormat;
		auto			GetKey(inet::HttpResponse& resp, const rt::String_Ref& varname, rt::String& ws) -> rt::String_Ref;
		void			SendKey(inet::HttpResponse& resp, const rt::String_Ref& key, rt::String& ws);
		bool			OnRequest(inet::HttpResponse& resp);
		bool			OnRequestList(inet::HttpResponse& resp, bool no_val);
		RocksDBHandler(RocksDB* p):pDB(p){}
	};

	ReadOptions						_ReadOpt;
	WriteOptions					_WriteOpt;
	rt::BufferEx<RocksDBHandler*>	_Endpoints;

public:
	~RocksDBServe();
	void RocksMap(RocksDB* pDB, const rt::String_Ref& L1_path, KeyFormat key_format = KF_STRING, LPCSTR mime = inet::TinyHttpd::MIME_STRING_JSON);
};
/** @}*/

} // namespace ext
/** @}*/
