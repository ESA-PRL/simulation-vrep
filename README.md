# V-REP simulation library

This library uses the [V-REP remote API](http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctions.htm) to communicate with a simulation environment in order to use it within the ROCK framework.

**Author: [Karl Kangur](mailto:karl.kangur@esa.int "Contact the author")  
Contact: [Martin Azkarate](mailto:Martin.Azkarate@esa.int "Contact the maintainer")  
Affiliation: Automation and Robotics Laboratories, ESTEC, ESA**

## Usage

### Building

Clone the library to `simulation/vrep` and add it to the ROCK manifest, call `amake`.

Note that the simulation in V-REP must be running before the script using this library is executed.

### Unit test

A test script is under `src/main.cpp`. It is built and stored under `build/vrep_test`. To run it call the executable with the device as argument:

    ./build/vrep_test
