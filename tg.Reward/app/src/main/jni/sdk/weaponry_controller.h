#pragma once

#include "weapon_controller.h"

#include "il2cpp/il2cpp.h"

class c_weaponry_controller 
{
	
public:
	c_weapon_controller * weapon_controller ( )
	{
		return * reinterpret_cast < c_weapon_controller ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0xA0) );
	}

};
