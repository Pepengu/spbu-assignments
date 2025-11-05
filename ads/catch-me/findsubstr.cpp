#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstring>


size_t KMP(const char *S, const char *pattern, size_t size, const size_t *pf){
    size_t ans = 0;
    char line[1028];
    size_t sizeS = 0;
    for(const char *c = S; *c != '\0'; ++c, ++sizeS){}
    for (size_t k = 0, i = size; i < sizeS; ++i){
        while ((k > 0) && (pattern[k] != S[i])){
            k = pf[k - 1];
        }

        if (pattern[k] == S[i]){
            k++;
        }

        if (k == size){
            ++ans;
        }

    }

    return ans;
}


int main(int argc, char **argv){
    if(argc != 3){
        std::cerr << "Invalid arguments amount";
        return 1;
    }

    std::ifstream fin(argv[2]);
    if(!fin.is_open()){
        std::cerr << "File opening failed";
        return 2;
    }


    char *pattern = argv[1];

    size_t size = 0;
    for(const char *c = pattern; *c != '\0'; ++c, ++size){}
    static size_t *pf = new size_t[size];

    pf[0] = 0;
    for (size_t k = 0, i = 1; i < size; ++i){
        while ((k > 0) && (pattern[i] != pattern[k])){
            k = pf[k - 1];
        }

        if (pattern[i] == pattern[k]){
            k++;
        }

        pf[i] = k;
    }

    char line[1028];
    std::memset(line, '\0', sizeof(line));
    size_t ans = 0;
    while (fin.getline(line, sizeof(line), '\n')) {
        ans += KMP(line, pattern, size, pf);
    }

    std::cout << ans;

    delete[] pf;
    fin.close();
}
