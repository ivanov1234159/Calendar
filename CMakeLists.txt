cmake_minimum_required(VERSION 3.10)
project(Calendar)

set(CMAKE_CXX_STANDARD 14)

add_executable(Calendar main.cpp Time.cpp Date.cpp Appointment.cpp MyFunctions.cpp Calendar.cpp Commander.cpp)