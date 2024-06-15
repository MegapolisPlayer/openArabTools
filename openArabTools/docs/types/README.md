# Types, enums and structures of OpenArabTools

### LightColorD
Enum, contains all colors from the base OpenArabTools
- LIGHTCOLOR_BLACK
- LIGHTCOLOR_BLUE
- LIGHTCOLOR_CYAN
- LIGHTCOLOR_DARK_GRAY
- LIGHTCOLOR_GRAY
- LIGHTCOLOR_GREEN
- LIGHTCOLOR_CHESSBOARD_BLACK
- LIGHTCOLOR_CHESSBOARD_DARK
- LIGHTCOLOR_CHESSBOARD_LIGHT
- LIGHTCOLOR_CHESSBOARD_WHITE
- LIGHTCOLOR_LIGHT_GRAY
- LIGHTCOLOR_MAGENTA
- LIGHTCOLOR_ORANGE
- LIGHTCOLOR_PINK
- LIGHTCOLOR_RED
- LIGHTCOLOR_TRAFFIC_GREEN_OFF
- LIGHTCOLOR_TRAFFIC_GREEN_ON
- LIGHTCOLOR_TRAFFIC_RED_OFF
- LIGHTCOLOR_TRAFFIC_RED_ON
- LIGHTCOLOR_TRAFFIC_YELLOW_OFF
- LIGHTCOLOR_TRAFFIC_YELLOW_ON
- LIGHTCOLOR_WHITE
- LIGHTCOLOR_YELLOW

### LightColorEx
Enum, contains some additional colors
- LIGHTCOLOREX_DARK_GREEN
- LIGHTCOLOREX_DARKER_GREEN
- LIGHTCOLOREX_LIGHT_BLUE
- LIGHTCOLOREX_DARK_BLUE
- LIGHTCOLOREX_CESKEDRAHY_LIGHT_BLUE
- LIGHTCOLOREX_CESKEDRAHY_DARK_BLUE
- LIGHTCOLOREX_ERROR_COLOR

### LightColor
- Public member variables: *R, G, B* (RGB values for color in range 0-1)
- Constructors:
  - Default (no parameters)
  - Takes `LightColorD` as parameter
  - Takes `LightColorEx` as parameter
  - Takes `R, G, B` floats in range 0-1 as parameters
  - Takes `R, G, B` `uint8_t`s in range 0-255 as parameters
  - Copy constructor (takes `const LightColor&` as parameter)
- Member functions ("methods"):
  - `LightColor& Set(const LightColorD aColor) noexcept;`
	- Sets new color from `LightColorD` enum
  - `LightColor& Set(const LightColorEx aColor) noexcept;`
	- Sets new color from `LightColorEx` enum
  - `LightColor& RGB(const float aR, const float aG, const float aB) noexcept;`
	- Sets new color from `R, G, B` floats in range 0-1
  - `LightColor& RGB255(const uint8_t aR, const uint8_t aG, const uint8_t aB) noexcept;`
	- Sets new color from `R, G, B` `uint8_t`s in range 0-255
  - `LightColor& Darken() noexcept;`
	- Darkens the saved color
  - `LightColor& Lighten() noexcept;`
	- Lightens the saved color
  - Assignment operator, equality operator
  - Destructor