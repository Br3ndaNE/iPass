#include "hwlib.hpp"
#include "BME280.hpp"
#include "weatherstation.hpp"
#include "oled.hpp"

int main( void )
{
    //hwlib set the scl & sda pin
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    //creats bus
    hwlib::i2c_bus_bit_banged_scl_sda bus(scl, sda);

    //creats oled object called oled
    oled oled(bus);
    //creats BME280 object called sensor
    BME280 sensor(bus);

    //creats weatherstation object that has 4 parameters, 3x BME280 and 1x Oledscreen
    weatherstation ws(sensor, sensor, sensor, oled);

    //weatherstation test function that has parameter where you can fill in how many times you want it to test
//    ws.test(40);

    //weatherstation start function that has endless loop that will put data on screen.
    ws.start();

}

