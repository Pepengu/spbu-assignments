#include <fstream>
#include <iostream>

struct pair{
    double data;
    int idx;
};

int Partition(pair *arr, int l, int r){
    double pivot = arr[r].data;
    int i = l;
    int j = l;
    for (; j < r; ++j) {
        if (arr[j].data < pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[r]);
    return i;
}

int randomPartition(pair *arr, int l, int r){
    int n = r - l + 1;
    int pivot = rand() % n;
    std::swap(arr[l + pivot], arr[r]);
    return Partition(arr, l, r);
}

pair findMedian(pair *arr, int l, int r, int k){
    int partitionIndex = randomPartition(arr, l, r);

    if (partitionIndex == k) {
        return arr[partitionIndex];
    }

    if (partitionIndex >= k and l <= partitionIndex - 1){
        return findMedian(arr, l, partitionIndex - 1, k);
    }

    return findMedian(arr,partitionIndex + 1,r, k);
}

int main(int argc, char* argv[]){
    std::ifstream fin(argv[1]);
    if (!fin.is_open()){
        std::cerr << "Error opening file\n";
        return 1;
    }

    int n; 
    fin >> n;
    pair *array = new pair[n];
    fin >> array[0].data;
    array[0].idx = 1;

    pair min = array[0];
    pair max = array[0];
    for(int i = 1; i < n; ++i){
        fin >> array[i].data;
        array[i].idx = i + 1;

        if(min.data < array[i].data){
            min = array[i];
        }
        if(max.data > array[i].data){
            max = array[i];
        }
    }

    std::cout << max.idx << " " << findMedian(array, 0, n-1, n/2).idx << " " << min.idx; 
    delete[] array;
    return 0;
}
