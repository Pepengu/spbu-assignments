#include <fstream>
#include <iostream>

void quickSelect(int *array, int left, int right, int k1, int k2){
    if(left >= right){
        return;
    }

    int pivotVal = array[(left + right) / 2];
    int l = left - 1;
    int r = right + 1;

    while (l < r) {
        for(;array[++l] < pivotVal;){}
        for(;array[--r] > pivotVal;){}

        if(l >= r){
            break;
        }

        std::swap(array[l], array[r]);
    }

    if(r >= k1-1){
        quickSelect(array, left, r, k1, k2);
    }
    if (r < k2-1){
        quickSelect(array, r+1, right, k1, k2);
    }
}

int main(int argc, char *argv[]){
    if(argc != 3){
        std::cerr << "Wrong command" << '\n';
        return 1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    if(!fin.is_open() || !fout.is_open()){
        std::cerr << "Files could not be opened" << '\n';

        fin.close(); fout.close();

        return 1;
    }

    int n;
    int k1;
    int k2;
    fin >> n >> k1 >> k2;

    int *x = new int[n];
    int A;
    int B;
    int C;
    fin >> A >> B >> C >> x[0] >> x[1];

    for(int i = 2; i < n; ++i){
        x[i] = A*x[i-2] + B*x[i-1] + C;
    }

    quickSelect(x, 0, n - 1, k1, k2);

    for (size_t i = k1-1; i < k2-1; ++i) {
		fout << x[i] << ' ';
	}
    fout << x[k2-1];

    fin.close();
    fout.close();
    
    delete[] x;
    return 0;
}
