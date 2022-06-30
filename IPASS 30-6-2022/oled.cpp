/****************************************************************************************************************************
*  auther ::       Brendan Endenburg
* File ::              oled.cpp
* Date::           29 - 06 - 2022
* copyright:    Brendan Endenburg 2022
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

#include "oled.hpp"

void oled::print(int temp, int press, int hum) {

    auto oled = hwlib::glcd_oled( bus, adress );

    auto w2 = hwlib::part(
            oled,
            hwlib::xy( 0, 0 ),
            hwlib::xy( 128, 64));


    auto f2 = hwlib::font_default_8x8();
    auto d2 = hwlib::terminal_from( w2, f2 );

//the format that will be on screen
    d2  << "\f"
        << "Weatherstation" << "\n"
        << "" << "\n"
        << "-----Temp-----\n"
        << "" << "\n"
        << "---Pressure---\n"
        << ""  << "\n"
        << "---Humidity---\n"
        << "" << "\n";


    d2  << "\t0603" << temp << " C"
        << "\t0405" << press << " Pa"
        << "\t0607" << hum << " %";
    oled.flush();
    hwlib::wait_ms(1000);
}
