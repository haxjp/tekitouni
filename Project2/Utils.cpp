#include "Utils.h"
#include "Pointer.h"

int keystatecalculation(int vkey) {
	uintptr_t KeyPointer[] = {(uintptr_t)BaseAddress+ 0x05A163A0 };
	return *((int*)(calclatepointer(KeyPointer, sizeof KeyPointer)) + vkey);
}

uintptr_t* calclatepointer(uintptr_t pointer[],int size) {
	size = size / sizeof uintptr_t;
	uintptr_t* Result = (uintptr_t*)pointer[0];
	for (int n = 1; n < size; n++) {
		Result = (uintptr_t*)(*Result + pointer[n]);
	}
	return Result;
}

uintptr_t* getAddress(void* thisptr, size_t index) {
	return ((uintptr_t**)(*(void**)thisptr))[index];
}
