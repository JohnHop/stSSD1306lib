/**
	****************************************************************************
	* @brief		Definitions for ssd1306 display driver
	****************************************************************************
*/

#ifndef __SSD1306_H
#define __SSD1306_H		//Define to prevent recursive inclusion

#include "main.h"

/*	@brief	SSD1306 Configuration Structure definition	
 */
typedef struct SSD1306_HandleTypeDef {
  uint8_t	slave_address;			//0x3C (usually) or 0x3D according to SA0
  uint8_t	height_resolution;		//usually 32 or 64
  I2C_HandleTypeDef 	*i2cHandle; //I2C handle initialized by user
} SSD1306_HandleTypeDef;

/* Exported constants ------------------------------------------------------- */
/* Low level defines */
#define SSD1306_CONTROLBYTE_COMMAND		0x00
#define SSD1306_CONTROLBYTE_DATA		0x40

/* 1. Fundamental Command table */
#define SSD1306_SET_CONTRAST_CONTROL			0x81
#define SSD1306_ENTIRE_DISPLAY_ON_FOLLOW_RAM	0xA4
#define SSD1306_ENTIRE_DISPLAY_ON_IGNORE_RAM	0xA5
#define SSD1306_SET_NORMAL_DISPLAY				0xA6
#define SSD1306_SET_INVERSE_DISPLAY				0xA7
#define SSD1306_SET_DISPLAY_ON					0xAF
#define SSD1306_SET_DISPLAY_OFF					0xAE

/* 3. Addressing Setting Command Table */
#define SSD1306_SET_PAGE_ADDRESS_FOR_PAGE_ADDRESS_MODE	0xB0
#define SSD1306_SET_LOWER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESS_MODE	0x00
#define SSD1306_SET_HIGHER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESS_MODE	0x10

/* 4. Hardware Configuration (Panel resolution & layout related) Command Table */
#define SSD1306_SET_DISPLAY_START_LINE			0x40
#define SSD1306_SET_SEGMENT_REMAP_RESET			0xA0
#define SSD1306_SET_SEGMENT_REMAP_SET			0xA1
#define SSD1306_SET_MULTIPLEX_RATIO				0xA8
#define SSD1306_SET_COM_OUTPUT_SCAN_DIR_NORMAL	0xC0
#define SSD1306_SET_COM_OUTPUT_SCAN_DIR_REMAP	0xC8
#define SSD1306_SET_DISPLAY_OFFSET				0xD3
#define SSD1306_SET_COM_PINS_HARDWARE_CONF		0xDA

/* 5. Timing & Driving Scheme Setting Command Table */
#define SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RO_FREQ	0xD5
#define SSD1306_SET_PRECHANGE_PERIOD				0xD9
#define SSD1306_SET_VCOMH_DESELECT_LEVEL			0xDB

/* Other */
#define SSD1306_CHARGE_PUMP_SETTING		0x8D
#define SSD1306_CHARGE_PUMP_DISABLE		0x10
#define SSD1306_CHARGE_PUMP_ENABLE		0x14

/* Exported functions ------------------------------------------------------- */
/* Low level functions */
void ssd1306_send_command(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_send_data(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_send_multiple_data(SSD1306_HandleTypeDef*, uint8_t*, const uint8_t);
void ssd1306_send_multiple_commands(SSD1306_HandleTypeDef*, uint8_t*, const uint8_t);

/* High level functions */
void ssd1306_Init(SSD1306_HandleTypeDef*, uint8_t, uint8_t, I2C_HandleTypeDef*);
void ssd1306_clear_screen(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_cursor_position(SSD1306_HandleTypeDef*, uint8_t, uint8_t);
void ssd1306_write_char(SSD1306_HandleTypeDef*, const char);
void ssd1306_write_string(SSD1306_HandleTypeDef*, const char*);

/* Mid level functions */
/* 1. Fundamental Command table */
void ssd1306_set_contrast_control(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_entire_display_on(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_normal_inverse_display(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_display_on(SSD1306_HandleTypeDef*);
void ssd1306_set_display_off(SSD1306_HandleTypeDef*);

/* 3. Addressing Setting Command Table */
void ssd1306_set_lower_column_start_address_for_page_addressing_mode(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_higher_column_start_address_for_page_addressing_mode(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_page_start_address_for_page_addressing_mode(SSD1306_HandleTypeDef*, uint8_t);

/* 4. Hardware Configuration (Panel resolution & layout related) Command Table */
void ssd1306_set_display_start_line(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_segment_remap(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_multiplex_ratio(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_com_output_scan_direction(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_display_offset(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_com_pins_hardware_configuration(SSD1306_HandleTypeDef*, uint8_t);
									
/* 5. Timing & Driving Scheme Setting Command Table */
void ssd1306_display_clock_divide_ro_frequency(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_prechange_period(SSD1306_HandleTypeDef*, uint8_t);
void ssd1306_set_vcomh_deselect_level(SSD1306_HandleTypeDef*, uint8_t);

/* Other */
void ssd1306_charge_pump_setting(SSD1306_HandleTypeDef*, uint8_t);

#endif