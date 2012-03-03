/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2011 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef CH_COMMON_H
#define CH_COMMON_H

#include <glib.h>
#include <gusb.h>
#include <colord.h>

/* device constants */
#define	CH_USB_VID				0x04d8
#define	CH_USB_PID				0xf8da
#define	CH_USB_CONFIG				0x0001
#define	CH_USB_INTERFACE			0x0000
#define	CH_USB_HID_EP				0x0001
#define	CH_USB_HID_EP_IN			(CH_USB_HID_EP | 0x80)
#define	CH_USB_HID_EP_OUT			(CH_USB_HID_EP | 0x00)
#define	CH_USB_HID_EP_SIZE			64

/* constants for ownership tags */
#define CH_OWNER_LENGTH_MAX			60

/**
 * CH_CMD_GET_COLOR_SELECT:
 *
 * Get the color select state.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][1:color_select]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_COLOR_SELECT			0x01

/**
 * CH_CMD_SET_COLOR_SELECT:
 *
 * Set the color select state.
 *
 * IN:  [1:cmd][1:color_select]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_COLOR_SELECT			0x02

/**
 * CH_CMD_GET_MULTIPLIER:
 *
 * Gets the multiplier value.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][1:multiplier_value]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_MULTIPLIER			0x03

/**
 * CH_CMD_SET_MULTIPLIER:
 *
 * Sets the multiplier value.
 *
 * IN:  [1:cmd][1:multiplier_value]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_MULTIPLIER			0x04

/**
 * CH_CMD_GET_INTEGRAL_TIME:
 *
 * Gets the integral time.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:integral_time]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_INTEGRAL_TIME		0x05

/**
 * CH_CMD_SET_INTEGRAL_TIME:
 *
 * Sets the integral time.
 *
 * IN:  [1:cmd][2:integral_time]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_INTEGRAL_TIME		0x06

/**
 * CH_CMD_GET_FIRMWARE_VERSION:
 *
 * Gets the firmware version.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:major][2:minor][2:micro]
 *
 * This command is available in bootloader and firmware mode.
 **/
#define	CH_CMD_GET_FIRMWARE_VERSION		0x07

