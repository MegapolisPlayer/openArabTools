# Graphical documentation

All classes contain the following methods:

- `showWindow`: shows the window
- `hideWindow`: hides the window
- `setTitle`: sets the title of the window, takes a `std::string&` as a parameter
- `open`: returns if window is still open
- `update`: updates the window
- `run`: runs the window and block the main thread
- `showWindowAndRun`: shows the window and then runs it
- `sleep`: sleep on this window, takes a `uint64_t` as a parameter (how long to sleep for), returns whether the window is still open. Blocks the thread. 
- **Move and copy assignment operators (explicitly declared OR automatic)**

- **All classes are also both movable and copiable.**
- All methods are marked as `noexcept`
- All methods which don't affect the class are marked `const`

### Matrix
Basic class. Implements a matrix of lights of any size.
- Constructors:
  - Default, copy, move
  - Takes size of matrix as parameter (uint64_t x, uint64_t y) 
- Member functions:
  - `void setBackground(LightColor aColor)`
  - `void setBackground(uint64_t aId,LightColor& aColor)`
  - `void setBackground(uint64_t aColumn,uint64_t aRow,LightColor& aColor)`
	- Set the background of the whole matrix or of a specific light.
  - `void setColor(LightColor& aColor)`
  - `void setColor(uint64_t aId,LightColor& aColor)`
  - `void setColor(uint64_t aColumn,uint64_t aRow,LightColor& aColor)`
	- Set the "on/enabled" color of lights in the whole matrix or of a speicific light.
  - `void setOff()`
  - `void setOff(uint64_t aId)`
  - `void setOff(uint64_t aColumn,uint64_t aRow)`
	- Ddisable all lights or a specific light.
  - `void setOn()`
  - `void setOn(uint64_t aId)`
  - `void setOn(uint64_t aColumn,uint64_t aRow)`
	- Enable all lights or a specific light.
  - `void setOnOff(bool aOnOff)`
  - `void setOnOff(uint64_t aId,bool aOnOff)`
  - `void setOnOff(uint64_t aColumn,uint64_t aRow,bool aOnOff)`
	- Set the state of all lights or a specific light.
  - `LightColor getBackground()`
  - `LightColor getBackground(uint64_t aId)`
  - `LightColor getBackground(uint64_t aColumn,uint64_t aRow)`
	- Get the background color of a specific light, if no parameters are provided then of the top left one.
  - `LightColor getColor()`
  - `LightColor getColor(uint64_t aId)`
  - `LightColor getColor(uint64_t aColumn,uint64_t aRow)`
	- Get the "on" color of a specific light, if no parameters are provided then of the top left one.
  - `std::string getTitle()`
	- TGet the current window title.
  - `uint64_t getWidth()`
	- Gets the amount of **matrix lights** in the X direction.
  - `uint64_t getHeight()`
	- Gets the amount of **matrix lights** in the Y direction.
  - `uint64_t getSize()`
	- Gets the overall amount of **matrix lights**.
  - `bool isOff()`
  - `bool isOff(uint64_t aId)`
  - `bool isOff(uint64_t aColumn,uint64_t aRow)`
	- Get whether a specific light is off, if no parameters are provided then of the top left one.
  - `bool isOn()`
  - `bool isOn(uint64_t aId)`
  - `bool isOn(uint64_t aColumn,uint64_t aRow)`
	- Get whether a specific light is on, if no parameters are provided then of the top left one.
  - `void setOffColor(LightColor& aColor)`
  - `void setOffColor(uint64_t aId,LightColor& aColor)`
  - `void setOffColor(uint64_t aColumn,uint64_t aRow,LightColor& aColor)`
	- Set the "off/disabled" color of lights in the whole matrix or of a specific light.
  - `void setColorAlpha(float aAlpha)`
  - `void setColorAlpha(uint64_t aId,float aAlpha)`
  - `void setColorAlpha(uint64_t aColumn,uint64_t aRow,float aAlpha)`
	- Set the transparency of the "on/enabled" color of lights in the whole matrix or of a specific light.
  - `void setOffColorAlpha(float aAlpha)`
  - `void setOffColorAlpha(uint64_t aId,float aAlpha)`
  - `void setOffColorAlpha(uint64_t aColumn,uint64_t aRow,float aAlpha)`
	- Set the transparency of the "off/disabled" color of lights in the whole matrix or of a specific light.
  - `void setBackgroundAlpha(float aAlpha)`
  - `void setBackgroundAlpha(uint64_t aId,float aAlpha)`
  - `void setBackgroundAlpha(uint64_t aColumn,uint64_t aRow,float aAlpha)`
	- Set the transparency of the "off/disabled" color of lights in the whole matrix or of a specific light.
  - `void set(uint64_t aSizeX,uint64_t aSizeY)`
	- Initializes the matrix. (constructors call this method)
  - `void reset()`
	- Resets the matrix. It needs to be initialized again after this.
  - `void resizeMatrix(uint64_t aNewX,uint64_t aNewY)`
