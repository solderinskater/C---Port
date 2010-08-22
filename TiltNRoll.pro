#-------------------------------------------------
#
# Project created by QtCreator 2010-06-19T13:39:15
#
#-------------------------------------------------

TARGET = TiltNRoll
TEMPLATE = app
QT       += core gui


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
    highscorescreen.cpp \
    simulator/tricksimulator.cpp \
    newmat/svd.cpp \
    newmat/submat.cpp \
    newmat/sort.cpp \
    newmat/solution.cpp \
    newmat/newmatrm.cpp \
    newmat/newmatnl.cpp \
    newmat/newmatex.cpp \
    newmat/newmat9.cpp \
    newmat/newmat8.cpp \
    newmat/newmat7.cpp \
    newmat/newmat6.cpp \
    newmat/newmat5.cpp \
    newmat/newmat4.cpp \
    newmat/newmat3.cpp \
    newmat/newmat2.cpp \
    newmat/newmat1.cpp \
    newmat/newfft.cpp \
    newmat/myexcept.cpp \
    newmat/jacobi.cpp \
    newmat/hholder.cpp \
    newmat/fft.cpp \
    newmat/evalue.cpp \
    newmat/cholesky.cpp \
    newmat/bandmat.cpp \
    trickdetector.cpp \
    trickmanager.cpp \
	DTW/dtw.cpp\
    trainwidget.cpp \
    trainpage.cpp \
    soundplayer.cpp \
    recordwidget.cpp

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
    highscorescreen.h \
    simulator/tricksimulator.h \
    newmat/solution.h \
    newmat/precisio.h \
    newmat/newmatrm.h \
    newmat/newmatrc.h \
    newmat/newmatnl.h \
    newmat/newmatio.h \
    newmat/newmatap.h \
    newmat/newmat.h \
    newmat/myexcept.h \
    newmat/include.h \
    newmat/controlw.h \
    newmat/boolean.h \
    trickdetector.h \
    IOCapture.h \
    documentation.h \
    DTW/dtw.h \
    trickmanager.h\
    trainwidget.h \
    trainpage.h \
    ringbuffer.h \
    soundplayer.h \
    recordwidget.h

#CONFIG += mobility
#MOBILITY = systeminfo
#INCLUDEPATH += \NokiaQtSDK\Symbian\SDK\epoc32\include\QBlueTooth

symbian {
 #   deploy.path = $(EPOCROOT)
    TARGET.UID3 = 0xe0c33b86
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000 # 80 kB
    #TARGET.EPOCHEAPSIZE = 0x020000 0x800000 # Min 128 kB, Max 8 Mb
    TARGET.EPOCHEAPSIZE = 0x020000 0x2000000 # Min 128 kB, Max 32 Mb
    INCLUDEPATH += /epoc32/include/QBluetooth
 #                   /epoc32/include/QBluetooth

    LIBS += -lQBluetooth

 #   TARGET.CAPABILITY = LocalServices \
 #       NetworkServices \
 #       ReadUserData \
 #       UserEnvironment \
 #       WriteUserData
   TARGET.CAPABILITY = LocalServices \
        NetworkServices \
        ReadUserData \
        UserEnvironment \
        WriteUserData

    SOURCES += btcapture.cpp
    HEADERS += btcapture.h

#    addFiles.sources = $(EPOCROOT)Epoc32/BUILD/NokiaDev/C---Port/TILTNROLL_0XE0C33B87/GCCE/udeb/TiltNRoll.exe
    addFiles.sources = $(EPOCROOT)Epoc32/release/$(PLATFORM)/$(CFG)/QBluetooth.dll
    addFiles.path = /sys/bin
    DEPLOYMENT += addFiles
}

RESOURCES += \
    Resources/tnr.qrc \
    Resources/images.qrc \
    Resources/simulator/Simulator.qrc \
    Resources/fonts.qrc \
    Resources/sounds.qrc

#sounds.sources = Resources/sounds/*.wav
#DEPLOYMENT += sounds

OTHER_FILES += \
    .gitignore \
    hours.txt \
    todo.txt \
    dev-installation.txt \
    hours_private.txt \
    Resources/tnr.css
