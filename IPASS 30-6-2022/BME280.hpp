/****************************************************************************************************************************
*  auther ::       Brendan Endenburg
* File ::              BME280.hpp
* Date::           29 - 06 - 2022
* copyright:    Brendan Endenburg 2022
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

#include "SensorHumidity.hpp"
#include "SensorPressure.hpp"
#include "SensorTemp.hpp"
#include "hwlib.hpp"

#ifndef V1OOPC_EXAMPLES_BME280_HPP
#define V1OOPC_EXAMPLES_BME280_HPP


/// @file
/// \brief
/// BME280 Library
/// \details
/// Reads out the tempature, atmospheric presseure and humidity of the BME280 chip.
/// BME280 chip inherits the abstract classes SensorTemp, SensorHumidity, SensorPressure. The abstract classes are overwritten in this class.
class BME280 : public SensorTemp, public SensorHumidity, public SensorPressure{
private:
    //adress
    const uint_fast8_t address = 0x76;
    //temp
    const uint_fast8_t ctrl_meas = 0xF4; //write for temp & airpressure
    const uint_fast8_t reg_data = 0x27; //register setting for temp & airpressure
    const uint_fast8_t temp_msb = 0xFA;
    //airpressure
    const uint_fast8_t press_msb = 0xF7;
    //humidity
    const uint_fast8_t ctrl_hum = 0xF2;
    const uint_fast8_t reg_data_hum = 0b00000001;
    const uint_fast8_t hum_msb = 0xFD;
    int32_t t_fine;

    //definedChipRegisters Temp
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;

    //definedChipRegisters Pressure
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;

    //definedChipRegisters Humidity
    uint8_t dig_H1 = 0;
    int16_t dig_H2;
    uint8_t dig_H3 = 0;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t dig_H6 = 0;

/// \brief
/// setChipDefinedRegistersTemp
/// \details
/// Gets the register data from the chip and buts it in dig_T1 t/m dig_T3
    void setChipDefinedRegistersTemp();
/// \brief
/// setChipDefinedRegistersPress
/// \details
/// Gets the register data from the chip and buts it in dig_P1 t/m dig_P9
    void setChipDefinedRegistersPress();
/// \brief
/// setChipDefinedRegistersHum
/// \details
/// Gets the register data from the chip and buts it in dig_H1 t/m dig_H6
    void setChipDefinedRegistersHum();

    hwlib::i2c_bus &bus;

public:
    BME280(hwlib::i2c_bus &bus):
    bus(bus)
    {
        setChipDefinedRegistersTemp();
        setChipDefinedRegistersPress();
        setChipDefinedRegistersHum();
    }

/// \brief
/// GetTemp override
/// \details
/// Gets the tempature that the BME280 reads.
    double GetTemp() override;
/// \brief
/// GetPressure override
/// \details
/// Gets the atmospheric pressure that the BME280 reads.
    int GetPressure() override;
/// \brief
/// GetHumidity override
/// \details
/// Gets the humidity that the BME280 reads.
    double GetHumidity() override;

};



#endif //V1OOPC_EXAMPLES_BME280_HPP
