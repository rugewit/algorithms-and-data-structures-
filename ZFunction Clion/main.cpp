#include <iostream>
#include <vector>
#include <string>

// src
// https://algorithmica.org/ru/string-searching

std::vector<int> zFunctionTrivial (const std::string& inputString) {
    int n = (int) inputString.length();
    std::vector<int> z (n,0);
    for(int i = 1; i < n; i++){
        int curZLength = 0;
        while( (i + curZLength < n) && (inputString[i + curZLength] == inputString[curZLength]) ){
            curZLength++;
        }
        z[i] = curZLength;
    }
    return z;
}

std::vector<int> ZFunction(const std::string& inputString);


std::vector<int> z_function (const std::string& s) {
    int n = (int) s.size();
    std::vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        // если мы уже видели этот символ
        if (i <= r)
            // то мы можем попробовать его инициализировать z[i - l],
            // но не дальше правой границы: там мы уже ничего не знаем
            z[i] = std::min(r - i + 1, z[i - l]);
        // дальше каждое успешное увеличение z[i] сдвинет z-блок на единицу
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        // проверим, правее ли мы текущего z-блока
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}



template <class T>
void printVec(const std::vector<T>& vec){
    for(const auto& el: vec){
        std::cout << el << " ";
    }
    std::cout << std::endl;
}



int main() {
    std::string inputLine = "abacabad";
    printVec<int>(z_function(inputLine));
    return 0;
}
