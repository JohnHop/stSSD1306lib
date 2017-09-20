# stSSD1306lib

## Description
This is a simple library for ST MCU's in order to write characters on a SSD1306 display.<br>
I created this library just to learn how SSD1306 controller works and eventually to use it for future projects. It is designed to be easy to undestand and modify as you want.<br>
Actually you can only write 7-bit characters. You cannot draw single pixels.<br>
Support is limited only to a subset of SSD1306 functionalities:

- Fundamental commands
- Only page addressing mode (with scrollig support)
- Hardware Configuration (needed for initialization)
- Timing & Driving Scheme Setting (also needed for initialization)
	
Sourcecode should be easy to undestand. This limited function set is enough to write characters and for scrolling.

## How to use the library
You need the HAL driver in order to use the library. Please refer to you board documentation for how to create a new project with you editor.<br>
I use a STM32F3 EVAL board with IAR Embedded Workbench IDE.

### Installation
For IAR, just copy `/Src` and `/Inc` inside the same directories of you project.
When open a workspace, add to the directory User from the workspace all files inside Src directory.
In my case, the I2C handle does not work if I declare it only inside the main.c. You need to declare it also in main.h with **extern** keyword.<br>
Example:
	
```c
main.c:
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef i2c1Handle;

main.h:
/* Exported functions ------------------------------------------------------- */
extern I2C_HandleTypeDef i2c1Handle;
extern void Error_Handler(void);
```
Please allow VLA (Variable Length Arrays) from C/C++ Compiler options.<br>
If you want to improve the library, you may be interested to read 'How it works' section.

### Usage
After `HAL_Init()`, `SystemClock_Config()` and I2C configuration, declare a `SSD1306_HandleTypeDef` structure and initialize it with the function `ssd1306_Init()`. See `ssd1306.c` for function explanatory and also `SSD1306_HandleTypeDef` struct definition inside `ssd1306.h` for some hints.<br>
Use `ssd1306_write_string()` to write something and `ssd1306_set_cursor_position()` for scrolling. That's all.


## How it works
Library functions are assigned to three main layers.

<table>
<tr>
<td>Low layer functions</td>
</tr>
<tr>
<td>Mid layer functions</td>
</tr>
<tr>
<td>High layer functions</td>
</tr>
</table>

Low layer functions are used to communicate with the ssd1306 controller.<br>
Mid layer functions are usually mapped with the functionalities described at COMMAND TABLE section inside the datasheet.<br>
High layer functions combines Mid layer functions in order to show a better and simple interface of the library to the user.<br>
Usually, a single layer uses only functions declared in the layer above it.


I am sure that this library is not well optimized. I made it in order to learn how ssd1306 driver works and for fun. Code should be clear so you can easily edit in order to improve speed if you need optimizations.<br>
For example, `ssd1306_Init()` function maybe uses too many function calls. You can, instead, use a single `ssd1306_send_multiple_commands()` call to save time. Same for `ssd1306_write_string()` function. To undestand this you need to read the ssd1306 datasheet.<br>
I chose only I2C functions in blocking mode. I think that you can easily edit low layer functions in order to use interrupts and DMA.



