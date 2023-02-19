#ifndef MAINFUNCTIONS_NEWOPERATORS_H
#define MAINFUNCTIONS_NEWOPERATORS_H

#include <sstream>
#include "stdexcept"
#include "Functions/BaseFunc.h"
#include "ArithmeticFuncs/Sum.h"
#include "ArithmeticFuncs/Diff.h"
#include "ArithmeticFuncs/Mul.h"
#include "ArithmeticFuncs/Div.h"

template<class A, class B,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, A>, bool> = true,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator+(const A& first, const B& second) {
    return std::make_shared<Sum>(Sum(*first, *second));
}

template<class A, class B,
        std::enable_if_t<!std::is_base_of_v<std::shared_ptr<BaseFunc>, A> ||
                         !std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator+(const A& first, const B& second) {
    std::ostringstream stream;
    stream << "Invalid operands for operator+.";
    throw std::logic_error(stream.str());
}

template<class A, class B,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, A>, bool> = true,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator*(const A& first, const B& second) {
    return std::make_shared<Mul>(Mul(*first, *second));
}

template<class A, class B,
        std::enable_if_t<!std::is_base_of_v<std::shared_ptr<BaseFunc>, A> ||
                         !std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator*(const A& first, const B& second) {
    std::ostringstream stream;
    stream << "Invalid operands for operator*.";
    throw std::logic_error(stream.str());
}

template<class A, class B,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, A>, bool> = true,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator/(const A& first, const B& second) {
    return std::make_shared<Div>(Div(*first, *second));
}

template<class A, class B,
        std::enable_if_t<!std::is_base_of_v<std::shared_ptr<BaseFunc>, A> ||
                         !std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator/(const A& first, const B& second) {
    std::ostringstream stream;
    stream << "Invalid operands for operator/.";
    throw std::logic_error(stream.str());
}

template<class A, class B,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, A>, bool> = true,
        std::enable_if_t<std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator-(const A& first, const B& second) {
    return std::make_shared<Diff>(Diff(*first, *second));
}

template<class A, class B,
        std::enable_if_t<!std::is_base_of_v<std::shared_ptr<BaseFunc>, A> ||
                         !std::is_base_of_v<std::shared_ptr<BaseFunc>, B>, bool> = true>
std::shared_ptr<BaseArithmetic> operator-(const A& first, const B& second) {
    std::ostringstream stream;
    stream << "Invalid operands for operator-.";
    throw std::logic_error(stream.str());
}


#endif //MAINFUNCTIONS_NEWOPERATORS_H