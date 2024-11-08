/****************************************************************************************************************************
*  auther ::       Brendan Endenburg
* File ::              oled.hpp
* Date::           29 - 06 - 2022
* copyright:    Brendan Endenburg 2022
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

#ifndef V1OOPC_EXAMPLES_OLED_HPP
#define V1OOPC_EXAMPLES_OLED_HPP
#include "BME280.hpp"
#include "SensorTemp.hpp"
#include "SensorPressure.hpp"
#include "SensorHumidity.hpp"
#include "hwlib.hpp"
#include "oled.hpp"

///@file
/// \brief
/// oled class
/// \details
/// Class that is needed to write data on oledscreen.
class oled {
private:
    uint8_t adress = 0x3c;
    hwlib::i2c_bus &bus;
public:
    oled(hwlib::i2c_bus &bus):
    bus(bus)
    {}

/// \brief
/// print function
/// \details
/// Gets the temp, press and humidity from the weatherstation class and formats it on the screen.
    void print(int temp, int press, int hum);
};


#endif //V1OOPC_EXAMPLES_OLED_HPP
