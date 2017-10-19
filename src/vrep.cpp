#include "vrep.hpp"

using namespace vrep;

extern "C"
{
    #include "extApi.h"
}

VREP::VREP()
{
    clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 2000, 5);
}

int VREP::getClientId()
{
  return clientID;
}

int VREP::getObjectNumber()
{
    int objectCount;
    int* objectHandles;
    int ret = simxGetObjects(clientID, sim_handle_all, &objectCount, &objectHandles, simx_opmode_blocking);
    if (ret == simx_return_ok)
    {
        return objectCount;
    }
    else
    {
        //printf("Remote API function call returned with error code: %d\n",ret);
    }

    return -1;
}

void VREP::sendStatusMessage(string message)
{
    simxAddStatusbarMessage(clientID, message.c_str(), simx_opmode_oneshot);
}

void VREP::getObjectHandle(string name, int * handle)
{
    simxGetObjectHandle(clientID, name.c_str(), handle, simx_opmode_blocking);
}

void VREP::setJointVelocity(int jointHandle, float targetVelocity)
{
    simxSetJointTargetVelocity(clientID, jointHandle, targetVelocity, simx_opmode_oneshot);
}

void VREP::setJointVelocity(string jointName, float targetVelocity)
{
    int handle = -1;
    getObjectHandle(jointName, &handle);
    if(handle != -1)
    {
      setJointVelocity(handle, targetVelocity);
    }
}

void VREP::setJointPosition(int jointHandle, float targetPosition)
{
    simxSetJointTargetPosition(clientID, jointHandle, targetPosition, simx_opmode_oneshot);
}

void VREP::setJointPosition(string jointName, float targetPosition)
{
    int handle = -1;
    getObjectHandle(jointName, &handle);
    if(handle != -1)
    {
      setJointPosition(handle, targetPosition);
    }
}

void VREP::initJointPositionStreaming(int jointHandle, float * currentPosition)
{
    simxGetJointPosition(clientID, jointHandle, currentPosition, simx_opmode_streaming);
}

void VREP::getJointPosition(int jointHandle, float * currentPosition)
{
    simxGetJointPosition(clientID, jointHandle, currentPosition, simx_opmode_streaming);
}

float VREP::getJointPosition(int jointHandle)
{
    float position;
    simxGetJointPosition(clientID, jointHandle, &position, simx_opmode_streaming);
    return position;
}

void VREP::getJointPosition(string jointName, float * currentPosition)
{
    int handle = -1;
    getObjectHandle(jointName, &handle);
    if(handle != -1)
    {
      getJointPosition(handle, currentPosition);
    }
}

void VREP::initJointVelocityStreaming(int jointHandle, float * currentVelocity)
{
    simxGetObjectFloatParameter(clientID, jointHandle, 2012, currentVelocity, simx_opmode_streaming);
}

void VREP::getJointVelocity(int jointHandle, float * currentVelocity)
{
    simxGetObjectFloatParameter(clientID, jointHandle, 2012, currentVelocity, simx_opmode_streaming);
}

void VREP::getJointVelocity(string jointName, float * currentVelocity)
{
    int handle = -1;
    getObjectHandle(jointName, &handle);
    if(handle != -1)
    {
      getJointVelocity(handle, currentVelocity);
    }
}

void VREP::initPositionStreaming(string objectName, string objectNameRelative, float * position)
{
    int objectHandle = -1;
    int objectHandleRelative = -1;
    getObjectHandle(objectName, &objectHandle);
    getObjectHandle(objectNameRelative, &objectHandleRelative);
    // Relative can be -1 to get absolute position
    if(objectHandle != -1)
    {
        simxGetObjectPosition(clientID, objectHandle, objectHandleRelative, position, simx_opmode_streaming);
    }
}

void VREP::getPosition(int objectHandle, int objectHandleRelative, float * position)
{
    simxGetObjectPosition(clientID, objectHandle, objectHandleRelative, position, simx_opmode_streaming);
}

