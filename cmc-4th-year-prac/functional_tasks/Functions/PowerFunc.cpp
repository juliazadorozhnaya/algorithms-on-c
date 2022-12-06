#include <sstream>
#include "PowerFunc.h"
#include <math.h>

//filling in the power function
PowerFunc::PowerFunc(std::vector<double> v) {
    if (!v.empty()) {
        this->degree = int(v[0]);
    } else {
        this->degree = 0;
    }
}

//making a string representation of the function
auto PowerFunc::ToString() const -> std::string {
    if (degree == 0) {
        return "1";
    }
    return "x^(" + std::to_string(degree) + ")";
}

//calculate the derivative of the power function
auto PowerFunc::GetDerivativeAtPoint(double point) const -> double {
    if (degree == 0) {
        return 0;
    }
    return degree * pow(point, degree-1);
}

auto PowerFunc::operator()(double point) const -> double {
    return pow(point, degree);
}

auto PowerFunc::copy() const -> std::shared_ptr<BaseFunc> {
    return std::make_shared<PowerFunc>(*this);
}
