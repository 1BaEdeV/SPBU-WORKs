#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string input_txt() {
    ifstream file("text");
    string fileContent;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            fileContent += line + "\n";
        }
        file.close(); // Закрываем файл
    }
    return fileContent;
}

void quicksort_hz(vector<char>& sym, vector<int>& num, int left, int right) {
    if (left < right) {
        int pivot = num[(left + right) / 2]; // Выбираем опорный элемент
        int i = left;
        int j = right;

        // Разделяем массив на две части
        while (i <= j) {
            while (num[i] < pivot) i++;
            while (num[j] > pivot) j--;
            if (i <= j) {
                swap(num[i], num[j]);
                swap(sym[i], sym[j]);
                i++;
                j--;
            }
        }

        // Рекурсивно вызываем quickSort для двух половин
        if (left < j) quicksort_hz(sym, num, left, j);
        if (i < right) quicksort_hz(sym, num ,i, right);
    }
}
void hz(vector<char> & symbols, vector<int> & numbers, string & str, int & k){
    symbols.push_back(str[0]);
    numbers.push_back(1);
    for(int i=1;i<k;i++){
        int a = 0;
        for(int j=0;j<symbols.size();j++){
            if (str[i]==symbols[j]){
                numbers[j]++;
                a++;
            }}

        if(a==0){
            symbols.push_back(str[i]);
            numbers.push_back(1);
        };
    }
}

int main() {
    vector<int> numbers;
    vector<char> symbols;
    string str = input_txt();
    int k = str.size();
    hz(symbols,numbers,str,k);
    int l = symbols.size();
    quicksort_hz(symbols, numbers, 0,l-1);
    for(int i=0;i<symbols.size();i++){
        cout<<symbols[i]<<"    "<<numbers[i]<<endl;
    }
}