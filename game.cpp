#include"game.h"
#include<ctime>
#include<cstdlib>
void Game::setLevel(int l)
{
    level=l;
}

Game::Game(QPixmap p,int l,QWidget *parent):QWidget(parent)
{
    level=l;
    source=p;
    glayout=new QGridLayout(this);
    glayout->setSpacing(0);
    glayout->setMargin(0);
    init();
    setFixedSize(dw*col,dh*row);
    setLayout(glayout);
}

void Game::setSource(QPixmap &p)
{
    source=p;
}

void Game::init()
{
    stat.append(0);                                                     //0 empty;
    switch(level)
    {
        case 0:col=3;row=4;break;
        case 1:col=5;row=6;break;
        case 2:col=7;row=8;break;
    }
    max=col*row;
    dw=source.width()/col;
    dh=source.height()/(row-1);
    for(int i=1;i<col;i++)
    {
        pixmaps.insert(i,QPixmap(":/resources/pixmaps/block.jpg"));
        stat.append(1);                                                     //blocks
        pieces.append(new Piece(pixmaps[i],i,i,this));
        pieces[i-1]->setFixedSize(dw,dh);
//        pieceMap.insert(i,pieces[i-1]);
    }

    partition();

    pieces.append(new Piece(pixmaps[col],col,col,this));          //第一张图必须在左上角
    pieceMap.insert(col,pieces[col-1]);
    connect(pieces[col-1],SIGNAL(clicked(int,int)),this,SLOT(handleClick(int,int)));
    stat.append(2);
    int count=max-col-1;
    for(int i=0;i<count;i++)
    {
        pieces.append(new Piece(pixmaps[i+col+1],i+col+1,i+col+1,this));
        pieceMap.insert(i+col+1,pieces[i+col]);
        connect(pieces[i+col],SIGNAL(clicked(int,int)),this,SLOT(handleClick(int,int)));
        stat.append(2);                                                 //2 piece
    }
    do
    {
        moveBeforePlay();
    }
    while(check());

    for(int i=0;i<max-1;i++)
    {
        glayout->addWidget(pieces[i],pieces[i]->currentPos()/col,pieces[i]->currentPos()%col,1,1);
    }

}

void Game::partition()
{
   for(int i=1;i<row;i++)
        for(int j=0;j<col;j++)
        {
            pixmaps.insert(i*col+j,source.copy(dw*j,dh*(i-1),dw,dh));
        }
}

//void Game::randomArray(int index[],int len)
//{/*
//    srand((unsigned int)time(NULL));
//    int t;
//    bool flag=false;
//    for(int i=0;i<len;i++)
//    {
//        bool flag=false;
//        t=rand()%len;
//        for(int j=0;j<i;j++)
//        {
//            if(t==index[j])
//            {
//                flag=true;
//                break;
//            }
//        }
//        if(flag)
//            i--;
//        else
//            index[i]=t;
//    }*/
//    for(int i=0;i<len;i++)
//        index[i]=i;
//}

void Game::handleClick(int id,int cid)
{
    int x=cid/col;
    int y=cid%col;
//    qDebug()<<"You Clicked at "<<x<<","<<y;
    empty=findPlace(cid);
//    qDebug()<<empty;
    if(empty!=-1)
    {
        pieces[id-1]->moveMe(empty);
        stat[cid]=0;
        stat[empty]=2;
        glayout->removeWidget(pieces[id-1]);
        glayout->addWidget(pieces[id-1],empty/col,empty%col,1,1);
        this->update();
        if(check())
            emit win();
//        pieces.move(id-col,empty-);
    }
}

int Game::findPlace(int id)
{
    int a=id/col;
    if(id+1<max&&(id+1)/col==a)
        if(!stat[id+1])
            return id+1;
    if(id-1>-1&&(id-1)/col==a)
        if(!stat[id-1])
            return id-1;
    if(id+col<max)
        if(!stat[id+col])
            return id+col;
    if(id-col>-1)
        if(!stat[id-col])
            return id-col;
    return -1;
}

bool Game::check()
{
    for(int i=0;i<pieces.size();i++)
    {
        if(!pieces[i]->check())
            return false;
    }
    return true;
}

int Game::findPiece(int id)
{
    num.clear();
    int a=id/col;
    if(id+1<max&&(id+1)/col==a&&stat[id+1]==2)
            num.append(id+1);
    if(id-1>-1&&(id-1)/col==a&&stat[id-1]==2)
            num.append(id-1);
    if(id+col<max&&stat[id+col]==2)
            num.append(id+col);
    if(id-col>-1&&stat[id-col]==2)
            num.append(id-col);
    if(num.size()>1)                //take attention
        num.removeOne(lastPos);
    srand((unsigned int)time(NULL));
    a=rand()%(num.size());
    lastPos=id;
    return num[a];
}

void Game::moveBeforePlay()
{
    empty=0;
    lastPos=0;
    int n=max*max*50;
    int id;
    Piece *p=NULL;
    for(int i=0;i<n;i++)
    {
        id=findPiece(empty);
        pieceMap[id]->moveMe(empty);
        p=pieceMap[id];
        pieceMap.remove(id);
        pieceMap.insert(empty,p);
        stat[empty]=2;
        stat[id]=0;
        empty=id;
    }
}

int Game::getWidth()
{
    return dw*col;
}

int Game::getHeight()
{
    return dh*(row-1);
}

//void Game::showPic()
//{
//    QLabel *pic=new QLabel(this);
//    pic->setPixmap(source.scaled(dw*col,dh*row));
//    pic->setFixedSize(dw*col,dh*row);
//    delete layout();
//    glayout=new QGridLayout(this);
//    glayout->setMargin(0);
//    glayout->setSpacing(0);
//    for(int i=0;i<max-1;i++)
//    {
//        glayout->addWidget(pieces[i],pieces[i]->currentPos()/col,pieces[i]->currentPos()%col,1,1);
//    }
//    QHBoxLayout *hbox=new QHBoxLayout(this);
//    hbox->addLayout(glayout);
//    hbox->addWidget(pic);
//    setLayout(hbox);
//}

//void Game::hidePic()
//{
//    delete layout();
//    delete glayout;
//    glayout=new QGridLayout(this);
//    glayout->setMargin(0);
//    glayout->setSpacing(0);
//    for(int i=0;i<max-1;i++)
//    {
//        glayout->addWidget(pieces[i],pieces[i]->currentPos()/col,pieces[i]->currentPos()%col,1,1);
//    }
//    setLayout(glayout);
//}

QPixmap* Game::getSource()
{
    return &source;
}
