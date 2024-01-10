# openArabTools
open-source C++ and OpenGL 4 implementation of ArabTools, a student-only library for demonstration purposes

# Why?
This library is designed as a programming exercise as well as to give students who dislike Java a choice. 

# How to use it?

Simply include the `OpenArabTools.hpp` header and link the library.

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
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	ArabTools::Semaphore s;
	s.showWindow();
}
```

Example: Running concurrently in C++ with openArabTools
```cpp
#include "OpenArabTools.hpp"

void Function(const ArabTools::U08 ThreadId, const ArabTools::U64 Id) {
	//do something
	return;
}

int main() {
	ArabTools::init();
	ArabTools::Utils::runConcurrently(100000, true, Function);
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
Copyright (c) 2023-2024 Martin/MegapolisPlayer and contributors.

Licensed under CC-BY 4.0.

Full legal text [here](https://creativecommons.org/licenses/by/4.0/)

### Original Author

Based on Ing. Daniel Kahoun's ArabTools Library.

Copyright (c) 2014-2020 Ing. Daniel Kahoun

All rights reserved.