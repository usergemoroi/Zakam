#pragma once

#include "il2cpp/il2cpp.h"

#include "photon_player.h"

struct c_score_extensions
{
	static void add_score ( c_photon_player * photon , int value )
	{
		static auto fn = reinterpret_cast < void ( * ) ( c_photon_player * , int ) > ( il2cpp_base + oxorany(0x5BDDECC) );
		
		return fn ( photon , value );
	}
};
