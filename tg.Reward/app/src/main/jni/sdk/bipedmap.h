#pragma once

#include "il2cpp/il2cpp.h"

#include "player_controller.h"

struct c_bipedmap
{
	
	vectors::vector3 get_position_bone ( )
	{
		static auto fn = reinterpret_cast < vectors::vector3 ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x48E0F60) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}
};
