#include <fstream>

template<typename T>
class list{
    struct node {
        T key;
        node *next;
        
        node(T val, node* n): key(val), next(n){}
        ~node(){
            delete next;
        }
    } *root;

    public:
    list(): root(nullptr){}
    ~list(){delete root;}

    void push_front(T val){
        root = new node(val, root);
    }

    void remove(T val){
        node *cur = root;
        node *parent = nullptr;
        while(cur != nullptr && cur->key != val){
            parent = cur;
            cur = cur->next;
        }

        if(cur == nullptr){
            return;
        }

        if(parent == nullptr){
            root = cur->next;
        }
        else{
            parent->next = cur->next;
        }

        cur->next = nullptr;
        delete cur;
    }


    bool find(T val){
        node *cur = root;
        while(cur != nullptr && cur->key != val){
            cur = cur->next;
        }

        return cur != nullptr;
    }
};

template<size_t capacity, 
         typename T,
         size_t hash_function(T)>
class unordered_set{
    size_t size;
    list<T> *arr;

    public:
    unordered_set(): arr(new list<T>[capacity]){}

    ~unordered_set(){
        delete[] arr;
    }

    void insert(int val){
        arr[hash_function(val)].push_front(val);
    }

    void remove(int val){
        arr[hash_function(val)].remove(val);
    }

    bool find(int val){
        return arr[hash_function(val)].find(val);
    }
};

const size_t capacity = 1000;
inline size_t hash_function(int val){return std::abs(val)%capacity;}

int main(int argc, char **argv){
    if(argc != 3){
        return 1;
    }
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    if(!fin.is_open() || !fout.is_open()){
        fin.close();
        fout.close();
        return 2;
    }

    size_t n;
    unordered_set<capacity, int, &hash_function> set;
    fin >> n;
    while(n-- > 0){
        char cmd;
        int val;
        fin >> cmd >> val;

        switch(cmd){
            default:
                return 3;

            case '?':
                fout << (set.find(val) ? "true" : "false") << '\n';
                break;

            case '-':
                set.remove(val);
                break;

            case '+':
                set.insert(val);
                break;
        }
    }
}
