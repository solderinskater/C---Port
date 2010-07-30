#-------------------------------------------------
#
# Project created by QtCreator 2010-06-19T13:39:15
#
#-------------------------------------------------

QT       += core gui

TARGET = TiltNRoll
TEMPLATE = app


SOURCES += main.cpp\
    startscreen.cpp \
    buttons.cpp \
    tiltnroll.cpp \
    playscreen.cpp \
    settingsscreen.cpp \
    singleplayerscreen.cpp \
    freestylescreen.cpp \
    pausescreen.cpp \
    timeline.cpp \
    graph.cpp \
    enternamescreen.cpp \
    highscore.cpp \
    highscorescreen.cpp

HEADERS  += \
    startscreen.h \
    buttons.h \
    tiltnroll.h \
    playscreen.h \
    settingsscreen.h \
    singleplayerscreen.h \
    freestylescreen.h \
    pausescreen.h \
    timeline.h \
    graph.h \
    enternamescreen.h \
    highscore.h \
    highscorescreen.h

CONFIG += mobility
MOBILITY = systeminfo

symbian {
    TARGET.UID3 = 0xe0c33b86
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000 # 80 kB
    #TARGET.EPOCHEAPSIZE = 0x020000 0x800000 # Min 128 kB, Max 8 Mb
    TARGET.EPOCHEAPSIZE = 0x020000 0x2000000 # Min 128 kB, Max 32 Mb
}

RESOURCES += \
    Resources/buttons/btn.qrc \
    Resources/anims/anims.qrc \
    Resources/sounds/sounds.qrc \
    Resources/tnr.qrc \
    Resources/backgrounds/backgrounds.qrc

OTHER_FILES += \
    .gitignore \
    hours.txt \
    todo.txt \
    dev-installation.txt
