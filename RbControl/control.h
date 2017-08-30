#ifndef RBCONTROL_CONTROL_H
#define RBCONTROL_CONTROL_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <OSAPI/Timer/CDPParameterTimer.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <iostream>
#include <fstream>
#include <time.h>

namespace RbControl {

class control : public CDPComponent
{
public:
    control();
    ~control() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;
    int MessageMOVE_UP(void* message);
    int MessageMOVE_DOWN(void* message);
    int MessageMOVE_LEFT(void* message);
    int MessageMOVE_RIGHT(void* message);
    int MessageSPIN(void* message);
    int MessageDoCircle(void* message);
    int MessageAsterisk(void* message);
    int MessageDoRetangle(void* message);

protected:
    void fileHandler(CDPPropertyBase* pProperty);
    void cmdHandler(CDPPropertyBase* pProperty);
    CDPProperty<std::string> cmd_ln;
    CDPProperty<std::string> cmdHistory;
    CDPProperty<std::string> fileName;
    CDPParameterTimer delayTimer;
    CDPSignal<bool> leftFoward;
    CDPSignal<bool> leftBackward;
    CDPParameterTimer delayTimer;
    CDPSignal<bool> rightFoward;
    CDPSignal<bool> rightBackward;
    CDPSignal<bool> leftEnable;
    CDPSignal<bool> rightEnable;
    void moveUp(double ms);
    void moveDown(double ms);
    void moveLeft(double ms);
    void moveRight(double ms);
    void cleanUp();
    void spin();
    void Circle();
    void Retangle();
    void asterisk();
    std::string getTime();
    bool Flag;
    void chooseFunction(int times, int command);
    void writeHistory(std::string command);
    int readcommand(std::string command);
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace RbControl

#endif
