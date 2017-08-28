/**
RbControlBuilder header file.
*/

#ifndef RBCONTROL_RBCONTROLBUILDER_H
#define RBCONTROL_RBCONTROLBUILDER_H

#include <CDPSystem/Application/CDPBuilder.h>

namespace RbControl {

class RbControlBuilder : public CDPBuilder
{
public:
    RbControlBuilder(const char* libName,const char* timeStamp);
    CDPComponent* CreateNewComponent(const std::string& type) override;
    CDPBaseObject* CreateNewCDPOperator(const std::string& modelName,const std::string& type,const CDPPropertyBase* inputProperty) override;
};

}

#endif // RBCONTROL_RBCONTROLBUILDER_H
