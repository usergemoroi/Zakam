#pragma once

#include "vectors/vectors.h"
#include "il2cpp/il2cpp.h"

#include "photon_player.h"
#include "transform.h"
#include "bipedmap.h"
#include "player_character_view.h"
#include "weaponry_controller.h"

struct c_player_controller
{
	
	c_weaponry_controller * weaponry_controller ( )
	{
		return * reinterpret_cast < c_weaponry_controller ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x88) );
	}
	
	c_photon_player * photon_player ( )
	{
		return *reinterpret_cast < c_photon_player ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x158) );
	}
	
	c_transform * transform ( )
	{
		return *reinterpret_cast < c_transform ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0xF8) );
	}
	
	vectors :: vector3 get_head (  )
	{
		c_bipedmap * biped = this -> get_biped_map ( );
		
		c_bipedmap * part = *reinterpret_cast < c_bipedmap ** > ( reinterpret_cast < uintptr_t > ( biped ) + oxorany(0x20) );
		
		return part -> get_position_bone ( );
	}
	
	vectors :: vector3 get_neck ( ) 
	{
		c_bipedmap * biped = this -> get_biped_map ( );
		
		c_bipedmap * part = *reinterpret_cast < c_bipedmap ** > ( reinterpret_cast < uintptr_t > ( biped ) + oxorany(0x28) );
		
		return part -> get_position_bone ( );
	}
	
	c_transform * camera_transform ( )
	{
		return *reinterpret_cast < c_transform ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x28) );
	}
	
	uintptr_t character_lod_group ( )
	{
		return reinterpret_cast < uintptr_t > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x120) );
	}
	
	c_player_character_view * player_character_view ( )
	{
		return *reinterpret_cast < c_player_character_view ** > ( reinterpret_cast < uintptr_t > ( this ) + oxorany(0x48) );
	}
	
	c_bipedmap * get_biped_map ( )
	{
		const auto& view_character = this -> player_character_view ( );
	
		view_character -> is_visible ( );
		
		return view_character -> biped_map ( );
	}
	
	int get_team ( ) 
	{
		static auto fn = reinterpret_cast < int ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x5B0C9B4) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}
	
	uintptr_t set_tps ( )
	{
		static auto fn = reinterpret_cast < uintptr_t ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x5B0CCDC) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}
	
	uintptr_t bug_server ( )
	{
		static auto fn = reinterpret_cast < uintptr_t ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x2874034) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}
	
};

c_player_controller * local_player = nullptr;
c_player_controller * enemy_player = nullptr;
std::vector < c_player_controller * > player_list;
il2cpp_ray :: dictionary < int , c_player_controller * > * get_player_list;
