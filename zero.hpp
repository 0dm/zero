#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <Psapi.h>
#include <initguid.h>
#include <dbgeng.h>
static bool flag = false;

IDebugControl* GetDebugControl(DWORD ProcessId) {
    static IDebugClient* DebugClient;
    static IDebugControl* DebugControl;
    static bool DebugAttached;
    static DWORD LastProcessId;
    if (DebugClient == 0) {
        HMODULE dbgeng = LoadLibraryW(L"dbgeng.dll");
        if (dbgeng) ((decltype(::DebugCreate)*)GetProcAddress(dbgeng, "DebugCreate"))(IID_IDebugClient, reinterpret_cast<void**>(&DebugClient));
    }
    if (DebugClient && DebugControl == 0) DebugClient->QueryInterface(IID_IDebugControl, reinterpret_cast<void**>(&DebugControl));
    if (DebugClient && DebugControl) {
        IDebugClient* debugClient;
        IDebugControl* debugControl;
        if (DebugClient->CreateClient(&debugClient) == 0) {
            if (debugClient->QueryInterface(IID_IDebugControl, reinterpret_cast<void**>(&debugControl)) == 0) {
                if (DebugAttached && ProcessId != LastProcessId) {
                    debugClient->DetachProcesses();
                    DebugAttached = false;
                }
                if (!DebugAttached) {
                    DebugAttached = debugClient->AttachProcess(0, ProcessId, DEBUG_ATTACH_NONINVASIVE | DEBUG_ATTACH_NONINVASIVE_NO_SUSPEND) == 0 || debugClient->AttachProcess(0, ProcessId, DEBUG_ATTACH_EXISTING) == 0;
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

namespace zero {

template <typename T>
float getExecutionTime(T f) {
    auto getTime1 = std::chrono::high_resolution_clock::now();
    f();
    auto getTime2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fpms = getTime2 - getTime1;
    return fpms.count();
}

template <typename T>
void disassemble(T address, unsigned lines, bool trim) {
    ULONG64 addr = reinterpret_cast<ULONG64>(address);
    char buf[2048];
    int len = lines;
    IDebugControl* debugControl = GetDebugControl(GetCurrentProcessId());
    if (debugControl) {
        ULONG Offset = 0, DisassemblySize;
        while (debugControl->Disassemble(addr, 0, buf + Offset, sizeof(buf) - Offset, &DisassemblySize, &addr) == 0 && lines-- > 0) {
            Offset += DisassemblySize - 1;
        }
    }

    std::string newBuf = buf;
    if (trim) {
        while (newBuf.find("0000000" != 0)) {
            try {
                newBuf.erase(newBuf.find("`"), 1);
                newBuf.erase(newBuf.find("000000000"), 7);
            } catch (std::out_of_range) {
                break;
            }
        }
    }
    if (!flag) {
    std::cout << ("\n//////////////////////////////////////////////////////////////////////////////////\n")
              << newBuf << "//////////////////////////////////////////////////////////////////////////////////" << std::endl;
    flag = true;
    }
    else 
        std::cout << newBuf;
}

}  // namespace zero
