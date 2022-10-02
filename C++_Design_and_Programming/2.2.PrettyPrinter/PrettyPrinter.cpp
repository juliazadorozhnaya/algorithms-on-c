#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <tuple>
#include <functional>
using namespace std;

struct Printer {

    std::stringstream mystr;

    std::string str() const {
        return mystr.str();
    }

    
    template<typename T>
	Printer& format(const T& t){
		mystr << t;
		return *this;
	}


    template < typename T_1, typename T_2 >
    Printer & format(std::pair < T_1, T_2 >& p) {
        mystr << "( ";
        format(p.first);
        mystr << ", ";
        format(p.second);
        mystr << " )";
        return *this;
    }

    template <typename T >
    void brackets(T obj) {
        for (auto i = obj.begin(); i != obj.end(); i++) {
            format( * i);
            if (std::next(i) != obj.end()) {
                mystr << ", ";
            } else {
                mystr << " ";
            }
        }
    }

    template < typename T >
        Printer & format(std::set < T > s) {
            mystr << "{ ";
            brackets(s);
            mystr << "}";
            return *this;
        }

    template < typename T >
        Printer & format(std::vector < T > v) {
            mystr << "[ ";
            brackets(v);
            mystr << "]";
            return *this;
        }

    template<typename T>
	void write_tuple(T x) {
		mystr << Printer().format(x).str();
		mystr << ", ";		
	}

	template<typename... T>
	Printer& format(std::tuple<T... >& t) {
		mystr << "( ";
		std::apply([&](auto& ...x){(..., write_tuple(x));}, t);
		mystr.seekp(-2, std::ios_base::end);
		mystr << " )";
		return  *this;
	}

};

template<typename T>
	std::string format(const T& t) {
	return Printer().format(t).str();
}

int main() {
	std::tuple<std::string, int, int> t = {"xyz", 1, 2};
	std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
	std::string s1 = Printer().format(" vector: ").format(v).str();
	std::cout << s1 << endl;
	std::string s2 = Printer().format(t).format(" ! ").format(0).str();
	std::cout << s2 << endl;
}