/**
 * CH_CMD_GET_CALIBRATION:
 *
 * Gets the calibration matrix. The description does not have to be NULL
 * terminated.
 *
 * @types is a bitmask which corresponds to:
 *
 * bit:
 *  0     Can be used with LCD panels
 *  1     Can be used with CRT monitors
 *  2     Can be used with projectors
 *  3     Can be used with LED panels
 *  4-7   Reserved for future use
 *
 * IN:  [1:cmd][2:index]
 * OUT: [1:retval][1:cmd][2*9:matrix_value][1:types][23:description]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_CALIBRATION			0x09

/**
 * CH_CMD_SET_CALIBRATION:
 *
 * Sets the calibration matrix.
 *
 * IN:  [1:cmd][2:index][4*9:matrix_value][1:types][23:description]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_CALIBRATION			0x0a

/**
 * CH_CMD_GET_SERIAL_NUMBER:
 *
 * Gets the device serial number.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][4:serial_number]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_SERIAL_NUMBER		0x0b

/**
 * CH_CMD_SET_SERIAL_NUMBER:
 *
 * Sets the device serial number.
 *
 * IN:  [1:cmd][4:serial_number]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_SERIAL_NUMBER		0x0c

/**
 * CH_CMD_GET_LEDS:
 *
 * Get the LED state.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][1:led_state]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_LEDS				0x0d

/**
 * CH_CMD_SET_LEDS:
 *
 * Set the LED state. Using a @repeat value of anything other than
 * 0 will block the processor for the duration of the command.
 *
 * If @repeat is not 0, then the LEDs are reset to all off at the end
 * of the sequence.
 *
 * IN:  [1:cmd][1:led_state][1:repeat][1:on-time][1:off-time]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_LEDS				0x0e

/**
 * CH_CMD_GET_DARK_OFFSETS:
 *
 * Get the dark offsets.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:red][2:green][2:blue]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_DARK_OFFSETS			0x0f

/**
 * CH_CMD_SET_DARK_OFFSETS:
 *
 * Set the dark offsets.
 *
 * IN:  [1:cmd][2:red][2:green][2:blue]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_DARK_OFFSETS			0x10

/**
 * CH_CMD_GET_OWNER_NAME:
 *
 * Get User's Name
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][60:owner-name]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_OWNER_NAME			0x11

/**
 * CH_CMD_SET_OWNER_NAME:
 *
 * Set User's Name
 *
 * IN:  [1:cmd][60:owner-name]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_OWNER_NAME			0x12

/**
 * CH_CMD_GET_OWNER_EMAIL:
 *
 * Get User's Email Address
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][60:owner-email]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_OWNER_EMAIL			0x13

/**
 * CH_CMD_SET_OWNER_NAME:
 *
 * Set User's Email Address
 *
 * IN:  [1:cmd][60:owner-email]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_OWNER_EMAIL			0x14

/**
 * CH_CMD_WRITE_EEPROM:
 *
 * Write values to EEPROM.
 *
 * IN:  [1:cmd][8:eeprom_magic]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_WRITE_EEPROM			0x20

/**
 * CH_CMD_TAKE_READING_RAW:
 *
 * Take a raw reading.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:count]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_TAKE_READING_RAW			0x21

/**
 * CH_CMD_TAKE_READINGS:
 *
 * Take a reading taking into account just dark offsets.
 * All of @red, @green and @blue are _signed_ values.
 *
 * This command is useful if you want to do an ambient reading.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:red][2:green][2:blue]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_TAKE_READINGS			0x22

/**
 * CH_CMD_TAKE_READING_XYZ:
 *
 * Take a reading taking into account:
 *  1. dark offsets
 *  2. the calibration matrix
 *
 * If the calibration index > %CH_CALIBRATION_MAX then the calibration
 * map is used to find the default calibration index to use.
 *
 * IN:  [1:cmd][2:calibration-index]
 * OUT: [1:retval][1:cmd][4:red][4:green][4:blue]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_TAKE_READING_XYZ			0x23

/**
 * CH_CMD_RESET:
 *
 * Reset the processor.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd] (but with success the device will disconnect)
 *
 * This command is available in bootloader and firmware mode.
 **/
#define	CH_CMD_RESET				0x24

/**
 * CH_CMD_READ_FLASH:
 *
 * Read in raw data from the flash memory.
 *
 * IN:  [1:cmd][2:address][1:length]
 * OUT: [1:retval][1:cmd][1:checksum][1-60:data]
 *
 * This command is only available in bootloader mode.
 **/
#define	CH_CMD_READ_FLASH			0x25

/**
 * CH_CMD_ERASE_FLASH:
 *
 * Erases flash memory before a write is done.
 * Erasing flash can only be done in 1k byte chunks and should be
 * aligned to 1k.
 *
 * IN:  [1:cmd][2:address][2:length]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in bootloader mode.
 **/
#define	CH_CMD_ERASE_FLASH			0x29

/**
 * CH_CMD_WRITE_FLASH:
 *
 * Write raw data to the flash memory. You can only write aligned to
 * a 32 byte boundary, and you must flush any incomplete 64 byte block.
 *
 * IN:  [1:cmd][2:address][1:length][1:checksum][1-32:data]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in bootloader mode.
 **/
#define	CH_CMD_WRITE_FLASH			0x26

/**
 * CH_CMD_BOOT_FLASH:
 *
 * Boot into to the flash memory.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in bootloader mode.
 **/
#define	CH_CMD_BOOT_FLASH			0x27

/**
 * CH_CMD_SET_FLASH_SUCCESS:
 *
 * Sets the result of the firmware flashing. The idea of this command
 * is that the flashing interaction is thus:
 *
 * 1.	Reset()			device goes to bootloader mode
 * 2.	SetFlashSuccess(FALSE)
 * 3.	WriteFlash($data)
 * 4.	ReadFlash($data)	to verify
 * 5.	BootFlash()		switch to program mode
 * 6.	SetFlashSuccess(TRUE)
 *
 * The idea is that we only set the success FALSE from the bootoloader
 * to indicate that on booting we should not boot into the program.
 * We can only set the success true from the *new* program code so as
 * to verify that the new program boots, and can accept HID commands.
 *
 * IN:  [1:cmd][1:success]
 * OUT: [1:retval][1:cmd]
 *
 * This command is available in bootloader and firmware mode, although
 * different values of @success are permitted in each.
 **/
