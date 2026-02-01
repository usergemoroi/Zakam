#pragma once

#include "weapon_parameters.h"
#include "gun_controller.h"

#include "il2cpp/il2cpp.h"

class c_weapon_controller : public c_gun_controller
{
public:
	c_weapon_parameters * weapon_parameters ( )
	{
		return * reinterpret_cast < c_weapon_parameters ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x160) );
	}
};
