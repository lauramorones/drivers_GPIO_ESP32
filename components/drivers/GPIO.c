/*
 Nombre del archivo:	GPIO.c
 Dependencias: 			GPIO.h
 Procesador: 			ESP32
 Placa:					ESP32-PANTHER48
 Versión del programa:  5.1
 Empresa:		 		Espressif Systems
 Descripción: 	 		Este archivo contiene funciones para configurar pines GPIO como entrada
 	 	 	 	 	 	o salida, activar resistencias PullUp o PullDown, escribir en pines y leer
 	 	 	 	 	 	el estado de pines configurados como entrada. Se proporcionan implementaciones
 	 	 	 	 	 	para estas operaciones, junto con comentarios detallados sobre su funcionamiento
 	 	 	 	 	 	y parámetros de entrada. Además, se incluyen definiciones de arreglos para
 	 	 	 	 	 	mapear registros de configuración de pines y direcciones de registro para
 	 	 	 	 	 	el control de pines RTC. .
 Autores: 		 		Ninguno
 Actualizado: 			05/2024 */


#include "../drivers/include/GPIO.h"

volatile uint32_t GPIO_PINX_MUX_REG[] = {
    IO_MUX_GPIO_0_REG,
    IO_MUX_GPIO_1_REG,
    IO_MUX_GPIO_2_REG,
    IO_MUX_GPIO_3_REG,
    IO_MUX_GPIO_4_REG,
    IO_MUX_GPIO_5_REG,
    IO_MUX_GPIO_6_REG,
    IO_MUX_GPIO_7_REG,
    IO_MUX_GPIO_8_REG,
    IO_MUX_GPIO_9_REG,
    IO_MUX_GPIO_10_REG,
    IO_MUX_GPIO_11_REG,
    IO_MUX_GPIO_12_REG,
    IO_MUX_GPIO_13_REG,
    IO_MUX_GPIO_14_REG,
    IO_MUX_GPIO_15_REG,
    IO_MUX_GPIO_16_REG,
    IO_MUX_GPIO_17_REG,
    IO_MUX_GPIO_18_REG,
    IO_MUX_GPIO_19_REG,
    IO_MUX_GPIO_20_REG,
    IO_MUX_GPIO_21_REG,
    IO_MUX_GPIO_22_REG,
    IO_MUX_GPIO_23_REG,
    0,
    IO_MUX_GPIO_25_REG,
    IO_MUX_GPIO_26_REG,
    IO_MUX_GPIO_27_REG,
    0,
    0,
    0,
    0,
    IO_MUX_GPIO_32_REG,
    IO_MUX_GPIO_33_REG,
    IO_MUX_GPIO_34_REG,
    IO_MUX_GPIO_35_REG,
    IO_MUX_GPIO_36_REG,
    IO_MUX_GPIO_37_REG,
    IO_MUX_GPIO_38_REG,
    IO_MUX_GPIO_39_REG,
};

uint32_t rtc_pins[] = {
	RTCIO_TOUCH_PAD1, /*GPIO_0*/
	0,                /*GPIO_1*/
	RTCIO_TOUCH_PAD2, /*GPIO_2*/
	0,                /*GPIO_3*/
	RTCIO_TOUCH_PAD0, /*GPIO_4*/
	0,                /*GPIO_5*/
	0,                /*GPIO_6*/
	0,                /*GPIO_7*/
	0,                /*GPIO_8*/
	0,                /*GPIO_9*/
	0,                /*GPIO_10*/
	0,                /*GPIO_11*/
	RTCIO_TOUCH_PAD5, /*GPIO_12*/
	RTCIO_TOUCH_PAD4, /*GPIO_13*/
	RTCIO_TOUCH_PAD6, /*GPIO_14*/
	RTCIO_TOUCH_PAD3, /*GPIO_15*/
	0,                /*GPIO_16*/
	0,                /*GPIO_17*/
	0,                /*GPIO_18*/
	0,                /*GPIO_19*/
	0,             	  /*GPIO_20*/
	0,                /*GPIO_21*/
	0,                /*GPIO_22*/
	0,                /*GPIO_23*/
	0,           	  /*GPIO_24*/
	1,                /*GPIO_25*/
	1,                /*GPIO_26*/
	RTCIO_TOUCH_PAD7, /*GPIO_27*/
	0,            	  /*GPIO_28*/
	0,                /*GPIO_29*/
	0,                /*GPIO_30*/
	0,             	  /*GPIO_31*/
	0,                /*GPIO_32*/
	0,                /*GPIO_33*/
	0,                /*GPIO_34*/
    0,                /*GPIO_35*/
    0,                /*GPIO_36*/
    0,                /*GPIO_37*/
    0,                /*GPIO_38*/
    0,                /*GPIO_39*/
};

