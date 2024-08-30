#pragma once
#include <Windows.h>
#include "MinHook.h"
#include "vftcalling.h"
#include <iostream>
using namespace std;
int keystatecalculation(int vkey);
uintptr_t* calclatepointer(uintptr_t pointer[], int size);
uintptr_t* getAddress(void* thisptr, size_t index);
//typedef 
typedef uintptr_t* (*ClientInstanceOriginal)(uintptr_t* a1);
typedef float (__fastcall* test)(uintptr_t*);