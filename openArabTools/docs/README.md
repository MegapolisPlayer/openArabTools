# Documentation

The documentation for openArabTools is contained in this directory.
This file contains a general overview and some code examples.
In order to access documentation for sections of oAT, check the README files in the folders.

- graphics/ - information for graphical tools
- types/ - LightColor and enums information
- utils/ - information about Utils namespace and other utilities
- internal/ - Internal documentation, not yet completed.

### Namespaces assigned to oAT
OpenArabTools, ArabTools, oAT, AT
This can be disabled with the `OPENARABTOOLS_NO_NAMESPACE_OVERRIDE` macro (leaves only OpenArabTools)

### Includes
OpenArabTools includes many headers from the C++ standard library.
If you are importing them on your own, you may disable oAT's imports with the `OPENARABTOOLS_NO_STANDARD_INCLUDE` macro.

# Code examples
### runConcurrently

```cpp
#include "OpenArabTools.hpp"

void Function(const ArabTools::uint8_t ThreadId, const ArabTools::uint64_t Id) {
	//do something
	return;
}

int main() {
	ArabTools::init();
	ArabTools::Utils::runConcurrently(100000, true, Function);
	ArabTools::terminate();
}
```

### Matrix

```cpp
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();

	ArabTools::Matrix m(7, 3); //make a 7x3 matrix

	//enable some lights
	m.setOn(0, 0);
	m.setOn(1, 1);
	m.setOn(2, 0);
	m.setOn(3, 1);
	m.setOn(4, 0);

	//we can set colors AFTER set on/off (but we also can set them before)
	m.setBackground(ArabTools::LIGHTCOLOREX_CESKEDRAHY_DARK_BLUE); //LIGHTCOLOREX enum
	m.setColor(ArabTools::LightColor((uint8_t)255, (uint8_t)255, (uint8_t)0)); //convert to uint8_t to trigger correct constructor
	m.setOffColor(ArabTools::LIGHTCOLOR_DARK_GRAY); //LIGHTCOLOR enum

	m.showWindowAndRun();

	ArabTools::terminate();
}
```

### Semaphore

```cpp
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	ArabTools::Semaphore s;
	s.showWindowAndRun();
	ArabTools::terminate();
}
```

### Dice

```cpp
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	ArabTools::Dice d(1, 2); //1 tile free space between dots, 2 tiles padding
	uint64_t Counter = 0;
	while(d.update()) {
		d.setValue(Counter % 10); //modulo 10, remainder
		if(!d.sleep(500)) { break; } //sleep for 500ms
		Counter++;
	}
	ArabTools::terminate();
}
```

### Crossing

```cpp
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();

	ArabTools::Crossing c;
	//We get the pointers to the semaphores: DO NOT DELETE THEM!
	ArabTools::CrossingSemaphoreAccessor* csa1 = c.getSemaphore(0);
	ArabTools::CrossingSemaphoreAccessor* csa2 = c.getSemaphore(1);
	ArabTools::CrossingSemaphoreAccessor* csa3 = c.getSemaphore(2);
	ArabTools::CrossingSemaphoreAccessor* csa4 = c.getSemaphore(3);

	//Semaphores have only red on as a default
	//The accessors have the same syntax as normal semaphores

	csa1->setRedOn();
	csa2->setYellowOn();
	csa3->setGreenOn();

	csa4->setRedOn();
	csa4->setYellowOn();
	csa4->setGreenOn();

	//running only AFTER semaphores set
	c.showWindowAndRun();

	ArabTools::terminate();
}
```

###	Crossing: loading from file

```cpp
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();

	//Parameter in constructor: filename of file to load, must be 30x30 text file
	ArabTools::Crossing c("crossing2.oat");

	//Rest same as previous example

	ArabTools::CrossingSemaphoreAccessor* csa1 = c.getSemaphore(0);
	ArabTools::CrossingSemaphoreAccessor* csa2 = c.getSemaphore(1);
	ArabTools::CrossingSemaphoreAccessor* csa3 = c.getSemaphore(2);
	ArabTools::CrossingSemaphoreAccessor* csa4 = c.getSemaphore(3);
	csa1->setRedOn();
	csa2->setYellowOn();
	csa3->setGreenOn();
	csa4->setRedOn();
	csa4->setYellowOn();
	csa4->setGreenOn();

	c.showWindowAndRun();

	ArabTools::terminate();
}
```

### Canvas

```cpp
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();

	ArabTools::Canvas c;

	ArabTools::Rectangle r;
	r.setColor(ArabTools::LIGHTCOLOR_RED);
	r.setPosition(50, 50);
	r.setWidth(100);
	r.setHeight(200);
	c.add(r);

	ArabTools::Circle c2;
	c2.setColor(ArabTools::LIGHTCOLOR_BLUE).setPosition(200, 200).setRadius(100);
	c.add(c2);

	c.showWindowAndRun();

	ArabTools::terminate();
}
```

### ScopedTimer

```cpp

void SomeBuggyFunction() {
	ArabTools::ScopedTimer st("Name");
	//something, something
}

```