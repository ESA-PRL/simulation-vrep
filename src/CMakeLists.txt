rock_library(vrep
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(vrep_bin Main.cpp
    DEPS vrep)

