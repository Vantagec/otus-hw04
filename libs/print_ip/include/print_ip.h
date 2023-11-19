#pragma once

#include "custom_traits.h"

/** @name Функции вывода условного IP-адреса
 * These two functions can be used to encode a integer value in a string.
 * if encode_chars is null, it defaults to a 84-base characterset which
 * has been designed to produce smilies for low values. 
 */

/// @{ 
/** @name Функции вывода условного IP-адреса
 * Функция печати условного IP-адреса. 
 * Условность заключается в том, что количество элементов не обязательно должно быть равно 4-ём или 8-ми,
 *  а также каждый элемент не обязательно должен быть числом из диапазона 0..255. От идеи IP-адреса остаётся 
 * фактически только вывод элементов через `.` (символ точки).
 */
/// @{ \defgroup print Функции вывода

/*!
* \ingroup print
* \brief Функция вывода условной последовательности в поток вывода
* \param value входная последовательность типа T
* \param outStream ссылка на поток вывода
* \return ссылка на поток вывода, которая поступила на вход
*/
template <typename T>
std::ostream &print_ip(T &&value, std::ostream &outStream = std::cout)
{
    return print_ip_impl(std::forward<T>(value), outStream);
}
 
/// @} 