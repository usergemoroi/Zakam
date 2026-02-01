#pragma once

#include "il2cpp/il2cpp.h"
#include "vectors/vectors.h"

struct c_transform
{
	vectors::vector3 get_position ( )
	{
		static auto fn = reinterpret_cast < vectors::vector3 ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x48E0F60) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}
	
	void set_position ( vectors :: vector3 pos )
	{
		static auto fn = reinterpret_cast < void ( * ) ( uintptr_t , vectors :: vector3 ) > ( il2cpp_base + oxorany(0x48E1000) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) , pos );
	}
	
	vectors::vector3 get_forward ( )
	{
		static auto fn = reinterpret_cast < vectors::vector3 ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x48E1564) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}

	vectors::vector3 get_right()
	{
		static auto fn = reinterpret_cast <vectors::vector3(*) (uintptr_t)> (il2cpp_base + oxorany(0x48E13E8));

		return fn(reinterpret_cast <uintptr_t> (this));
	}
};
