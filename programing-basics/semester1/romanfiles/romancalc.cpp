#include <fstream>
#include <iostream>
#include "roman.hpp"

void foutRomanAndCheck(std::ofstream& fout, int n){
    if(n > 3999){
        fout << "ERR";
    }
    else{
        foutRoman(fout, n);
    }
}

bool isRoman(char c){
    char romans[8] = "MDCLXVI";

    for(size_t i = 0; i < 8; ++i){
        if(c == romans[i]){
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]){
    
    if(argc < 3){
        std::cout << "Not enough parameters" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1], std::ios_base::binary);
    std::ofstream fout(argv[2], std::ios_base::binary);

    if(!fin.is_open() or !fout.is_open()){
        std::cout << "File can not be opened" << std::endl;
        fin.close();
        fout.close();
        return 2;
    }

    fin >> std::noskipws;
    
    int numbers[101];
    for(int i = 0; i < 101; i++){
        numbers[i] = -1;
    }
    int top_index = 0;
    while(fin.peek() != EOF){      
        switch (fin.peek()){
            case ' ':
                fout << ' ';
                fin.get();
                break;

            case '+':
                fout << static_cast<char>(fin.get());
                if(top_index > 1){
                    top_index--;
                    numbers[top_index-1]=numbers[top_index-1] + numbers[top_index];
                }
                break;
            case '-':
                fout << static_cast<char>(fin.get());
                if(top_index > 1){
                    top_index--;
                    numbers[top_index-1]=numbers[top_index-1] - numbers[top_index];
                }
                break;
            case '*':
                fout << static_cast<char>(fin.get());
                if(top_index > 1){
                    top_index--;
                    numbers[top_index-1]=numbers[top_index-1] * numbers[top_index];
                }
                break;
            case '/':
                fout << static_cast<char>(fin.get());
                if(top_index > 1){
                    top_index--;
                    if(numbers[top_index] != 0){
                        numbers[top_index-1]=numbers[top_index-1] / numbers[top_index];
                    }
                }
                break;
            
            case '\n':
                fout << " = ";
                foutRomanAndCheck(fout, numbers[top_index-1]);
                fin.get();
                top_index = 0;
                fout << "\n";
                break;
            
            default:
                if(isRoman(static_cast<char>(fin.peek()))){
                    int current_number = 0;
                    while(isRoman(static_cast<char>(fin.peek()))){
                        switch (fin.get()){
                            case 'M':
                                if(current_number/100%10>0){
                                    current_number -= 200;
                                }
                                current_number+=1000;
                                break;
                            case 'D':
                                if(current_number/100%10 > 0){
                                    current_number -= 200;
                                }
                                current_number+= 500;
                                break;
                            case 'C':
                                if(current_number/10%10>0){
                                    current_number -= 20;
                                }
                                current_number+=100;
                                break;
                            case 'L':
                                if(current_number/10%10 > 0){
                                    current_number -= 20;
                                }
                                current_number+= 50;
                                break;
                            case 'X':
                                if(current_number%10>0){
                                    current_number -= 2;
                                }
                                current_number+=10;
                                break;
                            case 'V':
                                if(current_number%10 > 0){
                                    current_number -= 2;
                                }
                                current_number+= 5;
                                break;
                            case 'I':
                                current_number++;
                                break;
                        }
                    }
                    
                    foutRomanAndCheck(fout, current_number);

                    numbers[top_index++] = current_number;       
                }
                else{
                        fin.get();
                    //fout << static_cast<char>(fin.get());
                }
                break;
        }
    }

    if(top_index > 0){
        fout << " = ";
        foutRomanAndCheck(fout, numbers[top_index-1]);
    }

    fin.close();
    fout.close();
    return 0;
}