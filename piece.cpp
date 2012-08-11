#include"piece.h"

Piece::Piece(QPixmap& pix,int ci,int ri,QWidget *parent):QLabel(parent)
{
    setPixmap(pix);
    id=ci;
    cid=ci;
    rid=ri;
}

void Piece::mouseReleaseEvent(QMouseEvent *ev)
{
        emit clicked(id,cid);
}

void Piece::moveMe(int n)
{
    cid=n;
}

bool Piece::check()
{
    return cid==rid;
}

int Piece::currentPos()
{
    return cid;
}

void Piece::closeEvent(QCloseEvent *e)
{
    e->accept();
    emit closed();
}