void VREP::getPosition(string objectName, string objectNameRelative, float * position)
{
    int objectHandle = -1;
    int objectHandleRelative = -1;
    getObjectHandle(objectName, &objectHandle);
    getObjectHandle(objectNameRelative, &objectHandleRelative);
    // Relative can be -1 to get absolute position
    if(objectHandle != -1)
    {
        simxGetObjectPosition(clientID, objectHandle, objectHandleRelative, position, simx_opmode_streaming);
    }
}

void VREP::initOrientationStreaming(string objectName, string objectNameRelative, float * orientation)
{
    int objectHandle = -1;
    int objectHandleRelative = -1;
    getObjectHandle(objectName, &objectHandle);
    getObjectHandle(objectNameRelative, &objectHandleRelative);
    // Relative can be -1 to get absolute orientation
    if(objectHandle != -1)
    {
        simxGetObjectOrientation(clientID, objectHandle, objectHandleRelative, orientation, simx_opmode_streaming);
    }
}

void VREP::getOrientation(int objectHandle, int objectHandleRelative, float * orientation)
{
    simxGetObjectOrientation(clientID, objectHandle, objectHandleRelative, orientation, simx_opmode_streaming);
}

void VREP::getOrientation(string objectName, string objectNameRelative, float * orientation)
{
    int objectHandle = -1;
    int objectHandleRelative = -1;
    getObjectHandle(objectName, &objectHandle);
    getObjectHandle(objectNameRelative, &objectHandleRelative);
    // Relative can be -1 to get absolute orientation
    if(objectHandle != -1)
    {
        simxGetObjectOrientation(clientID, objectHandle, objectHandleRelative, orientation, simx_opmode_buffer);
    }
}

int VREP::createDummy(float size, const unsigned char * color)
{
    int handle;
    simxCreateDummy(clientID, size, color, &handle, simx_opmode_blocking);
    return handle;
}

void VREP::setPosition(int objectHandle, float * position)
{
    simxSetObjectPosition(clientID, objectHandle, -1, position, simx_opmode_oneshot);
}

void VREP::setOrientation(int objectHandle, float * orientation)
{
    simxSetObjectOrientation(clientID, objectHandle, -1, orientation, simx_opmode_oneshot);
}

bool VREP::getToggleButtonState(string uiName, int uiButtonID)
{
    int uiHandle = -1;
    simxGetUIHandle(clientID, uiName.c_str(), &uiHandle, simx_opmode_blocking);
    if(uiHandle != -1)
    {
        int properties;
        simxGetUIButtonProperty(clientID, uiHandle, uiButtonID, &properties, simx_opmode_streaming);
        return ((properties & sim_buttonproperty_isdown) != 0);
    }
    return false;
}

void VREP::enableControlLoop(int jointHandle)
{
    simxSetObjectIntParameter(clientID, jointHandle,sim_jointintparam_ctrl_enabled,1,simx_opmode_oneshot);
}

void VREP::disableControlLoop(int jointHandle)
{
    simxSetObjectIntParameter(clientID, jointHandle,sim_jointintparam_ctrl_enabled,0,simx_opmode_oneshot);
}

void VREP::appendStringSignal(const char* signalname, std::vector<float> matrixData)
{
    simxClearStringSignal(clientID, signalname, simx_opmode_oneshot);
    simxAppendStringSignal(clientID, signalname, (const unsigned char*)&matrixData[0], matrixData.size()*4, simx_opmode_oneshot);
}

void VREP::enableSynchronization()
{
    simxSynchronous(clientID, true);
}


void VREP::syncTrigger()
{
    simxSynchronousTrigger(clientID);
}

void VREP::getPingTime(int& pingTime)
{
    simxGetPingTime(clientID, &pingTime);
}

void VREP::getQuaternion(double& w, double& x, double& y, double& z)
{
    double* stringSignal;
    int size = 4;

    simxGetStringSignal(clientID, "roverHeading", (simxUChar**)&stringSignal, &size, simx_opmode_streaming);
    w = stringSignal[3];
    x = stringSignal[0];
    y = stringSignal[1];
    z = stringSignal[2];
}

int VREP::getSimulationTime()
{
    return simxGetLastCmdTime(clientID);
}
