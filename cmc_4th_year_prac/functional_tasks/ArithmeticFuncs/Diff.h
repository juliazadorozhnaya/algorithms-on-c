#ifndef MAINFUNCTIONS_DIFF_H
#define MAINFUNCTIONS_DIFF_H


#include "BaseArithmetic.h"

class Diff: public BaseArithmetic {
public:
    Diff(const BaseFunc&, const BaseFunc&);

    auto ToString() const -> std::string  override;

    auto GetDerivativeAtPoint(double d) const -> double override;

    auto operator()(double d) const -> double override;

    auto copy() const -> std::shared_ptr<BaseFunc> override;
};


#endif //MAINFUNCTIONS_DIFF_H
