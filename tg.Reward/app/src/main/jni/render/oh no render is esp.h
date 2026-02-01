#pragma once 

#include "il2cpp/il2cpp.h"

#include "menus.h"

#include "sdk/photon_player.h"
#include "sdk/player_controller.h"
#include "sdk/transform.h"
#include "sdk/camera.h"
#include "sdk/game_manager.h"
#include "sdk/component.h"

#include "information.h"

#define pi 3.14159265358979323846264338327950288419716939937510f

#define deg_2_rad ( 2.f * pi / 360.f )
#define rad_2_deg ( 1.f / deg_2_rad )

inline void arc ( float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness ) {
    ImGui::GetBackgroundDrawList ( ) -> PathArcTo ( ImVec2 ( x, y ) , radius, deg_2_rad * min_angle , deg_2_rad * max_angle, 32 );
    ImGui::GetBackgroundDrawList ( ) -> PathStroke ( col, false, thickness );
}

inline ImVec2 flooring(ImVec2 vec) {
    return { (float)(vec.x), (float)int(vec.y) };
}

inline ImVec2 flooring(float x, float y) {
    return { (float)int(x), (float)int(y) };
}

inline ImVec2 flooring(int x, int y) {
    return { (float)x, (float)y };
}

inline float grape_text(ImFont* font, ImVec2 pos, ImVec2 allign, ImColor col, std::string text, float size = 20, bool shadow = false, bool outline = false, bool glow = false, float glowalpha = 10, bool gradient = false, ImColor col2 = ImColor(255, 255, 255)) {
    const char* ctext = text.c_str();
    ImVec2 textsize = font->CalcTextSizeA(size, FLT_MAX, 0, ctext);
    ImVec2 textrelative = ImVec2(1, 1) - ((allign + ImVec2(1, 1)) / 2);
    textrelative.x *= textsize.x;
    textrelative.y *= textsize.y;
    ImVec2 textpos = pos - textrelative;
    if (!gradient) {
        if (shadow) {
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos + ImVec2(1, 1)), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.85f), ctext);
        }
        if (outline) {
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(-1, -1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(0, -1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(1, -1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(-1, 0), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(1, 0), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(-1, 1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(0, 1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
            ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos) + ImVec2(1, 1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.7f), ctext);
        }

        ImGui::GetBackgroundDrawList()->AddText(font, size, flooring(textpos), col, ctext);
    }
    return textsize.x;
}

struct evo_rect_t {
    int x;
    int y;
    int w;
    int h;
};

void player_fix ( ) {
	std::vector < c_player_controller * > new_vector;
	for ( int i = 0; i < player_list.size ( ); i++ ) {
		auto obj = player_list [ i ];
		if ( ! obj ) continue;

		const auto& photon = obj -> photon_player ( );
		if ( ! photon ) continue;

        if ( obj && obj != nullptr && photon != NULL && photon -> get_health ( ) > 0 ) {
            new_vector.push_back ( obj );
		}
	}
	player_list = new_vector;
}

bool player_find ( c_player_controller * obj ) {
	for ( const auto& object : player_list ) {
		if ( object == obj )
			return true;
	}
	return false;
}

void player_add ( c_player_controller * obj ) {
	if ( ! player_find ( obj ) ) {
		const auto& photon = obj -> photon_player ( );
		if (!photon) return;

		if (obj && obj != nullptr && photon != NULL && photon -> get_health ( ) > 0) { player_list.push_back ( obj ); };
	}
}

void render ( ImDrawList * draw_list = ImGui::GetBackgroundDrawList ( ) )
{
	if ( info_bool :: render_esp )
	{	
			player_fix ( );
			
			for ( int i = 0; i < player_list.size ( ); i++ )
			{
			
				auto target = player_list [ i ];
				
			if ( target -> get_team ( ) != local_player -> get_team ( ) ) 
			{
			
			const auto& photon = target -> photon_player ( );
			
			if ( target && photon )
			{
				const auto& pos = reinterpret_cast < c_component * > ( target ) -> get_transform ( ) -> get_position ( );
				
				bool w2s_checker = false;
				
				ImVec2 top_pos (
				w2s_r(pos + vectors::vector3 ( 0, 1.9f, 0 ) )
				);
				
				ImVec2 bot_pos (
                w2s_r(pos + vectors::vector3 ( 0, -0.15f, 0 ) )
				);
				
				auto posTop = top_pos.x;
                auto posBottom = bot_pos.x;
                if ( top_pos.x > bot_pos.x ) {
                posTop = bot_pos.x;
                posBottom = top_pos.x;
                }
				
				const auto& w2s_center = w2s_c ( pos + vectors::vector3 ( 0, 0.75f, 0 ), w2s_checker );
				
				const auto& calculated_position = fabs ( (top_pos.y - bot_pos.y ) * ( 0.0092f / 0.0155f ) / 2 );
				
				const ImRect bb_rect = {
                ImVec2 ( static_cast < int > ( posTop - calculated_position ), static_cast < int > ( top_pos.y ) ),
                ImVec2 ( static_cast < int > ( posBottom + calculated_position ), static_cast < int > ( bot_pos.y ) )
            };
			
			const auto& evo_rect = evo_rect_t {
		        static_cast < int > ( bb_rect.Min.x ),
		        static_cast < int > ( bb_rect.Min.y ),
		        static_cast < int > ( bb_rect.GetWidth ( ) ),
		       static_cast < int > ( bb_rect.GetHeight ( ) )
	        };
			
			vectors::vector3 viewpos = reinterpret_cast < c_component * > ( c_camera :: get_main ( ) ) -> get_transform ( ) -> get_position ( );
			
			if ( info_bool :: render_war )
			{
				const auto& display_size = ImGui::GetIO ( ).DisplaySize;
				
				if ( ( w2s_center.x < 0 || w2s_center.x > display_size.x ) || ( w2s_center.y < 0 || w2s_center.y > display_size.y ) || !w2s_checker )
				{
					constexpr int maxpixels = 150;
					
					int pixels = maxpixels;
					
					if ( w2s_checker )
					{
						if ( w2s_center.x < 0 )
                            pixels = std::clamp ( ( int ) -w2s_center.x, 0, ( int ) maxpixels);
                        if (w2s_center.y < 0)
                            pixels = std::clamp ( ( int ) -w2s_center.y, 0, ( int ) maxpixels);

                        if (w2s_center.x > display_size.x)
                            pixels = std::clamp ( ( int ) w2s_center.x - ( int ) display_size.x, 0, ( int ) maxpixels);
							
                        if (w2s_center.y > display_size.y)
                            pixels = std::clamp ( ( int ) w2s_center.y - ( int ) display_size.y, 0, ( int ) maxpixels);
							
					}
					
					float opacity = ( float ) pixels / ( float ) maxpixels;
					
					float size = 5.0f;
					
					vectors::vector3 viewdir = reinterpret_cast < c_component * > ( c_camera :: get_main ( ) ) -> get_transform ( ) -> get_forward ( );
					
                    vectors::vector3 targetdir = ( pos - viewpos ).normalized ( );
					
					float viewangle = atan2 ( viewdir.z, viewdir.x ) * rad_2_deg;
					
                    float targetangle = atan2 ( targetdir.z, targetdir.x ) * rad_2_deg;
					
					if ( viewangle < 0 ) viewangle += 360;
                    if ( targetangle < 0 ) targetangle += 360;

                    float angle = targetangle - viewangle;

                    while ( angle < 0 ) angle += 360;
                    while ( angle > 360 ) angle -= 360;

                    angle = 360 - angle;
                    angle -= 90;

                    arc ( display_size.x / 2, display_size.y / 2, 112 + vectors::vector3::Distance ( viewpos, pos ) * 2,
                        angle - size,
                        angle + size,
                        ImColor ( 1.f, 1.f, 1.f, 1.f * opacity ) , 4.f );
				}
			}
			
			if ( w2s_checker ) {
				
			if ( info_bool :: render_box )
			{
				draw_list->AddRect(ImVec2(evo_rect.x + 1, evo_rect.y + 1), ImVec2((evo_rect.x + evo_rect.w) - 1, (evo_rect.y + evo_rect.h) - 1), ImColor(0, 0, 0, 220), 0, 0, 1);
                    draw_list->AddRect(ImVec2(evo_rect.x - 1, evo_rect.y - 1), ImVec2((evo_rect.x + evo_rect.w) + 1, (evo_rect.y + evo_rect.h) + 1), ImColor(0, 0, 0, 220), 0, 0, 1);

                    draw_list->AddRect(ImVec2(evo_rect.x, evo_rect.y), ImVec2(evo_rect.x + evo_rect.w, evo_rect.y + evo_rect.h), ImColor(255, 255, 255, 250), 0, 0, 1);
			}
					
			if ( info_bool :: render_name )
			{
				const auto& name = photon -> name_field ( );
				
				if ( name )
				{
					const auto& name_size = verdana->CalcTextSizeA(13, FLT_MAX, 0, name->get_string().c_str());
					
					const ImVec2& name_pos = {bb_rect.Min.x + bb_rect.GetWidth() / 2, bb_rect.Min.y - 3 - name_size.y};
					
					grape_text(verdana, name_pos, ImVec2(0, 1), ImColor(255, 255, 255), name->get_string(), 13, true, false);
				}
			}
			
			if ( info_bool :: render_health ) 
			{
				int player_hp = std::min(100, photon -> get_health ( ) );
				
				int r = std::fmin((510 * (100 - player_hp)) / 100, 255);
		        int g = std::fmin((510 * player_hp) / 100, 255);

		        int h = evo_rect.h + 2;
		        int fill = static_cast<int>(std::round(player_hp * h / 100.f));
				
				draw_list->AddRectFilled({evo_rect.x - 5, evo_rect.y}, {evo_rect.x - 5 + 2, evo_rect.y + evo_rect.h}, ImColor(0, 0, 0, 200), 0);
				draw_list->AddRectFilled({evo_rect.x - 5, evo_rect.y + (h - fill)}, {evo_rect.x - 5 + 2, evo_rect.y + (h - fill) + fill - 2}, ImColor(128, 0, 128), 0);
				draw_list->AddRect({evo_rect.x - 6, evo_rect.y - 1}, {evo_rect.x - 6 + 4, evo_rect.y - 1 + evo_rect.h + 2}, ImColor(0, 0, 0, 220), 0, 0, 1);
			}
				}
			}
			}
			}
	}
}
