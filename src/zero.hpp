#ifndef _ZERO_HPP
#define _ZERO_HPP

#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <initguid.h>
#include <dbgeng.h>


class zero {
public:
    static IDebugControl *GetDebugControl(DWORD ProcessId);

    template<typename function>
    static float getExecutionTime(function f);

    template<typename memory>
    static void disassemble(memory address, unsigned lines, bool trim);
};
#include "zero.ipp"

#endif //_ZERO_HPP
