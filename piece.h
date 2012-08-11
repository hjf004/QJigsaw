#ifndef PIECE_H
#define PIECE_H

#include<QtGui>
class Piece:public QLabel
{
    Q_OBJECT
public:
    Piece(QPixmap&,int,int,QWidget *parent=0);
    void moveMe(int);
    int currentPos();
    bool check();
protected:
    void mouseReleaseEvent(QMouseEvent *ev);
    void closeEvent(QCloseEvent *);
signals:
    void clicked(int,int);
    void closed();
private:
    int id;
    int rid;
    int cid;
    int type;               //0:empty.1:block2:piece
};
#endif // PIECE_H
