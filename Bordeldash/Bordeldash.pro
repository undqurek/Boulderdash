QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../core/
LIBS += -L"C:\Users\qurek\Desktop\Projects - from Poland\projekty-z git mini itx\git\cpp\build-core\debug" -l"core1"

SOURCES += \
    main.cpp \
	logic\monstermovement.cpp \
	logic\objectmovement.cpp \
	logic\map.cpp \
	mvc/gamemodel.cpp \
	mvc/gameview.cpp \
	mvc/gamepart.cpp \
	mvc/gamecontroller.cpp \
    logic/bordeldashmodel.cpp \
    logic/bordeldashcontroller.cpp \
    console/bordeldashconsoleview.cpp \
    logic/playermovement.cpp

HEADERS += \
	logic\monstermovement.h \
	logic\objectmovement.h \
	logic\types.h \
	logic\map.h \
    logic/ui.h \
    mvc/gamemodel.h \
    mvc/gameview.h \
    mvc/gamepart.h \
    mvc/gamecontroller.h \
    logic/bordeldashview.h \
    logic/bordeldashmodel.h \
    logic/bordeldashcontroller.h \
    console/bordeldashconsoleview.h \
    logic/playermovement.h
