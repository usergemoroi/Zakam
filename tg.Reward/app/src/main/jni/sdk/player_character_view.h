#pragma once

#include "il2cpp/il2cpp.h"

#include "bipedmap.h"

struct c_player_character_view
{
	bool is_visible ( )
	{
		return *reinterpret_cast < bool * > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x30) ) = true;
	}
	
	c_bipedmap * biped_map ( )
	{
		return *reinterpret_cast < c_bipedmap ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x48) );
	}
};
