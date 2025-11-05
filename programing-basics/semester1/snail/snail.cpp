#include <iostream>

int digit_amount(int n){
    int res = 0;
    while(n>0){
        res++;
        n/=10;
    }
    return res;
}

int main(){
    int rowsAmmount;
    int columnsAmount;
    std::cin >> rowsAmmount >> columnsAmount;
    int** snailMatrix = new int*[rowsAmmount];
    for(int i = 0; i < rowsAmmount; ++i){
        snailMatrix[i] = new int[columnsAmount];
        for(int j = 0; j < columnsAmount; ++j){
            snailMatrix[i][j]=0;
        }
    }
    
    int i = 0;
    int j = -1;
    int count = 0;
    while (count < rowsAmmount*columnsAmount) {
        while (j < columnsAmount - 1 && (snailMatrix[i][j+1]==0)){
            snailMatrix[i][++j] = ++count;
        }
        while (i < rowsAmmount - 1 && (snailMatrix[i+1][j]==0)){
            snailMatrix[++i][j] = ++count;
        }
        while (j > 0 && (snailMatrix[i][j-1]==0)){
            snailMatrix[i][--j] = ++count;
        }
        while (i > 0 && (snailMatrix[i-1][j]==0)){
            snailMatrix[--i][j] = ++count;
        }
    }
            
    int* maximum_size = new int[columnsAmount];
    for(int i = 0; i < columnsAmount; i++){
        int m = snailMatrix[0][i];
        for(int j = 1; j < rowsAmmount; j++){
            m = std::max(m, snailMatrix[j][i]);
        }
        maximum_size[i]=digit_amount(m);
    }

    for(int i = 0; i < rowsAmmount; i++){
        for(int j = 0; j < columnsAmount; j++){
            int current_size = digit_amount(snailMatrix[i][j]);
            for(int k = 0; k < maximum_size[j]-current_size; k++){
                std::cout << " ";
            }
            std::cout << snailMatrix[i][j];
            if(j<columnsAmount-1){
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    for(int i = 0; i < rowsAmmount; i++){
        delete[] snailMatrix[i];
    }
    delete[] snailMatrix;
    delete[] maximum_size;;
}
