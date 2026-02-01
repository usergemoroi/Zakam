#pragma once

#include <cmath>
#include <codecvt>
#include <fstream>
#include <functional>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include "vectors/vectors.h"

int get_3D_Distance(int Self_x, int Self_y, int Self_z, int Object_x, int Object_y, int Object_z)
{
    int x, y, z;
    x = Self_x - Object_x;
    y = Self_y - Object_y;
    z = Self_z - Object_z;
    return (int)(sqrt(x * x + y * y + z * z));
}

namespace info_bool
{
	// misc
	bool add_score;
	bool test_bool;
	bool third_tps;
	bool noclip_enable;
	bool anti_aim;
	bool antiaim_transform;
	bool antiaim_character;
	bool antiaim_jitter;
	bool bhop;
	bool strafehelper;
	bool no_recoil;
	bool off_he;
	bool dont_return_spawn;
	bool move_before_time;
	bool respawn_hack;
	bool fastwin;
	bool cancel_match;
	bool ammo;
	bool rapid_fire;
	bool onehitkill;
	bool airjump;
	bool wall_shot;
	bool telekill;
	bool masskill;
	bool hit_sound;
	bool hit_logs;
	bool hit_tracer;
    bool airstrafe;
    bool always_head;
    bool world_color_solid;
    bool world_color;
    bool setworldcolor;
    bool antigrenade;
    bool autowin;
    bool invisible;
    bool moneyhack;
    bool aspect_ratio;
    bool friendlyfire;
    bool bighead;
    bool highjump;
    bool speedhack;

    bool aa_spinbot = false;
    bool aa_world = false;
    bool aa_character = false;
    bool aa_jitter = false;
    bool aa_in_air_only = false;

    float aa_spin_speed = 10.f;
    float aa_pitch = 0.f;

	bool fovhack;
	float fovValue = 85;
	float world_color_color;
    bool skycolor;

	bool fastknife;

	bool handspos;

	bool triggerbot;

    bool autostop;

	bool autoscope;

	bool infinitygrenade;
	
	//esp
	bool render_esp;
	bool render_box;
	bool render_war;
	bool render_name;
	bool render_health;
	
	//silent
	bool silent_enable;
	bool silent_check;
	bool draw_check;
	
	//opengl chams
	bool shading_chams;
	bool shading_wallhack;
	bool draw_chams;
	
	//material chams
    bool chams;
	bool chams_enemies;
};

namespace info_int
{
	//silent 
	int hitSoundIndex = 0;
	int silent_fov;
	int owidth;
}

namespace info_float 
{
	//exploits
	float tps_offset = 5.f;
	vectors::vector3 antiaim_transform_rotation = { 0.f, 5.f, 0.f };
	vectors::vector3 antiaim_character_rotation = { 0.f, 5.f, 0.f };
	float noclip_speed = 5.f;
	float bhop_offset = 3.f;
	float aspect_value = 0.0f;

	float trigger_delay = 0.1f;

    float skc[3] = { 255,255,255 };

	float hands_x = 0.0f;
	float hands_y = 0.0f;
	float hands_z = 0.0f;

    float jump_up = 0.20f;
}

namespace info_color
{
	//exploits
	ImVec4 bullet_color = ImColor ( 255, 255, 255 );
	float world_color_color[3] = {95, 85, 0};
    ImVec4 worldColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}

namespace info_combo
{
	int ch_bone = 0;
	const char * bones [ ] = { " none " , " head " , " neck ", " chest " };
	
	int ch_skin = 0;
	const char * skin [ ] = { " none " , " m9 blue blood " , " m9 universe " };

	static int knrn = 0;
	const char* kn[] = { oxorany("M9 Bayonet Dragon Glass"),  oxorany("M9 Bayonet Scratch"), oxorany("M9 Bayonet Universe"), oxorany("M9 Bayonet Blue Blood"), oxorany("M9 Bayonet Digital Burst"), oxorany("M9 Bayonet Kumo"), oxorany("M9 Bayonet Frozen"), oxorany("M9 Bayonet Ancient"), oxorany("Butterfly Black Window"), oxorany("Sting Shroud"), oxorany("Karambit Pelagia"), oxorany("Sting Pelagia"), oxorany("Scorpion AHAU"), oxorany("Dual Daggers Tiki") };
	static int glvn = 0;
	const char* gl[] = { oxorany("None"), oxorany("Acid Veil") };

    //std::vector<int> inventorySkins;

