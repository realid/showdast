#ifndef AVLTREE_H
#define AVLTREE_H
#include <QPoint>
#include <QPainter>
#include <cstdlib>
#include <QString>

template<class T>
class AvlNode {
    public:
        AvlNode():Left(NULL),Right(NULL),Height(0){}
    public:
        T Element;
        AvlNode *Left;
        AvlNode *Right;
        int Height;
};

template<class T>
class AvlTree {
    public:
        AvlTree():pRoot(NULL){}
        void MakeEmpty();
        AvlNode<T>* Find(T X);
        void Insert(T X);
        AvlNode<T>* Delete(T X);
        void Draw(AvlNode<T>* pNode, QPoint pt, QPainter* painter, 
                int scale, int height, int radi);
        void PreOrder(AvlNode<T>* pNode, void (*pf)(AvlNode<T>* pV));
    private:
        int Height(AvlNode<T>* Node);
        int Max(int cmpa, int cmpb);
        AvlNode<T>* InsertPri(AvlNode<T>* Node, T X);
        AvlNode<T>* SingleRotateWithLeft(AvlNode<T>* pNode);
        AvlNode<T>* SingleRotateWithRight(AvlNode<T>* pNode);
        AvlNode<T>* DoubleRotateWithLeft(AvlNode<T>* pNode);
        AvlNode<T>* DoubleRotateWithRight(AvlNode<T>* pNode);
    public:
        AvlNode<T>* pRoot;
};

template<class T>
AvlNode<T>* AvlTree<T>::Find(T X)
{
    AvlNode<T> *pNode = pRoot;
    while (pNode != NULL && pNode->Element() != X) {
        if (X < pNode->Element)
            pNode = pNode->Left;
        else
            pNode = pNode->Right;
    }

    return pNode;
}

template<class T>
int AvlTree<T>::Height(AvlNode<T>* pNode)
{
    if (pNode == NULL)
        return -1;
    else
        return pNode->Height;
}

template<class T>
int AvlTree<T>::Max(int cmpa, int cmpb)
{
    return cmpa > cmpb ? cmpa : cmpb;
}

template<class T>
AvlNode<T>* AvlTree<T>::SingleRotateWithLeft(AvlNode<T> *pNode)
{
    AvlNode<T> *pLeft = pNode->Left;
    pNode->Left = pLeft->Right;
    pLeft->Right = pNode;

    pNode->Height = Max(Height(pNode->Left), Height(pNode->Right)) + 1;
    pLeft->Height = Max(Height(pLeft->Left), pNode->Height) + 1;

    return pLeft;
}

template<class T>
AvlNode<T>* AvlTree<T>::SingleRotateWithRight(AvlNode<T> *pNode)
{
    AvlNode<T>* pRight = pNode->Right;
    pNode->Right = pRight->Left;
    pRight->Left = pNode;

    pNode->Height = Max(Height(pNode->Left), Height(pNode->Right)) + 1;
    pRight->Height = Max(Height(pRight->Right), pNode->Height) + 1;

    return pRight;
}

template<class T>
AvlNode<T>* AvlTree<T>::DoubleRotateWithLeft(AvlNode<T>* pNode)
{
    pNode->Left = SingleRotateWithRight(pNode->Left);
    return SingleRotateWithLeft(pNode);
}

template<class T>
AvlNode<T>* AvlTree<T>::DoubleRotateWithRight(AvlNode<T>* pNode)
{
    pNode->Right = SingleRotateWithLeft(pNode->Right);
    return SingleRotateWithRight(pNode);
}

template<class T>
AvlNode<T>* AvlTree<T>::InsertPri(AvlNode<T>* pNode, T X)
{
    if (pNode == NULL) {
        pNode = new AvlNode<T>;
        pNode->Element = X;
    } else if (X < pNode->Element) {
        pNode->Left = InsertPri(pNode->Left, X);
        if (Height(pNode->Left) - Height(pNode->Right) > 1) {
            if (X < pNode->Left->Element)
                pNode = SingleRotateWithLeft(pNode);
            else
                pNode = DoubleRotateWithLeft(pNode);
        }
    } else if (X > pNode->Element) {
        pNode->Right = InsertPri(pNode->Right, X);
        if (Height(pNode->Right) - Height(pNode->Left) > 1) {
            if (X > pNode->Right->Element)
                pNode = SingleRotateWithRight(pNode);
            else
                pNode = DoubleRotateWithRight(pNode);
        }
    }
    pNode->Height = Max(Height(pNode->Left), Height(pNode->Right)) + 1;
    return pNode;
}

template<class T>
void AvlTree<T>::Insert(T X)
{ 
    pRoot = InsertPri(pRoot, X);
}

template<class T>
void AvlTree<T>::Draw(AvlNode<T>* pNode, QPoint pt, 
        QPainter* painter, int scale, int height, int radi)
{
    QPoint end;
    QRect rect(QPoint(pt.x()-radi, pt.y()-radi), QPoint(pt.x()+radi, pt.y()+radi));
    QBrush brush(Qt::green, Qt::SolidPattern);
    QString str = QString("%1").arg(pNode->Element, 0, 10);
    QFont font;
    font.setPixelSize(radi-2*str.length());
    if (pNode != NULL) {
        if (pNode->Left != NULL) {
            end.setX(pt.x() - scale);
            end.setY(pt.y() + height);
            painter->setPen(Qt::black);
            painter->drawLine(pt, end);
            Draw(pNode->Left, end, painter, scale/2, height, radi); 
        }
        if (pNode->Right != NULL) {
            end.setX(pt.x() + scale);
            end.setY(pt.y() + height);
            painter->setPen(Qt::black);
            painter->drawLine(pt, end);
            Draw(pNode->Right, end, painter, scale/2, height, radi); 
        }
        painter->setBrush(brush);
        painter->setPen(Qt::black);
        painter->drawEllipse(pt, radi, radi);
        painter->setPen(Qt::red);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter,  str);
    }
}

template<class T>
void AvlTree<T>::PreOrder(AvlNode<T>* pNode, void (*pf)(AvlNode<T>* pV))
{
    if (pNode != NULL) {
        pf(pNode);
        PreOrder(pNode->Left, pf);
        PreOrder(pNode->Right, pf);
    }
}
#endif
