# zero
Adding useful C++ functions to this, currently has:



```cpp
template<typename function>
zero::getExecutionTime(function f)
```
returns the time (ms) that a function took to execute

```cpp
template<typename memory>
zero::disassemble(memory address, unsigned lines, bool trim)
```
```
address: starting address to disassemble (can pass function)
lines: amount of lines to display
trim: attempt to remove zeros from addresses, works fine with x86.
```
![gif](https://i.imgur.com/eaPbmc3.gif)

Only works on Windows.
