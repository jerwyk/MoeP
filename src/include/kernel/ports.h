#pragma once

/*
    definition of different ports used by the cpu
*/

#include <MoeP/types.h>

template<typename T = uint16>
class Port
{
protected:
    uint16 portNumber;
public:
    Port(uint16 portNum);
    ~Port();
    virtual void Write(T data);
    virtual T Read();
};

template<typename T = uint16>
class PortSlow : public Port<T>
{
public:
    PortSlow(uint16 portNum);
    ~PortSlow();
    void Write(T data);
};



template<typename T>
Port<T>::Port(uint16 portNum)
{
    this->portNumber = portNum;
}

template<typename T>
Port<T>::~Port()
{

}

template<typename T>
void Port<T>::Write(T data)
{
    asm volatile("outb %0, %1": : "a" (data), "Nd" (portNumber));
}

template<typename T>
T Port<T>::Read()
{
    T result;
    asm volatile("inb %1, %0": "=a" (result): "Nd" (portNumber));
    return result;
}

template<typename T>
PortSlow<T>::PortSlow(uint16 portNum) : Port<T>(portNum)
{
}

template<typename T>
PortSlow<T>::~PortSlow()
{
}

template<typename T>
void PortSlow<T>::Write(T data)
{
    asm volatile("outb %0, %1\nnop\nnop": : "a" (data), "Nd" (this->portNumber));
}