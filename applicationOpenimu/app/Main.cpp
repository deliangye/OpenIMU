#include <QApplication>
#include <QTranslator>
#include<QMainWindow>
#include "MainWindow.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    QString locale = QLocale::system().name();

    QTranslator translator;
    if(translator.load(QString("../translations/openImu_") + locale))
    {
           qDebug() << QString("../translations/openImu_") + locale << " loaded";
            a.installTranslator(&translator);
    }
    else
    {
           qDebug() <<QString("../translations/openImu_") + locale << "loading failed";
    }

    //specify a new font.
    QFont newFont("Helvetica",9, QFont::Light, false);
    //set font of application
    QApplication::setFont(newFont);

    MainWindow *window = new MainWindow();
    window->show();

    return a.exec();
}



