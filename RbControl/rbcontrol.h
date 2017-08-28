/**
RbControl header file. Include this file in the project to use the library.
*/
#ifndef RBCONTROL_RBCONTROL_H
#define RBCONTROL_RBCONTROL_H

#include "RbControlBuilder.h"

namespace RbControl {

/** Instantiate the RbControlBuilder for this object */
RbControlBuilder gRbControlBuilder("RbControl", __TIMESTAMP__);

}

#endif // RBCONTROL_RBCONTROL_H
