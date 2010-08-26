#include <QtGui/QApplication>
#include "tiltnroll.h"
//#ifdef Q_OS_SYMBIAN
//#include <QSystemInfo> //(1)
//#include <qsysteminfo.h>
//#else
//#include <QSystemInfo> //(1)
//#endif
//using namespace QtMobility; //(2)
#ifdef Q_OS_SYMBIAN
#include <eikspane.h>
#include <aknappui.h>
#include <avkon.rsg>
#include <EIKENV.H>
#include <coemain.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // load Adore64 font
    QFontDatabase::addApplicationFont(":/fonts/Adore64.ttf");

    // read stylesheet
    QFile f(":/tnr.css");
    if (f.open(QIODevice::ReadOnly)) {
        a.setStyleSheet(f.readAll());
        f.close();
    }

    TiltNRoll w;

#ifdef Q_OS_SYMBIAN
    // lock orientation
    CAknAppUi* appUi = dynamic_cast<CAknAppUi*>(CEikonEnv::Static()->AppUi());
    if(appUi){
        QT_TRAP_THROWING(appUi ->SetOrientationL(CAknAppUi::EAppUiOrientationLandscape));
    }
    CEikStatusPane* statusPane = STATIC_CAST( CAknAppUi*, CEikonEnv::Static()->EikAppUi())->StatusPane();
    statusPane->MakeVisible(EFalse);
    w.showFullScreen();
#else
    w.showFullScreen();
#endif

    return a.exec();
}
