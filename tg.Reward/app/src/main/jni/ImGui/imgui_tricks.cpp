#include "imgui_tricks.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <deque>
#include <queue>
#include <map>

namespace ImTricks {

    namespace Animations {

        int FastLerpInt(const char* identifier, bool state, int min, int max, int speed) {
            static std::map<const char*, int> valuesMapInt;
            auto value = valuesMapInt.find(identifier);

            if (value == valuesMapInt.end()) {
                valuesMapInt.insert({ identifier, min });
                value = valuesMapInt.find(identifier);
            }

            const float frameRateSpeed = static_cast<float>(speed) * ImGui::GetIO().DeltaTime;

            if (state) {
                if (value->second < max)
                    value->second += static_cast<int>(frameRateSpeed);
            }
            else {
                if (value->second > min)
                    value->second -= static_cast<int>(frameRateSpeed);
            }

            value->second = std::clamp(value->second, min, max);
            return value->second;
        }

        float FastLerpFloat(const char* identifier, bool state, float min, float max, float speed) {
            static std::map<const char*, float> valuesMapFloat;
            auto value = valuesMapFloat.find(identifier);

            if (value == valuesMapFloat.end()) {
                valuesMapFloat.insert({ identifier, min });
                value = valuesMapFloat.find(identifier);
            }

            const float frameRateSpeed = speed * ImGui::GetIO().DeltaTime;

            if (state) {
                if (value->second < max)
                    value->second += frameRateSpeed;
            }
            else {
                if (value->second > min)
                    value->second -= frameRateSpeed;
            }

            value->second = std::clamp(value->second, min, max);
            return value->second;
        }

        float SmoothStep(float t) {
            return t * t * (3.0f - 2.0f * t);
        }

        ImColor FastColorLerp(ImColor start, ImColor end, float stage) {
            ImVec4 lerp = ImLerp(
                ImVec4(start.Value.x, start.Value.y, start.Value.z, start.Value.w),
                ImVec4(end.Value.x, end.Value.y, end.Value.z, end.Value.w),
                stage);
            return ImGui::ColorConvertFloat4ToU32(lerp);
        }

    }

    namespace NotifyManager {

        std::deque<NotifyStruct> active_notifies;
        std::queue<NotifyStruct> waiting_notifies;
        std::map<std::string, NotifyAnimData> notifyAnimations; // Используем строку как ключ
        const int MAX_ACTIVE_NOTIFIES = 5;

        void AddNotify(const char* message, NotifyState state, int duration_ms) {
            auto now = std::chrono::steady_clock::now();
            NotifyStruct new_notify = { 
                std::string(message), // Создаем копию строки
                state, 
                now + std::chrono::milliseconds(duration_ms) 
            };
            
            const ImVec2 ScreenSize = ImGui::GetIO().DisplaySize;
            float target_y = ScreenSize.y * 0.9f;
            
            for (const auto& notify : active_notifies) {
                const float padding = 25.0f;
                const ImVec2 text_size = ImGui::CalcTextSize(notify.message.c_str()); // Используем .c_str()
                const float notify_height = text_size.y + padding;
                target_y -= notify_height + 10.0f;
            }

            if (active_notifies.size() < MAX_ACTIVE_NOTIFIES) {
                active_notifies.push_back(new_notify);
                notifyAnimations[new_notify.message] = { 
                    ScreenSize.y,
                    target_y,
                    target_y,
                    ScreenSize.y,
                    0.0f,
                    true,
                    false
                };
            } else {
                waiting_notifies.push(new_notify);
            }
        }

