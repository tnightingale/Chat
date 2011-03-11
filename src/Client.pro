include(./Nightingale.pri)

include(./client/client.pri)
include(./core/core.pri)

DEPENDPATH  += .
INCLUDEPATH += .

HEADERS     += $$CLIENT_HDRS $$CORE_HDRS
SOURCES     += $$CLIENT_SRCS $$CORE_SRCS
FORMS       += $$CLIENT_FORMS
RESOURCES   += $$CLIENT_RES
