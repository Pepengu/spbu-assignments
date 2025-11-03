#include <fstream>
#include <iostream>
#include "roman.hpp"

void redirectTillEnd(std::ifstream& fin, std::ofstream& fout){
    char current;
    while(fin.peek()!=' ' and fin.peek() != EOF and fin.peek() != '\n'){
        fin >> current;
        
        fout << current;
    }
}

int main(int argc, char* argv[]){

    if(argc < 3){
        std::cout << "Not enough parameters" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    if(!fin.is_open() or !fout.is_open()){
        std::cout << "File can not be opened" << std::endl;
        fin.close();
        fout.close();
        return 2;
    }
    
    fin >> std::noskipws;
    int cnt = 0;
    while(fin.peek() != EOF){
        char current; fin >> current;
        if((current <= '9' and current >= '0')){
            int number = current-'0';

            bool is_number = true;
            while(fin.peek() != ' ' and fin.peek() != EOF and fin.peek() != ')' and fin.peek() != '\n' and fin.peek() != '-'){
                fin >> current;

                if(not(current <= '9' and current >= '0')){
                    fout << number << current;
                    redirectTillEnd(fin, fout);
                    is_number = false;
                    break;
                }

                number*=10;
                number+=current-'0';
            }
            
            if(is_number){
                if(number < 4000){
                    foutRoman(fout, number);
                }
                else{
                    fout << number;
                }
            }
        }
        else{
            fout << current; 
            if(current != '(' and current != ' ' and current != '\n'){
                redirectTillEnd(fin, fout);
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}