        void HandleNotifies(ImDrawList* draw) {
            auto now = std::chrono::steady_clock::now();
            
            active_notifies.erase(std::remove_if(active_notifies.begin(), active_notifies.end(),
                [&now](const NotifyStruct& notify) {
                    return now > notify.expiration_time;
                }), active_notifies.end());

            while (active_notifies.size() < MAX_ACTIVE_NOTIFIES && !waiting_notifies.empty()) {
                NotifyStruct next_notify = waiting_notifies.front();
                waiting_notifies.pop();
                
                next_notify.expiration_time = now + std::chrono::milliseconds(3000);
                active_notifies.push_back(next_notify);
                
                const ImVec2 ScreenSize = ImGui::GetIO().DisplaySize;
                float target_y = ScreenSize.y * 0.41f;
                
                for (const auto& notify : active_notifies) {
                    if (notify.message == next_notify.message) continue;
                    
                    const float padding = 25.0f;
                    const ImVec2 text_size = ImGui::CalcTextSize(notify.message.c_str()); // Используем .c_str()
                    const float notify_height = text_size.y + padding;
                    target_y -= notify_height + 10.0f;
                }
                
                notifyAnimations[next_notify.message] = { 
                    ScreenSize.y,
                    target_y,
                    target_y,
                    ScreenSize.y,
                    0.0f,
                    true,
                    false
                };
            }

            if (active_notifies.empty())
                return;

            const ImVec2 ScreenSize = ImGui::GetIO().DisplaySize;
            const float center_x = ScreenSize.x * 0.5f;
            
            float current_y = ScreenSize.y * 0.41f;
            std::vector<std::pair<NotifyStruct*, float>> notify_positions;
            
            for (auto& notify : active_notifies) {
                const float padding = 25.0f;
                const ImVec2 text_size = ImGui::CalcTextSize(notify.message.c_str()); // Используем .c_str()
                const float notify_height = text_size.y + padding;
                
                notify_positions.push_back({&notify, current_y});
                current_y -= notify_height + 10.0f;
                
                notifyAnimations[notify.message].target_y = current_y + notify_height + 10.0f;
            }

            for (auto& [notify, target_y] : notify_positions) {
                NotifyAnimData& anim = notifyAnimations[notify->message];

                float total_duration = 3000.0f;
                float time_remaining = std::chrono::duration_cast<std::chrono::milliseconds>(
                    notify->expiration_time - now).count();
                
                float life_progress = 1.0f - (time_remaining / total_duration);
                life_progress = std::clamp(life_progress, 0.0f, 1.0f);

                if (life_progress < 0.06f && anim.is_animating) {
                    float appear_t = life_progress / 0.06f;
                    appear_t = Animations::SmoothStep(appear_t);
                    
                    anim.offset_y = ImLerp(ScreenSize.y, target_y, appear_t);
                    anim.alpha = appear_t;
                } else if (life_progress < 0.8f) {
                    anim.is_animating = false;
                    anim.offset_y = target_y;
                    anim.alpha = 1.0f;
                } else {
                    if (!anim.is_disappearing) {
                        anim.is_disappearing = true;
                    }
                    
                    float disappear_t = (life_progress - 0.8f) / 0.2f;
                    disappear_t = Animations::SmoothStep(disappear_t);
                    
                    anim.offset_y = ImLerp(target_y, ScreenSize.y, disappear_t);
                    anim.alpha = 1.0f - disappear_t;
                }

                const float padding = 25.0f;
                const float rounding = 10.0f;
                const float border_size = 1.5f;

                const ImVec2 text_size = ImGui::CalcTextSize(notify->message.c_str()); // Используем .c_str()
                const ImVec2 notify_size = ImVec2(text_size.x + padding * 2.0f, text_size.y + padding);

                const ImVec2 notify_pos = ImVec2(
                    center_x - notify_size.x * 0.5f,
                    anim.offset_y
                );

                const ImVec2 notify_end_pos = ImVec2(
                    notify_pos.x + notify_size.x,
                    notify_pos.y + notify_size.y
                );

                ImColor bg_color = ImColor(28, 28, 28, static_cast<int>(anim.alpha * 200)); 
                ImColor border_color = ImColor(60, 60, 65, static_cast<int>(anim.alpha * 195));
                ImColor text_color = ImColor(255, 255, 255, static_cast<int>(anim.alpha * 255));

                draw->AddRectFilled(notify_pos, notify_end_pos, bg_color, rounding);
                
                draw->AddRect(notify_pos, notify_end_pos, border_color, rounding, 0, border_size);

                const ImVec2 text_pos = ImVec2(
                    notify_pos.x + padding,
                    notify_pos.y + padding * 0.5f
                );

                draw->AddText(text_pos, text_color, notify->message.c_str()); // Используем .c_str()
            }

            for (auto it = notifyAnimations.begin(); it != notifyAnimations.end(); ) {
                bool found = false;
                for (const auto& notify : active_notifies) {
                    if (notify.message == it->first) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    it = notifyAnimations.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
	
    namespace Widgets {
        void ColorEdit3(const char* label, ImColor& color, ImGuiColorEditFlags flags) {
            float col[3] = { color.Value.x, color.Value.y, color.Value.z };
            if (ImGui::ColorEdit3(label, col, flags))
                color = ImColor(col[0], col[1], col[2]);
        }

        void ColorEdit4(const char* label, ImColor& color, ImGuiColorEditFlags flags) {
            float col[4] = { color.Value.x, color.Value.y, color.Value.z, color.Value.w };
            if (ImGui::ColorEdit4(label, col, flags))
                color = ImColor(col[0], col[1], col[2], col[3]);
        }
    }
}
