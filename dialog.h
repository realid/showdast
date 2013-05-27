#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ui_dialog.h"
#include "painttree.h"

class MyDialog: public QDialog, public Ui_Dialog
{
    Q_OBJECT
    public:
        MyDialog(QWidget *parent = 0);
    public slots:
        void show();
    private slots:
        void InsertClicked();
    private:
        PaintTree tree;
};

#endif
