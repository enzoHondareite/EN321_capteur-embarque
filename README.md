# EN321_capteur-embarque 

Project of HONDAREITE Enzod and DUMARTIN Carl.

Project using the Zest_Sensor_P-T-RH with the sensor board Zest_Sensor_P-T-RH.


## Description

Measurement of temperature and humidity. 

Transmission of measurements on UART and LoRaWan. 

Displaying measurements on a ThingsBoard dashboard.


## Installation



```bash
mbed deploy
mbed compile --target ZEST_CORE_FMLR-72 --toolchain GCC_ARM
sixtron_flash
```

## LoRaWan UART informations

These debug logs trace the process of initialization, transmission of the join request, and successful connection of a LoRaWAN device using the OTAA method. They provide useful information for debugging and monitoring the connection process.

```bash
User Registration Status
```
  - Indicates the user's registration status (level battery, heater status, OTP one-time password status) 
```bash
[DBG] [LSTK]: MAC layer initialization
```
  - Specify the start of Medium Access Control (MAC) layer initialization.
```bash
Mbed LoRaWANStack initialized
```
  - Confirm that the LoRaWAN Mbed stack has been initialized successfully.
```bash
CONFIRMED message retries: 3
```
  - Indicates that the device is configured to retransmit a confirmation message up to three times if it fails.
```bash
Adaptive Data Rate (ADR) - Enabled
```
  - Means Adaptive Data Rate (ADR) is enabled, which allows the LoRaWAN network to automatically regulate the data rate based on network conditions.
```bash
[DBG] [LSTK]: OTAA launch
```
  - Indicates the start of the OTAA activation process.
```bash
[DBG] [LSTK]: Sending join request...
```
  - Means the device sends a join request to the LoRaWAN network.
```bash
[DBG ][LMAC]: frame ready to send on port 0
```
  - Indicate that the frame is ready to be sent on port 0.
```bash
[DBG] [LMAC]: TX: channel = 1, TX DR = 5, RX1 DR = 5
```
  - Provides information about the current transmission, such as transmission channel, transmit data rate (TX DR), and receive data rate (RX1 DR).
```bash
Current connection...
```
  - Indicates that the connection is in progress.
```bash
[DBG ][LSTK]: Transmission completed
```
  - Confirm that the join request transmission is complete.
```bash
[DBG][LMAC]: RX1 slot open, Freq=868300000
```
  - Indicate that the RX1 (Receive 1) slot is open, and it provides the frequency on which the device will listen for network responses.
```bash
[DBG][LSTK]: OTAA connection OK!
```
  - Means the OTAA connection has been established successfully.

## Dashboards

[ThingsBoard](https://thingsboard.cloud/dashboards/all/c3ac7470-87ba-11ee-bb3f-95d9fd3bcf97)


## License

[apache](https://www.apache.org/licenses/LICENSE-2.0)