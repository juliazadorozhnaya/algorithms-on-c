#ifndef MAINFUNCTIONS_POLYNOMFUNC_H
#define MAINFUNCTIONS_POLYNOMFUNC_H

#include "BaseFunc.h"
#include <vector>
#include <iostream>

class PolynomFunc: public BaseFunc {
private:
    auto removeTrailingZeroes() -> void;
protected:
    std::vector<double> polynomialVector;
public:
    PolynomFunc();
    PolynomFunc(const PolynomFunc&);
    explicit PolynomFunc(const std::vector<double>&);
    explicit PolynomFunc(double f);

    auto ToString() const -> std::string override;
    auto operator()(double d) const -> double override;
    auto GetDerivativeAtPoint(double d) const -> double override;

    auto copy() const -> std::shared_ptr<BaseFunc> override;
};

class IdentityFunc: public PolynomFunc {
public:
    IdentityFunc() {
        polynomialVector = {0, 1};
    }

    explicit IdentityFunc(double ) {
        polynomialVector = {0, 1};
    }

    explicit IdentityFunc(std::vector<double>) {
        polynomialVector = {0, 1};
    }


};

class ConstantFunc: public PolynomFunc {
public:
    explicit ConstantFunc(double c) {
        polynomialVector = {c};
    }

    ConstantFunc() {
        polynomialVector = {0};
    }

    explicit ConstantFunc(std::vector<double> v) {
        polynomialVector.clear();
        if (!v.empty()) {
            polynomialVector.push_back(v[0]);
        } else {
            polynomialVector.push_back(0);
        }
    }
};


#endif //MAINFUNCTIONS_POLYNOMFUNC_H