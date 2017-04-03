include_directories(../include ../remoteApi)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255")

add_library(extApi ../remoteApi/extApi.c)
add_library(extApiPlatform ../remoteApi/extApiPlatform.c)

target_include_directories(extApi PUBLIC ../include ../remoteApi)
target_include_directories(extApiPlatform PUBLIC ../include ../remoteApi)

target_link_libraries(extApi extApiPlatform -lpthread)

rock_library(vrep SOURCES vrep.cpp HEADERS vrep.hpp DEPS extApi extApiPlatform)

rock_executable(vrep_bin main.cpp DEPS vrep extApi extApiPlatform)
