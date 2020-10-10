// lazy template implementation
#include "zero.hpp"

template <typename function>
float zero::getExecutionTime(function f) {
    auto getTime1 = std::chrono::high_resolution_clock::now();
    f();
    auto getTime2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> fpms = getTime2 - getTime1;
    return fpms.count();
}

static bool flag = false;

template <typename memory>
void zero::disassemble(memory address, unsigned lines, bool trim) {
    ULONG64 addr = reinterpret_cast<ULONG64>(address);
    char buf[2048];
    IDebugControl *debugControl = zero::GetDebugControl(GetCurrentProcessId());
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
                newBuf.erase(newBuf.find("`"),1);
                newBuf.erase(newBuf.find("000000000"),7);
            } catch (std::out_of_range) {
                break;
            }
        }
    }
    if (!flag) {
        std::cout << ("\n//////////////////////////////////////////////////////////////////////////////////\n")
                  << newBuf << "//////////////////////////////////////////////////////////////////////////////////"
                  << std::endl;
        flag = true;
    } else
        std::cout << newBuf;
}