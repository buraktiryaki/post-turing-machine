#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QtCore>
#include <QString>

#include "memory.h"

#define RT_ERR_WRITE -2
#define RT_ERR_OVERFLOW -3
#define RT_ERR_INFINITELOOP -4
#define RT_ERR_INVALIDOPERAND -5
#define RT_ERR_UNKNOW -6

class Interpreter
{
    enum regExTypes{
        CONDITION_TYPE,V_TYPE,X_TYPE,L_TYPE,
        R_TYPE,EXC_TYPE,COMMENT,ERR
    };

public:
    Interpreter();
    Interpreter(QString code, Memory *mem);

    int checkError();
    regExTypes checkRegExType(QString s);

    int runOneStep();


    ~Interpreter();

public:
    int step;
    QString code;
    Memory *mem;

    QStringList lines;
};






#endif // INTERPRETER_H
