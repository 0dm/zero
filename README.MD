# zero.hpp
Adding useful C++ functions to this, currently has:


**zero::getExecutionTime(function)**
```cpp
<typename T>
```
returns the time (ms) that a function took to execute


**zero::disassemble(typename T> address, unsigned lines, bool trim)**
```
address: starting address to disassemble (can pass function)
lines: amount of lines to display
trim: attempt to remove zeros from addresses, works fine with x86.
```
![gif](https://i.imgur.com/eaPbmc3.gif)

Only works on Windows.
