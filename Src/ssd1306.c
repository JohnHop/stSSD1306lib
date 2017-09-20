#include "ssd1306.h"

#include "fonts.h"

/*
================================================================================
							Low Level Functions
================================================================================
*/

/*	@brief	Send a single command byte to the ssd1306.
	@param1	A SSD1306 handle structure pointer
	@param2	A command constant
	@note	if I2C fails, Error_Handler function is called
**/
void ssd1306_send_command(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t command)
{
  if(HAL_I2C_Mem_Write(ssd1306Handle->i2cHandle, ssd1306Handle->slave_address<<1, SSD1306_CONTROLBYTE_COMMAND, 1, &command, 1, 100) != HAL_OK) {
	Error_Handler();
  }
}

/*	@brief	Send a single data byte to the ssd1306.
	@param1	A SSD1306 handle structure pointer
	@param2	A byte of data
	@note	if I2C fails, Error_Handler function is called
**/
void ssd1306_send_data(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t data)
{
  if(HAL_I2C_Mem_Write(ssd1306Handle->i2cHandle, ssd1306Handle->slave_address<<1, SSD1306_CONTROLBYTE_DATA, 1, &data, 1, 100) != HAL_OK) {
	Error_Handler();
  }
}

/*	@brief	Send multiple byte to the driver.
	@param1	A SSD1306 handle structure pointer
	@param2	A array of data
	@param3	Size of array
	@note	if I2C fails, Error_Handler function is called
**/
void ssd1306_send_multiple_data(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t *pData, const uint8_t size)
{
  uint8_t array[size*2];	//NOTE: please allow VLA in compiler settings
  
  for(uint16_t i = 0, j = 0; i < size*2; i+= 2, ++j) {
	array[i] = SSD1306_CONTROLBYTE_DATA;
	array[i+1] = pData[j];
  }
  
  if(HAL_I2C_Master_Transmit(ssd1306Handle->i2cHandle, ssd1306Handle->slave_address<<1, array, size*2, 100) != HAL_OK) {
	Error_Handler();
  }
}

/*	@brief	Send multiple byte to the driver.
	@param1	A SSD1306 handle structure pointer
	@param2	A array of data
	@param3	Size of array
	@note	if I2C fails, Error_Handler function is called
**/
void ssd1306_send_multiple_commands(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t *pData, const uint8_t size)
{
  uint8_t array[size*2];	//NOTE: please allow VLA in compiler settings
  
  for(uint16_t i = 0, j = 0; i < size*2; i+= 2, ++j) {
	array[i] = SSD1306_CONTROLBYTE_COMMAND;
	array[i+1] = pData[j];
  }
  
  if(HAL_I2C_Master_Transmit(ssd1306Handle->i2cHandle, ssd1306Handle->slave_address<<1, array, size*2, 100) != HAL_OK) {
	Error_Handler();
  }
}

/*
================================================================================
							Mid Level Functions
================================================================================
*/

/* 1. Fundamental Command Table ********************************************* */
/*	@param2	contrast level between 1 and 256. Reset is 0x7F
*/
void ssd1306_set_contrast_control(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t contrast_level)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_CONTRAST_CONTROL);
  ssd1306_send_command(ssd1306Handle, contrast_level); 
}

/*	@param2	Reset value is SSD1306_ENTIRE_DISPLAY_ON_FOLLOW_RAM
*/
void ssd1306_set_entire_display_on(SSD1306_HandleTypeDef *ssd1306Handle, const uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, arg);
}

/*	@param2	Reset value is SSD1306_SET_NORMAL_DISPLAY
*/
void ssd1306_set_normal_inverse_display(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, arg);
}

void ssd1306_set_display_on(SSD1306_HandleTypeDef *ssd1306Handle)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_DISPLAY_ON);
}

void ssd1306_set_display_off(SSD1306_HandleTypeDef *ssd1306Handle)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_DISPLAY_OFF);
}

/* 3. Addressing Setting Command Table ************************************** */
/*	@param2	max value for arg is 15 (0xF)
*/
void ssd1306_set_lower_column_start_address_for_page_addressing_mode(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_LOWER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESS_MODE+arg);
}

