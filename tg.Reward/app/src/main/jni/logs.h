#pragma once

#include <deque>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

void customtext(bool shadow, bool outline, const ImVec2& pos, ImColor color, const char* value, ImDrawList* drawlist = ImGui::GetBackgroundDrawList()) {
    if (outline) {
        drawlist->AddText({pos.x, pos.y}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x+0.75f, pos.y+0.75f}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x, pos.y+0.75f}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x+0.75f, pos.y}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x-0.75f, pos.y-0.75f}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x-0.75f, pos.y}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x, pos.y-0.75f}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);

        drawlist->AddText({pos.x, pos.y}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x+1, pos.y+1}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x, pos.y+1}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x+1, pos.y}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x-1, pos.y-1}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x-1, pos.y}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
        drawlist->AddText({pos.x, pos.y-1}, ImColor(0, 0, 0, (int)float(color.Value.w * 255)), value);
    }
    if (shadow) drawlist->AddText({ pos.x + 1, pos.y + 1 }, ImColor(5, 5, 5, (int)float(color.Value.w * 255)), value);
    drawlist->AddText(pos, color, value);
}

struct log_t {
    std::string text;
    int64_t creation_time;
    int64_t duration;
    int animation = 0;
    int bganimation = 0;
    int animpos1 = 20;
    int animpos2 = 0;
};

namespace cstd {
    template<class T, class A, class Predicate>
    void erase_if(std::deque<T, A> &c, Predicate pred) {
        c.erase(remove_if(c.begin(), c.end(), pred), c.end());
    }
}

std::deque<log_t> logs_list;

namespace logs {
    using namespace std::chrono;

    template<typename ... Args>
    void push(const std::string& format, Args ... args) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size_s <= 0) { std::runtime_error(std::string("Error during formatting string.").c_str()); }

        auto size = static_cast<size_t>(size_s);
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
#pragma clang diagnostic pop

        logs_list.push_back({
                                    std::string(buf.get(), buf.get() + size - 1),
                                    duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(),
                                    6000
                            });
    }

    void render(ImVec2 screen_size, ImDrawList* draw, int log_height) {
        int64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cstd::erase_if(logs_list, [current_time](auto& it) { return (it.animpos2 >= 20 && it.bganimation <= 0); });

        int count = 0;
        for (int i = 0; i < logs_list.size(); i++) {
            if (count > 15) break;
            if (logs_list[i].animpos1 > 0) logs_list[i].animpos1 -= 1;
            if (logs_list[i].animpos1 > 0 && logs_list[i].animation < 385) logs_list[i].animation += 20;
            if (logs_list[i].animpos1 > 0 && logs_list[i].bganimation < 385) logs_list[i].bganimation += 20;
            if (logs_list[i].animpos1 == 0 && logs_list[i].animation > 0) logs_list[i].animation -= 1;
            if (logs_list[i].animpos1 == 0 && logs_list[i].bganimation > 0) logs_list[i].bganimation -= 1;
            if (logs_list[i].bganimation <= 60 && logs_list[i].animpos2 < 600) logs_list[i].animpos2 += 1;
            //draw->AddRectFilled(ImVec2(screen_size.x / 2 - ImGui::CalcTextSize(logs_list[i].text.c_str()).x / 2 - 10, screen_size.y / 2 + 110+50*ImGui::GetIO().FontGlobalScale+60*ImGui::GetIO().FontGlobalScale + log_height * count - 10 - logs_list[i].animpos1 + logs_list[i].animpos2), ImVec2(screen_size.x / 2 + ImGui::CalcTextSize(logs_list[i].text.c_str()).x / 2 + 10, screen_size.y / 2 + 110+50*ImGui::GetIO().FontGlobalScale+60*ImGui::GetIO().FontGlobalScale + log_height * count + ImGui::CalcTextSize(logs_list[i].text.c_str()).y+10- logs_list[i].animpos1 + logs_list[i].animpos2), ImColor(0, 0, 0, logs_list[i].bganimation/3.5), 2);
            std::string final_text = std::string(oxorany("[ luminate ] ") + logs_list[i].text);
            auto text_size(ImGui::CalcTextSize(final_text.c_str()));
            std::string prefix_text = oxorany("[ luminate ] ");
            auto prefix_size(ImGui::CalcTextSize(prefix_text.c_str()));
			customtext(false, true, ImVec2(screen_size.x / 2 - text_size.x / 2, screen_size.y / 2 + 100 * ImGui::GetIO().FontGlobalScale + log_height * count - logs_list[i].animpos1 + logs_list[i].animpos2), ImColor(255, 0, 0, logs_list[i].animation), prefix_text.c_str(), draw);
            customtext(false, true, ImVec2(screen_size.x / 2 - text_size.x / 2 + prefix_size.x, screen_size.y / 2 + 100 * ImGui::GetIO().FontGlobalScale + log_height * count - logs_list[i].animpos1 + logs_list[i].animpos2), ImColor(255, 255, 255, logs_list[i].animation), logs_list[i].text.c_str(), draw);
            ++count;
        }
    }
}
