#ifndef GAME_H
#define GAME_H
#include"piece.h"
#include<QtGui>
class Game:public QWidget
{
    Q_OBJECT
public:
    Game(QPixmap p=QPixmap(":/resources/pixmaps/longkui.jpg"),int l=1,QWidget *parent=0);
    void init();
    void partition();
    void setSource(QPixmap&);
    void setLevel(int);                 //level easy,normal,hard.
//    void randomArray(int [],int);
    int findPlace(int);
    bool check();
    int findPiece(int);
    void moveBeforePlay();              //
    int getWidth();
    int getHeight();
    QPixmap* getSource();
private:
    int level;                          //level:0-2;easy:3x3;normal:5x5;hard:7x7
    QGridLayout *glayout;
    QMap<int,QPixmap> pixmaps;        //
    QMap<int,Piece*> pieceMap;        //a map of current pos and piece.
    QPixmap source;
    QList<int> stat;
    QList<Piece*> pieces;
    QList<int> num;                 //save some id that may be chosen.
    int row,col;
    int dw,dh;
    int max;
    int empty;
    int lastPos;
public slots:
    void handleClick(int,int);
signals:
    void win();
};
#endif // GAME_H
