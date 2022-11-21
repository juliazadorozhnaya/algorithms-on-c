//
// Created by jzadorozhnaya on 10.11.22.
//
#include <memory>
#include <iostream>

class Any{
public:
    template<typename T>
    Any(const T& a_v){
        v = std::unique_ptr<Base>(static_cast<Base*>(new Holder<T>(a_v)));
    };

    template<typename T>
    T get(){
        auto holder = static_cast<Holder<T>*>(v.get());
        if (typeid(T) != holder->type_info()){
            throw std::runtime_error("Bad cast");
        }

        return holder->a_value;
    }

private:
    struct Base{
        virtual ~ Base(){};
        virtual const std::type_info& type_info() const = 0;
    };
    template<typename T> struct Holder: Any::Base{
        Holder(const T & value): a_value(value){};
        const std::type_info& type_info() const {
            return typeid(a_value);
        }
        T a_value;
    };

    std::unique_ptr<Base> v;
};

int main(){
    Any a(5);
    auto value1 = a.get<int>(); // 5
    std::cout << value1 << std::endl;
    //auto value2 = a.get<std::string>(); // error
    return 0;
}