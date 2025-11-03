#include <iostream>
#include <fstream>

class Hex{
    private:
        uint64_t dec;
        char hex[17];
        size_t length;

        static char getHexVal(int n);
    
    public:
        Hex(int s, int n);
        const char* GetHexValue() const;

        friend std::ostream& operator<< (std::ostream &out, Hex &n);
};

char Hex::getHexVal(int n){
    if(n%16>9){
        return static_cast<char>(static_cast<int>('A')+n%16-10);
    }
    return static_cast<char>(static_cast<int>('0')+n%16);
}

Hex::Hex(int s, int n){
    this->length = s;
    this->hex[s]='\0';
    this->dec = n;

    if(n==EOF){
        for(size_t i = 0; i < s; ++i){
            this->hex[i] = ' ';
        }
        return;
    }

    for(size_t i = s; i > 0; --i){
        this->hex[i-1] = this->getHexVal(n%16);
        n/=16;
    }
}

const char* Hex::GetHexValue() const{
    return this->hex;
}

std::ostream& operator<< (std::ostream &out, Hex &n){
    out << n.GetHexValue();
    return out;
}

int main(int argc, char* argv[]){
    std::ifstream fin;
    std::ofstream fout;

    if(argc != 3){
        std::cout << "Wrong input" << std::endl;
        return 1;
    }

    fin.open(argv[1], std::ios_base::binary);
    fout.open(argv[2], std::ios_base::binary);

    if(!fin.is_open() or !fout.is_open()){
        std::cout << "File can not be opened" << std::endl;
        fin.close();
        fout.close();
        return 2;
    }

    fin >> std::noskipws;
    int idx = -16;
    unsigned char line[16];
    int ended = -1;
    while(fin.peek() != EOF){
        for(int i = 0; i < 16; ++i){
            if(fin.peek()==EOF){
                if(ended == -1){
                    ended = i;
                }
                line[i] = '\0';
            }
            else{
                fin >> line[i];
            }
        }
        Hex cur = Hex(10, idx+=16);
        fout << cur << ": ";
        for(int i = 0; i < 8; ++i){
            if(ended!= -1 and i >= ended){
                cur =Hex(2, EOF);
                fout << cur << " ";
            }
            else{
                cur = Hex(2, line[i]);
                fout << cur << " ";
            }
        }
        fout << "| ";
        for(int i = 8; i < 16; ++i){
            if(ended!= -1 and i >= ended){
                cur =Hex(2, EOF);
                fout << cur << " ";
            }
            else{
                cur = Hex(2, line[i]);
                fout << cur << " ";
            }
        }

        fout << " ";
        for(int i = 0; i < 16; ++i){
            if(ended!= -1 and i >= ended){
                break;
            }
            if(line[i] < 32){
                fout << '.';
            }
            else{
                fout << line[i];
            }
        }
        if(ended == -1){
            fout << "\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}