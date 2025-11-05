#include <iostream>
#include <fstream>

typedef uint8_t card;
const int deck_size = 52;

class Hand{
private:
    card _cards[deck_size];
    int _top;
    int _bot;

public:
    Hand(): _top(-1), _bot(0){}

    bool is_empty() const;

    void push_bot(card c);
    void push_top(card c);

    card pop_top();
    card pop_bot();

    card get();
};

bool Hand::is_empty() const{
    return _top == -1;
}
    
void Hand::push_bot(card card){
    if(_top == -1){
        _bot = _top = 0;
    }
    else{
        _bot = (_bot + 1)%deck_size;
    }
    _cards[_bot] = card;
}

void Hand::push_top(card card){
    if(_top == -1){
        _bot = _top = 0;
    }
    else{
        _top = (deck_size + _top - 1)%deck_size;
    }
    _cards[_top] = card;
}

card Hand::pop_top(){
    if(_top == _bot){
        _top = _bot = -1;
    }

    card res = _cards[_top];
    if(_top == _bot){
        _top = _bot = -1;
    }
    else{
        _top = (_top + 1) % deck_size;
    }
    return res;
}

card Hand::pop_bot(){
    card res = _cards[_bot];
    if(_top == _bot){
        _top = _bot = -1;
    }
    else{
        _bot = (deck_size + _bot - 1) % deck_size;
    }
    return res;
}

int main(int argc, char* argv[]){
    std::ifstream fin(argv[1]);
    if (!fin.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    
    Hand players[2];

    for(int i = 0; i < deck_size; ++i){
        char cur; 
        fin >> cur;

        card c;

        switch (cur){
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            c = static_cast<card>(cur-'0');
            break;
        
        case '1':
            c = 10;
            break;
        
        case 'J':
            c = 11;
            break;

        case 'Q':
            c = 12;
            break;

        case 'K':
            c = 13;
            break;

        case 'A':
            c = 14;
            break;

        default:
            std::cerr << "Unknown card found" << std::endl;
            return 1;
        }

        players[i >= deck_size/2].push_bot(c);

        fin.ignore(10, '\n');
    }
    
    fin.close();

    Hand table;
    for(size_t move = 0; 
        move < 1000000 && !players[0].is_empty() && !players[1].is_empty(); 
        ++move){
        card first = 0;
        card second = 0;

        while(first == second && !players[0].is_empty() && !players[1].is_empty()){
            first = players[0].pop_top();
            second = players[1].pop_top();
            
            table.push_top(first);
            table.push_top(second);
        }

        if(players[0].is_empty() && players[1].is_empty()){
            std::cout << "draw" << std::endl;
            return 0;
        }
        
        if(players[0].is_empty()){
            std::cout << "second" << std::endl;
            return 0;
        }

        if(players[1].is_empty()){
            std::cout << "first" << std::endl;
            return 0;
        }
        
        bool winner = (first < second && !((first == 2) && (second == 14))) || 
                      ((first == 14) && (second == 2));
        while(!table.is_empty()){
            players[static_cast<size_t>(winner)].push_bot(table.pop_bot());
        }
    }

    if(players[0].is_empty()){
        std::cout << "second" << std::endl;
        return 0;
    }

    if(players[1].is_empty()){
        std::cout << "first" << std::endl;
        return 0;
    }

    std::cout << "unknown" << std::endl;
    return 0;
}
