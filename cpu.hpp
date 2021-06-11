/*!
    \file
    \brief Заголовочный файл с описанием класса CPU

    Данный файл содержит в себе определение класса CPU и основных методов для работы с ним
*/
#ifndef CPU_HPP
#define CPU_HPP

#include <string>

/*!
    \brief Класс CPU

    Класс описывает объект процессора и содержит соответствующие методы для работы с ним
*/

class CPU
{
private:
    std::string manufacturer; ///< Производитель
    std::string model; ///< Модель
    int cost; ///< Цена
    std::string socket; ///< Сокет
    int core_num; ///< Количество ядер
    int proc_speed; ///< Тактовая частота
    std::string mem_type; ///< Тип памяти
    int mem_freq; ///< Частота памяти

public:
    /// Конструктор по умолчанию
    CPU();

    /*!
     * \brief Конструктор с параметрами
     * \param[in] sManufacturer Производитель
     * \param[in] sModel Модель
     * \param[in] sCost Цена
     * \param[in] sSocket Сокет
     * \param[in] sCore_num Количество ядер
     * \param[in] sProc_speed Тактовая частота
     * \param[in] sMem_type Тип памяти
     * \param[in] sMem_freq Частота памяти
     */
    CPU(const std::string sManufacturer,
        const std::string sModel,
        const int sCost,
        const std::string sSocket,
        const int sCore_num,
        const int sProc_speed,
        const std::string sMem_type,
        const int sMem_freq
        );

    /*!
     * \brief Конструктор копирования
     * \param[in] other Другой объект класса CPU
     */
    CPU(const CPU &other);

    /// Деструктор по умолчанию
    ~CPU();

    /*!
     * \brief Перегрузка оператора равно
     * \param rhs Операнд
     * \return Возвращает указатель на текущий объект
     */
    CPU& operator=(const CPU &rhs);

    // геттеры и сеттеры
    /*!
     * \brief Устанавливает параметр производитель
     * \param[in] sManufacturer Устанавливаемый производитель
     */
    void setManufacturer(const std::string sManufacturer);
    /*!
     * \brief Возвращает параметр прозводитель
     */
    std::string getManufacturer() const;

    /*!
     * \brief Устанавливает параметр модель
     * \param[in] sModel Устанавливаемая модель
     */
    void setModel(const std::string sModel);
    /*!
     * \brief Возвращает параметр модель
     */
    std::string getModel() const;

    /*!
     * \brief Устанавливает параметр цена
     * \param[in] sCost Устанавливаемая цена
     */
    void setCost(const int sCost);
    /*!
     * \brief Возвращает параметр цена
     */
    int getCost() const;

    /*!
     * \brief Устанавливает параметр сокет
     * \param[in] sSocket Устанавливаемый сокет
     */
    void setSocket(const std::string sSocket);
    /*!
     * \brief Возвращает параметр сокет
     */
    std::string getSocket() const;

    /*!
     * \brief Устанавливает параметр количество ядер
     * \param[in] sCore_num Устанавливаемое количество ядер
     */
    void setCore_num(const int sCore_num);
    /*!
     * \brief Возвращает параметр количество ядер
     */
    int getCore_num() const;

    /*!
     * \brief Устанавливает параметр тактовая частота
     * \param[in] sProc_speed Устанавливаемая тактовая частота
     */
    void setProc_speed(const int sProc_speed);
    /*!
     * \brief Возвращает параметр тактовая частота
     */
    int getProc_speed() const;

    /*!
     * \brief Устанавливает параметр тип памяти
     * \param[in] sMem_type Устанавливаемый тип памяти
     */
    void setMem_type(const std::string sMem_type);
    /*!
     * \brief Возвращает параметр тип памяти
     */
    std::string getMem_type() const;

    /*!
     * \brief Устанавливает параметр частота памяти
     * \param[in] sMem_freq Устанавливаемая частота памяти
     */
    void setMem_freq(const int sMem_freq);
    /*!
     * \brief Возвращает параметр частота памяти
     */
    int getMem_freq() const;

};

#endif // CPU_HPP
