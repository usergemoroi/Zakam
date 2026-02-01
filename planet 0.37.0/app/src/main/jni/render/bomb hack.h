#pragma once

#include "il2cpp/il2cpp.h"

#include "sdk/planted_bomb_controller.h"

void plantbomb ( )
{
	uintptr_t action = reinterpret_cast < uintptr_t > ( reinterpret_cast < uintptr_t > ( pbcontroller ) + 0x50 );
	
	pbcontroller -> plant ( reinterpret_cast < c_component * > ( local_player ) -> get_transform ( ) -> get_position ( ) , 1.0f , action );
}
