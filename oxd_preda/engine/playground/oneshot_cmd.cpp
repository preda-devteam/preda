#include "oneshot_cmd.h"
#include "../../../oxd_bc/oxd_bc.h"
#include "../interface/base_impl.h"

namespace oxd
{

using namespace rvm;

rt::String_Ref ParseContractName(const rt::String_Ref& src)
{
	auto def = src.FindString("contract ");
	if(def < 0)def = src.FindString("contract\t");
	if(def < 0)return nullptr;

	auto end = src.FindCharacter('{', def + 8);
	if(end < 0)return nullptr;

	return rt::String_Ref(&src[def + 8], &src[end]).TrimSpace();
}

void RunOneshotCommand(os::CommandLine& cmd)
{
	if(!cmd.GetTextCount())return;
	rt::String_Ref dapp_name = cmd.GetOption("dapp", "myDapp");

	rt::BufferEx<rt::String>	filenames;
	rt::BufferEx<rt::String>	sources;
	rt::BufferEx<rt::String>	contr_names;

	for(UINT i=0; i<cmd.GetTextCount(); i++)
	{
		rt::String_Ref filename = cmd.GetText(i);
		_LOG("Loading "<<filename<<" ...");

		rt::String src;
		if(!os::File::LoadText(ALLOCA_C_STRING(filename), src))
		{	_LOG("  failed to open the file");
			return;
		}

		auto contract_name = ParseContractName(src);
		if(contract_name.IsEmpty())
		{	_LOG("  contract definition is not found or incomplete");
			return;
		}

		sources.push_back(src);
		filenames.push_back(filename);
		contr_names.push_back(contract_name);
	}

	bool deploy = cmd.HasOption("deploy");

	DAppName dapp;
	auto* dapp_reg = DAppCore::Get().FindDAppByName(dapp_name);
	dapp.Name = (ConstString&)dapp_name;
	UINT contract_sn_next = 0;

	if(dapp_reg)
	{
		dapp.DAppId = dapp_reg->DAppId;
		contract_sn_next = dapp_reg->NextContractSerialNum;
	}
	else
	{
		dapp.DAppId = DAppCore::Get().GetNextDAppId();
	}

	rt::BufferEx<ContractName>	contr_args;
	contr_args.SetSize(contr_names.GetSize());
	for(UINT i=0; i<contr_names.GetSize(); i++)
	{
		contr_args[i].Name = (ConstString&)contr_names[i];

		const ContractRegistration* creg = nullptr;
		if(dapp_reg && (creg = DAppCore::Get().FindContractByName(dapp.DAppId, contr_names[i])))
		{
			contr_args[i].ContractId = creg->ContractId;
		}
		else
		{
			contr_args[i].ContractId = RVM_CONTRACT_ID_MAKE(contract_sn_next, CTRSS_WILDCARD, dapp.DAppId);
		}
	}

	auto* rvm = DAppCore::Get().GetRvmEngine();
	rt::Buffer<const uint8_t*> srcs;
	srcs.SetSize(contr_args.GetSize());
	for(UINT i=0; i<sources.GetSize(); i++)
		srcs[i] = (const uint8_t*)sources[i].Begin();

	rt::Buffer<HashValue>	hashes;
	hashes.SetSize(contr_args.GetSize());

	rt::Buffer<DeployError>	errs;
	errs.SetSize(contr_args.GetSize());

	rt::Buffer<StringStreamImpl>	output_strings;
	output_strings.SetSize(contr_args.GetSize());

	rt::Buffer<StringStream*>	outputs;
	outputs.SetSize(contr_args.GetSize());
	for(UINT i=0; i<outputs.GetSize(); i++)
		outputs[i] = &output_strings[i];

	DAppDeployContext ddc;

	rvm->DeployContracts(	&ddc, 
							cmd.HasOption("deploy")?DeployStage::Deploy:DeployStage::VerifyData,
							&dapp, 
							contr_names.GetSize(), 
							contr_args, 
							srcs,
							hashes,
							errs,
							outputs
	);
	
	for(UINT i=0; i<filenames.GetSize(); i++)
	{
		_LOG("Deploy "<<filenames[i]<<" result: "<<errs[i]<<", IRHASH="<<b32str(hashes[i]));
		rt::String_Ref& out = *(rt::String_Ref*)output_strings[i].GetString();
		if(out[0] == '{')
		{
			_LOG(rt::JsonBeautified(out));
		}
		else
		{
			_LOG(out);
		}
	}
}

} // namespace oxd

