#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"game.h"
#include"piece.h"
#include<QtGui>
class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=0);
    void setSource(QPixmap&);
    void setLevel(int);
public slots:
    void handleWin();
    void handleTimeOut();
//    void pause();
    void handleNew();
    void handleSettings();
    void handleHelp();
    void handleAbout();
    void handleShow();
    void handlePicClose();
protected:
    void closeEvent(QCloseEvent *);
private:
    Game *game;
    QMenuBar *menuBar;
    QMenu *gameMenu;
    QMenu *help;
    QTimer timer;
    int level;
    QPixmap source;
    int sec;
    bool showOrHide;
    Piece *pic;
    QAction *showAction;
};
#endif // MAINWINDOW_H
