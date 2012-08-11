#ifndef SETTING_H
#define SETTING_H
#include"mainwindow.h"
#include <QWidget>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT
    
public:
    explicit Setting(MainWindow *,int l=1,QWidget *parent = 0);
    ~Setting();
    void handleLevel();

public slots:
    void handleFileChoose();
    void handleConfirm();
    void handleCancel();
private:
    Ui::Setting *ui;
    MainWindow *mWind;
    QString filename;
};

#endif // SETTING_H
