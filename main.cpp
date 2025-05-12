#include <iostream>
#include <fstream>
using namespace std;

 
class Word {
public:
    Word() {
        str = nullptr;
        length = 0;
    }

    ~Word() {
        delete[] str;
    }

    Word(const Word& other) {
        copyFrom(other);
    }

    Word& operator=(const Word& other) {
        if (this != &other)
            copyFrom(other);
        return *this;
    }

    Word& operator+=(char c) {
        // Добавление символа к слову
        char* newStr = new char[length + 2];
        for (int i = 0; i < length; i++) {
            newStr[i] = str[i];
        }
        newStr[length] = c;
        newStr[length + 1] = '\0';

        delete[] str;
        str = newStr;
        length++;
        return *this;
    }

    void clear();
    int len();
    void toLowerAll();
    bool isValid();
    unsigned char getFirst();
    void print();
private:
    char* str;
    int length;
    void copyFrom(const Word& other);
    unsigned char toLower(unsigned char ch);
};

class Dict {
public:
    Dict() {
        for (int i = 0; i < MAX; i++) {
            letters[i] = '\0';
            counters[i] = 0;
        }
        size = 0;
    }

    void add(unsigned char letter);
    void sort();
    void print();
private:
    static const int MAX = 50;
    unsigned char letters[MAX];
    int counters[MAX];
    int size;

    int find(unsigned char letter);
    void swap(int i, int j);
};

void work(Word& wordBuffer, ifstream& file, Dict& dict);
void Checkfile(const ifstream& file);
void fileIsEmpty(ifstream& file);
void ToWord(Word& currentWord, Word& readyWord, char ch);

int main() {
    setlocale(LC_ALL, "Russian");
    Word buffer;
    Dict dict;
    ifstream file("data.txt", ios::binary);
    Checkfile(file);
    fileIsEmpty(file);
    work(buffer, file, dict);
    dict.sort();          
    dict.print();         
    file.close();
    return 0;
}


void Checkfile(const ifstream& file) {
    if (!file) {
        cout << "Файл не найден!" << endl;
        exit(1);
    }
}

void fileIsEmpty(ifstream& file) {
    if (file.peek() == ifstream::traits_type::eof()) {
        cout << "Файл пустой!" << endl;
        exit(1);
    }
}

void ToWord(Word& currentWord, Word& readyWord, char ch) {
    // Разделение текста на слова
    if (ch == ' ' || ch == '\n' || ch == '.' || ch == ',' || ch == ';' ||
        ch == ':' || ch == '-' || ch == '?' || ch == '!') {
        if (currentWord.len() > 0) {
            readyWord = currentWord;
            currentWord.clear();
        }
    }
    else {
        currentWord += ch;
    }
}

void work(Word& wordBuffer, ifstream& file, Dict& dict) {
    Word readyWord;
    char ch;
    while (file.get(ch)) {
        ToWord(wordBuffer, readyWord, ch);
        if (readyWord.len() > 0) {
            readyWord.toLowerAll();
            if (readyWord.isValid()) {
                //readyWord.print();
                dict.add(readyWord.getFirst());
            }
            readyWord.clear();
        }
    }
    if (wordBuffer.len() > 0) {
        wordBuffer.toLowerAll();
        if (wordBuffer.isValid()) {
            wordBuffer.print();
            dict.add(wordBuffer.getFirst());
        }
    }
}

void Word::print() {
    cout << str << endl;
}

unsigned char Word::getFirst() {
    if (length == 0)
        return '\0';
    return str[0];
}

bool Word::isValid() {
    if (length <= 1)
        return false;
    unsigned char first = str[0];
    unsigned char last = str[length - 1];
    return first == last;
}

void Word::toLowerAll() {
    for (int i = 0; i < length; i++) {
        str[i] = toLower(str[i]);
    }
}

int Word::len() {
    return length;
}

void Word::clear() {
    delete[] str;
    str = nullptr;
    length = 0;
}

unsigned char Word::toLower(unsigned char ch) {
    if (ch >= 192 && ch <= 223)
        return ch + 32;
    if (ch == 168) // 'Ё'
        return 184;
    return ch;
}

void Word::copyFrom(const Word& other) {
    length = other.length;
    delete[] str;
    str = new char[length + 1];
    for (int i = 0; i < length; i++) {
        str[i] = other.str[i];
    }
    str[length] = '\0';
}


void Dict::add(unsigned char letter) {

    int index = find(letter);
    if (index != -1) {
        counters[index]++;
    }
    else {
        letters[size] = letter;
        counters[size] = 1;
        size++;
    }
}

void Dict::sort() {

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (counters[j] < counters[j + 1] ||
                (counters[j] == counters[j + 1] && letters[j] > letters[j + 1])) {
                swap(j, j + 1);
            }
        }
    }
}

void Dict::print() {
    if (size > 0) {
        cout << "\nРезультат по буквам:\n";
        for (int i = 0; i < size; i++) {
            cout << "[" << letters[i] << "] : " << counters[i] << endl;
        }
    }
    else {
        cout << "Подходящие слова отсутствуют" << endl;
    }
}

int Dict::find(unsigned char letter) {

    for (int i = 0; i < size; i++) {
        if (letters[i] == letter)
            return i;
    }
    return -1;
}

void Dict::swap(int i, int j) {

    unsigned char tmpLetter = letters[i];
    letters[i] = letters[j];
    letters[j] = tmpLetter;

    int tmpCounter = counters[i];
    counters[i] = counters[j];
    counters[j] = tmpCounter;
}
