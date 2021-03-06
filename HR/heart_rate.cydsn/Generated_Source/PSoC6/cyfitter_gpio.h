/*******************************************************************************
* File Name: cyfitter_gpio.h
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_GPIO_H
#define INCLUDED_CYFITTER_GPIO_H
#include "cy_device_headers.h"

/* LE */
#define LE_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define LE_0_INBUF_ENABLED 0u
#define LE_0_INIT_DRIVESTATE 1u
#define LE_0_INIT_MUXSEL 0u
#define LE_0_INPUT_SYNC 2u
#define LE_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define LE_0_NUM 5u
#define LE_0_PORT GPIO_PRT0
#define LE_0_SLEWRATE CY_GPIO_SLEW_FAST
#define LE_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define LE_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define LE_INBUF_ENABLED 0u
#define LE_INIT_DRIVESTATE 1u
#define LE_INIT_MUXSEL 0u
#define LE_INPUT_SYNC 2u
#define LE_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define LE_NUM 5u
#define LE_PORT GPIO_PRT0
#define LE_SLEWRATE CY_GPIO_SLEW_FAST
#define LE_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* OE */
#define OE_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define OE_0_INBUF_ENABLED 0u
#define OE_0_INIT_DRIVESTATE 1u
#define OE_0_INIT_MUXSEL 0u
#define OE_0_INPUT_SYNC 2u
#define OE_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define OE_0_NUM 2u
#define OE_0_PORT GPIO_PRT7
#define OE_0_SLEWRATE CY_GPIO_SLEW_FAST
#define OE_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define OE_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define OE_INBUF_ENABLED 0u
#define OE_INIT_DRIVESTATE 1u
#define OE_INIT_MUXSEL 0u
#define OE_INPUT_SYNC 2u
#define OE_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define OE_NUM 2u
#define OE_PORT GPIO_PRT7
#define OE_SLEWRATE CY_GPIO_SLEW_FAST
#define OE_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* AMP */
#define AMP_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define AMP_0_INBUF_ENABLED 0u
#define AMP_0_INIT_DRIVESTATE 1u
#define AMP_0_INIT_MUXSEL 5u
#define AMP_0_INPUT_SYNC 2u
#define AMP_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define AMP_0_NUM 5u
#define AMP_0_PORT GPIO_PRT5
#define AMP_0_SLEWRATE CY_GPIO_SLEW_FAST
#define AMP_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define AMP_DRIVEMODE CY_GPIO_DM_ANALOG
#define AMP_INBUF_ENABLED 0u
#define AMP_INIT_DRIVESTATE 1u
#define AMP_INIT_MUXSEL 5u
#define AMP_INPUT_SYNC 2u
#define AMP_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define AMP_NUM 5u
#define AMP_PORT GPIO_PRT5
#define AMP_SLEWRATE CY_GPIO_SLEW_FAST
#define AMP_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CLK */
#define CLK_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CLK_0_INBUF_ENABLED 0u
#define CLK_0_INIT_DRIVESTATE 1u
#define CLK_0_INIT_MUXSEL 0u
#define CLK_0_INPUT_SYNC 2u
#define CLK_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CLK_0_NUM 7u
#define CLK_0_PORT GPIO_PRT12
#define CLK_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CLK_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CLK_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CLK_INBUF_ENABLED 0u
#define CLK_INIT_DRIVESTATE 1u
#define CLK_INIT_MUXSEL 0u
#define CLK_INPUT_SYNC 2u
#define CLK_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CLK_NUM 7u
#define CLK_PORT GPIO_PRT12
#define CLK_SLEWRATE CY_GPIO_SLEW_FAST
#define CLK_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* SDI */
#define SDI_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define SDI_0_INBUF_ENABLED 0u
#define SDI_0_INIT_DRIVESTATE 1u
#define SDI_0_INIT_MUXSEL 0u
#define SDI_0_INPUT_SYNC 2u
#define SDI_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define SDI_0_NUM 6u
#define SDI_0_PORT GPIO_PRT12
#define SDI_0_SLEWRATE CY_GPIO_SLEW_FAST
#define SDI_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define SDI_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define SDI_INBUF_ENABLED 0u
#define SDI_INIT_DRIVESTATE 1u
#define SDI_INIT_MUXSEL 0u
#define SDI_INPUT_SYNC 2u
#define SDI_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define SDI_NUM 6u
#define SDI_PORT GPIO_PRT12
#define SDI_SLEWRATE CY_GPIO_SLEW_FAST
#define SDI_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* I2C_scl */
#define I2C_scl_0_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_scl_0_INBUF_ENABLED 1u
#define I2C_scl_0_INIT_DRIVESTATE 1u
#define I2C_scl_0_INIT_MUXSEL 19u
#define I2C_scl_0_INPUT_SYNC 2u
#define I2C_scl_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_scl_0_NUM 4u
#define I2C_scl_0_PORT GPIO_PRT6
#define I2C_scl_0_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_scl_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define I2C_scl_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_scl_INBUF_ENABLED 1u
#define I2C_scl_INIT_DRIVESTATE 1u
#define I2C_scl_INIT_MUXSEL 19u
#define I2C_scl_INPUT_SYNC 2u
#define I2C_scl_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_scl_NUM 4u
#define I2C_scl_PORT GPIO_PRT6
#define I2C_scl_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_scl_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* I2C_sda */
#define I2C_sda_0_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_sda_0_INBUF_ENABLED 1u
#define I2C_sda_0_INIT_DRIVESTATE 1u
#define I2C_sda_0_INIT_MUXSEL 19u
#define I2C_sda_0_INPUT_SYNC 2u
#define I2C_sda_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_sda_0_NUM 5u
#define I2C_sda_0_PORT GPIO_PRT6
#define I2C_sda_0_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_sda_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define I2C_sda_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_sda_INBUF_ENABLED 1u
#define I2C_sda_INIT_DRIVESTATE 1u
#define I2C_sda_INIT_MUXSEL 19u
#define I2C_sda_INPUT_SYNC 2u
#define I2C_sda_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_sda_NUM 5u
#define I2C_sda_PORT GPIO_PRT6
#define I2C_sda_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_sda_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART_rx */
#define UART_rx_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_0_INBUF_ENABLED 1u
#define UART_rx_0_INIT_DRIVESTATE 1u
#define UART_rx_0_INIT_MUXSEL 18u
#define UART_rx_0_INPUT_SYNC 2u
#define UART_rx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_0_NUM 0u
#define UART_rx_0_PORT GPIO_PRT5
#define UART_rx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_rx_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_INBUF_ENABLED 1u
#define UART_rx_INIT_DRIVESTATE 1u
#define UART_rx_INIT_MUXSEL 18u
#define UART_rx_INPUT_SYNC 2u
#define UART_rx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_NUM 0u
#define UART_rx_PORT GPIO_PRT5
#define UART_rx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART_tx */
#define UART_tx_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_0_INBUF_ENABLED 0u
#define UART_tx_0_INIT_DRIVESTATE 1u
#define UART_tx_0_INIT_MUXSEL 18u
#define UART_tx_0_INPUT_SYNC 2u
#define UART_tx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_0_NUM 1u
#define UART_tx_0_PORT GPIO_PRT5
#define UART_tx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_tx_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_INBUF_ENABLED 0u
#define UART_tx_INIT_DRIVESTATE 1u
#define UART_tx_INIT_MUXSEL 18u
#define UART_tx_INPUT_SYNC 2u
#define UART_tx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_NUM 1u
#define UART_tx_PORT GPIO_PRT5
#define UART_tx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

#endif /* INCLUDED_CYFITTER_GPIO_H */
