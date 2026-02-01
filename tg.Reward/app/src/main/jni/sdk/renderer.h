#pragma once 

#include "il2cpp/il2cpp.h"

class c_renderer
{
public:
	void set_material ( c_material * material )
	{
		static auto fn = reinterpret_cast < void ( * ) ( uintptr_t , c_material * ) > ( il2cpp_base + oxorany(0x4B4AF74) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) , material );
	}
};
