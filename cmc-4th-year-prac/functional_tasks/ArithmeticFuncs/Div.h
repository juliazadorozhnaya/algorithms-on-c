#ifndef MAINFUNCTIONS_DIV_H
#define MAINFUNCTIONS_DIV_H


#include "BaseArithmetic.h"

class Div: public BaseArithmetic {
public:
    Div(const BaseFunc&, const BaseFunc&);

    auto ToString() const -> std::string override;

    auto GetDerivativeAtPoint(double d) const -> double override;

    auto operator()(double d) const -> double override;

    auto copy() const -> std::shared_ptr<BaseFunc> override;
};


#endif //MAINFUNCTIONS_DIV_H
