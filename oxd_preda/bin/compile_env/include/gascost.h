#pragma once

#include <array>
#include <vector>
#include "common.h"
#include "exceptions.h"
#include <iostream>

namespace prlrt
{

thread_local uint64_t RemainingGas = 0;

thread_local bool GasSwitch = true;

const uint16_t* gas_costs = nullptr;						// gas cost table pointer

constexpr uint64_t relay_base_gas = 2000;

	void burn_gas(uint64_t gas_cost)
	{
		if(!GasSwitch) return;
		if(RemainingGas < gas_cost)
		{
			RemainingGas = 0;
			preda_exception::throw_exception("insufficient gas", prlrt::ExceptionType::GasUsedUp);
		}
		RemainingGas -= gas_cost;
	}

	void burn_gas_loop()
	{
		burn_gas(gas_costs[PRDOP_JUMP]);
	}

	void burn_gas_function_call()
	{
		burn_gas(gas_costs[PRDOP_JUMP]);
	}

	void enable_burn_gas()
	{
		GasSwitch = true;
	}

	void disable_burn_gas()
	{
		GasSwitch = false;
	}
} // namespace prlrt
