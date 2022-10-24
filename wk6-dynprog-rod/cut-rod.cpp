#include <iostream>
#include <vector>
#include <algorithm>

int cutRodDynamic(const std::vector<int> & p, int n, std::vector<int> rmemo) {
    int r;
    rmemo[0] = 0;
    for (int j = 1; j <= n; j++) {
        r = -1;
        for (int i = 1; i <= j ; i ++) {
            r = std::max(r, p[i] + rmemo[j-i]);
        } 
        rmemo[j] = r;
    }
    return rmemo[n];
}

int main() {
    std::vector<int> p{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n;
    std::cin >> n;
    std::vector<int> r(n+1);
    std::cout << cutRodDynamic(p, n, r) << std::endl;
}