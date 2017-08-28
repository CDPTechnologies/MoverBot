/**
RbControlBuilder implementation.
*/

#include "control.h"
#include "RbControlBuilder.h"

using namespace RbControl;

RbControlBuilder::RbControlBuilder(const char* libName, const char* timeStamp)
    : CDPBuilder(libName, timeStamp)
{
}

CDPComponent* RbControlBuilder::CreateNewComponent(const std::string& type)
{
    if (type=="RbControl.control")
        return new control;
    
    return CDPBuilder::CreateNewComponent(type);
}

CDPBaseObject* RbControlBuilder::CreateNewCDPOperator(const std::string& modelName, const std::string& type, const CDPPropertyBase* inputProperty)
{
    return CDPBuilder::CreateNewCDPOperator(modelName, type, inputProperty);
}
