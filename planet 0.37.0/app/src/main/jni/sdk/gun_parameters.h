#pragma once

#include "il2cpp/il2cpp.h"

class c_gun_parameters 
{
public:
	uintptr_t penetration_power ( )
	{
		return * reinterpret_cast < uintptr_t * > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x258) );
	}
};
