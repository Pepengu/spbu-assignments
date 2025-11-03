#include <fstream>
#include <iostream>
#include <cstring>

class Matrix{
    private:
        double** matrix;
        size_t rows_amount;
        size_t columns_amount;
    
    public:
        Matrix(size_t r, size_t c, double **m): rows_amount(r), columns_amount(c), matrix(m){}

        void addNumberToRow(size_t r, int n);
        void addNumberToRow(size_t r, double n);
        void addToNumberColumn(size_t c, int n);
        void addToNumberColumn(size_t c, double n);

        void reduceNumberFromRow(size_t r, int n);
        void reduceNumberFromRow(size_t r, double n);
        void reduceNumberFromColumn(size_t c, int n);
        void reduceNumberFromColumn(size_t c, double n);

        void multiplyRowByNumber(size_t r, int n);
        void multiplyRowByNumber(size_t r, double n);
        void multiplyColumnByNumber(size_t c, int n);
        void multiplyColumnByNumber(size_t c, double n);

        void divideRowByNumber(size_t r, int n);
        void divideRowByNumber(size_t r, double n);
        void divideColumnByNumber(size_t c, int n);
        void divideColumnByNumber(size_t c, double n);

        void reduceByMultipliedRow(size_t r1, size_t r2, double m);

        void addColumnToColumn(size_t c1, size_t c2);
        void addRowToRow(size_t r1, size_t r2);

        Matrix getMinor(size_t r, size_t c);

        double getDetermenant();

        double* getRowMultiplied(size_t r, double m);

        Matrix getInverted();

        friend std::ofstream& operator<< (std::ofstream& fout, Matrix matrix);

        void free();
};

class MatrixException  : public std::exception {
    private:
        const char * message;

    public:
        explicit MatrixException(const char * msg) : message(msg) {}

        const char * what () {
            return message;
        }
};

//Output to file function

std::ofstream& operator<< (std::ofstream& fout, Matrix matrix){
    for(int i = 0; i < matrix.rows_amount; ++i){
        for(int j = 0; j < matrix.columns_amount; ++j){
            if(matrix.matrix[i][j] == -0){
                fout << 0;
            }
            else{
                fout << matrix.matrix[i][j];
            }
            if(j!=matrix.columns_amount){
                fout << " ";
            }
        }
        fout << std::endl;
    }
    return fout;
}

void Matrix::free(){
    for(size_t i = 0; i < this->rows_amount; ++i){
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
}


//Matrix addition functions

void Matrix::addNumberToRow(size_t r, int n){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]+=n;
    }
}

void Matrix::addNumberToRow(size_t r, double n){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]+=n;
    }
}

void Matrix::addToNumberColumn(size_t c, int n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]+=n;
    }
}

void Matrix::addToNumberColumn(size_t c, double n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]+=n;
    }
}


//Matrix subtraction functions

void Matrix::reduceNumberFromRow(size_t r, int n){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]-=n;
    }
}

void Matrix::reduceNumberFromRow(size_t r, double n){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]-=n;
    }
}

void Matrix::reduceNumberFromColumn(size_t c, int n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]-=n;
    }
}

void Matrix::reduceNumberFromColumn(size_t c, double n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]-=n;
    }
}


//Matrix multiplication functions

void Matrix::multiplyRowByNumber(size_t r, int n){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]*=n;
    }
}

void Matrix::multiplyRowByNumber(size_t r, double n){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]*=n;
    }
}

void Matrix::multiplyColumnByNumber(size_t c, int n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]*=n;
    }
}

void Matrix::multiplyColumnByNumber(size_t c, double n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]*=n;
    }
}


//Matrix division functions

void Matrix::divideRowByNumber(size_t r, int n){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]/=n;
    }
}

void Matrix::divideRowByNumber(size_t r, double n){    
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r][i]/=n;
    }
}

void Matrix::divideColumnByNumber(size_t c, int n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]/=n;
    }
}

void Matrix::divideColumnByNumber(size_t c, double n){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c]/=n;
    }
}

//Rows and columns addition funtions

void Matrix::addColumnToColumn(size_t c1, size_t c2){
    for(size_t i = 0; i < this->rows_amount; ++i){
        this->matrix[i][c1]+=this->matrix[i][c2];
    }
}

void Matrix::addRowToRow(size_t r1, size_t r2){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r1][i]+=this->matrix[r2][i];
    }
}



