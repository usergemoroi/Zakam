#pragma once

#include "il2cpp/il2cpp.h"

class c_resources
{
public:
	static uintptr_t find_shader_by_name ( std::string name )
	{
		static auto fn = reinterpret_cast < uintptr_t ( * ) ( std::string ) > ( il2cpp_base + oxorany(0x49F955C) );
		
		return fn ( name );
	}
};
