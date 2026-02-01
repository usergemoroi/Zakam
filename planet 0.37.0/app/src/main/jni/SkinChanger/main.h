#pragma once

#include "il2cpp/il2cpp.h"
#include "il2cpp/il2cpp.hpp"
#include "dictionary.h"



namespace skins
{
	int string_to_int(const char* str) {
    int result = 0;
    bool is_negative = false;

    // Пропускаем пробелы
    while (*str == ' ') {
        str++;
    }

    // Проверяем знак
    if (*str == '-') {
        is_negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Преобразуем строку в число
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return is_negative ? -result : result;
}
	
	void * MainController_Instance ( )
	{
		static auto fn = reinterpret_cast < void * ( * ) ( ) > ( il2cpp_base + 0x5461568 );
		
		return fn ( );
	}
	
	static void* MainController_GetInvController()
{
 return *(void **)((uintptr_t)MainController_Instance() + 0xB0);
}
static void* InventoryController_GetInvTabController()
{
 return *(void **)((uintptr_t)MainController_GetInvController() + 0x80);
}
static void* InventoryTabController_GetPopupMenu()
{
 return *(void **)((uintptr_t)InventoryController_GetInvTabController() + 0x88);
}
bool change_skin(int newid = 71004) {
 void* BoltInventoryItem = *(void **)((uintptr_t)InventoryTabController_GetPopupMenu() + 0xA8);
 if(BoltInventoryItem) {
  *(int *)((uintptr_t)BoltInventoryItem + 0x10) = newid;
  *(void **)((uintptr_t)InventoryTabController_GetPopupMenu() + 0xA8) = BoltInventoryItem;
  return true;
 }
 return false;
 }
}

void change(int id) {
    uintptr_t boltInventoryService = *(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(il2cpp_base + 135055488) + 0x58) + 0xB8) + 0x0);
    if (!boltInventoryService) return;

    uintptr_t dictionary = *(uintptr_t*)(boltInventoryService + 0xF8);
    if (!dictionary) return;

    int skinsCount = *(int*)(dictionary + 0x20);
    if (!skinsCount) return;

    for (int i = 0; i < skinsCount; i++) {
        uintptr_t ptr = *(uintptr_t*)(*(uintptr_t*)(dictionary + 0x18) + 0x30 + 0x18 * i);
        if (!ptr) continue;

        *(int*)(ptr + 0x10) = id;
    }
}