/*	@param2	max value for arg is 15 (0xF)
*/
void ssd1306_set_higher_column_start_address_for_page_addressing_mode(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_HIGHER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESS_MODE+arg);
}

/*	@param2	Page number according to height resolution.
	@note	Max value for arg is 7 for 64 bit display and 3 for 32bit display
*/
void ssd1306_set_page_start_address_for_page_addressing_mode(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_PAGE_ADDRESS_FOR_PAGE_ADDRESS_MODE+arg);
}

/* 4. Hardware Configuration (Panel resolution & layout related) Command Table */

/*	@param2	Reset value is SSD1306_SET_DISPLAY_START_LINE.
	@note	Max value for arg is 63
*/
void ssd1306_set_display_start_line(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_DISPLAY_START_LINE+arg);
}

/*	@param2	Reset value is SSD1306_SET_SEGMENT_REMAP_RESET
*/
void ssd1306_set_segment_remap(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
   ssd1306_send_command(ssd1306Handle, arg);
}

/*	@param2	Height - 1. For 32x128 display is 31.
*/
void ssd1306_set_multiplex_ratio(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_MULTIPLEX_RATIO);
  ssd1306_send_command(ssd1306Handle, arg);	 
}

/*	@param2	Reset value is SSD1306_SET_COM_OUTPUT_SCAN_DIR_NORMAL
*/
void ssd1306_set_com_output_scan_direction(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, arg);
}

/*	@param2	Reset value is 0. Allowed range is 0-63 (decimal)
*/
void ssd1306_set_display_offset(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_DISPLAY_OFFSET);
  ssd1306_send_command(ssd1306Handle, arg);
}

/*	@param2	Reset value is 0x12
*/
void ssd1306_set_com_pins_hardware_configuration(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_COM_PINS_HARDWARE_CONF);
  ssd1306_send_command(ssd1306Handle, arg);
}

/* 5. Timing & Driving Scheme Setting Command Table ************************* */
/*	@param2	Reset value is 0x12
*/
void ssd1306_display_clock_divide_ro_frequency(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RO_FREQ);
  ssd1306_send_command(ssd1306Handle, arg);
}

/*	@param2	Reset value is 0x80
*/
void ssd1306_set_prechange_period(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_PRECHANGE_PERIOD);
  ssd1306_send_command(ssd1306Handle, arg);
}

/*	@param2	? :(
*/
void ssd1306_set_vcomh_deselect_level(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_SET_VCOMH_DESELECT_LEVEL);
  ssd1306_send_command(ssd1306Handle, arg);
}

/* Other */
/*	@param2	SSD1306_CHARGE_PUMP_DISABLE or SSD1306_CHARGE_PUMP_ENABLE
*/
void ssd1306_charge_pump_setting(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_send_command(ssd1306Handle, SSD1306_CHARGE_PUMP_SETTING);
  ssd1306_send_command(ssd1306Handle, arg);
}

/*
================================================================================
							High Level Functions
================================================================================
*/

