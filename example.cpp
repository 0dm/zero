#include "zero.hpp"

int test() {
    byte a = 69;
    std::cout << a;
    return 3;
}

int main() {
    std::cout << zero::getExecutionTime(test) << "\n"; // getExecutionTime
    zero::disassemble(test, 16, true); // disassemble

    // Using a hotkey
    ULONG64 offset = 68;
    while (true) {
        if (GetAsyncKeyState(VK_DOWN)) {
            offset += 4;
            zero::disassemble(reinterpret_cast<void*>((test+offset)), 16, true);
            Sleep(400);
        }
    }
}