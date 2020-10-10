#include "..\src\zero.cpp"

int test() {
    long long number = 0;
    for (long long i = 0; i != 2000000000; ++i) {
        number += 3;
    }
    std::cout << "Result: " << number << std::endl;
    return 3;
}

template <typename T>

float getExecutionTime(T f) {
    auto getTime1 = std::chrono::high_resolution_clock::now();
    f();
    auto getTime2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fpms = getTime2 - getTime1;
    return fpms.count();
}

int main() {
    std::cout << getExecutionTime(test) << "ms";
}