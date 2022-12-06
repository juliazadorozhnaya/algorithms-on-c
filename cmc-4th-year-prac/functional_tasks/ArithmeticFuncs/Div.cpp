#include <sstream>
#include "Div.h"

Div::Div(const BaseFunc &first, const BaseFunc &second) {
    first_term = first.copy();
    second_term = second.copy();
}

auto Div::ToString() const -> std::string {
    std::ostringstream result;
    result << "(" << first_term->ToString() << ")/(" << second_term->ToString() << ")";
    return result.str();
}

auto Div::GetDerivativeAtPoint(double point) const -> double {
    float u = (*first_term)(point);
    float v = (*second_term)(point);
    float ul = first_term->GetDerivativeAtPoint(point);
    float vl = second_term->GetDerivativeAtPoint(point);
    if (v != 0) {
        return (-u*vl + v*ul) / (v*v);
    } else {
        throw std::logic_error("Dividing by zero");
    }
}

double Div::operator()(double point) const {
    return (*first_term)(point) / (*second_term)(point);
}

auto Div::copy() const -> std::shared_ptr<BaseFunc> {
    return std::make_shared<Div>(*this);
}