/*	@brief	Initialize the SSD1306 driver. Some functions differs according to display height resolution.
	@param1	A SSD1306 handle structure pointer
	@param2	Slave anddress constant between 0x3C and 0x3D
	@param3	height resolution constant. Usually 32 o 64
	@param4	Pointer to a I2C_HandleTypeDef structure
	@note	This sequence is base to a datasheeet usually referred as the ER-OLED0.91-1/ ER-OLED0.96-1
*/
void ssd1306_Init(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t slave_address, uint8_t height, I2C_HandleTypeDef* i2cHandle)
{
  ssd1306Handle->slave_address = slave_address;
  ssd1306Handle->height_resolution = height;
  ssd1306Handle->i2cHandle = i2cHandle;
  
  // Initialization sequence. Refer to ER-OLED0.91-1 Series Datasheet page 14
  ssd1306_set_display_off(ssd1306Handle);
  ssd1306_display_clock_divide_ro_frequency(ssd1306Handle, 0x80);
  ssd1306_set_multiplex_ratio(ssd1306Handle, ssd1306Handle->height_resolution == 32 ? 0x1F : 0x3F);
  ssd1306_set_display_offset(ssd1306Handle, 0x00);
  ssd1306_set_display_start_line(ssd1306Handle, 0x40);
  ssd1306_charge_pump_setting(ssd1306Handle, SSD1306_CHARGE_PUMP_ENABLE);
  ssd1306_set_segment_remap(ssd1306Handle, SSD1306_SET_SEGMENT_REMAP_SET);
  ssd1306_set_com_output_scan_direction(ssd1306Handle, SSD1306_SET_COM_OUTPUT_SCAN_DIR_REMAP);
  ssd1306_set_com_pins_hardware_configuration(ssd1306Handle, ssd1306Handle->height_resolution == 32 ? 0x02 : 0x12);
  ssd1306_set_contrast_control(ssd1306Handle, 0xCF);
  ssd1306_set_prechange_period(ssd1306Handle, 0xF1);
  ssd1306_set_vcomh_deselect_level(ssd1306Handle, 0x40);
  ssd1306_set_entire_display_on(ssd1306Handle, SSD1306_ENTIRE_DISPLAY_ON_FOLLOW_RAM);
  ssd1306_set_normal_inverse_display(ssd1306Handle, SSD1306_SET_NORMAL_DISPLAY);
  ssd1306_clear_screen(ssd1306Handle, 0x00);
  ssd1306_set_display_on(ssd1306Handle);
  
  //Post initialization
  ssd1306_set_page_start_address_for_page_addressing_mode(ssd1306Handle, 0);
  ssd1306_set_lower_column_start_address_for_page_addressing_mode(ssd1306Handle, 0);
  ssd1306_set_higher_column_start_address_for_page_addressing_mode(ssd1306Handle, 0);
}

/*	@param2	byte to fill the screen
*/
void ssd1306_clear_screen(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t arg)
{
  ssd1306_set_page_start_address_for_page_addressing_mode(ssd1306Handle, 0);
  ssd1306_set_lower_column_start_address_for_page_addressing_mode(ssd1306Handle, 0);
  ssd1306_set_higher_column_start_address_for_page_addressing_mode(ssd1306Handle, 0);
  
  for(uint8_t page = 0; page < (ssd1306Handle->height_resolution == 32 ? 4 : 8); ++page) {
	for(uint8_t col = 0; col < 128; ++col) {
	  ssd1306_send_data(ssd1306Handle, arg);
	}
	ssd1306_set_page_start_address_for_page_addressing_mode(ssd1306Handle, page+1);
  }
}

/*	@brief 	Set cursor position between page 0 and 3 (or 0 and 7), and one of the 21 horizontal positions.
	@param2	Line between 0 and 3
	@param3	Column between 0 and 127
	@note	Remember that a single character is 6 bit wide
*/
void ssd1306_set_cursor_position(SSD1306_HandleTypeDef *ssd1306Handle, uint8_t page, uint8_t pos)
{
  ssd1306_set_page_start_address_for_page_addressing_mode(ssd1306Handle, page);
  ssd1306_set_lower_column_start_address_for_page_addressing_mode(ssd1306Handle, pos&0x0F);
  ssd1306_set_higher_column_start_address_for_page_addressing_mode(ssd1306Handle, (pos&0xF0)>>4);
}

/*	@brief	Write an ASCII character. Support only 7-bit characters.
	@param2	A 7-bit character to write on screen
*/
void ssd1306_write_char(SSD1306_HandleTypeDef *ssd1306Handle, const char c)
{
  uint8_t *font = font_table[c-32];
  
  for(uint8_t i = 0; i < 6; ++i) {
	ssd1306_send_data(ssd1306Handle, font[i]);
  }
}

/*	@brief	Write a sequence of characters.
	@param2	Pointer to a string.
*/
void ssd1306_write_string(SSD1306_HandleTypeDef *ssd1306Handle, const char *str)
{
  while(*str) {
	ssd1306_write_char(ssd1306Handle, *(str++));
  }
}