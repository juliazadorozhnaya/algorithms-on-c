#ifndef MAINFUNCTIONS_EXPONENTFUNC_H
#define MAINFUNCTIONS_EXPONENTFUNC_H

#include <vector>
#include "BaseFunc.h"

class ExponentFunc: public BaseFunc {
private:
    double coefficient;
public:
    explicit ExponentFunc(double c) : coefficient(c) {};
    ExponentFunc() : coefficient(0) {};
    explicit ExponentFunc(std::vector<double>);

    auto ToString() const -> std::string override;

    auto GetDerivativeAtPoint(double d) const -> double override;

    auto operator()(double d) const -> double override;

    auto copy() const -> std::shared_ptr<BaseFunc> override;
};


#endif //MAINFUNCTIONS_EXPONENTFUNC_H
