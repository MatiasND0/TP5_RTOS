#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "globales.h"
#include "driver/gpio.h"
#include "i2clcddisplay.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "hal/gpio_types.h"

#include "driver/i2c.h"
#include "rom/ets_sys.h"

QueueHandle_t cola;

struct DatosPin{
	uint8_t numeroPin;
	uint8_t nombrePin;
}typedef DatosPin;

void vTaskCode( void * pvParameters )
{
	uint8_t estado=0;
	DatosPin *pin = (DatosPin *) pvParameters;

	gpio_reset_pin(pin->numeroPin);
	gpio_set_direction(pin->numeroPin,GPIO_MODE_INPUT);
	gpio_pullup_en(pin->numeroPin);

	while(1){
		vTaskDelay(20 / portTICK_PERIOD_MS);
		if (estado==0 && gpio_get_level(pin->numeroPin)){
			gpio_set_level(2,1);
			estado=1;
			xQueueSend(cola,&pin->nombrePin,0);
		}
		if (estado==1 && !gpio_get_level(pin->numeroPin)){
			gpio_set_level(2,0);
			estado=0;
		}
	}
}

void app_main(void)
{
	DatosPin pin[4];
	uint8_t state = 0;

	gpio_reset_pin(2);
	gpio_set_direction(2,GPIO_MODE_OUTPUT);
	gpio_set_level(2,1);

	pin[0].numeroPin=19;		//GPIO 4
	pin[0].nombrePin=1;		//Numero

	pin[1].numeroPin=18;		//GPIO 4
	pin[1].nombrePin=2;		//Numero

	pin[2].numeroPin=5;		//GPIO 4
	pin[2].nombrePin=3;		//Numero

	pin[3].numeroPin=17;		//GPIO 4
	pin[3].nombrePin=4;		//Numero

	I2CLCD_InitPort();
	I2CLCDDisplay display;
	display.Address = 0x4E;
	display.Backlight = 1;
	I2CLCD_Init(display);

	cola = xQueueCreate(20,sizeof(unsigned int));
	BaseType_t xReturned;
	TaskHandle_t xHandle[4];
	xReturned = xTaskCreate(vTaskCode,"Boton1",4096,(void *) &pin[0],10,&xHandle[0]);
	xReturned = xTaskCreate(vTaskCode,"Boton2",4096,(void *) &pin[1],10,&xHandle[1]);
	xReturned = xTaskCreate(vTaskCode,"Boton3",4096,(void *) &pin[2],10,&xHandle[2]);
	xReturned = xTaskCreate(vTaskCode,"Boton4",4096,(void *) &pin[3],10,&xHandle[3]);

	while(1){
		uint8_t  cantidad = uxQueueMessagesWaiting(cola);
		char buffer_cant[16];
		char buffer_botones[16];
		uint8_t queueReceived;

		sprintf(buffer_cant,"Cantidad: %d  ",cantidad);

		for(int j=0;j<16;j++)
			buffer_botones[j]=' ';

		for(int i=0;i<cantidad;i++)
		{
			xQueueReceive(cola,&queueReceived,0);
			buffer_botones[i] = queueReceived+48;

			if( queueReceived==4 )
			{
				if(state==0)
				{
					vTaskSuspend(xHandle[0]);
					state=1;
				}
				else
				{
					vTaskResume(xHandle[0]);
					state=0;
				}
			}


		}
		I2CLCD_WriteLine(display,0,buffer_cant);
		I2CLCD_WriteLine(display,1,buffer_botones);
		xQueueReset(cola);
		vTaskDelay(5000/portTICK_PERIOD_MS);
	}

}
