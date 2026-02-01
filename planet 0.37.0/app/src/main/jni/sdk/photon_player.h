#pragma once

#include "il2cpp/il2cpp.h"

struct c_photon_player
{
	bool is_local( )
    {
        return *reinterpret_cast< bool* >( reinterpret_cast< uintptr_t >( this ) + oxorany(0x30) );
    }
	
	il2cpp_ray :: string * name_field ( )
	{
		return *reinterpret_cast < il2cpp_ray :: string ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x20) );
	}
	
	int get_health ( )
	{
		static auto fn = reinterpret_cast < int ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x4D95C48) ); // 
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}
};
