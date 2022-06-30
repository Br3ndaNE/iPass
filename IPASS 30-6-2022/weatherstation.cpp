/****************************************************************************************************************************
*  auther ::       Brendan Endenburg
* File ::              weatherstation.cpp
* Date::           29 - 06 - 2022
* copyright:    Brendan Endenburg 2022
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

#include "weatherstation.hpp"

void weatherstation::print(){
    window.print(degrees, pressure, humidity);
}

int weatherstation::get_temp(){
    return temp.GetTemp();
}

int weatherstation::get_press(){
    return press.GetPressure();
}

int weatherstation::get_hum(){
    return hum.GetHumidity();
}

void weatherstation::start(){
    for(;;){
        window.print(degrees, pressure, humidity);

        degrees = get_temp();
        pressure = get_press();
        humidity = get_hum();
        hwlib::wait_ms(200);
    }
}

void weatherstation::test(int x){
    for(int i = 0; i<x; i++) {
        window.print(degrees, pressure, humidity);
        hwlib::cout << "Case " << i+1 << "\n";
        if (degrees > -15 and degrees < 40) {
            hwlib::cout << "    1 test temp: Success" << "\n";
        } else {
            hwlib::cout << "    1 test temp: Failed" << "\n";
        }

        if (pressure > 99000 and pressure < 105000) {
            hwlib::cout << "    2 test air-pressure: Success" << "\n";
        } else {
            hwlib::cout << "    2 test air-pressure: Failed" << "\n";
        }

        if (humidity > 0 and humidity < 100) {
            hwlib::cout << "    3 test humidity: Success" << "\n";
        } else {
            hwlib::cout << "    3 test humidity: Failed" << "\n";
        }
        hwlib::cout << "\n";
        degrees = get_temp();
        pressure = get_press();
        humidity = get_hum();
    }
}