- Helper macros (pass them into the constructor):
  - `OPENARABTOOLS_MATRIX_SINGLE` - create a 1*1 matrix
  - `OPENARABTOOLS_MATRIX_VERTICAL(y)` - create a 1*y matrix
  - `OPENARABTOOLS_MATRIX_HORIZONTAL(x)` - create a 1*x matrix

### Semaphore
Implements a basic 3-light semaphore. May have a different orientation.
- Constructors:
  - Default
  - Takes orientation as parameter (`SemaphoreOrientation`)
- Member functions:
  - `void setRedOn()`
  - `void setYellowOn()`
  - `void setGreenOn()`
	- Enables a light
  - `void setRedOff()`
  - `void setYellowOff()`
  - `void setGreenOff()`
	- Disables a light
  - `void setRedOnOff(const bool aOnOff)`
  - `void setYellowOnOff(const bool aOnOff)`
  - `void setGreenOnOff(const bool aOnOff)`
	- Sets a state of the light
  - `std::string getTitle()`
	- Gets the window title
  - `bool isRedOn()`
  - `bool isYellowOn()`
  - `bool isGreenOn()`
	- Gets the state of a light
  - `void toggleRed()`
  - `void toggleYellow()`
  - `void toggleGreen()`
	- Toggles a light

### Dice
Implements a basic, 3x3, playing dice with values 0-9.
- Constructors:
  - Default
  - Takes space between dots as parameter (`uint64_t`)
  - Takes space between dots and amount of padding as parameters (`uint64_t`, `uint64_t`)
- Member functions:
  - `void setValue(const uint64_t aValue)`
	- Sets the value of the dice
  - `uint64_t getValue(const uint64_t aValue)`
	- Gets the current value of the dice
  - `void setBackground(const LightColor& aLC)`
	- Sets the background color of the dice
  - `void setColor(const LightColor& aLC)`
    - Sets the foregroud color of the dice
  - `void disableAll()`
	- Disables all points (sets value to 0)
  - `void enableAll()`
	- Enables all points (sets value to 9)

### Chessboard
Implements a basic of any size (8x8 is the default).
- Constructors:
  - Default
  - Takes size of chessboard as parameter
- Member functions:
  - `void put(const uint64_t aColumn, const uint64_t aRow, PieceColor aPiece)`
	- Puts a new piece on the board
  - `void remove(const uint64_t aColumn, const uint64_t aRow)`
	- Removes a piece from the board
  - `PieceColor get(const uint64_t aId)`
  - `PieceColor get(const uint64_t aColumn, const uint64_t aRow)`
	- Gets the color of the piece
  - `uint64_t getWidth()`
	- Get amount of square in the X direction
  - `uint64_t getHeight()`
	- Gets amount of squares in the Y direction
  - `uint64_t getSize()`
	- Gets amount of squares in chessboard

