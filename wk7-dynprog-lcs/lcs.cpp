#include <string>
#include <vector>
#include <iostream>
#include <fstream>

int lcsLength(std::string & x, std::string & y, int m, int n, std::vector<std::vector<char>> & dir, std::vector<std::vector<int>> & len) {
    // code
}

void printLCS(std::vector<std::vector<char>> & dir, std::string & x, int m, int n) {
    //code
}

int main() {
    
    // process file
    //std::ifstream in;
    //in.open("seq_data.txt");
    //std::string x, y;
    //in >> x >> y;
    //in.close();

    std::string x = "ACGTTTT";
    std::string y = "CGTT";

    int m = x.length() + 1;
    int n = y.length() + 1;

    std::vector<std::vector<char>> dir(m, std::vector<char>(n, ' ')); // "b"
    std::vector<std::vector<int>> seq(m, std::vector<int> (n, 0)); // "c"
    

    return 0;
}