#ifndef MAINFUNCTIONS_SUM_H
#define MAINFUNCTIONS_SUM_H

#include "../Functions/BaseFunc.h"
#include "BaseArithmetic.h"

class Sum: public BaseArithmetic {
public:
    Sum(const BaseFunc& first, const BaseFunc& second);

    auto ToString() const -> std::string override;

    auto GetDerivativeAtPoint(double d) const -> double override;

    auto operator()(double d) const -> double override;

    auto copy() const -> std::shared_ptr<BaseFunc> override;
};


#endif //MAINFUNCTIONS_SUM_H