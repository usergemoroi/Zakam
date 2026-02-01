#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#include <link.h>
#include <set>
#include <libgen.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/mman.h>
#include <dirent.h>
#include <map>
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Logger.h"
#include "oxorany/include.h"
#include "Includes/Utils.h"
#include "Color.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"
#define targetLibName oxorany("libunity.so")
#define libil2cpp oxorany("libunity.so")
int glHeight, glWidth;
bool setup;
uintptr_t address;
uintptr_t il2cpp_base;
uintptr_t il2cpp_addr = oxorany(0x0);
uintptr_t shared_base = oxorany(0x0);
int skin_ids [ ] = { oxorany(31004) , oxorany(31001) , oxorany(44902) };
bool isKnifeEquipped = false;
bool showMenu = true;
bool gameFullyLoaded = false;
int gameLoadTimer = 0;
const int GAME_LOAD_DELAY = 300;
bool chamsInitialized = false;
bool shadersLoaded = false;
int frameCounter = 0;

#include "map/Map.hpp"
#include "information.h"
#include "xdl/include/xdl.h"
#include "logs.h"
#include "SkinChanger/main.h"
#include "Xhook/xhook.h"
#include "sdk/score_extensions.h"
#include "sdk/player_controller.h"
#include "sdk/photon_player.h"
#include "sdk/transform.h"
#include "sdk/camera.h"
#include "sdk/material.h"
#include "sdk/resources.h"
#include "sdk/renderer.h"
#include "sdk/planted_bomb_controller.h"
#include "render/oh no render is esp.h"
#include "render/bomb hack.h"
#include "il2cpp/il2cpp.h"
#include "hooks.h"
#include "menus.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "logs", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "logs", __VA_ARGS__)

void PatchHex(uintptr_t addr, const uint8_t* bytes, size_t size)
{
    mprotect((void*)(addr & ~0xFFF), 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC);

    for (size_t i = 0; i < size; i++)
        *(uint8_t*)(addr + i) = bytes[i];
}

class InternalPatch
{
public:
    InternalPatch(uintptr_t baseAddr, size_t size, const uint8_t* patchData)
    {
        addr = baseAddr;
        patchSize = size;
        memcpy(patchBytes, patchData, size);
        isPatched = false;
        memset(originalBytes, 0, sizeof(originalBytes));
    }

    void Modify()
    {
        if (!isPatched)
        {
            memcpy(originalBytes, (void*)addr, patchSize);
            PatchHex(addr, patchBytes, patchSize);
            isPatched = true;
        }
    }

    void Restore()
    {
        if (isPatched)
        {
            PatchHex(addr, originalBytes, patchSize);
            isPatched = false;
        }
    }

private:
    uintptr_t addr;
    size_t patchSize;
    uint8_t patchBytes[16]{};
    uint8_t originalBytes[16]{};
    bool isPatched;
};

struct Patches
{
    InternalPatch* win = nullptr;
    InternalPatch* money = nullptr;
    InternalPatch* antigrenade = nullptr;
    InternalPatch* friendlyfire = nullptr;
};

Patches hexPatches;

bool AreShadersLoaded()
{
    static bool checked = false;
    static bool result = false;
    
    if (checked) return result;
    
    if (FindShader == nullptr)
    {
        LOGE("FindShader is nullptr!");
        return false;
    }
    
    monoString* standardShader = il2cpp_string_new("Standard");
    void* shader = FindShader(standardShader);
    
    if (shader)
    {
        result = true;
        checked = true;
        LOGI("Shaders are loaded!");
    }
    else
    {
        LOGI("Shaders not loaded yet...");
    }
    
    return result;
}

void SafeChamsInitialization()
{
    if (chamsInitialized) return;
    
    frameCounter++;
    
    if (frameCounter < 60)
    {
        return;
    }
    
    if (!AreShadersLoaded())
    {
        LOGI("Waiting for shaders to load...");
        return;
    }
    
    monoString* standardShader = il2cpp_string_new("Standard");
    monoString* hiddenShader = il2cpp_string_new("Hidden/Internal-Colored");
    
    if (!standardShader || !hiddenShader)
    {
        LOGE("Failed to create shader strings");
        return;
    }
    
    void* standardShaderPtr = FindShader(standardShader);
    void* hiddenShaderPtr = FindShader(hiddenShader);
    
    if (!standardShaderPtr || !hiddenShaderPtr)
    {
        LOGI("Shaders not available yet, waiting...");
        return;
    }
    
    LOGI("Shaders loaded successfully! Chams can now be enabled.");
    chamsInitialized = true;
    shadersLoaded = true;
}

