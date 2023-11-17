#pragma once

#include "custom_traits.h"

//!
//! \brief print_ip шаблонная функция печати условного IP-адреса
//! \param value входная последовательность типа T
//! \param outStream ссылка на поток вывода
//! \return ссылка на поток вывода, которая поступила на вход
//!
template <typename T>
std::ostream &print_ip(T &&value, std::ostream &outStream = std::cout)
{
    return print_ip_impl(std::forward<T>(value), outStream);
}
