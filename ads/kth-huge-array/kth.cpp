#include <fstream>
#include <iostream>
#include <limits.h>

class MaxHeap { 
    int* arr; 
  
    size_t capacity; 
    size_t size; 

    static size_t parent(size_t i){
        return (i - 1) / 2;
    }

    static size_t lChild(size_t i){
        return (2 * i + 1);
    }

    static size_t rChild(size_t i){
        return (2 * i + 2);
    }
  
public: 
    MaxHeap(size_t n): size(0), capacity(n), arr(new int[n]){}

    void MaxHeapify(size_t i);

    int removeMax(); 
  
    int getMax() { 
        return arr[0]; 
    }

    size_t curSize() const{
        return size;
    }

    void insertKey(int x); 

    int *getArray(){
        return arr;
    }

    ~MaxHeap(){
        delete[] arr;
    }
}; 
  
  
void MaxHeap::insertKey(int x) { 
    size++; 
    size_t i = size - 1; 
    arr[i] = x; 

    while (i != 0 && arr[parent(i)] < arr[i]) { 
        std::swap(arr[i], arr[parent(i)]); 
        i = parent(i); 
    } 
} 
  
int MaxHeap::removeMax() {
    if (size <= 0){
        return INT_MIN;
    }

    if (size == 1) { 
        size--; 
        return arr[0]; 
    } 
  
    int root = arr[0]; 
    arr[0] = arr[size - 1]; 
    size--; 

    MaxHeapify(0); 
  
    return root; 
} 

void MaxHeap::MaxHeapify(size_t i) { 
    size_t l = lChild(i); 
    size_t r = rChild(i); 
    size_t largest = i;

    if (l < size && arr[l] > arr[i]){
        largest = l;
    }

    if (r < size && arr[r] > arr[largest]){
        largest = r;
    }

    if (largest != i) { 
        std::swap(arr[i], arr[largest]); 
        MaxHeapify(largest); 
    } 
}

void mergeUtil(int *array, size_t l, size_t r){
    size_t mid = (l + r) / 2;

    size_t sizel = mid - l + 1;
    size_t sizer = r - mid;

    int *arrayl = new int[sizel];
    int *arrayr = new int[sizer];

    for(size_t i = 0; i < sizel; ++i){
        arrayl[i] = array[i+l];
    }  
    for(size_t i = 0; i < sizer; ++i){
        arrayr[i] = array[i+mid+1];  
    }

    size_t li = 0;
    size_t ri = 0;
    size_t i = l;

    while((li < sizel) && (ri < sizer)){
        if(arrayl[li] <= arrayr[ri]){
            array[i++] = arrayl[li++];
        }
        else{
            array[i++] = arrayr[ri++];
        }
    }

    while (li < sizel){
        array[i++] = arrayl[li++];
    }

    while (ri < sizer) {
        array[i++] = arrayr[ri++];
    }

    delete[] arrayl; 
    delete[] arrayr;
}

void mergeSort(int *array, size_t l, size_t r){
    if(r > l){
        size_t mid = (l + r) / 2;

        mergeSort(array, mid+1, r);
        mergeSort(array, l, mid);

        mergeUtil(array, l, r);
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

    int A;
    int B;
    int C;
    int x1;
    int x2;
    fin >> A >> B >> C >> x1 >> x2;

    MaxHeap heap(k2);
    heap.insertKey(x1);
    heap.insertKey(x2);

    for(size_t i = 2; i < k2; ++i){
        int xn = A*x1 + B*x2 + C;
        heap.insertKey(xn);
        x1 = x2;
        x2 = xn;
    }

    for(size_t i = k2; i < n; ++i){
        int xn = A*x1 + B*x2 + C;
        if(heap.getMax() > xn){
            heap.removeMax();
            heap.insertKey(xn);
        }
        x1 = x2;
        x2 = xn;
    }

    int *x = heap.getArray();

    mergeSort(x, 0, k2-1);

    for(size_t i = k1-1; i < k2; ++i){
        fout << x[i];
        if(i != k2-1){
            fout << " ";
        }
    }

    fin.close();
    fout.close();
    return 0;
}
