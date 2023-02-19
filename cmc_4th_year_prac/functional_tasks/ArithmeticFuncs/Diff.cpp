#include <sstream>
#include "Diff.h"

Diff::Diff(const BaseFunc &first, const BaseFunc &second) {
    first_term = first.copy();
    second_term = second.copy();
}

auto Diff::ToString() const -> std::string {
    std::ostringstream result;
    result << "(" << first_term -> ToString() << ") - (" << second_term -> ToString() << ")";
    return result.str();
}

auto Diff::GetDerivativeAtPoint(double point) const -> double {
    return first_term -> GetDerivativeAtPoint(point) - second_term -> GetDerivativeAtPoint(point);
}

auto Diff::operator()(double point) const -> double {
    return (*first_term)(point) - (*second_term)(point);
}

auto Diff::copy() const -> std::shared_ptr<BaseFunc> {
    return std::make_shared<Diff>(*this);
}
