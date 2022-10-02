#include <vector>
#include <iostream>
using namespace std;

int main()
{
    std::vector<bool> v;

    for (auto i: v) {}
    // for (auto&  i: v) {} // error
    for (auto&& i: v) {}
}

/*
Второй цикл не компилируется, поскольку он пытается привязать ссылку lvalue к rvalue, то есть vector<bool> 
использует вспомогательный ссылочный класс, rvalue-объект которого не может быть связан с неконстанной ссылкой. 
Первый и третий циклы в данном случае ведут себя одинаково. 
*/