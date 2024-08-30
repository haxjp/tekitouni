#include "Utils.h"
#include "Pointer.h"
#include "player.h"

void init(HINSTANCE HI);
int b;
uintptr_t* clientinstance;
using tramp = __int64(__fastcall*)(void*,void*);
static tramp a;
void hook(void* thisptr,void* target) {
    for (int n = 0; n < b; n++)
        a(thisptr, target);
    return;
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
    uintptr_t CI[] = { (uintptr_t)BaseAddress + 0x05AD5088 ,0x0,0x58,0x0,0x0};
    clientinstance = calclatepointer(CI, sizeof CI);
    cout<<"ClientInstance = " << clientinstance << endl;
    MH_CreateHook(getAddress(callVirtual<Player*>(clientinstance, 0x1D)->getgamemode(), 0xE), hook, (LPVOID*)&a);
    for (;;) {
        if (keystatecalculation(VK_HOME) & 1) {
            MH_EnableHook(getAddress(callVirtual<Player*>(clientinstance, 0x1D)->getgamemode(), 0xE));
            cin >> b;
        }
        if (keystatecalculation(VK_OEM_5) & 1) {
            MH_DisableHook(getAddress(callVirtual<Player*>(clientinstance, 0x1D)->getgamemode(), 0xE));
        }
        if (keystatecalculation(VK_END) & 1) {//exit
            ShowWindow(Handle, SW_HIDE);
            break;
        }
        Sleep(50);
    }

    MH_Uninitialize();
    FreeLibraryAndExitThread(HI, 0);
    return;
}
