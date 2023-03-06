#pragma once
#include "../../../oxd_net/oxd_net.h"
#include "../../../oxd_bc/oxd_bc.h"

namespace oxd
{

class Playground
{
protected:
	// Execution Context Data
	LPBLKINMEM			_pCurrentBlock;
	LPBLKINMEM			_pParentBlock;
	LPTXNINMEM			_pTransaction;

	UserWiseStateTree	_UserStates;
	PerShardStates		_ContractStates;

public:
	static void		Run(os::CommandLine& cmd);
};

} // namespace oxd



