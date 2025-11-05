#include <fstream>
#include <iostream>

class dsu{
private:
    size_t *arr;
    size_t *rank;
    size_t size;

public:
    dsu(size_t s): size(s), arr(new size_t[s]), rank(new size_t[s]){
        for(size_t i = 0; i < s; ++i) {
            arr[i] = i;
            rank[i] = 0;
        }
    }

    size_t find(size_t i){
        return (arr[i] == i ? i : arr[i] = find(arr[i]));
    }

    bool unite(size_t a, size_t b){
        a = find(a);
        b = find(b);
        if(a == b){
            return false;
        }

        if(rank[a] > rank[b]){
            std::swap(a,b);
        }

        if (rank[a] == rank[b]){
			++rank[a];
        }

        arr[a] = b;
        return true;
    }

    ~dsu(){
        delete[] arr;
        delete[] rank;
    }
};

struct edge {
    size_t u;
    size_t v;
    int cost;
};


size_t mergeutil(edge *array, size_t l, size_t r){
    size_t mid = (l + r) / 2;

    size_t sizel = mid - l + 1;
    size_t sizer = r - mid;

    edge *arrayl = new edge[sizel];
    edge *arrayr = new edge[sizer];

    for(size_t i = 0; i < sizel; ++i){
        arrayl[i] = array[i+l];
        arrayl[i] = array[i+l];
    }
    for(size_t i = 0; i < sizer; ++i){
        arrayr[i] = array[i+mid+1];
        arrayr[i] = array[i+mid+1];
    }

    size_t li = 0;
    size_t ri = 0;
    size_t i = l;
    size_t res = 0;

    while((li < sizel) && (ri < sizer)){
        if(arrayl[li].cost <= arrayr[ri].cost){
            array[i] = arrayl[li];
            array[i++] = arrayl[li++];
        }
        else{
            array[i] = arrayr[ri];
            array[i++] = arrayr[ri++];
            res += sizel - li;
        }
    }

    while (li < sizel){
        array[i] = arrayl[li];
        array[i++] = arrayl[li++];
    }

    while (ri < sizer) {
        array[i] = arrayr[ri];
        array[i++] = arrayr[ri++];
    }

    
    delete[] arrayl;
    delete[] arrayr; 

    return res;
}

size_t sort(edge *array, size_t l, size_t r){
    size_t res = 0ULL;
    if(r > l){
        size_t mid = (l + r) / 2;

        res += sort(array, mid+1, r);
        res += sort(array, l, mid);

        res += mergeutil(array, l, r);
    }

    return res;
}

int main(int argc, char **argv) {
    if(argc != 2){
        std::cerr << "Invalid arguments list\n";
        return 1;
    }

    std::ifstream fin(argv[1]);
    if(!fin.is_open()) {
        std::cerr << "File can not be opened";
        return 1;
    }

    int n;
    int m;
    fin >> n >> m;
    edge *edges;
    edges = new edge[m];
    dsu d(n);

    for(size_t i = 0; i < m; ++i){
        fin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }
    sort(edges, 0, m-1);

    size_t i = 0;
    int ans = 0;
    while(n > 0 && i < m){
        if(d.unite(edges[i].u, edges[i].v)){
            ans += edges[i].cost;
            --n;
        }
        ++i;
    }
    std::cout << ans;

    delete[] edges;
    return 0;
}

