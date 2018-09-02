#ifndef SETWIDTHDIALOG_H
#define SETWIDTHDIALOG_H

#include <QDialog>
#include "pipeitem.h"

namespace Ui {
class SetWidthDialog;
}

class SetWidthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetWidthDialog(PipeItem * pipeItem, QWidget *parent = nullptr);
    ~SetWidthDialog();

private:
    Ui::SetWidthDialog *ui;
    PipeItem *pipe;
protected slots:
    void okButtonPressed();
};

#endif // SETWIDTHDIALOG_H
