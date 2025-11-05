#include <iostream>
#include <cstring>
#include <fstream>

template<typename T>
class Vector 
{
private:
    T* data;
    int size;
    int capacity;

    void resize(int newCapacity)     {
        T* newData = new T[newCapacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), size(0), capacity(0) {}

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity){
            int newCapacity = (capacity == 0) ? 1 : 2 * capacity;
            resize(newCapacity);
        }

        data[size] = value;
        size++;
    }

    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    inline T& operator[](int index) {
        return data[index];
    }

    T& back() {
        return data[size - 1];
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }
};


class priorityQueue {
private:
    struct Values {
        int value = 0;
        size_t index = 0;
    };

    Vector<Values> heap;
    int* check_ind;
    size_t map_size;

    void resizeMap(size_t n) {
        int* newMap = new int[n];
        for (int i = 0; i < map_size; ++i) {
            newMap[i] = check_ind[i];
        }
        delete[] check_ind;
        check_ind = newMap;
        map_size = n;
    }

    void siftUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[parentIndex].value <= heap[index].value) {
                break;
            }

            std::swap(heap[index], heap[parentIndex]);
            check_ind[heap[index].index] = index;
            check_ind[heap[parentIndex].index] = parentIndex;
            index = parentIndex;
        }
    }

    void siftDown(int index) {
        int heapSize = heap.getSize();
        int minIndex;
        do {
            int l = 2 * index + 1;
            int r = 2 * index + 2;
            minIndex = index;

            if (l < heapSize && heap[l].value < heap[minIndex].value){
                minIndex = l;
            }

            if (r < heapSize && heap[r].value < heap[minIndex].value){
                minIndex = r;
            }

            if (minIndex != index) {
                std::swap(heap[index], heap[minIndex]);
                check_ind[heap[index].index] = index;
                check_ind[heap[minIndex].index] = minIndex;
                index = minIndex;
                minIndex = -1;
            }
        } while(minIndex != index);
    }

public:
    priorityQueue() : check_ind(new int[16]), map_size(16) {}
    ~priorityQueue() {delete[] check_ind;}

    inline bool is_empty(){
        return heap.empty();
    }

    void push(int value, size_t index) {
        Values n{value, index};
        heap.push_back(n);

        if (index >= map_size) {
            resizeMap(index*2); 
        }
        check_ind[index] = heap.getSize() - 1;

        siftUp(heap.getSize() - 1);
    }

    int extractMin() {
        int minValue = heap[0].value;
        size_t minIndex = heap[0].index;
        check_ind[minIndex] = -1; 

        if (heap.getSize() > 1) {
            heap[0] = heap.back();
            check_ind[heap[0].index] = 0;
            heap.pop_back();
            siftDown(0);
        }
        else {
            heap.clear();
        }

        return minValue;
    }

    void replace(int index, int newValue) {
        if (index >= map_size) {
            int newMapSize = index + 1;
            resizeMap(newMapSize);
        }

        int heapIndex = check_ind[index];

        int oldValue = heap[heapIndex].value;
        if (newValue < oldValue) 
        {
            heap[heapIndex].value = newValue;
            siftUp(heapIndex);
        }
    }
};



int main(int argc, char **argv){
    if(argc != 3){
        std::cerr << "Invalid arguments list\n";
        return 1;
    }

    std::ifstream fin(argv[1]);
    if(!fin.is_open()) {
        std::cerr << "Input file can not be opened";
        return 1;
    }

    std::ofstream fout(argv[2]);
    if(!fout.is_open()) {
        std::cerr << "Output file can not be opened";
        return 1;
    }

    priorityQueue pq;
    char command[15];
    int x;
    int y;

    for (size_t cmd = 0; fin >> command; ++cmd){
        switch(command[0]){
            case 'p':
                fin >> x;
                pq.push(x, cmd);
                break;
            
            case 'e':
                if(pq.is_empty()){
                    fout << "*\n";
                }
                else{
                    fout << pq.extractMin() << '\n';
                }
                break;

            case 'd':
                fin >> x >> y;
                pq.replace(x - 1, y);
                break;
        }
    }


    fin.close();
    fout.close();
}
