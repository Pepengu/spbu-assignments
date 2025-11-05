#include <fstream>
#include <iostream>
#include <climits>

void countSort(unsigned char **arr, const int n, int m){
	unsigned char **output = new unsigned char*[n+1];
	int count[CHAR_MAX]{0};

	for(int i = 0; i < n; ++i){
		++count[static_cast<int>(arr[i][m])];
	}

	int cnt = 0;
	for(int i = 0; i < CHAR_MAX; ++i){
		int tmp = count[i];
		count[i] = cnt;
		cnt += tmp;
	}

	for(int i = 0; i < n; ++i){
		output[count[static_cast<int>(arr[i][m])]] = arr[i];
		++count[static_cast<int>(arr[i][m])];
	}

	for(int i = 0; i < n; ++i){
		arr[i] = output[i];
	}

	delete[] output;
}

void lsdSort(unsigned char **arr, int n, int m, int k){
	for(int i = m-1; i >= m-k; --i){
		countSort(arr, n, i);
	}
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

	int n;
	int m;
	int k;
	fin >> n >> m >> k;
	unsigned char **arr = new unsigned char*[n+1];
	for(int i = 0; i < n; ++i){
		arr[i] = new unsigned char[m+1];
	}

	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			fin >> arr[j][i];
		}
	}

	lsdSort(arr, n, m, k);
	for(int i = 0; i < n; ++i){
		fout << arr[i][0];
	}

	for (int i = 0; i < n; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
