# openArabTools
open-source C++ and OpenGL 4 implementation of ArabTools, a student-only library for demonstration purposes

# Why?
This library is designed as a programming exercise as well as to give students who dislike Java a choice. 

# How to use it?

# Comparison to ArabTools

Example: Simple semaphore in Java (standard ArabTools)
```java
import cz.gyarab.util.Utils;
import cz.gyarab.util.light.Semaphore;

class Main {
  public static void Main(String[] Args) {
    Semaphore s = Semaphore.createSemaphore();
    s.showWindow();
  }
}
```
In C++ with openArabTools
```cpp
#include "openArabTools.hpp"

int main() {
  ArabTools::Semaphore s;
  s.showWindow();
}
```

# openArabTools - differences
- written in C++ as supposed to Java
- uses OpenGL 4
- has shorter syntax and is more extensible
- provides more utility functions and classes

# Accessing the internal API
...is not recommended.

Use it only if you want to extend the functionality.
Everything is in the ArabTools::Internal namespace.

# License
Licensed under CC-BY 4.0.
Full legal text [here](https://creativecommons.org/licenses/by/4.0/)
