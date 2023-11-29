/**
 * Copyright (c) 2017, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>

// Sensor
#include "Zest_sensor_PTRH.h"

// LoraWAN
#include "Zest_LoraWAN.h"


/**
 * HTU21D sensor class object
 */
Zest_sensor_PTRH sensor(P1_I2C_SDA, P1_I2C_SCL);

int getDatas(char *data)
{
    return sprintf( (char *) data, "{\"temperature\": %.2f, \"humidity\": %.2f}", sensor.getTemperature(), sensor.getHumidity());
}

Zest_LoraWAN loraWan(getDatas);

int main(void)
{
    // switch on LORA antenna
    DigitalOut _pin(LORA_ANTSW_PWR, 1);

    sensor.init();

    loraWan.init();

    return 0;
}
