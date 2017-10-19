#ifndef _VREP_HPP_
#define _VREP_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace vrep
{
    class VREP
    {
    private:
        int clientID;
    public:
        VREP();
        int getClientId();
        int getObjectNumber();
        void sendStatusMessage(string message);
        void getObjectHandle(string name, int * handle);
        void setJointVelocity(int jointHandle, float targetVelocity);
        void setJointVelocity(string jointName, float targetVelocity);
        void setJointPosition(int jointHandle, float targetPosition);
        void setJointPosition(string jointName, float targetPosition);

        void initJointPositionStreaming(int jointHandle, float * currentPosition);
        void getJointPosition(int jointHandle, float * currentPosition);
        void getJointPosition(string jointName, float * currentPosition);
        float getJointPosition(int jointHandle);
        void initJointVelocityStreaming(int jointHandle, float * currentVelocity);
        void getJointVelocity(int jointHandle, float * currentVelocity);
        void getJointVelocity(string jointName, float * currentVelocity);

        void initPositionStreaming(string objectName, string objectNameRelative, float * position);
        void initOrientationStreaming(string objectName, string objectNameRelative, float * orientation);
        void getPosition(int objectHandle, int objectHandleRelative, float * position);
        void getPosition(string objectName, string objectNameRelative, float * position);
        void getOrientation(int objectHandle, int objectHandleRelative, float * orientation);
        void getOrientation(string objectName, string objectNameRelative, float * orientation);

        int createDummy(float size, const unsigned char * color);
        void setPosition(int objectHandle, float * position);
        void setOrientation(int objectHandle, float * orientation);
        bool getToggleButtonState(string uiName, int uiButtonID);

	void enableControlLoop(int jointHandle);
	void disableControlLoop(int jointHandle);

        void appendStringSignal(const char* signalname, std::vector<float> matrixData);
        void enableSynchronization();

        void syncTrigger();
        void getPingTime(int& pingTime);

        void getQuaternion(double& w, double& x, double& y, double& z);

        int getSimulationTime();
    };
}

#endif