void SafeChamsFunction()
{
    if (!chamsInitialized || !shadersLoaded)
    {
        return;
    }
    
    if (!info_bool::chams)
    {
        return;
    }
    
    if (!local_player || player_list.empty())
    {
        return;
    }
    
    try
    {
        monoString* hiddenShaderName = il2cpp_string_new("Hidden/Internal-Colored");
        if (!hiddenShaderName)
        {
            LOGE("Failed to create shader string");
            return;
        }
        
        void* chamsShader = FindShader(hiddenShaderName);
        if (!chamsShader)
        {
            LOGE("Chams shader not found!");
            return;
        }
        
        void* chamsMat = CreateMaterial(std::string("Hidden/Internal-Colored"));
        if (!chamsMat)
        {
            LOGE("Failed to create chams material");
            return;
        }
        
        ImColor color = ImColor(128, 128, 128, 128);
        SetColorMaterial(chamsMat, il2cpp_string_new("_Color"), color);
        SetIntMaterial(chamsMat, il2cpp_string_new("_ZWrite"), 0);
        SetIntMaterial(chamsMat, il2cpp_string_new("_ZTest"), 8);
        
        for (int i = 0; i < player_list.size(); i++)
        {
            void* Player = player_list[i];
            if (!Player) continue;
            
            SetMaterials(Player, chamsMat);
        }
        
        LOGI("Chams applied successfully to %d players", player_list.size());
    }
    catch (...)
    {
        LOGE("Exception in chams function");
    }
}

void SetupImgui() {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize = ImVec2((float)glWidth, (float)glHeight);

    ImGui::StyleColorsDark();
    
    ImFontConfig font_cfg;
    _main = io.Fonts->AddFontFromMemoryTTF(Font, sizeof(Font), 35, &font_cfg);
    _main1 = io.Fonts->AddFontFromMemoryTTF(Font, sizeof(Font), 25, &font_cfg);
    verdana = io.Fonts->AddFontFromMemoryTTF(verdana_data, sizeof verdana_data, 13 * 2, NULL, io.Fonts->GetGlyphRangesCyrillic());
    
    ImGui_ImplOpenGL3_Init(oxorany("#version 300 es"));

    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontDefault(&font_cfg);
    
    ImGui::GetStyle().ScaleAllSizes(2.3f);
    
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.0f, 0.0f, 0.95f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.6f, 0.0f, 0.0f, 0.75f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.0f, 0.0f, 0.6f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.8f, 0.0f, 0.0f, 0.4f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 0.0f, 0.0f, 0.6f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.6f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.6f, 0.0f, 0.0f, 0.6f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.4f, 0.0f, 0.0f, 0.6f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.6f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_Border] = ImVec4(1.0f, 0.0f, 0.0f, 0.5f);
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.WindowRounding = 5.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
}

