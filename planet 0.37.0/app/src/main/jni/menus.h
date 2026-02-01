#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include "font.h"
#include "verdana.h"
#include <vector>
#include <map>





ImFont* _main;
ImFont* _main1;
ImFont* verdana;


float alpha;
bool menu;
float x;
float y;
bool anal;
float xz;
float yz;
int active_tab;

int taj;
bool testung;
float xx;
bool anals;

struct subtab_anim
{
    int active_text_anim;
    int active_rect_alpha;
};
bool subtab(const char* label, bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    ImVec2 pos = window->DC.CursorPos;

    const ImRect rect(pos, ImVec2(pos.x + label_size.x, pos.y + 40));
    ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x + 2.f, rect.Max.y), style.FramePadding.y);
    if (!ImGui::ItemAdd(rect, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

    static std::map <ImGuiID, subtab_anim> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end())
    {
        anim.insert({ id, {0, 0} });
        it_anim = anim.find(id);
    }

    if (selected)
        it_anim->second.active_text_anim += 16 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.active_text_anim -= 16 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.active_text_anim > 255)
        it_anim->second.active_text_anim = 255;
    else if (it_anim->second.active_text_anim < 0)
        it_anim->second.active_text_anim = 0;

    if (selected)
        it_anim->second.active_rect_alpha += 20 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.active_rect_alpha -= 20 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.active_rect_alpha > 255)
        it_anim->second.active_rect_alpha = 255;
    else if (it_anim->second.active_rect_alpha < 0)
        it_anim->second.active_rect_alpha = 0;

    window->DrawList->AddRectFilled(ImVec2(rect.Min.x, rect.Min.y + 40), ImVec2(rect.Max.x, rect.Max.y-5), ImColor(255,255,255, it_anim->second.active_rect_alpha));
    window->DrawList->AddText(ImVec2((rect.Min.x + rect.Max.x) / 2.f - (label_size.x / 2.f), (rect.Min.y + rect.Max.y) / 2.f - (label_size.y / 2.f) - 5), ImColor(255, 255, 255, 100), label);
    window->DrawList->AddText(ImVec2((rect.Min.x + rect.Max.x) / 2.f - (label_size.x / 2.f), (rect.Min.y + rect.Max.y) / 2.f - (label_size.y / 2.f) - 5), ImColor(255,255,255,  it_anim->second.active_text_anim), label);

    return pressed;
}

struct Snowflake
{
    ImVec2 position;
    float speed;
};

std::vector<Snowflake> snowflakes;

void InitializeSnowflakes()
{
    snowflakes.clear();
    for (int i = 0; i < 100; i++)
    {
        Snowflake flake;
        flake.position = ImVec2(ImGui::GetIO().DisplaySize.x * (rand() / (float)RAND_MAX), ImGui::GetIO().DisplaySize.y * (rand() / (float)RAND_MAX));
        flake.speed = 1.0f + (rand() / (float)RAND_MAX) * 3.0f;
        snowflakes.push_back(flake);
    }
}


