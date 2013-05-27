#include <QApplication>
#include <QTranslator>
#include "dialog.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QTranslator translator;
    translator.load("showdast_CN");
    app.installTranslator(&translator);
    MyDialog *dlg = new MyDialog;
    dlg->show();
//    PaintTree tree;
//    tree.pTree->Insert(10);
//    tree.show();

    return app.exec();
}
