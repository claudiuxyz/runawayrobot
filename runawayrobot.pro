TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    gameop.cpp \
    tile.cpp \
    tools.cpp \
    communicationservice.cpp \
    Algorithm.cpp \
    lazzybacktracking.cpp \
    backtracking.cpp \
    avoiddeadends.cpp

HEADERS += \
    board.h \
    gameop.h \
    position.h \
    tile.h \
    tools.h \
    communicationservice.h \
    Algorithm.h \
    lazzybacktracking.h \
    backtracking.h \
    avoiddeadends.h

