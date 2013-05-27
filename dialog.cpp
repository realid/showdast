#include "dialog.h"

MyDialog::MyDialog(QWidget *parent): QDialog(parent),tree(this)
{
    setupUi(this);
    connect(Insert, SIGNAL(clicked()), this, SLOT(InsertClicked()));
}

void MyDialog::InsertClicked()
{
    int value = InsertBox->value();
    tree.pTree->Insert(value);
    tree.update();
    return;
}

void MyDialog::show()
{
    tree.show();
    QWidget::show();
}
