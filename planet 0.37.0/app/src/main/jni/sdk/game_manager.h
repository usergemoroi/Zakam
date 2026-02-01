#pragma once

#include "il2cpp/il2cpp.h"

struct c_game_manager
{
	static bool get_in_game ( )
	{
		static auto fn = reinterpret_cast < bool ( * ) ( ) > ( il2cpp_base + oxorany(0x5CCE05C) );
		
		return fn ( );
	}
};
