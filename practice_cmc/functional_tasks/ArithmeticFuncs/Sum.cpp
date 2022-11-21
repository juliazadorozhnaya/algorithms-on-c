#include "sstream"
#include "Sum.h"

Sum::Sum(const BaseFunc& first, const BaseFunc& second) {
    first_term = first.copy();
    second_term = second.copy();
}

auto Sum::ToString() const -> std::string {
    std::ostringstream result;
    result << "(" << first_term -> ToString() << ")+(" << second_term -> ToString() + ")";
    return result.str();
}

auto Sum::GetDerivativeAtPoint(double point) const -> double {
    return first_term -> GetDerivativeAtPoint(point) + second_term->GetDerivativeAtPoint(point);
}

auto Sum::operator()(double point) const -> double {
    return (*first_term)(point) + (*second_term)(point);
}

auto Sum::copy() const -> std::shared_ptr<BaseFunc> {
    return std::make_shared<Sum>(*this);
}