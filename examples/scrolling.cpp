#include "..\src\zero.cpp"

int test() {
    byte a = 69;
    std::cout << a;
    return 3;
}

int main() {
    std::cout << zero::getExecutionTime(test) << "\n"; // getExecutionTime
    zero::disassemble(test, 20, true); // disassemble

    // Using a hotkey
    ULONG64 offset = 0;
    bool clear = true;

    while (true) {
        if (GetAsyncKeyState(VK_DOWN)) {
            offset += 4;
            if (!clear)
                clear = true;
                system("cls");
            zero::disassemble(reinterpret_cast<char*>(test)+offset, 20, true);
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_UP)) {
            offset -= 4;
            if (clear)
                clear = false;
                system("cls");
            zero::disassemble(reinterpret_cast<char*>(test)+offset, 20, true);
            Sleep(100);
        }
    }
}