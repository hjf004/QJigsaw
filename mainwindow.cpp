#include"mainwindow.h"
#include"setting.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    sec=0;
    level=1;
    game=NULL;
    pic=NULL;
    showOrHide=false;
    source=QPixmap(":/resources/pixmaps/longkui.jpg");
    timer.setInterval(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(handleTimeOut()));
//    game=new Game(2,this);
    menuBar=new QMenuBar(this);
    gameMenu=new QMenu(tr("Game"),menuBar);
    QAction *newGame=gameMenu->addAction(tr("New Game"));
    newGame->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    connect(newGame,SIGNAL(triggered()),this,SLOT(handleNew()));
    QAction *settings=gameMenu->addAction(tr("Settings"));
    connect(settings,SIGNAL(triggered()),this,SLOT(handleSettings()));
    QAction *quit=gameMenu->addAction(tr("Quit"));
    connect(quit,SIGNAL(triggered()),this,SLOT(close()));
    help=new QMenu(tr("Help"),this);
    QAction *helpInfo=help->addAction(tr("Help Information"));
    connect(helpInfo,SIGNAL(triggered()),this,SLOT(handleHelp()));
    showAction=help->addAction(tr("Show picture."));
    connect(showAction,SIGNAL(triggered()),this,SLOT(handleShow()));
    QAction *about=help->addAction(tr("About"));
    connect(about,SIGNAL(triggered()),this,SLOT(handleAbout()));

    menuBar->addMenu(gameMenu);
    menuBar->addMenu(help);
    setMenuBar(menuBar);
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    handleNew();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
//    setFixedSize(game->getWidth(),game->getHeight()+menuBar->height());
//    setCentralWidget(game);
//    connect(game,SIGNAL(win()),this,SLOT(handleWin()));
//    connect(&timer,SIGNAL(timeout()),this,SLOT(handleTimeOut()));
//    timer.start();
}

void MainWindow::handleWin()
{
    timer.stop();
    QMessageBox::StandardButton r=QMessageBox::information(this,tr("You Win!"),tr("You Win the Game.Take Out %1 Seconds.Once again?").arg(sec),QMessageBox::Yes,QMessageBox::No);
    if(r==QMessageBox::Yes)
        handleNew();
}

void MainWindow::handleTimeOut()
{
    sec+=1;
}

void MainWindow::handleAbout()
{
    QMessageBox::about(this,tr("About"),tr("This is a jigsaw game written by HuJifeng.Just for Killing time!(Not a joke...)"));
}

void MainWindow::handleNew()
{
    if(game!=0)
        delete game;
    sec=0;
    if(showOrHide)
    {
        handleShow();
    }
    game=new Game(source,level,this);
    timer.start();
    connect(game,SIGNAL(win()),this,SLOT(handleWin()));
    setCentralWidget(game);
//    setFixedSize(game->getWidth(),game->getHeight()+menuBar->height());
}

void MainWindow::handleSettings()
{
    Setting *s=new Setting(this,level);
    s->show();
}

void MainWindow::setSource(QPixmap &p)
{
    if(p.width()>640)
        source=p.scaledToWidth(640);
    if(p.height()>600)
    {
        source=p.scaledToHeight(600);
        return;
    }
        source=p;
}

void MainWindow::setLevel(int l)
{
    level=l;
}

void MainWindow::handleHelp()
{
    QMessageBox::information(this,tr("Help"),tr("The Author is to lazy to write anything..."));
}

void MainWindow::handleShow()
{
    if(showOrHide)
    {
        pic->hide();
        delete pic;
        showOrHide=!showOrHide;
        showAction->setText(tr("Show Picture"));
    }
    else
    {
        pic=new Piece(*(game->getSource()),0,0);
        pic->setFixedSize(game->getWidth(),game->getHeight());
        showOrHide=!showOrHide;
        showAction->setText(tr("Hide Picture"));
        pic->move(pos()+QPoint(width(),0));
        connect(pic,SIGNAL(closed()),this,SLOT(handlePicClose()));
        pic->show();
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->accept();
    exit(0);
}

void MainWindow::handlePicClose()
{
    showOrHide=!showOrHide;
    showAction->setText(tr("Show Picture"));
}
