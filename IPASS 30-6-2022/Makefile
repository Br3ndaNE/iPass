#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := BME280.cpp SensorHumidity.cpp SensorTemp.cpp SensorPressure.cpp weatherstation.cpp oled.cpp

# header files in this project
HEADERS := BME280.hpp SensorHumidity.hpp SensorTemp.hpp SensorPressure.hpp weatherstation.hpp oled.hpp

# other places to look for files for this project
SEARCH  := 

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
