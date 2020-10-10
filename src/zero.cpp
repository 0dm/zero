#include "zero.hpp"

IDebugControl *zero::GetDebugControl(DWORD ProcessId) {
    static IDebugClient *DebugClient;
    static IDebugControl *DebugControl;
    static bool DebugAttached;
    static DWORD LastProcessId;
    if (DebugClient == 0) {
        HMODULE dbgeng = LoadLibraryW(L"dbgeng.dll");
        if (dbgeng)
            ((decltype(::DebugCreate) *)GetProcAddress(dbgeng, "DebugCreate"))(IID_IDebugClient, reinterpret_cast<void **>(&DebugClient));
    }
    if (DebugClient && DebugControl == 0)
        DebugClient->QueryInterface(IID_IDebugControl, reinterpret_cast<void **>(&DebugControl));
    if (DebugClient && DebugControl) {
        IDebugClient *debugClient;
        IDebugControl *debugControl;
        if (DebugClient->CreateClient(&debugClient) == 0) {
            if (debugClient->QueryInterface(IID_IDebugControl, reinterpret_cast<void **>(&debugControl)) == 0) {
                if (DebugAttached && ProcessId != LastProcessId) {
                    debugClient->DetachProcesses();
                    DebugAttached = false;
                }
                if (!DebugAttached) {
                    DebugAttached = debugClient->AttachProcess(0, ProcessId, DEBUG_ATTACH_NONINVASIVE | DEBUG_ATTACH_NONINVASIVE_NO_SUSPEND) ==
                                        0 ||
                                    debugClient->AttachProcess(0, ProcessId, DEBUG_ATTACH_EXISTING) == 0;
                    debugControl->WaitForEvent(0, INFINITE);
                    LastProcessId = ProcessId;
                }
                debugClient->Release();
                if (DebugAttached)
                    return debugControl;
                else
                    debugControl->Release();
            }
        }
    }
    return 0;
}