volatile uint32_t dir_rtcio_touch_pad[]={
    RTC_IO_TOUCH_PAD0_REG,
    RTC_IO_TOUCH_PAD1_REG,
    RTC_IO_TOUCH_PAD2_REG,
    RTC_IO_TOUCH_PAD3_REG,
    RTC_IO_TOUCH_PAD4_REG,
    RTC_IO_TOUCH_PAD5_REG,
    RTC_IO_TOUCH_PAD6_REG,
    RTC_IO_TOUCH_PAD7_REG,
    RTC_IO_TOUCH_PAD8_REG,
    RTC_IO_TOUCH_PAD9_REG,
};

/**************************************************************************
Función: 	GPIO_Salida
Resumen: 	Configura el GPIO pasado como parámetro para poder usarlo como salida.
Parámetro: 	GPIO_
Retorno: 	Ninguno.
*****************************************************************************/
void GPIO_Salida(uint32_t GPIO_){

    /*Se validan que el GPIO esté disponible*/
    if(GPIO_PINX_MUX_REG[GPIO_]==0){
        printf("Error el GPIO_:%lu  está reservado o no existe.",GPIO_);
        exit(1);
    }

    /*GPIO SOLO INPUT */
    if(GPIO_>=GPIO_34 && GPIO_<=GPIO_39){
        printf("Error: el GPIO_%lu solo es permitido como entrada\n",GPIO_);
        exit(1);
    }

    /*se desactiva el pin como entrada*/
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) &~(1<<FUN_IE);

    /*Configurar como GPIO*/
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) & ~(1<<12);
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) | (1<<13);
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) & ~(1<<14);

   /*Se activa el pin como salida*/
   /*Caso especial para el GPIO 32 Y 33           I/O/T  */
    if((GPIO_==GPIO_32)||(GPIO_==GPIO_33)){
        GPIO_ENABLE1_REG = GPIO_ENABLE1_REG |(1<<(GPIO_-32));
    }
    else /*Caso para GPIO del 0 al 31*/
        GPIO_ENABLE_REG = GPIO_ENABLE_REG |(1<<GPIO_);
}
/**************************************************************************
Función: 	GPIO_Entrada
Resumen: 	Configura el GPIO que se le pase como parámetro para poder usarlo como entrada.
Parámetro: 	GPIO_
Retorno: 	Ninguno
*****************************************************************************/
void GPIO_Entrada(uint32_t GPIO_){
    /*Validar GPIO reservados*/
    if(GPIO_PINX_MUX_REG[GPIO_]==0){
        printf("Error el GPIO_:%lu  está reservado o no existe",GPIO_);
        exit(1);
    }
    /*Desactivamos el pin como salida*/
    if(GPIO_>=GPIO_32 && GPIO_<=GPIO_39){
        GPIO_ENABLE1_REG = GPIO_ENABLE1_REG &~(1<<(GPIO_-32));
    }
    else
        GPIO_ENABLE_REG = GPIO_ENABLE_REG &~(1<<GPIO_);
    /*Activar como entrada*/
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) =  HWREG32(GPIO_PINX_MUX_REG[GPIO_]) |(1<<FUN_IE);
    /*Configurar como GPIO*/
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) &~(1<<12);
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) =  HWREG32(GPIO_PINX_MUX_REG[GPIO_]) |(1<<13);
    HWREG32(GPIO_PINX_MUX_REG[GPIO_]) =  HWREG32(GPIO_PINX_MUX_REG[GPIO_]) &~(1<<14);
}

