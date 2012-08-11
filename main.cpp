#include"mainwindow.h"
#include"game.h"
#include<QtGui>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTranslator translator;
    translator.load(":/resources/locales/lang.qm");
    a.installTranslator(&translator);
    MainWindow *m=new MainWindow();
    m->show();
    return a.exec();
}
