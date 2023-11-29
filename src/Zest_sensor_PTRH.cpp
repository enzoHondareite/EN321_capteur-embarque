#include "Zest_sensor_PTRH.h"

Zest_sensor_PTRH::Zest_sensor_PTRH(PinName i2c_sda, PinName i2c_scl)
{
    sensor = new sixtron::HTU21D(i2c_sda, i2c_scl);
}

Zest_sensor_PTRH::~Zest_sensor_PTRH()
{
    delete sensor;
}

int Zest_sensor_PTRH::init()
{
    sensor->soft_reset();

    err = sensor->read_user_register(&reg);

    if (err == sixtron::HTU21D::ErrorType::Ok)
    {
        printf("User register status:\n");
        printf("Battery low: %s\nHeater: %s\nOTP reload: %s\n\n",
                reg.end_of_battery ? "TRUE" : "FALSE",
                reg.enable_heater ? "ON" : "OFF",
                reg.disable_otp_reload ? "DISABLED" : "ENABLED");

        reg.resolution = sixtron::MeasurementResolution::RH_12_Temp_14;
        sensor->write_user_register(&reg);
    } else
    {
        return Zest_sensor_PTRH_ON_ERROR;
    }

    return Zest_sensor_PTRH_NO_ERROR;
}

double Zest_sensor_PTRH::getHumidity()
{
    double humidity = 0;

    err = sensor->read_humidity(&humidity);
    if (err == sixtron::HTU21D::ErrorType::Ok)
    {
        printf("Relative humidity: %f%%\n", humidity);
    } else
    {
        return -1;
    }

    return humidity;
}

void Zest_sensor_PTRH::getHumidity(double &humidity)
{
    err = sensor->read_humidity(&humidity);
    if (err == sixtron::HTU21D::ErrorType::Ok)
    {
        printf("Relative humidity: %f%%\n", humidity);
        return;
    }
    humidity = -1;
    return;
}

double Zest_sensor_PTRH::getTemperature()
{
    double temperature = 0;

    err = sensor->read_temperature(&temperature);
    if (err == sixtron::HTU21D::ErrorType::Ok)
    {
        printf("Temperature: %fC\n", temperature);
    } else
    {
        return -1;
    }

    return temperature;
}

void Zest_sensor_PTRH::getTemperature(double &temperature)
{
    temperature = 0;
    
    err = sensor->read_temperature(&temperature);
    if (err == sixtron::HTU21D::ErrorType::Ok)
    {
        printf("Temperature: %fC\n", temperature);
        return;
    } else 
    {
        temperature = -1;
        return;
    }
    return;
}