#define	CH_CMD_SET_FLASH_SUCCESS		0x28

/**
 * CH_CMD_GET_PRE_SCALE:
 *
 * Get the pre XYZ scaling constant.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:scale]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_PRE_SCALE			0x2c

/**
 * CH_CMD_SET_PRE_SCALE:
 *
 * Set the pre XYZ scaling constant.
 *
 * IN:  [1:cmd][2:scale]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_PRE_SCALE			0x2d

/**
 * CH_CMD_GET_POST_SCALE:
 *
 * Get the post XYZ scaling constant.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:scale]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_POST_SCALE			0x2a

/**
 * CH_CMD_SET_POST_SCALE:
 *
 * Set the post XYZ scaling constant.
 *
 * IN:  [1:cmd][2:scale]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_POST_SCALE			0x2b

/**
 * CH_CMD_GET_CALIBRATION_MAP:
 *
 * Get the mappings from default calibration type to calibration
 * indexes.
 *
 * The calibration types are as follows:
 * LCD		= 0
 * CRT		= 1
 * Projector	= 2
 * LED		= 3
 * Custom1	= 4
 * Custom2	= 5
 *
 * In the future CustomX may be renamed to another display technology,
 * e.g. e-ink.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][6*2:types]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_GET_CALIBRATION_MAP		0x2e

/**
 * CH_CMD_SET_CALIBRATION_MAP:
 *
 * Set the calibration type to index map.
 *
 * IN:  [1:cmd][6*2:types]
 * OUT: [1:retval][1:cmd]
 *
 * This command is only available in firmware mode.
 **/
#define	CH_CMD_SET_CALIBRATION_MAP		0x2f

/**
 * CH_CMD_GET_HARDWARE_VERSION:
 *
 * Get the hardware version.
 *
 * The hardware versions are as follows:
 * 0x00		= Pre-production hardware
 * 0x01		= First generation hardware
 * 0x02-0x0f	= Reserved for future use
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][1:hw_version]
 *
 * This command is available in bootloader and firmware mode.
 **/
#define	CH_CMD_GET_HARDWARE_VERSION		0x30

/**
 * CH_CMD_TAKE_READING_ARRAY:
 *
 * Takes 30 raw samples and returns them in an array.
 *
 * This command can be used to find the optimum delay between patches
 * by showing a black sample area, then white, and then using this
 * command to find out how long the actual hardware delay is.
 *
 * It can also be used to find out how stable the device or output is
 * over a small amount of time, typically ~2.5 seconds for the maximum
 * integral time.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][30:reading_array]
 *
 * This command is available in firmware mode.
 **/
#define	CH_CMD_TAKE_READING_ARRAY		0x31

/**
 * CH_CMD_SET_PCB_ERRATA:
 *
 * Sets the board errata value. Board errata is used to correct swapped
 * LEDs and any future problems discovered that only affect some batches
 * of hardware version 1.
 *
 * The errata bitmask is as follows:
 * 0x00		= No errata for this PCB
 * 0x01		= Leds are swapped
 * 0x02-0xffff	= Reserved for future use
 *
 * IN:  [1:cmd][2:pcb_errata]
 * OUT: [1:retval][1:cmd]
 *
 * This command is available in firmware mode.
 **/
#define	CH_CMD_SET_PCB_ERRATA			0x32

/**
 * CH_CMD_GET_PCB_ERRATA:
 *
 * Gets the board errata value.
 *
 * IN:  [1:cmd]
 * OUT: [1:retval][1:cmd][2:pcb_errata]
 *
 * This command is available in firmware mode.
 **/
