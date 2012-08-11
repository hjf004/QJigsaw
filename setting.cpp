#include "setting.h"
#include"ui_setting.h"
#include<QtGui>
#include<QtGui/QStyle>
Setting::Setting(MainWindow *m,int l,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    mWind=m;
    ui->setupUi(this);
    ui->normal->setChecked(true);
    if(l==0)
        ui->easy->setChecked(true);
    else if(l==1)
        ui->normal->setChecked(true);
    else
        ui->hard->setChecked(true);
    QStyle *style=this->style();
    (ui->chooseFile)->setIcon(style->standardPixmap(QStyle::SP_FileDialogStart));
    connect(ui->chooseFile,SIGNAL(clicked()),this,SLOT(handleFileChoose()));
    connect(ui->confirmButton,SIGNAL(clicked()),this,SLOT(handleConfirm()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(handleCancel()));
}

Setting::~Setting()
{
    delete ui;
}

void Setting::handleFileChoose()
{
    filename=QFileDialog::getOpenFileName(this,tr("Choose File"),QDir::homePath(),tr("Images (*.png *.jpg)"));

}

void Setting::handleLevel()
{
    if(ui->easy->isChecked())
        mWind->setLevel(0);
    else if(ui->normal->isChecked())
        mWind->setLevel(1);
    else
        mWind->setLevel(2);
}

void Setting::handleConfirm()
{
    if(!filename.isEmpty())
    {
        QPixmap p(filename);
        mWind->setSource(p);
    }
    handleLevel();
    close();
}

void Setting::handleCancel()
{
    close();
}
