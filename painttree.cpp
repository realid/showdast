#include <QPainter>
#include <QPoint>
#include "painttree.h"

PaintTree::PaintTree(QWidget* parent) :QWidget(parent)
{
    pTree = new AvlTree<int>;
    resize(800, 600);
    setWindowTitle(tr("ShowTree"));
    setWindowFlags(windowFlags() | Qt::Window);
}

void PaintTree::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if (pTree->pRoot) {
        if (pTree->pRoot->Height != 0)
            pTree->Draw(pTree->pRoot, QPoint(size().width()/2, 25), 
                &painter, size().width()/4, 
                (size().height()-50)/(pTree->pRoot->Height),
                20);
        else
            pTree->Draw(pTree->pRoot, QPoint(size().width()/2, 25),
                &painter, size().width()/4,
                0, 20);
    }
}
