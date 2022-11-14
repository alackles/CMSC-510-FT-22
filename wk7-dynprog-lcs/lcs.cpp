#include <string>
#include <vector>
#include <iostream>
#include <fstream>

int lcsLength(std::string & x, std::string & y, int m, int n, std::vector<std::vector<char>> & dir, std::vector<std::vector<int>> & len) {
    for (int i = 1; i < m; i++){
        for (int j = 1; j < n; j++) {
            if (x[i-1] == y[j-1]) {
                len[i][j] = len[i-1][j-1] +1;
                dir[i][j] = 'd';
            } else if (len[i-1][j] >= len[i][j-1]) {
                len[i][j] = len[i-1][j];
                dir[i][j] = 'u';
            } else {
                len[i][j] = len[i][j-1];
                dir[i][j] = 'l';
            }
        }
    }
    return len[m-1][n-1];
}

void printLCS(std::vector<std::vector<char>> & dir, std::string & x, int m, int n) {
    if (m == 0 || n == 0) {
        std::cout << x[m];
        return;
    }
    if (dir[m][n] == 'd') {
        printLCS(dir, x, m-1, n-1);
        std::cout << x[m];
    } else if (dir[m][n] == 'u'){
        printLCS(dir, x, m-1, n);
    } else {
        printLCS(dir, x, m, n-1);
    }
}

int main() {
    
    // process file
    std::ifstream in;
    in.open("seq_data.txt");
    std::string x, y;
    in >> x >> y;
    in.close();

    //std::string x = "ACGTTT";
    //std::string y = "GTAT";

    int m = x.length() + 1;
    int n = y.length() + 1;

    std::vector<std::vector<char>> dir(m, std::vector<char>(n, ' ')); // "b"
    std::vector<std::vector<int>> len(m, std::vector<int> (n, 0)); // "c"
    
    std::cout << lcsLength(x, y, m, n, dir, len) << std::endl;

    printLCS(dir, x, m-1, n-1);
    std::cout << std::endl;

    return 0;
}