/*!
    \file
    \brief Заголовочный файл с описанием класса customList

    Данный файл содержит в себе определение класса customList и основных методов для работы с ним
*/
#ifndef CUSTOMLIST_HPP
#define CUSTOMLIST_HPP

#include "cpu.hpp"

/*!
    \brief Класс customList

    Класс описывает список и содержит соответствующие методы для работы с ним
*/
class customList
{
public:
    /*!
     * \brief Структура, описывающая элемент списка
     */
    struct Item
    {
        CPU cpu; ///< Объект, хранимый в списке
        Item* next; ///< Указатель на следующий элемент списка
        Item* prev; ///< Указатель на предыдущий элемент списка
    };
    Item* head; ///< Указатель на первый элемент списка
    Item* tail; ///< Указатель на последний элемент списка

public:
    /// Конструктор по умолчанию
    customList();

    /// запрет создания конструктора копирования и перегрузки оператора =
    customList(const customList &other) = delete;
    void operator=(const customList&) = delete; ///< запрет перегрузки оператора =

    /*!
     * \brief Перегрузка оператора []
     * \param index индекс, который поступает в оператор
     * \return если список пустой, то возвращается nullptr;
     *  если индекс больше кол-ва элементов в списке, то возвращается nullptr;
     *  и по умолчанию возвращает элемент
     */
    Item* operator[] (const int index);

    /// Деструктор по умолчанию
    ~customList();

    /*!
     * \brief Метод добавления элемента в список
     * \param[in] adCPU добавляемый элемент
     */
    void addToList(CPU &adCPU);

    /*!
     * \brief Метод удаления элемента из списка
     * \param[in] i номер удаляемого элемента
     */
    void deleteFromList(int i);

};

#endif // CUSTOMLIST_HPP
