#include "../components/drivers/include/GPIO.h"
#include "../Librerias/librerias.h"


void app_main(void)
{
    GPIO_Salida(GPIO_2);           //Se establece GPIO_2 como salida
    GPIO_Escribir(GPIO_2, BAJO);   //Led inicialmnete apagado

    while (true) {
    	GPIO_Escribir(GPIO_2, ALTO);        //Se enciende el LED
        vTaskDelay (pdMS_TO_TICKS(100));
        GPIO_Escribir(GPIO_2,BAJO);         //Se apaga el LED
        vTaskDelay (pdMS_TO_TICKS(100));
    }
}
