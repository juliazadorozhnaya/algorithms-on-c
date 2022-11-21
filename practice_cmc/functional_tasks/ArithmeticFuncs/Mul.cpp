#include <sstream>
#include "Mul.h"

Mul::Mul(const BaseFunc&first, const BaseFunc &second) {
    first_term = first.copy();
    second_term = second.copy();
}

auto Mul::ToString() const -> std::string {
    std::ostringstream result;
    result << "(" << first_term -> ToString() << ") * (" << second_term -> ToString() << ")";
    return result.str();
}

auto Mul::GetDerivativeAtPoint(double point) const -> double {
    return first_term -> GetDerivativeAtPoint(point) * (*second_term)(point)
    + second_term -> GetDerivativeAtPoint(point) * (*first_term)(point);
}

auto Mul::operator()(double point) const -> double {
    return (*first_term)(point)*(*second_term)(point);
}

auto Mul::copy() const -> std::shared_ptr<BaseFunc> {
    return std::make_shared<Mul>(*this);
}
