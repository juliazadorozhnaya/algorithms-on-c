#include <math.h>
#include "ExponentFunc.h"

//Fill in the exponent's degree
ExponentFunc::ExponentFunc(std::vector<double> v) {
    !v.empty() ? coefficient = v[0] : coefficient = 0;
}
//String definition of the function
auto ExponentFunc::ToString() const -> std::string {
    if (coefficient == 0) {
        return "1";
    }
    else {
        return "exp(" + std::to_string(coefficient) + "*x)";
    }
}
//We take the derivative at a given point
auto ExponentFunc::GetDerivativeAtPoint(double point) const -> double {
    return coefficient * exp(coefficient * point);
}

auto ExponentFunc::operator()(double point) const -> double {
    return exp(coefficient * point);
}
//Creating a copy of the object to perform further arithmetic operations
auto ExponentFunc::copy() const -> std::shared_ptr<BaseFunc> {
    return std::make_shared<ExponentFunc>(*this);
}
