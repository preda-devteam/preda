#include "crypt_misc.h"
#include "../../SFC/core/ext/botan/botan.h"
#include "../oxd_libsec.h"

namespace oxd
{

static_assert(HeavySaltedEncryptAlignmentSize == sec::Cipher<sec::CIPHER_AES256>::DataBlockSize, "HeavySaltedEncryptAlignmentSize is incorrect");

bool HeavySaltedEncrypt(const rt::String_Ref& pwd, rt::String& cipertext, const rt::String_Ref& plaintext_in, UINT order, UINT dilution_size)
{
	ASSERT(order);
	if((dilution_size%HeavySaltedEncryptAlignmentSize))return false;

	if(plaintext_in.GetLength()*2 + 16 + 16 > dilution_size)
		return false;

	rt::String plaintext;
	if(!plaintext.SetLength(dilution_size))
		return false;

	// data dilution
	{	SecuritySuite::Randomize(plaintext, dilution_size);
		UINT step = (UINT)((dilution_size - 32)/plaintext_in.GetLength());
		for(UINT i=0; i<plaintext_in.GetLength(); i++)
		{
			plaintext[dilution_size-1 - step*i] = plaintext_in[plaintext_in.GetLength()-1-i];
		}
	}
	// sign length and crc
	{	sec::Hash<sec::HASH_SHA1>().Calculate(plaintext_in.Begin(), (UINT)plaintext_in.GetLength(), &plaintext[16]);
		*((UINT*)&plaintext[16 - 12]) = (UINT)plaintext_in.GetLength();
	}

	cipertext.SetLength(dilution_size);
	sec::Cipher<sec::CIPHER_AES256>	cipher;
	// set password
	cipher.SetKey(pwd.Begin(), (UINT)pwd.GetLength());

	for(UINT i=0;i<order;i++)
	{
		cipher.EncryptBlockChained(plaintext.Begin(), cipertext.Begin(), dilution_size, i);
		rt::Swap(cipertext, plaintext);
	}

	rt::Swap(cipertext, plaintext);
	return true;
}

bool HeavySaltedDecrypt(const rt::String_Ref& pwd, rt::String& plaintext, const rt::String_Ref& cipertext_in, UINT order)
{
	ASSERT(order);

	UINT dilution_size = (UINT)cipertext_in.GetLength();
	if(dilution_size%sec::Cipher<sec::CIPHER_AES256>::DataBlockSize)return false;

	rt::String cipertext;
	if(!cipertext.SetLength(dilution_size) || !plaintext.SetLength(dilution_size))
		return false;

	sec::Cipher<sec::CIPHER_AES256>	cipher;
	cipher.SetKey(pwd.Begin(), (UINT)pwd.GetLength());

	cipher.DecryptBlockChained(cipertext_in.Begin(), plaintext, dilution_size, order - 1);

	for(UINT i=1;i<order;i++)
	{
		rt::Swap(cipertext, plaintext);
		cipher.DecryptBlockChained(cipertext.Begin(), plaintext, dilution_size, order - i - 1);
	}

	UINT len = *((UINT*)&plaintext[16 - 12]);
	if(len*2 > dilution_size - 32 || len == 0)
		return false;

	if(!cipertext.SetLength(len))
		return false;

	// condense data
	UINT step = ((dilution_size - 32)/len);
	if(step == 0)return false;

	for(UINT i=0; i<len; i++)
	{
		cipertext[len-1-i] = plaintext[dilution_size-1 - step*i];
	}

	char sha1[20];
	sec::Hash<sec::HASH_SHA1>().Calculate(cipertext.Begin(), (UINT)cipertext.GetLength(), sha1);

	if(memcmp(sha1, &plaintext[16], 20) == 0)
	{
		rt::Swap(cipertext, plaintext);
		return true;
	}

	plaintext.SetLength(0);
	return false;
}

} // namespace oxd

