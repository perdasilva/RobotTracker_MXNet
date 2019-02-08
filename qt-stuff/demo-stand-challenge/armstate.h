#ifndef ARMSTATE_H
#define ARMSTATE_H

#include<array>
#include<QString>

class ArmState
{
public:
    ArmState();
private:
    const QString arm;
    float x,y,z,yaw,pitch,roll;

};

#endif // ARMSTATE_H