void menus() {
    static bool chamsWarningShown = false;
    
    if (info_bool::draw_check)
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(glWidth / 2, glHeight / 2), info_int::silent_fov / 0.5, ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 1)));
    
    ImGui::SetNextWindowSize(ImVec2(900, 522), ImGuiCond_FirstUseEver);
    ImGui::Begin(oxorany("Tg.Revard"));

    if (!chamsInitialized && info_bool::chams)
    {
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Chams: Waiting for shaders to load...");
        chamsWarningShown = true;
    }
    else if (chamsWarningShown && chamsInitialized)
    {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Chams: Ready to use!");
        chamsWarningShown = false;
    }

    if (ImGui::BeginTabBar("MainTabs"))
    {
        // Esp Tab
        if (ImGui::BeginTabItem(oxorany("Esp")))
        {
            ImGui::Checkbox(oxorany(" Render Players "), &info_bool::render_esp);
            ImGui::Checkbox(oxorany(" Render Box "), &info_bool::render_box);
            ImGui::Checkbox( oxorany ( " Render Name " ) , & info_bool :: render_name );
            ImGui::Checkbox( oxorany ( " Render Health " ) , & info_bool :: render_health );
            ImGui::Checkbox(oxorany("Chams"), &info_bool::chams);
            
            if (!chamsInitialized)
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), " (Loading...)");
            }
            
            ImGui::EndTabItem();
        }

        // Aim Tab
        if (ImGui::BeginTabItem(oxorany("Aim")))
        {
            ImGui::Checkbox(oxorany(" Enable "), &info_bool::silent_enable);
            ImGui::Checkbox(oxorany(" Visible Check "), &info_bool::silent_check);
            ImGui::SliderInt(oxorany(" FOV "), &info_int::silent_fov, 0, 1180);
            ImGui::Checkbox(oxorany(" Draw FOV "), &info_bool::draw_check);
            ImGui::Combo(oxorany(" Bone "), &info_combo::ch_bone, info_combo::bones, IM_ARRAYSIZE(info_combo::bones));
            
            ImGui::EndTabItem();
        }

        // Fun Tab
        if (ImGui::BeginTabItem(oxorany("Fun")))
        {
            ImGui::Checkbox(oxorany(" Third Person "), &info_bool::third_tps);
            if (info_bool::third_tps) {
                ImGui::SliderFloat(oxorany(" Distance "), &info_float::tps_offset, 0, 5);
            }
            ImGui::Checkbox(oxorany(" Bunny Hop "), &info_bool::airstrafe);
            ImGui::Checkbox(oxorany(" Strafe Helper "), &info_bool::strafehelper);
            ImGui::Checkbox(oxorany(" Endless Ammo "), &info_bool::ammo);
            ImGui::Checkbox(oxorany(" Rapid Fire "), &info_bool::rapid_fire);
            ImGui::Checkbox(oxorany(" Anti Recoil "), &info_bool::no_recoil);
            ImGui::Checkbox(oxorany(" Fast Knife "), &info_bool::fastknife);
            ImGui::Checkbox(oxorany(" One Hit Kill "), &info_bool::onehitkill);
            ImGui::Checkbox(oxorany(" Auto Win "), &info_bool::autowin);
            ImGui::Checkbox(oxorany(" Invisible "), &info_bool::invisible);
            ImGui::Checkbox(oxorany(" Anti Aim "), &info_bool::anti_aim);
            ImGui::Checkbox(oxorany(" Aspect Ratio "), &info_bool::aspect_ratio);
            ImGui::SliderFloat(oxorany(" Aspect Ratio Value "), &info_float::aspect_value, 0.0f, 2.0f);
            
            if (info_bool::anti_aim) {
                ImGui::Checkbox(oxorany(" SpinBot "), &info_bool::aa_spinbot);
                ImGui::SliderFloat(oxorany(" Spin Speed "), &info_bool::aa_spin_speed, 1.f, 50.f);
                ImGui::Checkbox(oxorany(" Affect Transform "), &info_bool::aa_world);
                ImGui::Checkbox(oxorany(" Affect Character "), &info_bool::aa_character);
                ImGui::Checkbox(oxorany(" Jitter "), &info_bool::aa_jitter);
                ImGui::SliderFloat(oxorany(" Pitch "), &info_bool::aa_pitch, -180.f, 180.f);
                ImGui::Checkbox(oxorany(" In Air Only "), &info_bool::aa_in_air_only);
            }
            
            ImGui::Checkbox(oxorany(" Move Before Time "), &info_bool::move_before_time);
            ImGui::Checkbox(oxorany(" Big Head "), &info_bool::bighead);
            ImGui::Checkbox(oxorany(" Add Score "), &info_bool::add_score);
            ImGui::Checkbox(oxorany(" Sky Color "), &info_bool::skycolor);
            
            if (info_bool::skycolor) {
                ImGui::ColorEdit3(oxorany(" Sky Color "), info_float::skc);
            }
            
            ImGui::Checkbox(oxorany(" Air Jump "), &info_bool::airjump);
            
            ImGui::EndTabItem();
        }

        // Skins Tab
        if (ImGui::BeginTabItem(oxorany("Skins")))
        {
            ImGui::Combo("Select Skin", &info_combo::selected_skin_id, info_combo::skin_names, info_combo::skin_count);

            if (ImGui::Button("Change Skin")) {
                change(info_combo::skin_ids[info_combo::selected_skin_id]);
            }
            
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    
    ImGui::End();
}

EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (!setup) {
        SetupImgui();
        setup = oxorany ( true );
    }

    ImGuiIO &io = ImGui::GetIO();

    SafeChamsInitialization();
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    menus();
    
    if (info_bool::chams && chamsInitialized)
    {
        SafeChamsFunction();
    }
    
    render();
    logs::render(ImGui::GetIO().DisplaySize, ImGui::GetBackgroundDrawList(), oxorany(16));
    hit_function();
    
    ImGui::EndFrame();
    ImGui::Render();
    glViewport(oxorany(0), oxorany(0), (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return old_eglSwapBuffers(dpy, surface);
}

bool contains(std::string in, std::string target) {
    if(strstr(in.c_str(), target.c_str())) {
        return oxorany(true);
    }
    return oxorany(false);
}

void got_plt_hook()
{
    uintptr_t got = libunity_base + 0x8093130;
    uintptr_t old_addr = *(uintptr_t*)got;
    old_eglSwapBuffers = (decltype(old_eglSwapBuffers))old_addr;
    mprotect((void*)(got & ~0xFFF), 0x1000, PROT_READ | PROT_WRITE);
    *(uintptr_t*)got = (uintptr_t)&hook_eglSwapBuffers;
}

#if defined (__aarch64__)

#define RETURN _("C0 03 5F D6")
#define NOP _("1F 20 03 D5")
#define TRUE _("20 00 80 D2 C0 03 5F D6")
#define FALSE _("00 00 80 D2 C0 03 5F D6")

#else

#define RETURN _("1E FF 2F E1")
#define TRUE _("01 00 A0 E3 1E FF 2F E1")
#define FALSE _("00 00 A0 E3 1E FF 2F E1")

#endif

void *hack_thread(void *) {
    while (!isLibraryLoaded("libunity.so")) {
        sleep(1);
    }

    il2cpp_base = findLibrary("libunity.so");
    libunity_base = findLibrary("libunity.so");

    InitIl2CppAPI();
    got_plt_hook();

    LOGI("il2cpp_base = 0x%lX", il2cpp_base);
    LOGI("libunity_base = 0x%lX", libunity_base);

    get_transform = (void* (*)(void*)) (libunity_base + oxorany(0x48D4208));
    get_position = (vectors::vector3(*)(void*)) (libunity_base + oxorany(0x48E0F60));
    get_camera = (void* (*)()) (libunity_base + oxorany(0x48F9C0C));
    worldtoscreenpoint = (vectors::vector3(*)(void*, vectors::vector3)) (libunity_base + oxorany(0x48F9890));
    get_forward = (vectors::vector3(*)(void*)) (libunity_base + oxorany(0x48E1564));
    set_position = (void (*)(void*, vectors::vector3)) (libunity_base + oxorany(0x48E1000));
    get_BipedMap = (void* (*)(void*))(libunity_base + 0x5B0C240);
    Linecast = (bool (*)(vectors::vector3, vectors::vector3, int)) (libunity_base + 0x5B4B1CC);
    GetHealth = (decltype(GetHealth))(libunity_base + 0x4D95004);
    set_localEulerAngles = decltype(set_localEulerAngles)(libunity_base + 0x48E1364);
    set_eulerAngles = decltype(set_eulerAngles)(libunity_base + 0x48E1258);
    set_localScale = (void (*)(void*, vectors::vector3)) (libunity_base + oxorany(0x48E1790));
    uScreen_get_width = (get_width_t)(libunity_base + 0x4E72AF8);
    uScreen_get_height = (get_height_t)(libunity_base + 0x4E72AF0);

    FindShader = (void* (*)(monoString*)) (libunity_base + 0x490A698);
    new_material = (void (*)(void*, void*)) (libunity_base + 0x490ACFC);
    set_material = (void (*)(void*, void*)) (libunity_base + 0x490A1A4);
    get_material = (void* (*)(void*)) (libunity_base + 0x490A168);
    get_materials = (decltype(get_materials))(libunity_base + 0x490A128);
    set_materials = (decltype(set_materials))(libunity_base + 0x490A164);
    set_texture = (decltype(set_texture))(libunity_base + 0x490B438);
    get_texture = (decltype(get_texture))(libunity_base + 0x490B2AC);
    get_type = (decltype(get_type))(libunity_base + 0x47F21DC);
    find_objects = (decltype(find_objects))(libunity_base + 0x48DB178);
    has_property = (decltype(has_property))(libunity_base + 0x490B4FC);
    SetIntMaterial = (void (*)(void*, monoString*, int)) (libunity_base + 0x490BF78);
    SetColorMaterial = (void (*)(void*, monoString*, ImColor))(libunity_base + 0x490B13C);
    get_SkinnedMeshRenderer = (decltype(get_SkinnedMeshRenderer))(libunity_base + 0x49727D0);
    SetFloatMaterial = (decltype(SetFloatMaterial))(libunity_base + 0x490C04C);
    objectswin = decltype(objectswin)(libunity_base + 0x4C84950);

    hexPatches.win = new InternalPatch(libunity_base + 0x4C2FC48, 8, (uint8_t[]) { 0xE0, 0xE1, 0x84, 0xD2, 0xC0, 0x03, 0x5F, 0xD6 });
    hexPatches.money = new InternalPatch(libunity_base + 0x697BAA0, 8, (uint8_t[]) { 0x20, 0x00, 0x80, 0xD2, 0xC0, 0x03, 0x5F, 0xD6 });
    hexPatches.antigrenade = new InternalPatch(libunity_base + 0x691FA0C, 8, (uint8_t[]) { 0x20, 0x00, 0x80, 0xD2, 0xC0, 0x03, 0x5F, 0xD6 });
    hexPatches.friendlyfire = new InternalPatch(libunity_base + 0x53C6F84, 8, (uint8_t[]) { 0x20, 0x00, 0x80, 0xD2, 0xC0, 0x03, 0x5F, 0xD6 });

    void* delegate_input_touch1 = (void*)(libunity_base + 0x858B718);
    while (!*(void**)delegate_input_touch1) {
        sleep(1);
    }
    bool touch = icall_hook(delegate_input_touch1, "UnityEngine.Input::get_touchCount()", hooks::input_get_touchCount, &hooks::old_input_get_touchCount, "libunity");

    Il2CppClass* klass12 = GetClassFromA("Assembly-CSharp", "Axlebolt.Standoff.Player", "PlayerController");
    bool hooked11 = method_hook(klass12, "LateUpdate", hooks::player_controller_late_update, &hooks::old_player_controller_late_update, 0);

    Il2CppClass* klass1 = GetClassFromA("Assembly-CSharp", "Axlebolt.Standoff.Player", "PlayerController");
    bool hooked = method_hook(klass1, "Update", hooks::player_controller_update, &hooks::old_player_controller_update, 0);

    void* call_raycast = (void*)(libunity_base + 0x8587E18);
    while (call_raycast == nullptr)
    {
        sleep(1);
    }

    bool ok11 = icall_hook(call_raycast, "UnityEngine.PhysicsScene::Internal_Raycast_Injected(UnityEngine.PhysicsScene&,UnityEngine.Ray&,System.Single,UnityEngine.RaycastHit&,System.Int32,UnityEngine.QueryTriggerInteraction)", hooks::hk_raycast, &hooks::orig_raycast, "libunity");

    Il2CppClass* klass11 = GetClassFromA("Assembly-CSharp", "Axlebolt.Standoff.Controls", "PlayerControls");
    bool hooked2 = method_hook(klass11, "Update", hooks::updatepl1, &hooks::orig_updatepl1, 0);
    
    pthread_exit(nullptr);
    return nullptr;
}

__attribute__((constructor))
void lib_main() {
    pthread_t hacks;
    pthread_create(&hacks, NULL, hack_thread, NULL);
}
