#include <iostream>
#include <fstream>
#include <cstring>

void decode(std::istream &in, std::ostream &out){
    signed char length;
    while(in.peek() != EOF){
        length = static_cast<signed char>(in.get());
        if(length < 0){
            while(length++ < 0){
                out << static_cast<signed char>(in.get());
            }
        }
        else{
            char current = static_cast<char>(in.get());
            while(length-- >= 0){
                out << current;
            }
        }
    }
}

void encode(std::istream &in, std::ostream &out){
    char buffer[130];
    signed char length = 0;
    int current = -1;
    int last;
    in >> std::noskipws;
    while(in.peek()!=EOF){
        last = current;
        current = in.get();
        if(current != in.peek()){ 
            if(length > 0){
                out << length << static_cast<char>(current);
                length = 0;
            }
            else{
                if(length == -128){
                    out << length;
                    for(size_t i = 0; i < -length; ++i){
                        out << buffer[i];
                    }
                    length = 0;
                }
                buffer[-length--] = static_cast<char>(current);
            }

            if(length == static_cast<signed char>(-1) and last == current){
                out << '\0' << static_cast<char>(current);
                length = 0;
            }  
        }
        else{   
            if(length < 0){
                out << length;
                for(size_t i = 0; i < -length; ++i){
                    out << buffer[i];
                }
                length = 0;
            }

            if(length == 127){
                out << length << static_cast<char>(current);
                length = 0;
            }
            else{
                length++;
            }
        }
    }
    if(length < 0){
        out << length;
        for(size_t i = 0; i < -length; ++i){
            out << buffer[i];
        }
    }
}

int main(int argc, char* argv[]){
    if(argc!=4){
        std::cout << "Wrong input";
        return 1;
    }
    
    std::ifstream fin;
    std::ofstream fout;

    fin.open(argv[2], std::ios_base::binary);
    fout.open(argv[3], std::ios_base::binary);

    if(!fin.is_open() or !fout.is_open()){
        std::cout << "File can not be opened" << std::endl;
        fin.close();
        fout.close();
        return 2;
    }

    if(strcmp(argv[1], "-d") == 0){
        decode(fin, fout);
    }
    else if(strcmp(argv[1], "-e") == 0){
        encode(fin, fout);
    }
    else{
        std::cout << "No such command";
    }
    
    return 0;
}