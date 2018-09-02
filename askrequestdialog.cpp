#include "askrequestdialog.h"
#include "ui_askrequestdialog.h"

askRequestDialog::askRequestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askRequestDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(getTargetNet()));
}

void askRequestDialog::getTargetNet()
{

}

askRequestDialog::~askRequestDialog()
{
    delete ui;
}
