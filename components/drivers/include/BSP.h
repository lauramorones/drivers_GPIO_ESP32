/*
  Nombre del archivo: 		BSP.h
  Dependencias: 			Ninguna
  Procesador: 				ESP32
  Placa: 					ESP32-PANTHER48
  Versión del programa: 	5.1
  Empresa: 					Espressif Systems
  Descripción: 				Definición de los pines GPIO y otros elementos de hardware
  	  	  	  	  	  	  	utilizados en el sistema. Se incluyen enumeraciones para
  	  	  	  	  	  	  	los LED, botones y pines GPIO, así como las direcciones de
  	  	  	  	  	  	  	registro correspondientes a los pines GPIO para el mapeo
  	  	  	  	  	  	  	del periférico en el ESP32
  Autores: 					Luis Aguilera, Victor Duarte, Laura Morones.
  Actualizado: 				05/2024
  */
#pragma once

#ifndef _BSP_H_
#define _BSP_H_


enum LEDS{
    LED1=17, LED2=16, LED3=4, LED4=2,
    LED5=14, LED6=12, LED7=13, LED8=5,
    LEDR=14, LEDG=13, LEDB=12,
};

enum BOTONES{
    BOTON1=18,
    BOTON2 =19,
};

enum GPIOS{
    GPIO_0, GPIO_1, GPIO_2, GPIO_3, GPIO_4, GPIO_5, GPIO_6, GPIO_7, GPIO_8, GPIO_9,
    GPIO_10, GPIO_11, GPIO_12, GPIO_13, GPIO_14, GPIO_15, GPIO_16, GPIO_17, GPIO_18, GPIO_19,
    GPIO_20, GPIO_21, GPIO_22, GPIO_23, GPIO_24, GPIO_25, GPIO_26, GPIO_27, GPIO_28, GPIO_29,
    GPIO_30, GPIO_31, GPIO_32, GPIO_33, GPIO_34, GPIO_35, GPIO_36, GPIO_37, GPIO_38, GPIO_39,
};

#define IO_MUX_GPIO_0_REG  0x3FF49044
#define IO_MUX_GPIO_1_REG  0x3FF49088
#define IO_MUX_GPIO_2_REG  0x3FF49040
#define IO_MUX_GPIO_3_REG  0x3FF49084
#define IO_MUX_GPIO_4_REG  0x3FF49048
#define IO_MUX_GPIO_5_REG  0x3FF4906C
#define IO_MUX_GPIO_6_REG  0x3FF49060
#define IO_MUX_GPIO_7_REG  0x3FF49064
#define IO_MUX_GPIO_8_REG  0x3FF49068
#define IO_MUX_GPIO_9_REG  0x3FF49054
#define IO_MUX_GPIO_10_REG 0x3FF49058
#define IO_MUX_GPIO_11_REG 0x3FF4905C
#define IO_MUX_GPIO_12_REG 0x3FF49034
#define IO_MUX_GPIO_13_REG 0x3FF49038
#define IO_MUX_GPIO_14_REG 0x3FF49030
#define IO_MUX_GPIO_15_REG 0x3FF4903C
#define IO_MUX_GPIO_16_REG 0x3FF4904C
#define IO_MUX_GPIO_17_REG 0x3FF49050
#define IO_MUX_GPIO_18_REG 0x3FF49070
#define IO_MUX_GPIO_19_REG 0x3FF49074
#define IO_MUX_GPIO_20_REG 0x3FF49078
#define IO_MUX_GPIO_21_REG 0x3FF4907C
#define IO_MUX_GPIO_22_REG 0x3FF49080
#define IO_MUX_GPIO_23_REG 0x3FF4908C
#define IO_MUX_GPIO_24_REG 0
#define IO_MUX_GPIO_25_REG 0x3FF49024
#define IO_MUX_GPIO_26_REG 0x3FF49028
#define IO_MUX_GPIO_27_REG 0x3FF4902C
#define IO_MUX_GPIO_28_REG 0
#define IO_MUX_GPIO_29_REG 0
#define IO_MUX_GPIO_30_REG 0
#define IO_MUX_GPIO_31_REG 0
#define IO_MUX_GPIO_32_REG 0x3FF4901C
#define IO_MUX_GPIO_33_REG 0x3FF49020
#define IO_MUX_GPIO_34_REG 0x3FF49014
#define IO_MUX_GPIO_35_REG 0x3FF49018
#define IO_MUX_GPIO_36_REG 0x3FF49004
#define IO_MUX_GPIO_37_REG 0x3FF49008
#define IO_MUX_GPIO_38_REG 0x3FF4900C
#define IO_MUX_GPIO_39_REG 0x3FF49010

#endif
