#ifndef MAINFUNCTIONS_FUNCFACTORY_H
#define MAINFUNCTIONS_FUNCFACTORY_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include "BaseFunc.h"
#include "PolynomFunc.h"
#include "PowerFunc.h"
#include "ExponentFunc.h"

class FuncFactory {
private:
    class ICreator {
    public:
        virtual auto create(double coefficient) -> std::shared_ptr<BaseFunc> = 0;
        virtual auto create() -> std::shared_ptr<BaseFunc> = 0;
        virtual auto create(std::vector<double> coefficients) -> std::shared_ptr<BaseFunc> = 0;
    };

    template<class T>
    class Creator: public ICreator {
    public:
        auto create(double coefficient) -> std::shared_ptr<BaseFunc> override {
            return std::make_shared<T>(T(coefficient));
        }

        auto create() -> std::shared_ptr<BaseFunc> override {
            return std::make_shared<T>(T());
        }

        auto create(std::vector<double> coefficients) -> std::shared_ptr<BaseFunc>  override {
            return std::make_shared<T>(T(coefficients));
        }
    };

    std::map<std::string, std::shared_ptr<ICreator>> registered;

    void registerAll() {
        registered["ident"] = std::make_shared<Creator<IdentityFunc>>();
        registered["const"] = std::make_shared<Creator<ConstantFunc>>();
        registered["polynomial"]  = std::make_shared<Creator<PolynomFunc>>();
        registered["power"] = std::make_shared<Creator<PowerFunc>>();
        registered["exp"]   = std::make_shared<Creator<ExponentFunc>>();
    }

public:
    FuncFactory() {
        registerAll();
    }

    auto create(const std::string& type, double coefficient) -> std::shared_ptr<BaseFunc> {
        return registered[type]->create(coefficient);
    }

    auto create(const std::string& type) -> std::shared_ptr<BaseFunc> {
        return registered[type]->create();
    }

    auto create(const std::string& type, std::vector<double> coefficients) -> std::shared_ptr<BaseFunc> {
        return registered[type]->create(coefficients);
    }
};


#endif //MAINFUNCTIONS_FUNCFACTORY_H