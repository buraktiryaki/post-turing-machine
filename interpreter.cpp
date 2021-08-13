#include "interpreter.h"

Interpreter::Interpreter()
{

}

Interpreter::Interpreter(QString code, Memory *mem)
{
    this->code = code;
    this->mem = mem;
    step = 0;

    QRegExp rx("(\\s*\\n\\s*)");
    lines = code.split(rx);

}

int Interpreter::checkError()
{
    //i=1 (0. satirda hata olursa true olsun)
    for(int i = 1; i <= lines.size(); i++)
    {
        if(checkRegExType(lines[i-1]) == ERR)
        {
            return i;
        }
    }
    return 0;
}

Interpreter::regExTypes Interpreter::checkRegExType(QString s)
{
    // ?3;11
    QRegExp re("(\\?\\d\\d*;\\d\\d*)");
    // v5
    QRegExp re2("(v\\d\\d*)");
    // x5
    QRegExp re3("(x\\d\\d*)");
    // L5
    QRegExp re4("(L\\d\\d*)");
    // R5
    QRegExp re5("(R\\d\\d*)");
    // !
    QRegExp re6("(!)");
    // comment
    QRegExp re7("(\\/\\/(.)*)");

    if(re.exactMatch(s))          return CONDITION_TYPE;
    else if(re2.exactMatch(s))    return V_TYPE;
    else if(re3.exactMatch(s))    return X_TYPE;
    else if(re4.exactMatch(s))    return L_TYPE;
    else if(re5.exactMatch(s))    return R_TYPE;
    else if(re6.exactMatch(s))    return EXC_TYPE;
    else if(re7.exactMatch(s))    return COMMENT;
    else                          return ERR;
}

/*
return 2: comment line
return 1: success command
return 0: Halt success
return RT_ERR_...: RT_ERR
*/
int Interpreter::runOneStep()
{
    // !(halt)
    if(checkRegExType(lines[step]) == EXC_TYPE)
    {
        return 0;
    }

    // v(put 1)
    else if(checkRegExType(lines[step]) == V_TYPE)
    {
        //find d1 operand
        QRegularExpression re("\\d\\d*");
        QRegularExpressionMatchIterator i =
                re.globalMatch(lines[step]);
        int d1 = i.next().captured(0).toInt();

        if(step == d1-1)
            return RT_ERR_INFINITELOOP;
        else if(d1 == 0 || d1 > lines.size())
            return RT_ERR_INVALIDOPERAND;

        step = d1-1;

        if(mem->setMem(1) == -1)
            return RT_ERR_WRITE;
        else return 1;
    }

    // x(put 0)
    else if(checkRegExType(lines[step]) == X_TYPE)
    {
        //find d1 operand
        QRegularExpression re("\\d\\d*");
        QRegularExpressionMatchIterator i =
                re.globalMatch(lines[step]);
        int d1 = i.next().captured(0).toInt();

        if(step == d1-1)
            return RT_ERR_INFINITELOOP;
        else if(d1 == 0 || d1 > lines.size())
            return RT_ERR_INVALIDOPERAND;

        step = d1-1;

        if(mem->setMem(0) == -1)
            return RT_ERR_WRITE;
        else return 1;
    }
    // L(shift left)
    else if(checkRegExType(lines[step]) == L_TYPE)
    {
        //find d1 operand
        QRegularExpression re("\\d\\d*");
        QRegularExpressionMatchIterator i =
                re.globalMatch(lines[step]);
        int d1 = i.next().captured(0).toInt();

        if(step == d1-1)
            return RT_ERR_INFINITELOOP;
        else if(d1 == 0 || d1 > lines.size())
            return RT_ERR_INVALIDOPERAND;

        step = d1-1;

        if(mem->headL() == -1)
            return RT_ERR_OVERFLOW;
        else return 1;
    }

    // R(shift right)
    else if(checkRegExType(lines[step]) == R_TYPE)
    {
        //find d1 operand
        QRegularExpression re("\\d\\d*");
        QRegularExpressionMatchIterator i =
                re.globalMatch(lines[step]);
        int d1 = i.next().captured(0).toInt();

        if(step == d1-1)
            return RT_ERR_INFINITELOOP;
        else if(d1 == 0 || d1 > lines.size())
            return RT_ERR_INVALIDOPERAND;

        step = d1-1;

        if(mem->headR() == -1)
            return RT_ERR_OVERFLOW;
        else return 1;
    }

    // ?d;d condition
    else if(checkRegExType(lines[step]) == CONDITION_TYPE)
    {
        //find d1,d2 operand
        QRegularExpression re("\\d\\d*");
        QRegularExpressionMatchIterator i =
                re.globalMatch(lines[step]);
        int d1 = i.next().captured(0).toInt();
        int d2 = i.next().captured(0).toInt();

        if(step == d1-1 || step == d2-1)
            return RT_ERR_INFINITELOOP;
        else if(d1 == 0 || d2 == 0 ||
                d1 > lines.size() || d2 > lines.size())
            return RT_ERR_INVALIDOPERAND;

        if(mem->getMem()) step = d2-1;
        else step = d1-1;

        return 1;
    }
    else if(checkRegExType(lines[step]) == COMMENT)
    {
        step++;
        return 2;
    }

    else return RT_ERR_UNKNOW;
}

Interpreter::~Interpreter()
{

}





































