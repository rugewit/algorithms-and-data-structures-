#include <iostream>
#include <vector>
#include <string>


std::vector<int> z_function_trivial (std::string s) {
    int n = (int) s.length();
    std::vector<int> z (n);
    for (int i=1; i<n; ++i)
        while (i + z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
    return z;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
