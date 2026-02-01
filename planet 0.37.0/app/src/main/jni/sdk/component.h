#pragma once

#include "il2cpp/il2cpp.h"
#include "camera.h"

struct c_component
{
	c_transform * get_transform (  )
	{
		static auto fn = reinterpret_cast < c_transform * ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x48D4208) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}

	void set_eulerAngles(vectors::vector3 pos)
	{
		static auto fn = reinterpret_cast <void (*) (uintptr_t, vectors::vector3)> (il2cpp_base + oxorany(0x48E1258));

		return fn(reinterpret_cast <uintptr_t> (this), pos);
	}

	void set_localEulerAngles(vectors::vector3 pos)
	{
		static auto fn = reinterpret_cast <void (*) (uintptr_t, vectors::vector3)> (il2cpp_base + oxorany(0x48E1364));

		return fn(reinterpret_cast <uintptr_t> (this), pos);
	}
};
