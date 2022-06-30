/****************************************************************************************************************************
*  auther ::       Brendan Endenburg
* File ::              weatherstation.hpp
* Date::           29 - 06 - 2022
* copyright:    Brendan Endenburg 2022
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

#ifndef V1OOPC_EXAMPLES_WEATHERSTATION_HPP
#define V1OOPC_EXAMPLES_WEATHERSTATION_HPP
#include "BME280.hpp"
#include "SensorTemp.hpp"
#include "SensorPressure.hpp"
#include "SensorHumidity.hpp"
#include "hwlib.hpp"
#include "oled.hpp"

/// @file
/// \brief
/// Weatherstation class
/// \details
/// This class forms the whole weathersystem with display and the data of the BME280.
class weatherstation{
private:
    int degrees, pressure, humidity;
    SensorTemp& temp;
    SensorPressure& press;
    SensorHumidity & hum;
    oled& window;

public:
    weatherstation(SensorTemp & temp, SensorPressure & press, SensorHumidity & hum, oled & window):
    degrees(temp.GetTemp()),
    pressure(press.GetPressure()),
    humidity(hum.GetHumidity()),
    temp(temp),
    press(press),
    hum(hum),
    window(window){}

/// \brief
/// print function
/// \details
/// This function gives the tempature, atmospheric pressure and humidity to the oled class print function.
    void print();

/// \brief
/// start function
/// \details
/// This function calls the print function in a endless loop that will write the tempature, atmospheric pressure and humidity to the oledscreen.
    void start();

/// \brief
/// Weatherstation test
/// \details
/// Tests the given values of the BME280. Parameter x is how many times you want to test the function.
    void test(int x);

/// \brief
/// Weatherstation get_temp
/// \details
/// getter tempature
    int get_temp();

/// \brief
/// Weatherstation get_press
/// \details
/// getter atmospheric pressure
    int get_press();

/// \brief
/// Weatherstation get_hum
/// \details
/// getter humidity
    int get_hum();

};


#endif //V1OOPC_EXAMPLES_WEATHERSTATION_HPP
