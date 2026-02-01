#pragma once

#include <map>
#include <string>
#include <deque>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <imgui.h>
#include <imgui_internal.h>

enum NotifyState : int {
    ImTrickNotify_Success = 0,
    ImTrickNotify_Warning = 1,
    ImTrickNotify_Danger = 2,
    ImTrickNotify_Default = 3
};

namespace ImTricks {
	
    namespace Animations {
		
        int FastLerpInt(const char* identifier, bool state, int min, int max, int speed);

        float FastLerpFloat(const char* identifier, bool state, float min, float max, float speed);
		
        ImColor FastColorLerp(ImColor start, ImColor end, float stage);
    }

    namespace NotifyManager {

        struct NotifyStruct {
            std::string message;
            NotifyState state;
            std::chrono::steady_clock::time_point expiration_time;
        };
		
		struct NotifyAnimData {
			float initial_y;
            float offset_y = 0.0f;
            float target_y = 0.0f;
			float current_y;
            float alpha = 0.0f;
            float scale = 1.0f;
            float life_progress = 0.0f;
            bool is_animating = true;
            bool is_disappearing = false;
        };

        extern std::deque<NotifyStruct> active_notifies;
        extern std::queue<NotifyStruct> waiting_notifies;
		
        extern bool all_active_cleared;

        void AddNotify(const char* message, NotifyState state, int duration_ms = 3000);
		
        void HandleNotifies(ImDrawList* draw = ImGui::GetBackgroundDrawList());

    }

    namespace Widgets {

        void ColorEdit3(const char* label, ImColor& color, ImGuiColorEditFlags flags = 0);
        void ColorEdit4(const char* label, ImColor& color, ImGuiColorEditFlags flags = 0);

    }
}
