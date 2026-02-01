#pragma once

#include "vectors/vectors.h"
#include "il2cpp/il2cpp.h"

#include "transform.h"
#include "component.h"

#define M_PI 3.14159265358979323846264338327950288419716939937510f

struct c_camera
{
	static c_camera * get_main ( )
	{
		static auto fn = reinterpret_cast < c_camera * ( * ) ( ) > ( il2cpp_base + oxorany(0x48F9C0C) );
		
		return fn ( );
	}
	
	vectors::vector3 worldtoscreen ( vectors::vector3 pos )
	{
		static auto fn = reinterpret_cast < vectors::vector3 ( * ) ( uintptr_t , vectors::vector3 ) > ( il2cpp_base + oxorany(0x48F9890) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) , pos );
	}
	
	float field_of_view ( )
	{
		static auto fn = reinterpret_cast < float ( * ) ( uintptr_t ) > ( il2cpp_base + oxorany(0x48F9C0C) );
		
		return fn ( reinterpret_cast < uintptr_t > ( this ) );
	}
	
};

float getAngleBetween ( const vectors :: vector3& a , const vectors :: vector3& b ) {
    float dotProduct = a.x * b.x + a.y * b.y + a.z * b.z;
    return std::acos ( dotProduct ) * ( 180.0f / M_PI ); // Преобразование в радианы
}

bool isBoneVisible ( const vectors :: vector3& bonePosition, const vectors :: vector3& cameraPosition ) {
    vectors :: vector3 directionToBone = ( bonePosition - cameraPosition ).normalized ( );
    
    vectors :: vector3 cameraDirection = reinterpret_cast < c_component * > ( c_camera :: get_main ( ) ) -> get_transform ( ) -> get_forward ( );
	
    float angle = getAngleBetween(directionToBone, cameraDirection);
    
    return angle <= c_camera :: get_main ( ) -> field_of_view ( ) / 2;
}

ImVec2 w2s_r(vectors::vector3 pos) {
    auto cam = c_camera :: get_main ( );
    if (!cam) return { 0 , 0 };

    vectors::vector3 worldPoint = cam -> worldtoscreen ( pos );

    return { worldPoint.x , glHeight - worldPoint.y };
}

ImVec2 w2s_c(vectors::vector3 pos, bool &checker) {
    auto cam = c_camera :: get_main ( );
    if (!cam) return { 0, 0 };

    vectors::vector3 worldPoint = cam -> worldtoscreen ( pos );

    checker = worldPoint.z > 1;
    return ImVec2 ( worldPoint.x , glHeight - worldPoint.y );
}
