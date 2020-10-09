# zero.h
Adding useful functions to this, currently has:


**zero::getExecutionTime(function)**
```cpp
<typename T>
```
returns the time (ms) that a function took to execute


**zero::disassemble(address, lines, trim)**
```cpp
<typename T> address: starting address to disassemble (can pass function)
unsigned lines: amount of lines to display
bool trim: attempt to remove zeros from addresses, works fine with x86.
```
