#include <iostream>
#include <fstream>

size_t mergeUtil(int *array[2], size_t l, size_t r){
    size_t mid = (l + r) / 2;

    size_t sizel = mid - l + 1;
    size_t sizer = r - mid;

    int *arrayl[2] = {new int[sizel], new int[sizel]};
    int *arrayr[2] = {new int[sizer], new int[sizer]};

    for(size_t i = 0; i < sizel; ++i){
        arrayl[0][i] = array[0][i+l];
        arrayl[1][i] = array[1][i+l];
    }
    for(size_t i = 0; i < sizer; ++i){
        arrayr[0][i] = array[0][i+mid+1];
        arrayr[1][i] = array[1][i+mid+1];
    }

    size_t li = 0;
    size_t ri = 0;
    size_t i = l;
    size_t res = 0;

    while((li < sizel) && (ri < sizer)){
        if(arrayl[0][li] <= arrayr[0][ri]){
            array[0][i] = arrayl[0][li];
            array[1][i++] = arrayl[1][li++];
        }
        else{
            array[0][i] = arrayr[0][ri];
            array[1][i++] = arrayr[1][ri++];
            res += sizel - li;
        }
    }

    while (li < sizel){
        array[0][i] = arrayl[0][li];
        array[1][i++] = arrayl[1][li++];
    }

    while (ri < sizer) {
        array[0][i] = arrayr[0][ri];
        array[1][i++] = arrayr[1][ri++];
    }

    
    delete[] arrayl[0];
    delete[] arrayl[1]; 
    delete[] arrayr[0];
    delete[] arrayr[1]; 

    return res;
}

size_t mergeSortWithInv(int *array[2], size_t l, size_t r){
    size_t res = 0ULL;
    if(r > l){
        size_t mid = (l + r) / 2;

        res += mergeSortWithInv(array, mid+1, r);
        res += mergeSortWithInv(array, l, mid);

        res += mergeUtil(array, l, r);
    }

    return res;
}

size_t countRepeats(const int *array, size_t n){
    size_t ans = 0;
    size_t cur_rep = 1;
    for(size_t i = 1; i < n; ++i){
        if(array[i] == array[i-1]){
            ++cur_rep;
        }
        else if (cur_rep > 1){
            ans += cur_rep*(cur_rep-1)/2;
            cur_rep = 1;
        }
    }
    if (cur_rep > 1){
        ans += cur_rep*(cur_rep-1)/2;
    }
    return ans;
}

int main(int argc, char* argv[]){
    std::ifstream fin(argv[1]);
    if (!fin.is_open()){
        std::cerr << "Error opening file\n";
        return 1;
    }

    size_t n; fin >> n;
    int *y[2]{new int[n], new int[n]};

    for(size_t i = 0; i < n; ++i){
        fin >> y[0][i] >> y[1][i];
    }

    mergeSortWithInv(y, 0, n-1);

    size_t ans = countRepeats(y[0], n);

    std::swap(y[0], y[1]);
    ans += mergeSortWithInv(y, 0, n-1);
    ans += countRepeats(y[0], n);
    
    std::cout << ans << std::endl;
    delete[] y[0];
    delete[] y[1]; 
    return 0;
}
