#pragma once

#include "il2cpp/il2cpp.h"

#include "safe_values.h"

#include "weapon_controller.h"

class c_gun_controller
{
public:
    uintptr_t fire ( )
	{
		return * reinterpret_cast < uintptr_t * > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0xe8) );
	}

	uintptr_t capacity ( )
	{
		return * reinterpret_cast < uintptr_t * > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x108) );
	}
	
	uintptr_t magazine_capacity ( )
	{
		return * reinterpret_cast < uintptr_t * > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x110) );
	}
};