### Crossing
Implements a crossing of 2 roads with 4 traffic lights (Semaphores).
- Constructors:
  - Default
  - Takes in the name of the file with the graphical info as parameter (`std::string&`)
- Member functions:
  - `CrossingSemaphoreAccessor* const getSemaphore(const uint64_t aId)`
	- Gets an accessor for the provided semaphore. Use the SEMAPHORE_ID constants or provide a value between 0 and 3
  - `void showSemaphore(const uint64_t aId)`
	- Shows the selected semaphore
  - `void hideSemaphore(const uint64_t aId)`
	- Hides the seleced semaphore

### CrossingSemaphoreAccessor
An accessor to change a semaphore in a `Crossing` instance.
- Constructors:
  - Takes in pointer to `Crossing`  and id of said semaphor
	- WARNING: do not use this constructor, use `getSemaphore` in `Crossing` to get accessor
- Member functions:
  - `void setRedOn()`
  - `void setYellowOn()`
  - `void setGreenOn()`
	- Enables lights
  - `void setRedOff()`
  - `void setYellowOff()`
  - `void setGreenOff()`
	- Disable lights
  - `void setRedOnOff(const bool aOnOff)`
  - `void setYellowOnOff(const bool aOnOff)`
  - `void setGreenOnOff(const bool aOnOff)`
	- Sets the state of the lights
  - `bool isRedOn()`
  - `bool isYellowOn()`
  - `bool isGreenOn()`
	- Gets the the state of the light
  - `void toggleRed()`
  - `void toggleYellow()`
  - `void toggleGreen()`
	- Toggles light

### Canvas
Implements a Canvas, on which it is possible to draw filled-in shapes.
- Constructors:
  - Default, Move, Copy 
  - Takes in window title as parameter (`std::string& `)
  - Takes in window size and title as parameters (`uint64_t`, `uint64_t`, `std::string&`) 
- Member functions:
  - `uint64_t add(const Shape& aShape)`
	- Adds a new shape
  - `uint64_t updateShape(uint64_t aShapeId, const Shape& aNewData)`
	- Replaces an existing shape with new data
  - `void remove(uint64_t aShapeId)`
	- Removes a current shape
  - `void clear()`
	- Clears all shapes
  - `void setBackground(const LightColor& aLC)`
	- Sets the window background
  - `void paint()`
	- Same as `update`
  - `void set(uint64_t aWidth, uint64_t aHeight, const std::string& aTitle)`
	- Sets new data for Canvas
  - `void reset()`
	- Resets the canvas object

### Shape (and derivatives)
Base class of shape implements a shape drawable on `Canvas`
Derived classes: `Square`, `Circle`, `Rectangle`

Shape and all of its derived class contain the following methods:
- `setX`: (`uint64_t`) sets the X top-left position of the object
- `setY`: (`uint64_t`) sets the Y top-left position of the object
- `setPosition`: (`uint64_t, uint64_t`) sets both the X and Y position of the object
- `setColor`: (`const LightColor&`) sets the color of the object
- `resetColor`: (no parameters) reset the color
- `getX`: (no parameters) gets the current X position as a `uint64_t`
- `getY`: (no parameters) gets the current Y position as a `uint64_t`
- `getColor`: (no parameters) get the current color as a `LightColor`

- **Square**
  - `setWidth`: (`uint64_t`) sets the size of the square
  - `getWidth`: gets the size of the square as a `uint64_t`

- **Circle**
  - `setRadius`: (`uint64_t`) sets the radius of the circle
	- NOTE: the **diameter** is twice as large!
  - `getRadius`: gets the radius of the circle as a `uint64_t`

- **Rectangle**
  - `setWidth`: (`uint64_t`) sets the width of the rectangle
  - `setHeight`: (`uint64_t`) sets the height of the rectangle
  - `getWidth`: gets the width of the rectangle as a `uint64_t`
  - `getHeight`: gets the height of the rectangle as a `uint64_t`