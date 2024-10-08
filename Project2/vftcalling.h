#pragma once
#include "Utils.h"
template <typename TRet, typename... TArgs>
extern TRet callVirtual(void* thisptr, size_t index, TArgs... argList) {
	using TFunc = TRet(__fastcall*)(void*, TArgs...);
	TFunc* vtable = *reinterpret_cast<TFunc**>(thisptr);
	return vtable[index](thisptr, argList...);
}
template<typename TRet,typename... TArgs>
auto CreateFastCall(uintptr_t* Func) {
	using Fn = TRet(__fastcall*)(TArgs...);
	return reinterpret_cast<Fn>(Func);
}