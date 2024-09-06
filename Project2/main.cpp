#include "Utils.h"
#include "Pointer.h"
#include "player.h"


void init(HINSTANCE HI);
uintptr_t* tramp;
uintptr_t* etramp;
uintptr_t* clientinstance;
uintptr_t* entitylist;

__int64 gametick_hook(__int64 a1, __int64 a2, __int64 a3, uintptr_t* a4, char a5) {
    auto Tramp = CreateFastCall<__int64, __int64, __int64, __int64, uintptr_t*, char >(tramp);
    auto test = CreateFastCall<__int64, uintptr_t*, uintptr_t*>(getAddress(callVirtual<Player*>(clientinstance,0x1D)->getgamemode(),0xE));
    if (keystatecalculation(0x4B) & 1) {
        test(callVirtual<Player*>(clientinstance, 0x1D)->getgamemode(), (uintptr_t*)callVirtual<Player*>(clientinstance, 0x1D));
    }
    return Tramp(a1, a2, a3, a4, a5);
}
__int64 entitylist_hook(uintptr_t* a1, int* a2) {
    auto Tramp = CreateFastCall<__int64,uintptr_t*,int* >(etramp);
    entitylist = (uintptr_t*)Tramp(a1, a2);
    return (uintptr_t)entitylist;
}
BOOL APIENTRY DllMain(
    HINSTANCE hInstance,
    DWORD dReason,
    LPVOID lpvReserved) {

    if (dReason == DLL_PROCESS_ATTACH) {
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, nullptr);
    }
    return TRUE;
}
#define Player_isBlocking 0x2E
#define Player_getSpeed 0x98
void init(HINSTANCE HI) {
    MH_Initialize();
    HWND Handle = GetConsoleWindow();
    {
        if (Handle == NULL) {//null（今までにコンソールがないとき。）
            AllocConsole();
            Handle = GetConsoleWindow();

            FILE* stdinNew = nullptr;
            freopen_s(&stdinNew, "CONIN$", "r+", stdin);
            FILE* stdoutNew = nullptr;
            freopen_s(&stdoutNew, "CONOUT$", "w+", stdout);
            FILE* stderrNew = nullptr;
            freopen_s(&stderrNew, "CONOUT$", "w+", stderr);
        }
        else {//（今までにコンソールがあり、表示する。）
            ShowWindow(Handle, SW_NORMAL);
        }
    }
    BaseAddress = (uintptr_t*)GetModuleHandle("Minecraft.Windows.exe");
    uintptr_t CI[] = { (uintptr_t)BaseAddress + 0x05AD6078 ,0x0,0x58,0x0,0x0};
    clientinstance = calclatepointer(CI, sizeof CI);
    cout<<"ClientInstance = " << clientinstance << endl;
    MH_CreateHook((LPVOID)((uintptr_t)BaseAddress+ 0x6ABA00), gametick_hook, (LPVOID*)&tramp);
    MH_CreateHook((LPVOID)((uintptr_t)BaseAddress + 0x1805460), entitylist_hook, (LPVOID*)&etramp);
    for (;;) {
        if (keystatecalculation(VK_HOME) & 1) {
            MH_EnableHook((LPVOID)((uintptr_t)BaseAddress + 0x6ABA00));
            MH_EnableHook((LPVOID)((uintptr_t)BaseAddress + 0x1805460));
        }
        if (keystatecalculation(VK_OEM_5) & 1) {
            MH_DisableHook((LPVOID)((uintptr_t)BaseAddress + 0x6ABA00));
            MH_DisableHook((LPVOID)((uintptr_t)BaseAddress + 0x1805460));
        }
        if (keystatecalculation(0x4C) & keystatecalculation(VK_CONTROL)) {//exit
            ShowWindow(Handle, SW_HIDE);
            break;
        }
        Sleep(50);
    }
    MH_ALL_HOOKS(MH_DisableHook);
    MH_ALL_HOOKS(MH_RemoveHook);
    MH_Uninitialize();
    FreeLibraryAndExitThread(HI, 0);
    return;
}
