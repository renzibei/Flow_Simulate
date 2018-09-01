#include "mainwindow.h"
#include "settingdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingDialog settingDialog;
    settingDialog.show();
    //w.show();

    return a.exec();
}