    int selected_skin_id = 0;
    const char* skin_names[] = {
        "M9 Blue Blood",
        "M9 Ancient",
        "M9 Scratch",
        "M9 Universe",
        "M9 Dragon Glass",
        "M9 Frozen",
        "M9 Kumo",
        "M9 Dark Shiver",
        "M9 Digital Burst",
        "M9 Amber Koi",
        "M9 Moonstone",
        "Karambit Claw",
        "Karambit Gold",
        "Karambit Ice Dragon",
        "Karambit Scratch",
        "Karambit Universe",
        "Karambit Cold Flame",
        "Karambit Frozen",
        "Karambit SnowCamo",
        "Karambit Year Of The Tiger",
        "Karambit Purple Camo",
        "Karambit Vermilion",
        "Karambit Nebula",
        "Karambit Widows Weave",
        "Karambit Pelagia",
        "jKommando Ancient",
        "jKommando Reaper",
        "jKommando Floral",
        "jKommando Luxury",
        "jKommando Frozen",
        "jKommando Augustite",
        "jKommando Prism",
        "jKommando Shatter",
        "jKommando Plasma",
        "Butterfly Gold",
        "Butterfly Dragon Glass",
        "Butterfly Red",
        "Butterfly Starfall",
        "Butterfly Fire Storm",
        "Butterfly Cold Flame",
        "Butterfly Kumo",
        "Butterfly Glitch",
        "Butterfly Ripple",
        "Butterfly Gambit",
        "Butterfly Saphira",
        "Flip New1",
        "Flip New2",
        "Flip New3",
        "Flip New4",
        "Flip New5",
        "Flip Snow Camo",
        "Flip Holiday Frost",
        "Flip Magnalium",
        "Kunai Bone",
        "Kunai Luxury",
        "Kunai Poison",
        "Kunai Radiation",
        "Kunai Reaper",
        "Kunai Cold Flame",
        "Kunai Snow Camo",
        "Kunai Augustite",
        "Kunai Prism",
        "Kunai Glitch",
        "Kunai Wavesong",
        "Kunai Diffusion",
        "Scorpion Veil",
        "Scorpion Green",
        "Scorpion Scratch",
        "Scorpion Sea Eye",
        "Scorpion Cold Flame",
        "Scorpion Holiday Frost",
        "Scorpion Magnalium",
        "Scorpion Ahau",
        "Scorpion NekoJoy",
        "Tanto Dojo",
        "Tanto Mafia",
        "Tanto Malachite",
        "Tanto Pearl Abyss",
        "Tanto Transistor",
        "Tanto Flow",
        "Tanto Restless",
        "Tanto Year Of The Tiger",
        "Tanto Retro Arcade",
        "Tanto Glitch",
        "Tanto FrostNova",
        "Tanto Solstice",
        "Tanto Hanami",
        "Tanto Celestial Tiger",
        "Tanto Blossom",
        "Daggers Acid",
        "Daggers Demonic Steel",
        "Daggers Grunge",
        "Daggers Molten",
        "Daggers Harmony",
        "Daggers Jaws",
        "Daggers Retro Arcade",
        "Daggers Frost Nova",
        "Daggers Tiki",
        "Daggers Contagion",
        "Kukri Ares",
        "Kukri Eagle",
        "Kukri Gold",
        "Kukri Silver",
        "Kukri Stars",
        "Kukri Stone",
        "Kukri Digital Burst",
        "Kukri Sea Glint",
        "Kukri Decay",
        "Kukri Cascade",
        "Stiletto Soul Devourer",
        "Stiletto Viper",
        "Stiletto TieDye",
        "Stiletto Damascus",
        "Stiletto Flux",
        "Stiletto Dark Shiver",
        "Stiletto Voidroot",
        "Mantis Eclipse",
        "Mantis Citrine",
        "Mantis Nest",
        "Mantis Genesis",
        "Mantis Impact",
        "Mantis Yokai",
        "Fang Flare",
        "Fang Serpent",
        "Fang Obsidian",
        "Fang Relic",
        "Fang Aureate",
        "Fang Damascus",
        "Fang Haunt",
        "Fang Saphira",
        "Fang Wavesong",
        "Sting Mimicry",
        "Sting Meld",
        "Sting Corrode",
        "Sting Fleck",
        "Sting Shroud",
        "Sting Oil Sheen",
        "Sting Temper Shades",
        "Sting Pelagia",
        "Sting Arcane Surge"
    };

    const int skin_ids[] = {
        71001,
        71002,
        71003,
        71004,
        71005,
        97100,
        157100,
        240063,
        200012,
        240154,
        240228,
        72002,
        72003,
        72004,
        72006,
        72007,
        97200,
        97201,
        97203,
        157200,
        200011,
        240164,
        240014,
        240131,
        240111,
        73002,
        73003,
        73004,
        73006,
        97300,
        157300,
        200015,
        240056,
        240132,
        47502,
        47503,
        47504,
        47505,
        57501,
        97500,
        157500,
        240007,
        240130,
        240225,
        240059,
        67701,
        67702,
        67703,
        67704,
        67705,
        97700,
        157700,
        240011,
        77813,
        77814,
        77815,
        77816,
        77817,
        97800,
        97801,
        157800,
        200014,
        240008,
        240156,
        240231,
        87919,
        87920,
        87921,
        87922,
        97900,
        157900,
        240010,
        240112,
        240152,
        138000,
        138001,
        138002,
        138003,
        138004,
        138005,
        148000,
        158000,
        200016,
        240009,
        240061,
        240114,
        240151,
        240226,
        240251,
        170021,
        170022,
        170023,
        170024,
        180000,
        180028,
        200017,
        240060,
        240109,
        240129,
        180022,
        180023,
        180024,
        180025,
        180026,
        180027,
        200013,
        240110,
        240128,
        240227,
        220021,
        220022,
        220023,
        220024,
        240012,
        240062,
        240153,
        240198,
        240199,
        240200,
        240201,
        240211,
        240229,
        240029,
        240030,
        240031,
        240032,
        240033,
        240034,
        240045,
        240058,
        240155,
        240064,
        240065,
        240066,
        240067,
        240068,
        240069,
        240070,
        240113,
        240133
    };
    const int skin_count = IM_ARRAYSIZE(skin_names);
	
}