#define	CH_CMD_GET_PCB_ERRATA			0x33

/* secret code */
#define	CH_WRITE_EEPROM_MAGIC			"Un1c0rn2"

/* input and output buffer offsets */
#define	CH_BUFFER_INPUT_CMD			0x00
#define	CH_BUFFER_INPUT_DATA			0x01
#define	CH_BUFFER_OUTPUT_RETVAL			0x00
#define	CH_BUFFER_OUTPUT_CMD			0x01
#define	CH_BUFFER_OUTPUT_DATA			0x02

/* where the custom firmware is stored */
#define CH_EEPROM_ADDR_RUNCODE			0x4000

/* although each calibration can be stored in 60 bytes,
 * we use a full 64 byte block */
#define	CH_CALIBRATION_MAX			64	/* so finishes at device params */
#define	CH_CALIBRATION_DESCRIPTION_LEN		23	/* 60 - (9*4) - 1 */

/* the supported calibration types bitfield */
#define	CH_CALIBRATION_TYPE_LCD			0x01
#define	CH_CALIBRATION_TYPE_CRT			0x02
#define	CH_CALIBRATION_TYPE_PROJECTOR		0x04
#define	CH_CALIBRATION_TYPE_LED			0x08
#define	CH_CALIBRATION_TYPE_ALL			0xff

/* approximate sample times */
#define CH_INTEGRAL_TIME_VALUE_5MS		0x0300
#define CH_INTEGRAL_TIME_VALUE_50MS		0x1f00
#define CH_INTEGRAL_TIME_VALUE_100MS		0x3a00
#define CH_INTEGRAL_TIME_VALUE_200MS		0x7500
#define CH_INTEGRAL_TIME_VALUE_MAX		0xffff

/* flash constants */
#define	CH_FLASH_ERASE_BLOCK_SIZE		0x400	/* 1024 */
#define	CH_FLASH_WRITE_BLOCK_SIZE		0x040	/* 64 */
#define	CH_FLASH_TRANSFER_BLOCK_SIZE		0x020	/* 32 */
#define	CH_FLASH_RECONNECT_TIMEOUT		2500	/* ms */

/* calibration remapping contants */
#define	CH_CALIBRATION_INDEX_LCD		(CH_CALIBRATION_MAX + 0)
#define	CH_CALIBRATION_INDEX_CRT		(CH_CALIBRATION_MAX + 1)
#define	CH_CALIBRATION_INDEX_PROJECTOR		(CH_CALIBRATION_MAX + 2)
#define	CH_CALIBRATION_INDEX_LED		(CH_CALIBRATION_MAX + 3)

/* which color to select */
typedef enum {
	CH_COLOR_SELECT_RED,
	CH_COLOR_SELECT_WHITE,
	CH_COLOR_SELECT_BLUE,
	CH_COLOR_SELECT_GREEN
} ChColorSelect;

/* Led colors: possible bitfield values */
typedef enum {
	CH_STATUS_LED_GREEN	= 1 << 0,
	CH_STATUS_LED_RED	= 1 << 1
} ChStatusLed;

/* what frequency divider to use */
typedef enum {
	CH_FREQ_SCALE_0,
	CH_FREQ_SCALE_20,
	CH_FREQ_SCALE_2,
	CH_FREQ_SCALE_100
} ChFreqScale;

/* fatal error morse code */
typedef enum {
	CH_ERROR_NONE,
	CH_ERROR_UNKNOWN_CMD,
	CH_ERROR_WRONG_UNLOCK_CODE,
	CH_ERROR_NOT_IMPLEMENTED,
	CH_ERROR_UNDERFLOW_SENSOR,
	CH_ERROR_NO_SERIAL,
	CH_ERROR_WATCHDOG,
	CH_ERROR_INVALID_ADDRESS,
	CH_ERROR_INVALID_LENGTH,
	CH_ERROR_INVALID_CHECKSUM,
	CH_ERROR_INVALID_VALUE,
	CH_ERROR_UNKNOWN_CMD_FOR_BOOTLOADER,
	CH_ERROR_NO_CALIBRATION,
	CH_ERROR_OVERFLOW_MULTIPLY,
	CH_ERROR_OVERFLOW_ADDITION,
	CH_ERROR_OVERFLOW_SENSOR,
	CH_ERROR_OVERFLOW_STACK,
	CH_ERROR_DEVICE_DEACTIVATED,
	CH_ERROR_LAST
} ChError;

