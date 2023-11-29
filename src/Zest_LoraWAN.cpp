#include "Zest_LoraWAN.h"

#include "lora_radio_helper.h"

using namespace events;

Zest_LoraWAN::Zest_LoraWAN(Callback<int(char*)> callbackFunc)
{
    lorawan = new LoRaWANInterface(radio);
    ev_queue = new EventQueue(MAX_NUMBER_OF_EVENTS *EVENTS_EVENT_SIZE);

    packet = (char *)calloc(0, MAX_SIZE_MESSAGE * sizeof(char));
    packetLen = 0;

    Func = callbackFunc;
}

Zest_LoraWAN::~Zest_LoraWAN()
{
    delete lorawan;
}

int Zest_LoraWAN::init()
{
    if (lorawan->initialize(ev_queue) != LORAWAN_STATUS_OK) {
        printf("\r\n LoRa initialization failed! \r\n");
        return -1;
    }
    printf("\r\n Mbed LoRaWANStack initialized \r\n");

    // prepare application callbacks
    callbacks.events = mbed::callback(this, &Zest_LoraWAN::lora_event_handler);
    lorawan->add_app_callbacks(&callbacks);

    // // Set number of retries in case of CONFIRMED messages
    if (lorawan->set_confirmed_msg_retries(CONFIRMED_MSG_RETRY_COUNTER)
            != LORAWAN_STATUS_OK) {
        printf("\r\n set_confirmed_msg_retries failed! \r\n\r\n");
        return -1;
    }

    printf("\r\n CONFIRMED message retries : %d \r\n",
           CONFIRMED_MSG_RETRY_COUNTER);

    // Enable adaptive data rate
    if (lorawan->enable_adaptive_datarate() != LORAWAN_STATUS_OK) {
        printf("\r\n enable_adaptive_datarate failed! \r\n");
        return -1;
    }

    printf("\r\n Adaptive data  rate (ADR) - Enabled \r\n");

    retcode = lorawan->connect();

    if (retcode == LORAWAN_STATUS_OK ||
            retcode == LORAWAN_STATUS_CONNECT_IN_PROGRESS) {
    } else {
        printf("\r\n Connection error, code = %d \r\n", retcode);
        return -1;
    }

    printf("\r\n Connection - In Progress ...\r\n");

    // make your event queue dispatching events forever
    ev_queue->dispatch_forever();

    return 0;
}

void Zest_LoraWAN::lora_event_handler(lorawan_event_t event)
{
    switch (event) {
        case CONNECTED:
            printf("\r\n Connection - Successful \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            } else {
                ev_queue->call_every(TX_TIMER, mbed::callback(this, &Zest_LoraWAN::send_message));
            }

            break;
        case DISCONNECTED:
            ev_queue->break_dispatch();
            printf("\r\n Disconnected Successfully \r\n");
            break;
        case TX_DONE:
            printf("\r\n Message Sent to Network Server \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        case TX_TIMEOUT:
        case TX_ERROR:
        case TX_CRYPTO_ERROR:
        case TX_SCHEDULING_ERROR:
            printf("\r\n Transmission Error - EventCode = %d \r\n", event);
            // try again
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        case RX_DONE:
            printf("\r\n Received message from Network Server \r\n");
            break;
        case RX_TIMEOUT:
        case RX_ERROR:
            printf("\r\n Error in reception - Code = %d \r\n", event);
            break;
        case JOIN_FAILURE:
            printf("\r\n OTAA Failed - Check Keys \r\n");
            break;
        case UPLINK_REQUIRED:
            printf("\r\n Uplink required by NS \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        default:
            MBED_ASSERT("Unknown Event");
    }
}

int Zest_LoraWAN::send_message()
{
    int16_t retcode;

    packetLen = Func(packet);

    retcode = lorawan->send(MBED_CONF_LORA_APP_PORT, (uint8_t *)packet, packetLen,
                           MSG_UNCONFIRMED_FLAG);

    if (retcode < 0) {
        retcode == LORAWAN_STATUS_WOULD_BLOCK ? printf("send - WOULD BLOCK\r\n")
        : printf("\r\n send() - Error code %d \r\n", retcode);

        if (retcode == LORAWAN_STATUS_WOULD_BLOCK) {
            // retry in 3 seconds
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                ev_queue->call_in(3000, mbed::callback(this, &Zest_LoraWAN::send_message));
            }
        }
        return retcode;
    }

    printf("\r\n %d bytes scheduled for transmission \r\n", retcode);

    return retcode;
}