/**************************************************************************
Función: 		GPIO_PullUp
Requerimientos: GPIO_Input declarado como entrada previamente.
Resumen: 		Activa la resistencia PullUp interna del GPIO que se le pase como parámetro.
Parámetro: 		GPIO_
Retorno: 		Ninguna.
*****************************************************************************/

void GPIO_PullUp(uint32_t GPIO_){

	if(rtc_pins[GPIO_]!=0){
		HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) =	HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) |(1<<27);
		HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) = HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) &~(1<<28);
	}
	else {
		HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) |(1<<8);
		HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) & ~(1<<7);
	}
}

/**************************************************************************
Función: 		GPIO_PullDown
Requerimientos: GPIO a usar declarado como entrada previamente
Resumen: 		Activa la resistencia PullDown del GPIO que se le pase como parámetro.
Parámetro: 		GPIO al cual se le quiere activar la resistencia pull-down.
Retorno: 		Ninguno.
*****************************************************************************/
void GPIO_PullDown(uint32_t GPIO_){
	if(rtc_pins[GPIO_]!=0){
		HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) =	HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) |(1<<28);
		HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) = HWREG32(dir_rtcio_touch_pad[rtc_pins[GPIO_]]) &~(1<<27);
	}
	else {
		HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) |(1<<7);
		HWREG32(GPIO_PINX_MUX_REG[GPIO_]) = HWREG32(GPIO_PINX_MUX_REG[GPIO_]) & ~(1<<8);
	}
}
/**************************************************************************
Función: 		GPIO_Escribir
Requerimientos: GPIO_ declarado como salida previamente
Resumen:		Pone en alto o bajo al GPIO que se le pase como parámetro.
Parámetro: 		GPIO_ que se desea cambiar su estado lógico.
Retorno: 		Ninguno.
*****************************************************************************/
void GPIO_Escribir(uint32_t GPIO_,enum ESTADO ESTATUS){
    /*Poner el pin en alto*/
    if(ESTATUS==GPIO_HIGH){
        if((GPIO_==GPIO_32)||(GPIO_==GPIO_33))
            GPIO_OUT1_W1TS_REG = (1<<(GPIO_-32));
        else
            GPIO_OUT_W1TS_REG = (1<<GPIO_);/*Registro GPIO del 0 al 31*/
    }

        /*Poner el pin en bajo*/
    else if(ESTATUS == GPIO_LOW){
        if((GPIO_==GPIO_32)||(GPIO_==GPIO_33))
            GPIO_OUT1_W1TC_REG = (1<<(GPIO_-32));
        else
            GPIO_OUT_W1TC_REG = (1<<GPIO_);/*Registro GPIO del 0 al 31*/
    }
}
/**************************************************************************
Función: 		GPIO_Leer.
Requerimientos: GPIO_ establecido como entrada previamente.
Resumen:		Lee el estado del GPIO
Parámetro: 		GPIO_ al cual se quiera leer su estado.
Retorno: 		Valor leído en el GPIO 1 para ALTO , 0 para BAJO.
*****************************************************************************/
// Lee el estado de un pin GPIO y devuelve su valor como un entero (0 o 1)
int GPIO_Leer(uint32_t GPIO) {
    int valor_leido = 0; // Inicializa el valor leído como bajo (0)

    // Verifica si el pin está en el rango de GPIO_32 a GPIO_39
    if (GPIO >= GPIO_32 && GPIO <= GPIO_39) {
        // Lee el bit correspondiente al pin GPIO en GPIO_IN1_REG y actualiza el valor leído
        if (GPIO_IN1_REG & (1 << (GPIO - 32))) {
            valor_leido = 1;
        } else {
            valor_leido = 0;
        }
    }
    // Si el pin no está en el rango de GPIO_32 a GPIO_39
    else {
        // Lee el bit correspondiente al pin GPIO en GPIO_IN_REG y actualiza el valor leído
        if (GPIO_IN_REG & (1 << GPIO)) {
            valor_leido = 1;
        } else {
            valor_leido = 0;
        }
    }

    return valor_leido; // Devuelve el valor leído del pin GPIO
}
