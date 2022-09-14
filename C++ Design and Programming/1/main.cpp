#include <iostream>
#include <array>

constexpr int factor(int i, int j)
{
    return (i + j) % 2 ? 1 : -1;
}


template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a) {
    int res = 0;
    for (int i = 0; i != N; ++i) {
        std::array<std::array<int, N - 1>, N - 1> minor {};
        for (int j = 0; j < N-1; ++j) {
            int ll = 0;
            for (int l = 0; l < N; l++) {
                if (l != i) {
                    (&std::get<0>((&std::get<0>(minor))[ll]))[j] = a[j+1][l];
                    ++ll;
                }
            }
        }
        res += factor(i,1) *a[0][i] * det<N-1>(minor);
    }
    return res;
}


template <>
constexpr int det<0>(const std::array<std::array<int, 0>, 0>& a)
{
    return 1;
}

template <>
constexpr int det<1>(const std::array<std::array<int, 1>, 1>& a)
{
    return a[0][0];
}

template <>
constexpr int det<2>(const std::array<std::array<int, 2>, 2>& a)
{
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}


int main() {
    constexpr std::array<std::array<int, 3>, 3> A = {{
                                                             {0, 1, 2}
                                                             ,{1, 2, 3}
                                                             ,{2, 3, 7}
                                                     }};
    constexpr int res = det<3>(A);
    std::cout << res << std::endl;
}