/* any problems with the PCB */
typedef enum {
	CH_PCB_ERRATA_NONE		= 0,
	CH_PCB_ERRATA_SWAPPED_LEDS	= 1 << 0,
	CH_PCB_ERRATA_LAST		= 1 << 1
} ChPcbErrata;

/* prototypes */
const gchar	*ch_strerror			(ChError	 error_enum);
const gchar	*ch_command_to_string		(guint8		 cmd);
const gchar	*ch_multiplier_to_string	(ChFreqScale	 multiplier);
const gchar	*ch_color_select_to_string	(ChColorSelect	 color_select);

void		ch_device_write_command_async	(GUsbDevice	*device,
						 guint8		 cmd,
						 const guint8	*buffer_in,
						 gsize		 buffer_in_len,
						 guint8		*buffer_out,
						 gsize		 buffer_out_len,
						 GCancellable	*cancellable,
						 GAsyncReadyCallback callback,
						 gpointer	 user_data);
gboolean	 ch_device_write_command_finish	(GUsbDevice	*device,
						 GAsyncResult	*res,
						 GError		**error);
gboolean	ch_device_write_command		(GUsbDevice	*device,
						 guint8		 cmd,
						 const guint8	*buffer_in,
						 gsize		 buffer_in_len,
						 guint8		*buffer_out,
						 gsize		 buffer_out_len,
						 GCancellable	*cancellable,
						 GError		**error);

/* command utility functions */
gboolean	 ch_device_cmd_get_color_select	(GUsbDevice	*device,
						 ChColorSelect	*color_select,
						 GError		**error);
gboolean	 ch_device_cmd_get_hardware_version	(GUsbDevice	*device,
						 guint8		*hw_version,
						 GError		**error);
gboolean	 ch_device_cmd_set_color_select	(GUsbDevice	*device,
						 ChColorSelect	 color_select,
						 GError		**error);
gboolean	 ch_device_cmd_get_multiplier	(GUsbDevice	*device,
						 ChFreqScale	*multiplier,
						 GError		**error);
gboolean	 ch_device_cmd_set_multiplier	(GUsbDevice	*device,
						 ChFreqScale	 multiplier,
						 GError		**error);
gboolean	 ch_device_cmd_get_integral_time (GUsbDevice	*device,
						 guint16	*integral_time,
						 GError		**error);
gboolean	 ch_device_cmd_set_integral_time (GUsbDevice	*device,
						 guint16	 integral_time,
						 GError		**error);
gboolean	 ch_device_cmd_get_calibration_map(GUsbDevice	*device,
						 guint16	*calibration_map,
						 GError		**error);
gboolean	 ch_device_cmd_set_calibration_map (GUsbDevice	*device,
						 guint16	*calibration_map,
						 GError		**error);
gboolean	 ch_device_cmd_get_firmware_ver	(GUsbDevice	*device,
						 guint16	*major,
						 guint16	*minor,
						 guint16	*micro,
						 GError		**error);
gboolean	 ch_device_cmd_get_calibration	(GUsbDevice	*device,
						 guint16	 calibration_index,
						 CdMat3x3	*calibration,
						 guint8		*types,
						 gchar		*description,
						 GError		**error);
gboolean	 ch_device_cmd_set_calibration	(GUsbDevice	*device,
						 guint16	 calibration_index,
						 const CdMat3x3	*calibration,
						 guint8		 types,
						 const gchar	*description,
						 GError		**error);
gboolean	 ch_device_cmd_set_calibration_ccmx (GUsbDevice	*device,
						 guint16	 calibration_index,
						 const gchar	*filename,
						 GError		**error);
gboolean	 ch_device_cmd_clear_calibration (GUsbDevice	*device,
						 guint16	 calibration_index,
						 GError		**error);
