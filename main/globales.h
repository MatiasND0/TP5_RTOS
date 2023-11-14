/*
 * globales.h
 *
 *  Created on: Nov 7, 2023
 *      Author: edgardog
 */

#ifndef MAIN_GLOBALES_H_
#define MAIN_GLOBALES_H_
//Includes de freeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
//Includes de esp-idf
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#include "driver/i2c.h"
#include "rom/ets_sys.h"


//DEfines globales
#define LED_PIN 2
#define RGB_PIN 8




#endif /* MAIN_GLOBALES_H_ */
