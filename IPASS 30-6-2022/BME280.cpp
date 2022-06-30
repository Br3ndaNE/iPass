/****************************************************************************************************************************
*  auther ::       Brendan Endenburg
* File ::              BME280.cpp
* Date::           29 - 06 - 2022
* copyright:    Brendan Endenburg 2022
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

#include "hwlib.hpp"
#include "BME280.hpp"


// function that converts 2x unsigned 8bits to a unsigned 16bit
uint16_t convert_to_uint16t(uint16_t & name, uint8_t&last_bits, uint8_t&first_bits){
    name = (uint16_t)last_bits << 8;
    name = name | (uint16_t)first_bits;
    return name;
};

// function that converts 2x unsigned 8bits to a signed 16bit
int16_t convert_to_int16t(int16_t & name, uint8_t&last_bits, uint8_t&first_bits){
    name = (uint16_t)last_bits << 8;
    name = name | (uint16_t)first_bits;
    return name;
};

// function that converts 2x signed 8bits to a signed 16bit
int16_t int8_t_convert_to_int16t(int16_t & name, int8_t&last_bits, int8_t&first_bits){
    name = (uint16_t)last_bits << 8;
    name = name | (uint16_t)first_bits;
    return name;
};

// function that converts 3 unsigned bytes to 20 bits
uint32_t threebytes_to_20bits(uint32_t & total, uint8_t & reg0, uint8_t & reg1, uint8_t & reg2){
    reg2 = reg2 >> 4;
    total = reg0 << 8;
    total = total | reg1;
    total = total << 4;
    total = total | reg2;
    return total;
}


void BME280::setChipDefinedRegistersTemp(){
    uint_fast8_t parameter_readout = 0x88;
    uint8_t results_registers[6];


        bus.write(address).write(parameter_readout);

    { hwlib::i2c_read_transaction rtrans = bus.read(address);
        rtrans.read(results_registers, 6);}

    convert_to_uint16t(dig_T1,results_registers[1],results_registers[0]);
    convert_to_int16t(dig_T2,results_registers[3],results_registers[2]);
    convert_to_int16t(dig_T3,results_registers[5],results_registers[4]);

};

void BME280::setChipDefinedRegistersPress(){
    uint_fast8_t parameter_readout = 0x8E;
    uint8_t results_registers[18];

    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(parameter_readout);}

    { hwlib::i2c_read_transaction rtrans = bus.read(address);
        rtrans.read(results_registers, 18);}

    convert_to_uint16t(dig_P1,results_registers[1],results_registers[0]);
    convert_to_int16t(dig_P2,results_registers[3],results_registers[2]);
    convert_to_int16t(dig_P3,results_registers[5],results_registers[4]);
    convert_to_int16t(dig_P4,results_registers[7],results_registers[6]);
    convert_to_int16t(dig_P5,results_registers[9],results_registers[8]);
    convert_to_int16t(dig_P6,results_registers[11],results_registers[10]);
    convert_to_int16t(dig_P7,results_registers[13],results_registers[12]);
    convert_to_int16t(dig_P8,results_registers[15],results_registers[14]);
    convert_to_int16t(dig_P9,results_registers[17],results_registers[16]);
};

void BME280::setChipDefinedRegistersHum(){
    uint_fast8_t parameter_readout = 0xA1;
    uint8_t results_registers[9];

    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(parameter_readout);}

    { hwlib::i2c_read_transaction rtrans = bus.read(address);
        rtrans.read(results_registers, 9);}

    dig_H1 = dig_H1 | (uint8_t)results_registers[0];
    convert_to_int16t(dig_H2,results_registers[2],results_registers[1]);
    dig_H3 = dig_H3 | (uint8_t)results_registers[3];
    convert_to_int16t(dig_H4,results_registers[5],results_registers[4]);
    convert_to_int16t(dig_H5,results_registers[7],results_registers[6]);
    dig_H6 = dig_H6 | (int8_t)results_registers[8];
};




double BME280::GetTemp(){
    uint8_t results[3];
    uint32_t totalbits;

    double var1;
    double var2;

    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(ctrl_meas);
        wtrans.write(reg_data);}

    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(temp_msb);}

    { hwlib::i2c_read_transaction rtrans = bus.read(address);
        rtrans.read(results, 3)
                ;}

    threebytes_to_20bits(totalbits, results[0], results[1], results[2]);


    //formula for getting the temp
    var1 = (((double)totalbits)/16384.0-((double)dig_T1)/1024.0) * ((double)dig_T2);
    var2 = ((((double)dig_T1)/131072.0 - ((double)dig_T1)/8192) * (((double)totalbits)/131072.0-((double)dig_T1)/8192.0)) * ((double)dig_T3);
    t_fine = (int32_t) (var1 + var2);
    double Temperature = (var1+var2)/5120.0;

    return Temperature;

};

int BME280::GetPressure(){
    uint8_t results[3];
    uint32_t totalbits = 0;
    double var1, var2, p;

    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(ctrl_meas);
        wtrans.write(reg_data);}

    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(press_msb);}

    { hwlib::i2c_read_transaction rtrans = bus.read(address);
        rtrans.read(results, 3);}


    threebytes_to_20bits(totalbits, results[0], results[1], results[2]);

    //formula for getting the pressure
    var1= ((double)t_fine/2.0) - 64000.0;
    var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
    var2 =var2 + var1 * ((double)dig_P5) *2.0;
    var2 = (var2/4.0) + (((double)dig_P4) * 65536.0);
    var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0)* ((double)dig_P1);
    if(var1 == 0 ){
    }
    p = 1048576.0 - (double)totalbits;
    p = (p- (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((double)dig_P9) * p * p / 2147483648.0;
    var2= p* ((double)dig_P8) / 32768.0;
    p = p + (var1 + var2 + ((double) dig_P7)) / 16.0;
    return p;
}



double BME280::GetHumidity(){
    uint8_t results[2];
    uint_fast16_t totalbits;
    double var_H;
    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(ctrl_hum);
        wtrans.write(reg_data_hum);}


    { hwlib::i2c_write_transaction wtrans = bus.write(address);
        wtrans.write(hum_msb);}

    { hwlib::i2c_read_transaction rtrans = bus.read(address);
        rtrans.read(results, 2)
                ;}

    uint_fast8_t res0 = results[0];
    uint_fast8_t res1 = results[1];
    totalbits = res0 << 8;
    totalbits = totalbits | res1;

    //formula for getting the humidity
    var_H = (((double)t_fine) - 76800.0);
    var_H = (totalbits - (((double)dig_H4) * 64.0 + ((double)dig_H5) / 16384.0 *
            var_H)) * (((double)dig_H2) / 65536.0 * (1.0 + ((double)dig_H6) / 67108864.0 * var_H * (1.0 + ((double)dig_H3) / 67108864.0 * var_H)));
    var_H = var_H * (1.0 - ((double)dig_H1) * var_H / 524288.0);
    return var_H;

}
