#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

//Основвное: достаем инфу из файла

string input_txt() {//считывание файла в строку
    ifstream file("text");//делаем поток
    string content;//делаем выходную строку
    if (file.is_open()) {//открываем файлик
        string line;//делаем переменную строчку
        while (getline(file, line)) {//пока есть непустая строка
            content += line + "\n";//дописываем в выходную строку
        }
        file.close(); // закрываем файл
    }
    return content;//и соответсвенно возвращаем не обходимую строку
}

//Даллее идут необходимые структуры и функцию, можно было бы сделать в классе одном все, но нет времени и париться сильно не хотелось

struct HNode { //Структура узла дерева: символ, частота его в тексте, и сылки надочерние ветки
        char ch;
        int hz;
        HNode* left;
        HNode* right;
        //дефолтный конструктор
        HNode(char cha, int frequ){ ch =cha; hz=frequ; left=nullptr; right=nullptr; };
};

// тут уже посложнее, делаем сами коды для каждого символа, рекурсивно пробегаясь по дереву
void buildHCodes(HNode* root, string str, map<char, string>& huffmanCodes) {
    if (!root) {//если уже дошли до самого нижнего уровня в дереве, там где мы находимся в null дочерних узлах, то стопаем рекурсию
        return;
    }

    // если же в текущем узле в его дочерних узлах ничего нет,то сохраняем для него код итоговы
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = str;
    }

    // итак спускаемся до самого конца приписывая левому листу 0, правому 1
    buildHCodes(root->left, str + "0", huffmanCodes);
    buildHCodes(root->right, str + "1", huffmanCodes);
}
//дешефратор когда двоичного
string decoder(HNode* root, string& encodestr) {
    string decodedstr = "";
    HNode* currentNode = root;
    //тут мы проносим нашу строчку по дереву вниз, добавляя в нее 1 и 0 пока не спустимся вниз и не получим конкретный символ
    for (char bit : encodestr) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        // если достигли листа, добавляем символ в раскодированную строку
        if (!currentNode->left && !currentNode->right) {
            decodedstr += currentNode->ch;
            currentNode = root;
        }
    }
    return decodedstr;
}
//свап для узлов
void swap(HNode*& a, HNode*& b){
    HNode*& n = a;
    a = b;
    b = n;
}
//пузырек для узлов
void sortnodes(vector<HNode*> nodes) {
    int n = nodes.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (nodes[j]->hz > nodes[j + 1]->hz) {
                swap(nodes[j], nodes[j + 1]);
            }
        }
    }
}


// построение дерева Хаффмана и создание кодов
void HEncode(const string& text) {
    //ну здесь мы определяем частоту каждого символа в тексте(примере есть какие-то непонятные, но на декодирование текста не влияют)
    map<char, int> hzmap;//используем map для простоты хранения типа ключ-значение
    for (char ch : text) {
        hzmap[ch]++;
    }

    // теперь строим: я использовал обычный вектор для хранения корней каждого из узлов, сортируя их пузырьком
    vector<HNode*> nodes;
    for (auto& pair : hzmap) {
        nodes.push_back(new HNode(pair.first, pair.second));
    }

    while (nodes.size() > 1) {

        // Сортируем  узлы по частоте
        sortnodes(nodes);

        // извлекаем двуа узла с наименьшей частотой
        HNode* left = nodes[0];
        HNode* right = nodes[1];
        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());

        // делаем новый узел с суммарной частотой двух дочерних
        HNode* newNode = new HNode(' ', left->hz + right->hz);
        newNode->left = left;
        newNode->right = right;

        // добавляем новый узел в вектор
        nodes.push_back(newNode);
    }

    // берем корень дерева
    HNode* root = nodes[0];
    // с помощью написанной функции HCodes определяем
    map<char, string> HCodes;
    buildHCodes(root, "", HCodes);


    //                   ВЫВОДЫ:


    // Вывод кодов Хаффмана
    cout << "Huffman Codes: "<<endl;
    for (auto& pair : HCodes) {
        cout << pair.first << ": " << pair.second <<"    hz:"<<hzmap[pair.first]<< endl;
    }
    cout<<endl;

    //Исходный текст
    cout << "Исходный текст: \n\n" << text << "\n\n";
    cout<<endl;

    //Закодированная версия
    string encodedString = "";
    for (char ch : text) {
        encodedString += HCodes[ch];
    }
    cout << "Зашифрованный текст\n\n" << encodedString << "\n\n";

    //Раскодированный исходный текст
    string decodedstr = decoder(root, encodedString);
    cout<<"Расшифрованный текст:\n\n"<<decodedstr<<"\n\n";
}


int main() {
    string str = input_txt();
    HEncode(str);
    return 0;
}
