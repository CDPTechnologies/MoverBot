#include "control.h"
#include <string.h>

using namespace RbControl;

control::control()
{
    Flag = true;
}

control::~control()
{
}

void control::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    cmd_ln.Create("cmd_ln",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)&control::cmdHandler,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    cmdHistory.Create("cmdHistory",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    fileName.Create("fileName",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)&control::fileHandler,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    DelayTimer.Create("DelayTimer",this);
    leftFoward.Create("leftFoward",this);
    leftBackward.Create("leftBackward",this);
    rightFoward.Create("rightFoward",this);
    rightBackward.Create("rightBackward",this);
    leftEnable.Create("leftEnable",this);
    rightEnable.Create("rightEnable",this);
}

void control::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&control::ProcessNull, "Initial Null state");
    RegisterMessage(CM_TEXTCOMMAND,"MOVE_UP","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageMOVE_UP);
    RegisterMessage(CM_TEXTCOMMAND,"MOVE_DOWN","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageMOVE_DOWN);
    RegisterMessage(CM_TEXTCOMMAND,"MOVE_LEFT","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageMOVE_LEFT);
    RegisterMessage(CM_TEXTCOMMAND,"MOVE_RIGHT","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageMOVE_RIGHT);
    RegisterMessage(CM_TEXTCOMMAND,"SPIN","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageSPIN);
    RegisterMessage(CM_TEXTCOMMAND,"DoCircle","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageDoCircle);
    RegisterMessage(CM_TEXTCOMMAND,"Asterisk","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageAsterisk);
    RegisterMessage(CM_TEXTCOMMAND,"DoRetangle","",(CDPOBJECT_MESSAGEHANDLER)&control::MessageDoRetangle);
}

void control::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
}

void control::ProcessNull()
{
    leftEnable = true;
    rightEnable = true;
    if(DelayTimer.TimedOut() && !Flag)
    {
        cleanUp();
    }
}



int control::MessageMOVE_UP(void* message)
{
    moveUp(60.0);
    return 1;

}



int control::MessageMOVE_DOWN(void* message)
{
    moveDown(60.0);
    return 1;

}



int control::MessageMOVE_LEFT(void* message)
{
    moveLeft(60.0);
    return 1;

}



int control::MessageMOVE_RIGHT(void* message)
{
    moveRight(60.0);
    return 1;

}



int control::MessageSPIN(void* message)
{
    moveLeft(120.0);
    return 1;

}



int control::MessageDoCircle(void* message)
{
    moveLeft(60.0);
    moveUp(60.0);
    moveLeft(60.0);
    moveUp(60.0);
    return 1;

}



int control::MessageAsterisk(void* message)
{
    moveUp(60.0);
    moveDown(120.0);

    moveLeft(30.0);

    moveUp(60.0);
    moveDown(120.0);

    moveRight(60.0);

    moveUp(60.0);
    moveDown(120.0);
    return 1;

}



int control::MessageDoRetangle(void* message)
{
    moveUp(60.0);
    moveLeft(30.0);

    moveUp(60.0);
    moveLeft(30.0);

    moveUp(60.0);
    moveLeft(30.0);

    moveUp(60.0);
    moveLeft(30.0);
    return 1;

}

void control::fileHandler(CDPPropertyBase* pProperty)
{
    std::string line;
    std::ifstream file(pProperty->GetValue().c_str());

    std::string extension = pProperty->GetValue().substr(pProperty->GetValue().find("."));

    if(file.is_open() && file.good())
    {
        if(extension != ".cdp") { writeHistory("File Extension is not correct!"); return;}

        while(getline(file,line))
        {
            cmd_ln.SetValue(line);
        }
        file.close();
    }
    else
    {
        writeHistory("Could not open file");
    }
}

void control::moveDown(double ms)
{
    if(ms <= 0) { return; }

    if(Flag)  {
    CDPMessage("Turning down %f seconds\r\n",ms);
    leftBackward = true;
    rightBackward = true;
    DelayTimer.SetValue(ms);
    DelayTimer.Restart();
    Flag = false;
    }
}


void control::moveLeft(double ms)
{
    if(ms <= 0) { return; }

    if(Flag)  {
    CDPMessage("Turning left %f seconds\r\n",ms);
    rightFoward = true;
    DelayTimer.SetValue(ms);
    DelayTimer.Restart();
    Flag = false;
    }

}


void control::moveUp(double ms)
{
    if(ms <= 0) { return; }

    if(Flag)  {
    CDPMessage("Turning up %f seconds\r\n",ms);
    leftFoward = true;
    rightFoward = true;
    DelayTimer.SetValue(ms);
    DelayTimer.Restart();
    Flag = false;
    }
}


void control::moveRight(double ms)
{
    if(ms <= 0) { return; }

    if(Flag)  {
    CDPMessage("Turning right %f seconds\r\n",ms);
    leftFoward = true;
    DelayTimer.SetValue(ms);
    DelayTimer.Restart();
    Flag = false;
    }
}


std::string control::getTime()
{
    time_t currentTime;

    time( &currentTime );

    return std::string(asctime(localtime(&currentTime)));
}

void control::cleanUp()
{
    leftFoward = false;
    leftBackward = false;
    rightFoward = false;
    rightBackward = false;
    Flag = true;
}


int control::readcommand(std::string command)
{
    std::vector<std::string> cmdList = {"moveUp","moveDown","moveRight","moveLeft"};
    int j = 0;
    for(const std::string& i: cmdList)
    {
        j++;
        if((command.find(i) != std::string::npos) && (command.find(" ") != std::string::npos))
        {
            if(command.length() >= (command.find(" ") + 1))
            {
                return j;
            }
            else
            {
                writeHistory("Command failed! Use proper syntax Command value");
                return 0;
            }
        }
    }
    writeHistory("Command not Found");
    return 0;
}


void control::writeHistory(std::string command)
{
    std::string tmp = getTime();
    tmp.append(" - ");tmp.append(command);

    cmdHistory.SetValue(tmp);
}


void control::chooseFunction(int times, int command)
{
    switch(command)
    {
    case 1:
        moveUp(times);
        break;
    case 2:
        moveDown(times);
        break;
    case 3:
        moveRight(times);
        break;
    case 4:
        moveLeft(times);
        break;
    }
}

void control::cmdHandler(CDPPropertyBase* pProperty)
{
    writeHistory(pProperty->GetValue());
    chooseFunction(std::stoi(pProperty->GetValue().substr((pProperty->GetValue().find(" ") + 1))),readcommand(pProperty->GetValue()));
}

