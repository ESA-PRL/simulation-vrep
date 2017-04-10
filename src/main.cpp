#include <iostream>
#include <vrep/vrep.hpp>

int main(int argc, char** argv)
{
    vrep::VREP api;

    if(api.getClientId() == -1)
    {
        printf("Could not reach VREP simulation");
        return 0;
    }

    while(api.getClientId() != -1)
    {
        int objects = api.getObjectNumber();

        printf("Objects in the scene: %d\n", objects);

        api.sendStatusMessage("Hello from ROCK!");
    }

    return 0;
}
