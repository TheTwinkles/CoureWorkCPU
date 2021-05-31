#include "cpu.hpp"

#include <iostream>

using namespace std;

CPU::CPU(): //реализация конструктора по умолчанию
    manufacturer("Undefined manufacturer"),
    model("Undefined model"),
    cost(0),
    socket("Undefined socket"),
    core_num(0),
    proc_speed(0),
    mem_type("Undefined memory type"),
    mem_freq(0)
{

}

CPU::CPU(const string sManufacturer, const string sModel,
         const int sCost,
         const string sSocket, const int sCore_num,
         const int sProc_speed, const string sMem_type,
         const int sMem_freq): //реализация конструктора с параметрами
    manufacturer(sManufacturer),
    model(sModel),
    cost(sCost),
    socket(sSocket),
    core_num(sCore_num),
    proc_speed(sProc_speed),
    mem_type(sMem_type),
    mem_freq(sMem_freq)
{

}

CPU::CPU(const CPU &other): //реализация конструктора копирования
    manufacturer(other.manufacturer),
    model(other.model),
    cost(other.cost),
    socket(other.socket),
    core_num(other.core_num),
    proc_speed(other.proc_speed),
    mem_type(other.mem_type),
    mem_freq(other.mem_freq)
{

}

CPU::~CPU() //реализация деструктора по умолчанию
{

}

CPU &CPU::operator=(const CPU &rhs) //реализация перегрузки оператора =
{
    if (this == &rhs) return *this;

    manufacturer = rhs.manufacturer;
    model = rhs.model;
    cost = rhs.cost;
    socket = rhs.socket;
    core_num = rhs.core_num;
    proc_speed = rhs.proc_speed;
    mem_type = rhs.mem_type;
    mem_freq = rhs.mem_freq;

    return *this;
}

//реализация геттеров и сеттеров

void CPU::setManufacturer(const string sManufacturer)
{
    manufacturer = sManufacturer;
}
string CPU::getManufacturer() const
{
    return manufacturer;
}

void CPU::setModel(const string sModel)
{
    model = sModel;
}

string CPU::getModel() const
{
    return model;
}

void CPU::setCost(const int sCost)
{
    cost = sCost;
}
int CPU::getCost() const
{
    return cost;
}

void CPU::setSocket(const string sSocket)
{
    socket = sSocket;
}
string CPU::getSocket() const
{
    return socket;
}

void CPU::setCore_num(const int sCore_num)
{
    core_num = sCore_num;
}
int CPU::getCore_num() const
{
    return core_num;
}

void CPU::setProc_speed(const int sProc_speed)
{
    proc_speed = sProc_speed;
}
int CPU::getProc_speed() const
{
    return proc_speed;
}

void CPU::setMem_type(const string sMem_type)
{
    mem_type = sMem_type;
}
string CPU::getMem_type() const
{
    return mem_type;
}

void CPU::setMem_freq(const int sMem_freq)
{
    mem_freq = sMem_freq;
}
int CPU::getMem_freq() const
{
    return mem_freq;
}
