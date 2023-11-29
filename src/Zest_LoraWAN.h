#ifndef ZEST_LORAWAN_H_
#define ZEST_LORAWAN_H_

#include "mbed.h"

#include "lorawan/LoRaWANInterface.h"
#include "lorawan/system/lorawan_data_structures.h"

#include "events/EventQueue.h"

#define MAX_NUMBER_OF_EVENTS 10
#define CONFIRMED_MSG_RETRY_COUNTER 3
#define TX_TIMER 10000
#define MAX_SIZE_MESSAGE 100

class Zest_LoraWAN
{
    public:
        Zest_LoraWAN(Callback<int(char*)> callbackFunc);
        ~Zest_LoraWAN();

        int init();

        char *packet;
        int packetLen;

    private:
        LoRaWANInterface *lorawan;
        lorawan_status_t retcode;
        events::EventQueue *ev_queue;
        lorawan_app_callbacks_t callbacks;

        void lora_event_handler(lorawan_event_t event);
        int send_message();

        Callback<int(char*)> Func;
};
#endif