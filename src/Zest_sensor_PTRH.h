#ifndef ZEST_SENSOR_PTRH_H_
#define ZEST_SENSOR_PTRH_H_

#include "htu21d.h"

#define Zest_sensor_PTRH_NO_ERROR 0
#define Zest_sensor_PTRH_ON_ERROR 0

class Zest_sensor_PTRH
{
    public:
        Zest_sensor_PTRH(PinName i2c_sda, PinName i2c_scl);
        ~Zest_sensor_PTRH();

        int init();
        double getHumidity();
        void getHumidity(double &humidity);
        double getTemperature();
        void getTemperature(double &temperature);

    private:
        sixtron::HTU21D *sensor;

        sixtron::HTU21D::ErrorType err;
        sixtron::htud21d_user_reg_t reg;
};
#endif