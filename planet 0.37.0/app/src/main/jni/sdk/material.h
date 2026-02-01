#pragma once

#include "il2cpp/il2cpp.h"

#include "resources.h"

class c_material
{
public:
	void ctor ( uintptr_t shader )
	{
		static auto fn = reinterpret_cast < void ( * ) ( uintptr_t , uintptr_t ) > ( il2cpp_base + oxorany(0x49DC3D8) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) , shader );
	}
	
	void set_color ( Il2CppString * name , ImColor value )
	{
		static auto fn = reinterpret_cast < void ( * ) ( uintptr_t , Il2CppString * , ImColor ) > ( il2cpp_base + oxorany(0x49DC818) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) , name , value );
	}
	
	void set_int ( Il2CppString * name , int value )
	{
		static auto fn = reinterpret_cast < void ( * ) ( uintptr_t , Il2CppString*, int ) > ( il2cpp_base + oxorany(0x49DD654) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) , name , value );
	}
	
	static c_material * create ( const char * shader )
	{
		uintptr_t shader_ptr = c_resources :: find_shader_by_name ( std :: string ( shader ) );
		
		c_material * material = 0;
		
		static Il2CppImage * unity_asm;
		
		if ( ! unity_asm ) 
			unity_asm = il2cpp_api :: get ( ) -> functions.get_img_to_asm ( "UnityEngine.CoreModule" );
			
		static Il2CppClass* material_class;
		
		if ( ! material_class )
			material_class = il2cpp_api :: get ( ) -> functions.class_from_name ( unity_asm , "UnityEngine" , "Material" );
			
		material = reinterpret_cast < c_material * > ( il2cpp_api :: get ( ) -> functions.object_new ( material_class ) );
		
		material -> ctor ( shader_ptr );
		
		return material;
	}
};
