TARGET = core
VERSION = 1.0.0.0

QT -= core gui
#TEMPLATE = app
TEMPLATE = lib
CONFIG += console

#DEFINES += CORE_LIBRARY

#CONFIG += thread

#LIBS += -L"$$_PRO_FILE_PWD_/libs/windows/x86/" -l"Ws2_32"
#LIBS += -L"$$_PRO_FILE_PWD_/../core-build-desktop/debug/" -l"core"
LIBS += -L"$$_PRO_FILE_PWD_/libs/windows/x86-x64/" -l"Ws2_32"

#LIBS += -l"socket" -l"nsl"

HEADERS += \
	intermediary/time.h \
    intermediary/math.h \
    intermediary/random.h \
	intermediary/directory.h \
    intermediary/file.h \
    intermediary/stopwatch.h \
	intermediary/thread.h \
	basic/preprocesor.h \
	basic/cleaner.h \
	basic/memory.h \
    basic/binarywriter.h \
	basic/binaryreader.h \
	basic/string.h \
	logging/printer.h \
    logging/fileprinter.h \
    logging/consoleprinter.h \
    global.h \
    network/socket.h \
    network/server.h \
    network/parallelserver.h \
    network/client.h \
    unittests/network_parallelserver/checkingrun.h \
	parsing/valueparser.h \
	parsing/parserutils.h \
    basic/unittest.h \
    unittests/basic_string/checkingcstringlength.h \
    unittests/basic_valueparser/checkingvalueparser.h \
    network/networkutils.h \
    console/consolemenu.h \
    console/consoleoperations.h \
    basic/list.h \
	unittests/console_consolemenu/checkingrun.h \
    basic/toggle.h \
    basic/calllist.h \
    basic/safepointer.h

SOURCES += \
    main.cpp \
    intermediary/time.cpp \
    intermediary/math.cpp \
    intermediary/random.cpp \
	intermediary/directory.cpp \
	intermediary/file.cpp \
    intermediary/stopwatch.cpp \
	intermediary/thread.cpp \
    basic/memory.cpp \
    basic/binarywriter.cpp \
    basic/binaryreader.cpp \
	basic/string.cpp \
	logging/fileprinter.cpp \
	logging/consoleprinter.cpp \
    network/utils.cpp \
    network/socket.cpp \
    network/server.cpp \
    network/parallelserver.cpp \
    network/client.cpp \
	parsing/valueparser.cpp \
	parsing/parserutils.cpp \
    basic/unittest.cpp \
    console/consolemenu.cpp \
    console/consoleoperations.cpp
