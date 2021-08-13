#ifndef MEMORY_H
#define MEMORY_H

#include <QPainter>
#include <QDebug>

#define KARE_YUKSEKLIK 50

class Memory
{

public:
    Memory();
    Memory(int x, int y, int boyut, int winW);
    ~Memory();

    void draw(QPainter *painter);
    int setMem(int value);
    int getMem();
    int headL();
    int headR();
    int getHeadPos();


    int boyut;


private:
    int headPos;
    int *memVals;//(bool yap)

    int x;
    int y;
    int winW;
    int winH;
};




#endif // MEMORY_H
