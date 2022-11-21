#include <iostream>
#include <vector>
#include "Functions/FuncFactory.h"
#include "NewOperators.h"
#include "Root.h"

using namespace std;

int main() {
    vector<double> v{0, 1};
    vector<double> u{1, 0, 1};

    vector<double> t = {1, -2, 1};
    vector<double> t1 = {0, 0, 1};
    vector<double> t2 = {0, 0,0,0,1};
    vector<double> t3 = {0, 0, 0, 1};
    vector<double> t4 = {3};
    vector<double> t5 = {0, 0, 3};

    auto factory = FuncFactory();
    auto a = factory.create("exp", -1.23);
    auto b = factory.create("polynomial", v);
    auto c = factory.create("polynomial", u);

    auto d = factory.create("polynomial", {1, -2, 1});

    auto d1 = factory.create("polynomial", t1);
    auto d2 = factory.create("polynomial", t2);
    auto d3 = factory.create("polynomial", t3);
    auto d4 = factory.create("power", t4);
    auto d5 = factory.create("polynomial", t5);
   //  std::cout << std::is_base_of_v<BaseFunc, BaseArithmetic>;
   //  d1+d2+d3;
   //  return 0;
   std::cout << c -> ToString() << "     "  << std::endl;

   std::cout <<  getRoot(d, 10, 0.1, 220) << std::endl;
   std::cout <<(d1 / d2) -> GetDerivativeAtPoint(1) << std::endl;
   std::cout << ((d1 / d2)->copy() / d1) -> GetDerivativeAtPoint(1) << std::endl;
   std::cout << getRoot(d3, 5, 0.1, 220) << std::endl;
   std::cout << getRoot(d5-d4, 5, 0.1, 220) << std::endl;
   std::cout << "END OF NEEDED RESULTS" << std::endl;

    cout << c -> ToString() << "     " << c->GetDerivativeAtPoint(2) << endl
         << a -> ToString() << "     " << a->GetDerivativeAtPoint(1) << endl << (c / a) -> GetDerivativeAtPoint(0) << endl;
}
