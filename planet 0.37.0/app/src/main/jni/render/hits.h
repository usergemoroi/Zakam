#pragma once

#include "il2cpp/il2cpp.h"
#include "vectors/vectors.h"

#include "information.h"

vectors :: vector3 CalculateWorldPosition ( vectors :: vector3 position ) {
        c_transform * camTransform = reinterpret_cast < c_component * > ( c_camera :: get_main ( ) ) -> get_transform ( );
        vectors :: vector3 camPos = camTransform -> get_position ( );
        vectors :: vector3 camNormal = camTransform -> get_forward ( );
        vectors :: vector3 vectorFromCam = position - camPos;
        float camNormDot = vectors :: vector3::Dot ( camNormal , vectorFromCam );
        return camNormDot <= 0 ? camPos + ( vectorFromCam - ( camNormal * camNormDot * 1.01 ) ) : position;
}

void drawlineglow(ImDrawList* draw, ImVec2 start, ImVec2 end, ImColor col, int thickness, int size) {
    draw->AddLine(start, end, col, thickness);
    for (int i = 0; i < size; i++) {
        if (start.y != end.y)
            draw->AddLine({start.x - i / 2, start.y}, {end.x + i / 2, end.y}, ImColor(col.Value.x, col.Value.y, col.Value.z, col.Value.w * (1.0f / (float) size) * (((float) (size - i)) / (float) size)), thickness+i);
        else
            draw->AddRectFilled({start.x - i / 2, start.y - i / 2 }, {end.x + i / 2, end.y + i / 2 }, ImColor(col.Value.x, col.Value.y, col.Value.z, col.Value.w * (1.0f / (float) size) * (((float) (size - i)) / (float) size)), 4+i);
    }
}

struct hit_info {
public:
    int health;
    vectors :: vector3 pos;
    vectors :: vector3 posCamera;
    int animation = 255;
};

std::deque < hit_info > hit_data;

void hit_function ( )
{
	ImGui::PushFont ( _main1 );
	
	if ( info_bool :: hit_tracer && ! hit_data.empty ( ) )
	{
		for ( auto i = 0; i < hit_data.size ( ); i++ )
		{
			if ( hit_data [ i ].animation < 1 ) hit_data.erase ( hit_data.begin ( ) + i );
			if ( hit_data [ i ].animation > 0 ) hit_data [ i ].animation -= 1;
			
			auto hp = hit_data [ i ].health;
			
			auto hitPos2 = CalculateWorldPosition(hit_data[i].pos);
			auto camPos2 = CalculateWorldPosition(hit_data[i].posCamera);
			auto animation = hit_data[i].animation;
                bool checker1;
                auto hitPos = w2s_c ( hitPos2 , checker1 );
                auto camPos = w2s_r ( camPos2 );
				
			if ( info_bool :: hit_tracer )
				drawlineglow ( ImGui :: GetBackgroundDrawList ( ) , ImVec2 ( camPos.x , camPos.y ) , ImVec2 ( hitPos.x , hitPos.y ) , ImColor ( info_color :: bullet_color.x , info_color :: bullet_color.y , info_color :: bullet_color.z , ( float ) animation / 255 ) , 1 , 12 );
		}
	}
	ImGui :: PopFont ( );
}
