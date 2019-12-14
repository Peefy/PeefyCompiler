
#ifndef __P_IO_BUFFER_H__
#define __P_IO_BUFFER_H__

// peefy 输入输出缓存库

#include "util.h"

BEGIN_PEEFY_NAMESPACE

class PBuffer
{
private:
    /* data */
public:
    PBuffer(/* args */);
    ~PBuffer();
};

PBuffer::PBuffer(/* args */)
{
}

PBuffer::~PBuffer()
{
}


class PIOBuffer : public PBuffer
{
private:
    /* data */
public:
    PIOBuffer(/* args */);
    ~PIOBuffer();
};

PIOBuffer::PIOBuffer(/* args */)
{
}

PIOBuffer::~PIOBuffer()
{
}

class PFileBuffer : public PIOBuffer
{
private:
    char _nextchar;
public:
    PFileBuffer() : _nextchar('\0') {}
    ~PFileBuffer();
    char nextChar();
};

PFileBuffer::PFileBuffer(/* args */)
{
}

PFileBuffer::~PFileBuffer()
{
}


END_PEEFY_NAMESPACE

#endif

