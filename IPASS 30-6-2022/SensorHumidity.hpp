/****************************************************************************************************************************
*  auther ::       Brendan Endenburg
* File ::              SensorHumidity.hpp
* Date::           29 - 06 - 2022
* copyright:    Brendan Endenburg 2022
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

#ifndef V1OOPC_EXAMPLES_SENSORHUMIDITY_HPP
#define V1OOPC_EXAMPLES_SENSORHUMIDITY_HPP

///@file
/// \brief
/// Abstract SensorHumidity class
/// \details
/// SensorHumidity class that will be overwritten
class SensorHumidity {
public:
    virtual double GetHumidity() = 0;
};


#endif //V1OOPC_EXAMPLES_SENSORHUMIDITY_HPP
