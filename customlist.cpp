#include "customlist.hpp"
#include "cpu.hpp"

#include <iostream>

customList::customList():
    head(nullptr)
  , tail(nullptr)
{

}

customList::Item *customList::operator[](const int index)
{
    //если элементов нет в списке
    if (head == nullptr)
    {
        return nullptr;
    }
    Item* element = head;
    for (int i = 0; i < index; i++)
    {
        element = element->next;
        if (!element) return nullptr; //если индекс был указан
        //больше размера списка
    }
    return element;
}

customList::~customList()
{
    while(head) //пока по адресу начала списка что-то есть
    {
        tail = head->next;
        delete head;
        head = tail;
    }
}

void customList::addToList(CPU &adCPU)
{
    Item *temp = new Item; //выделение памяти под новый элемент списка
    temp->next = nullptr; //изначально по следующему адресу null_ptr
    temp->cpu = adCPU; //записываем значение в структуру

    if (head != nullptr) //если список не пустой
    {
        temp->prev = tail; //указываем адрес на предыдущий элемент в соотв. поле
        tail->next = temp; //указываем адрес следующего за хвостом элемента
        tail = temp; //меняем адрес хвоста
    }
    else //если список пустой
    {
        temp->prev = nullptr; //предыдущий элемент указывает в null_ptr
        head = temp;
        tail = temp; //голова=хвост=тот элемент, что сейчас добавили
    }
}

void customList::printList() const
{
    Item *temp = head; //временный указатель на адрес последнего элемента
    while (temp!=NULL) //поднимаемся пока не встретим конец(начало)
    {
        temp->cpu.show();
        temp = temp->next; //записываем адрес предыдущего элемента
    }
}
