# openArabTools
an open-source C++ and OpenGL 4 implementation of ArabTools, a student-only library for demonstration purposes

# Why?
This library is designed so that the students who are currently learning C++,
students who have already left the school and/or the people just curious to experience
ArabTools a way to still have access to it.

The documentation for openArabTools is accessible here: (TODO: add documentation once completed)

# How to use it?

Simply include the `OpenArabTools.hpp` header and link the library.
The process will depend whether you are using Visual Studio, CodeLite or any other IDE.

# Comparison to the original ArabTools

Example: Simple semaphore in Java (standard ArabTools):
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
In C++ with openArabTools:

(NOTE: Other namespaces may be used: OpenArabTools = ArabTools = oAT = AT)

```cpp
#include "OpenArabTools.hpp"

int main() {
	OpenArabTools::init();
	OpenArabTools::Semaphore s;
	s.showWindowAndRun();
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
}
```

# openArabTools - differences
- written in C++ as supposed to Java
- uses OpenGL 4
- has slightly different syntax (while still retaining the methods and camelCase)
- provides more utility functions and classes
- compiles directly to an .exe file

# Accessing the internal API
...is not recommended, but possible nonetheless.

Use it only if you want to extend the functionality of oAT.
Everything from the internal API (which can be accessed without nuking the entire library) is in the ArabTools::Internal namespace.

Documentation for the internal API: (TODO: add documentation once completed)

# License
Copyright (c) 2023-2024 Martin/MegapolisPlayer and contributors.

Licensed under CC-BY 4.0.

Full legal text [here](https://creativecommons.org/licenses/by/4.0/)

https://github.com/MegapolisPlayer/openArabTools

### Original Author of ArabTools

Based on Ing. Daniel Kahoun's ArabTools Library.

Copyright (c) 2014-2020 Ing. Daniel Kahoun

All rights reserved.

https://www.it8.cz/pages/o-nas/