gboolean	 ch_device_cmd_get_pre_scale	(GUsbDevice	*device,
						 gdouble	*pre_scale,
						 GError		**error);
gboolean	 ch_device_cmd_set_pre_scale	(GUsbDevice	*device,
						 gdouble	 pre_scale,
						 GError		**error);
gboolean	 ch_device_cmd_get_post_scale	(GUsbDevice	*device,
						 gdouble	*post_scale,
						 GError		**error);
gboolean	 ch_device_cmd_set_post_scale	(GUsbDevice	*device,
						 gdouble	 post_scale,
						 GError		**error);
gboolean	 ch_device_cmd_get_serial_number (GUsbDevice	*device,
						 guint32	*serial_number,
						 GError		**error);
gboolean	 ch_device_cmd_set_serial_number (GUsbDevice	*device,
						 guint32	 serial_number,
						 GError		**error);
gboolean	 ch_device_cmd_get_leds		(GUsbDevice	*device,
						 guint8		*leds,
						 GError		**error);
gboolean	 ch_device_cmd_set_leds		(GUsbDevice	*device,
						 guint8		 leds,
						 guint8		 repeat,
						 guint8		 on_time,
						 guint8		 off_time,
						 GError		**error);
gboolean	 ch_device_cmd_get_pcb_errata	(GUsbDevice	*device,
						 guint16	*pcb_errata,
						 GError		**error);
gboolean	 ch_device_cmd_set_pcb_errata	(GUsbDevice	*device,
						 guint16	 pcb_errata,
						 GError		**error);
gboolean	 ch_device_cmd_get_dark_offsets	(GUsbDevice	*device,
						 CdColorRGB	*value,
						 GError		**error);
gboolean	 ch_device_cmd_set_dark_offsets	(GUsbDevice	*device,
						 CdColorRGB	*value,
						 GError		**error);
gboolean	 ch_device_cmd_write_eeprom	(GUsbDevice	*device,
						 const gchar	*magic,
						 GError		**error);
gboolean	 ch_device_cmd_take_reading_raw	(GUsbDevice	*device,
						 guint16	*take_reading,
						 GError		**error);
gboolean	 ch_device_cmd_take_readings	(GUsbDevice	*device,
						 CdColorRGB	*value,
						 GError		**error);
gboolean	 ch_device_cmd_take_readings_xyz (GUsbDevice	*device,
						 guint16	 calibration_index,
						 CdColorXYZ	*value,
						 GError		**error);
gboolean	 ch_device_cmd_reset		(GUsbDevice	*device,
						 GError		**error);
gboolean	 ch_device_cmd_boot_flash	(GUsbDevice	*device,
						 GError		**error);
gboolean	 ch_device_cmd_set_flash_success (GUsbDevice	*device,
						 guint8		 value,
						 GError		**error);
gboolean	 ch_device_cmd_write_flash	(GUsbDevice	*device,
						guint16		 address,
						guint8		*data,
						gsize		 len,
						GError		**error);
gboolean	 ch_device_cmd_read_flash	(GUsbDevice	*device,
						guint16		 address,
						guint8		*data,
						gsize		 len,
						GError		**error);
gboolean	 ch_device_cmd_erase_flash	(GUsbDevice	*device,
						guint16		 address,
						gsize		 len,
						GError		**error);
gboolean	 ch_device_cmd_set_owner_name	(GUsbDevice	*device,
						 const gchar	*name,
						 GError	 	**error);
gboolean	 ch_device_cmd_get_owner_name	(GUsbDevice	*device,
						 gchar		*name,
						 GError	 	**error);
gboolean	 ch_device_cmd_set_owner_email	(GUsbDevice	*device,
						 const gchar	*email,
						 GError	 	**error);
gboolean	 ch_device_cmd_get_owner_email	(GUsbDevice	*device,
						 gchar		*email,
						 GError	 	**error);
gboolean	 ch_device_cmd_take_reading_array (GUsbDevice	*device,
						 guint8		*reading_array,
						 GError	 	**error);

#endif
