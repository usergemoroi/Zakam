#pragma once

#include "il2cpp/il2cpp.h"

class c_planted_bomb_controller
{
public:
	void plant ( vectors :: vector3 position , float yRotation , uintptr_t action )
	{
		static auto fn = reinterpret_cast < void ( * ) ( uintptr_t , vectors :: vector3 , float , uintptr_t ) > ( il2cpp_base + oxorany(0x248B3A8) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) , position , yRotation , action );
	}
};

c_planted_bomb_controller * pbcontroller = nullptr;
