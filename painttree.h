#ifndef PAINTTREE_H
#define PAINTTREE_H

#include <QWidget>
#include "avltree.h"

class QPaintEvent;
class QPainter;

class PaintTree : public QWidget
{
    public:
        PaintTree(QWidget* parent=0);
        void paintEvent(QPaintEvent *event);
    public:
        AvlTree<int>* pTree;
};
#endif
