#pragma once
#include "../../SFC/core/rt/string_type.h"

namespace oxd
{

extern bool			HeavySaltedEncrypt(const rt::String_Ref& pwd, rt::String& cipertext, const rt::String_Ref& plaintext, UINT order, UINT dilution_size);
extern bool			HeavySaltedDecrypt(const rt::String_Ref& pwd, rt::String& plaintext, const rt::String_Ref& cipertext, UINT order);
static const UINT	HeavySaltedEncryptAlignmentSize = 128/8;

} // namespace oxd
