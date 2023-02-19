#ifndef MAINFUNCTIONS_POWERFUNC_H
#define MAINFUNCTIONS_POWERFUNC_H

#include <vector>
#include "BaseFunc.h"

class PowerFunc: public BaseFunc {
private:
    double degree;
public:
    explicit PowerFunc(double degree) : degree(degree) {};
    PowerFunc() : degree(0) {};
    explicit PowerFunc(std::vector<double> v);

    auto ToString() const -> std::string override;

    auto GetDerivativeAtPoint(double d) const -> double override;

    auto operator()(double d) const -> double override;

    auto copy() const -> std::shared_ptr<BaseFunc> override;
};


#endif //MAINFUNCTIONS_POWERFUNC_H