void Matrix::reduceByMultipliedRow(size_t r1, size_t r2, double m){
    for(size_t i = 0; i < this->columns_amount; ++i){
        this->matrix[r1][i]-=this->matrix[r2][i]*m;
    }
}


double Matrix::getDetermenant(){
    if(this->rows_amount!=this->columns_amount){
        throw MatrixException("error");
    }

    Matrix regular(this->rows_amount, this->columns_amount, this->matrix);

    double multiply = 1;
    for(size_t current_row = 0; current_row < rows_amount-1; ++current_row){
        size_t non_zero_element = current_row;
        while (non_zero_element < regular.columns_amount and regular.matrix[current_row][non_zero_element] == 0){
            non_zero_element++;
        }

        if(non_zero_element >= regular.columns_amount){
            return 0;
        }
        
        if(non_zero_element!=current_row){
            regular.addColumnToColumn(current_row, non_zero_element);
        }

        multiply*=regular.matrix[current_row][current_row];
        regular.divideRowByNumber(current_row, regular.matrix[current_row][current_row]);

        for(size_t next_row = current_row+1; next_row < rows_amount; ++next_row){
            regular.reduceByMultipliedRow(next_row, current_row, regular.matrix[next_row][current_row]);
        }
    }

    return regular.matrix[regular.rows_amount-1][regular.columns_amount-1]*multiply;
}


Matrix Matrix::getInverted(){
    if(this->rows_amount != this->columns_amount){
        throw MatrixException("error");
    }
    
    Matrix regular = *this;

    double** identity = new double*[rows_amount];
    for(size_t i = 0; i < rows_amount; ++i){
        identity[i] = new double[columns_amount];
        for(size_t j = 0; j < columns_amount; ++j){
            if(i==j){
                identity[i][j]=1;
            }
            else{
                identity[i][j]=0;
            }
        }
    }
    Matrix inverted(this->rows_amount, this->columns_amount, identity);

    for(size_t current_row = 0; current_row < rows_amount; ++current_row){
        size_t non_zero_element = current_row;
        while (non_zero_element < regular.columns_amount and regular.matrix[non_zero_element][current_row] == 0){
            non_zero_element++;
        }

        if(non_zero_element >= inverted.columns_amount){
            throw(MatrixException("singular"));
        }
        
        if(non_zero_element!=current_row){
            regular.addRowToRow(current_row, non_zero_element);
            inverted.addRowToRow(current_row, non_zero_element);
        }

        inverted.divideRowByNumber(current_row, regular.matrix[current_row][current_row]);
        regular.divideRowByNumber(current_row, regular.matrix[current_row][current_row]);

        for(size_t next_row = current_row+1; next_row < rows_amount; ++next_row){
            inverted.reduceByMultipliedRow(next_row, current_row, regular.matrix[next_row][current_row]);
            regular.reduceByMultipliedRow(next_row, current_row, regular.matrix[next_row][current_row]);
        }
    }
    
    size_t current_row = rows_amount;
    while(current_row > 0){
        current_row--;
        size_t next_row = current_row;
        while(next_row > 0){
            next_row--;
            inverted.reduceByMultipliedRow(next_row, current_row, regular.matrix[next_row][current_row]);
            regular.reduceByMultipliedRow(next_row, current_row, regular.matrix[next_row][current_row]);
        }
    }

    return inverted;
}

int main(int argc, char* argv[]){
    std::ifstream fin;
    std::ofstream fout;

    if(argc != 4){
        std::cout << "Wrong input" << std::endl;
        return 1;
    }

    fin.open(argv[2]);
    fout.open(argv[3]);

    size_t rows_amount;
    size_t columns_amount;
    fin >> rows_amount >> columns_amount;

    double** input = new double*[rows_amount];
    for(size_t i = 0; i < rows_amount; ++i){
        input[i] = new double[columns_amount];
        for(size_t j = 0; j < columns_amount; ++j){
            fin >> input[i][j];
        }
    }

    Matrix matrix(rows_amount, columns_amount, input);

    if(strcmp(argv[1], "-det") == 0){  
        try{
            fout << matrix.getDetermenant();
        }
        catch(MatrixException e){
            fout << e.what();
        }
    }

    if(strcmp(argv[1], "-inv") == 0){  
        try{
            Matrix inverted = matrix.getInverted();
            fout << rows_amount << " " << columns_amount << "\n";
            fout << inverted;
            inverted.free();
        }
        catch(MatrixException e){
            fout << e.what();
        }
    }

    matrix.free();

    fin.close();
    fout.close();
    return 0;
}
