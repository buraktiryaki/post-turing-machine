#include "Memory.h"

Memory::Memory()
{

}

Memory::Memory(int x, int y, int boyut, int winW)
{
    this->x = x;
    this->y = y;
    this->boyut = boyut;
    this->winW = winW;

    headPos = 0;

    //init 0
    memVals = new int[boyut];
    for(int i = 0; i < boyut; i++)
        memVals[i] = 0;
}

void Memory::draw(QPainter *painter)
{
    int kareGenislik = (winW - (2*x))/boyut;

    for(int i = 0; i < boyut; i++)
    {
        int kareX = x + (kareGenislik * i);
        QRect rect(kareX,y,kareGenislik,KARE_YUKSEKLIK);

        painter->drawRect(rect);
        painter->setFont(QFont("Times",16,QFont::Bold));

        if(memVals[i])
            painter->setPen(QColor(Qt::gray).lighter(80));
        painter->drawText(rect,Qt::AlignCenter,QString::number(memVals[i]));
        painter->setPen(QColor(Qt::black));

        //draw head(for disina al)
        if(i == headPos)
        {
            rect = QRect(kareX,y+KARE_YUKSEKLIK,kareGenislik,KARE_YUKSEKLIK);
            painter->drawText(rect,Qt::AlignHCenter|Qt::AlignTop,"^");
        }

    }
}

int Memory::setMem(int value)
{
    if(memVals[headPos] == value)
        return -1;
    else
        memVals[headPos] = value;
    return 0;
}

int Memory::getMem()
{
    return memVals[headPos];
}

int Memory::headL()
{
    if(headPos > 0)
        headPos--;
    else return -1;
    return 0;
}

int Memory::headR()
{
    if(headPos < boyut-1)
        headPos++;
    else return -1;
    return 0;
}

int Memory::getHeadPos()
{
    return headPos;
}

Memory::~Memory()
{

}



