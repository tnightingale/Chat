include(./Nightingale.pri)

include(./server/server.pri)
include(./core/core.pri)

DEPENDPATH  += .
INCLUDEPATH += .

OBJECTS_DIR  = ../obj/server

HEADERS     += $$SERVER_HDRS $$CORE_HDRS
SOURCES     += $$SERVER_SRCS $$CORE_SRCS
