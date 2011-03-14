include(../Nightingale.pri)

include(./server.pri)
include(../core/core.pri)

DEPENDPATH  += .
INCLUDEPATH += .

HEADERS     += $$SERVER_HDRS $$CORE_HDRS
SOURCES     += $$SERVER_SRCS $$CORE_SRCS
