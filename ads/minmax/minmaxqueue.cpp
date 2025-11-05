#include <fstream>
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack{
    T *_arr;
    size_t _top;
    size_t _size;

public:
    Stack(): _size(32), _arr(new T[32]), _top(-1) {}
    ~Stack(){
        delete[] _arr;
    }

    inline bool isEmpty() const{
        return _top == -1;
    }

    void push(const T &val){
        if(++_top == _size){
            T *tmp = new T[_size*2];
            _size *= 2;

            for(size_t i = 0; i < _top; ++i){
                tmp[i] = _arr[i];
            }

            delete[] _arr;
            _arr = tmp;
        }

        _arr[_top] = val;
    }

    T top() const{
        if(isEmpty()){
            throw std::out_of_range("Empty stack");
        }

        return _arr[_top];
    }

    void pop(){
        if(isEmpty()){
            throw std::out_of_range("Empty stack");
        }

        --_top;
    }

    T top_pop(){
        if(isEmpty()){
            throw std::out_of_range("Empty stack");
        }

        return _arr[_top--];
    }
    
};



class PQueue{
    struct data{
        int val;
        int min;
        int max;
    };
    Stack<data> in;
    Stack<data> out;

    static void stack_push(int n, Stack<data> &s);

public:
    int min() const;
    int max() const;

    void push(int n);
    void pop();
    int dif();
};


void PQueue::stack_push(int n, Stack<data> &s){
    if(s.isEmpty()){
        s.push({n,n,n});
        return;
    }

    s.push({n,
            std::min(s.top().min, n),
            std::max(s.top().max, n)});
}

int PQueue::min() const{
    if (in.isEmpty() && out.isEmpty()){
        return 0;
    }

    if (in.isEmpty() || out.isEmpty()){
        return in.isEmpty() ? out.top().min : in.top().min;
    }
    
    return std::min(out.top().min, in.top().min);
}


int PQueue::max() const{
    if (in.isEmpty() && out.isEmpty()){
        return 0;
    }

    if (in.isEmpty() || out.isEmpty()){
        return in.isEmpty() ? out.top().max : in.top().max;
    }
    
    return std::max(out.top().max, in.top().max);
} 

void PQueue::push(int n){
    stack_push(n, in);
}

void PQueue::pop(){
    if(out.isEmpty()){
        while(!in.isEmpty()){
            stack_push(in.top_pop().val, out);
        }
    }

    out.pop();
}

int PQueue::dif(){
    if (in.isEmpty() && out.isEmpty()){
        return 0;
    }
    return this->max() - this->min();
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

        fin.close();
        fout.close();

        return 1;
    }

    PQueue q;

    size_t n;
    fin >> n;

    while(n-- > 0){
        char cmd;
        fin >> cmd;
        int val;

        switch (cmd){
        case '?':
            fout << q.dif() << '\n';
            break;
        
        case '+':
            fin >> val;
            q.push(val);
            break;

        case '-':
            q.pop();
            break;
            
        default:
            break;
        }
    }

    return 0;
}
