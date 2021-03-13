#include <iostream>
#include <vector>
#include <string>

const char DELIMITER = '@';

// src
// https://habr.com/ru/post/307220/
// https://algorithmica.org/ru/string-searching

std::vector<size_t> prefixFunction (const std::string& s) {
    size_t n =  s.length();
    std::vector<size_t> pi(n); // в i-м элементе (его индекс i-1) количество совпавших символов в начале и конце для подстроки длины i.
    // p[0]=0 всегда, p[1]=1, если начинается с двух одинаковых
    for (size_t i=1; i<n; ++i)
    {
        // ищем, какой префикс-суффикс можно расширить
        size_t j = pi[i-1]; // длина предыдущего префикса-суффикса, возможно нулевая
        while ((j > 0) && (s[i] != s[j])) // этот нельзя расширить,
            j = pi[j-1];   // берем длину меньшего префикса-суффикса

        if (s[i] == s[j])
            ++j;  // расширяем найденный (возможно пустой) префикс-суффикс
        pi[i] = j;
    }
    return pi;
}

std::vector<int> zFunction (const std::string& s) {
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

void inside(const std::string& text,const std::string& str){
    long n = str.size();
    if (text.size() < str.size()){
        throw std::logic_error("text.size() < str.size()");
    }
    std::string line = str + DELIMITER + text;
    std::vector<size_t> prefixArray = prefixFunction(line);
    std::vector<int> zArray = zFunction(line);
    for(long i = n + 1;i < line.size(); i++){
        if (prefixArray[i] == n){
            std::cout << "inside on " << (i - n - 1 - n + 1) << std::endl;
        }
        if (zArray[i] == n){
            std::cout << "z on " << (i - n - 1) << std::endl;
        }
    }
}


int main() {
    inside("qweaqwea","qwe");
    return 0;
}