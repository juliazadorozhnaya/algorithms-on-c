#include "PolynomFunc.h"
#include "sstream"
#include <math.h>

PolynomFunc::PolynomFunc(double f) {
    polynomialVector.push_back(f);
}

PolynomFunc::PolynomFunc() {
    polynomialVector.push_back(0);
}

PolynomFunc::PolynomFunc(const PolynomFunc& other) : polynomialVector(other.polynomialVector) {}

PolynomFunc::PolynomFunc(const std::vector<double>& v) {
    polynomialVector = v;
    removeTrailingZeroes();
}

auto PolynomFunc::ToString() const -> std::string {
    std::ostringstream resultString;
    if (polynomialVector.size() == 1 && polynomialVector[0] == 0) {
        return "0";
    }
    for (size_t degree = 0; degree < polynomialVector.size(); ++degree) {
        auto coefficient = polynomialVector[degree];
        auto positive = coefficient >= 0;
        auto negative = coefficient >= 0;
        if (coefficient != 0) {
            resultString << (!positive or degree==0 or (polynomialVector.size() ==2) or (degree == 3) ? "" : "+");
            if (degree == 0) {
                resultString << coefficient;
                continue;
            }
            if (coefficient == -1) {
                resultString << "-x";
            } else if (coefficient == 1) {
                resultString << "x";
            } else {
                resultString << coefficient << "*x";
            }
            if (degree != 1) {
                resultString << "^" << degree;
            }
        }
    }
    return std::string(resultString.str());
}

auto PolynomFunc::GetDerivativeAtPoint(double point) const -> double {
    double result = 0;
    size_t degree = 1;
    for (size_t i = 1; i < polynomialVector.size(); ++i) {
        result += polynomialVector[i] * degree * pow(point, degree - 1);
        degree++;
    }
    return result;
}

auto PolynomFunc::operator()(double point) const -> double {
    double result = 0;
    for (size_t i = 0; i < polynomialVector.size(); ++i) {
        result += polynomialVector[i] * pow(point, i);
    }
    return result;
}

auto PolynomFunc::copy() const -> std::shared_ptr<BaseFunc> {
    return std::make_shared<PolynomFunc>(*this);
}

auto PolynomFunc::removeTrailingZeroes()-> void {
    std::vector<double> new_polynomial_vector;
    size_t zeroes_count = 0;
    for (const auto &coefficient: polynomialVector) {
        if (coefficient == 0) {
            zeroes_count++;
        } else {
            for (int i = 0; i < zeroes_count; ++i) {
                new_polynomial_vector.push_back(0);
            }
            new_polynomial_vector.push_back(coefficient);
            zeroes_count = 0;
        }
    }
    if (new_polynomial_vector.empty()) {
        polynomialVector = {0};
    } else {
        polynomialVector = new_polynomial_vector;
    }
}