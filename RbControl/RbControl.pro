CDPVERSION = 4.2
TYPE = library
PROJECTNAME = RbControl

DEPS += \

HEADERS += \
    rbcontrol.h \
    RbControlBuilder.h \
    control.h

SOURCES += \
    RbControlBuilder.cpp \
    control.cpp

DISTFILES += $$files(*.xml, true) \
    Templates/Models/RbControl.control.xml

load(cdp)
