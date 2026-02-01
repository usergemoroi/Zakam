#pragma once

#include "il2cpp/il2cpp.h"

struct c_physics 
{
	static bool linecast ( vectors::vector3 a , vectors::vector3 b, int c )
	{
		static auto fn = reinterpret_cast < bool ( * ) ( vectors::vector3 , vectors::vector3 , int ) > ( il2cpp_base + oxorany(0x4A54078) );
		
		fn ( a , b , c );
	}
};
