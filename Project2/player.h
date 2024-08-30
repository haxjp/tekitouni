#pragma once
#include "Utils.h"
class Gamemode;
class Player {
public:
	uintptr_t* getgamemode() {
		return (uintptr_t*)(*(uintptr_t*)((uintptr_t)this + 0xB00));
	}
};