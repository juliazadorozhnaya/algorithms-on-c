#ifndef MAINFUNCTIONS_Mul_H
#define MAINFUNCTIONS_Mul_H


#include "BaseArithmetic.h"

class Mul: public BaseArithmetic {
public:
    Mul(const BaseFunc&, const BaseFunc&);

    auto ToString() const -> std::string override;

    auto GetDerivativeAtPoint(double d) const -> double override;

    auto operator()(double d) const -> double override;

    auto copy() const -> std::shared_ptr<BaseFunc> override;
};


#endif //MAINFUNCTIONS_Mul_H
