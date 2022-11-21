#ifndef MAINFUNCTIONS_BASEFUNC_H
#define MAINFUNCTIONS_BASEFUNC_H

#include <string>
#include <memory>

//Base class containing basic constructors
class BaseFunc {
public:
    virtual auto ToString() const -> std::string = 0;
    virtual auto GetDerivativeAtPoint(double) const -> double = 0;
    //Using the double parenthesis operator, we can change the number of parameters passed and their type
    virtual auto operator()(double) const -> double = 0;
    //The copy constructor allows you to create a copy of an object of the BaseFunc class in order to be inherited with the same constructors in the future
    virtual auto copy() const -> std::shared_ptr<BaseFunc> = 0;
};


#endif //MAINFUNCTIONS_BaseFunc_H
