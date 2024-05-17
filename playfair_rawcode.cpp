#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isChet = false;
bool isEnd = false;
bool flag = false;
bool flagX = false;
bool flagAdd = false;

string getKeyword() {
    string key;
    cout << "Enter keyword: ";
    getline(cin, key);
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
    replace(key.begin(), key.end(), 'J', 'I');
    return key;
}

string getString() {
    string str;
    cout << "Enter string: ";
    getline(cin, str);
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    replace(str.begin(), str.end(), 'J', 'I');
    return str;
}

vector<vector<char>> processKey() {
    string key = getKeyword();
    vector<vector<char>> result;
    string temp = "";
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    for (char i : key) {
        auto it = find(alphabet.begin(), alphabet.end(), i);
        if (it != alphabet.end()) {
            alphabet.erase(it);
            temp += i;
        }
    }
    temp += alphabet;
    while (!temp.empty()) {
        result.push_back(vector<char>(temp.begin(), temp.begin() + 5));
        temp.erase(0, 5);
    }
    return result;
}

string cipher() {
    vector<vector<char>> keyresult = processKey();
    string res;
    string error = "Warning!!! String is empty";
    string str = getString();
    if (str.empty()) {
        cout << error << endl;
    }
    string textPhrase, separator;
    if (str.length() == 0) {
        
    } else {
        textPhrase = str[0];
    }
    int help = 0;
    flagAdd = false;
    for (size_t i = 1; i < str.length(); i++) {
        if (str[i - 1] == str[i]) {
            if (str[i] == 'X') {
                separator = 'Q';
            } else {
                separator = 'X';
            }
            textPhrase += separator + str[i];
            help = 1;
        } else {
            textPhrase += str[i];
        }
        if (help == 1) {
            flagAdd = true;
        }
    }

    if (textPhrase.length() % 2 != 0) {
        if (textPhrase[textPhrase.length() - 1] == 'X') {
            textPhrase += 'Q';
            isEnd = true;
            flagX = false;
        } else {
            textPhrase += 'X';
            isEnd = true;
            flagX = true;
        }
    }

    string enCodeStr;
    for (size_t i = 0; i < textPhrase.length(); i += 2) {
        char pair1 = textPhrase[i];
        char pair2 = textPhrase[i + 1];
        int p1i, p1j, p2i, p2j;
        for (size_t stroka = 0; stroka < keyresult.size(); stroka++) {
            for (size_t stolbec = 0; stolbec < keyresult[stroka].size(); stolbec++) {
                if (keyresult[stroka][stolbec] == pair1) {
                    p1i = stroka;
                    p1j = stolbec;
                }
                if (keyresult[stroka][stolbec] == pair2) {
                    p2i = stroka;
                    p2j = stolbec;
                }
            }
        }
        char coord1, coord2;

        if (p1i == p2i) {
            coord1 = (p1j == 4) ? keyresult[p1i][0] : keyresult[p1i][p1j + 1];
            coord2 = (p2j == 4) ? keyresult[p2i][0] : keyresult[p2i][p2j + 1];
        }
        if (p1j == p2j) {
            coord1 = (p1i == 4) ? keyresult[0][p1j] : keyresult[p1i + 1][p1j];
            coord2 = (p2i == 4) ? keyresult[0][p2j] : keyresult[p2i + 1][p2j];
        }
        if (p1i != p2i && p1j != p2j) {
            coord1 = keyresult[p1i][p2j];
            coord2 = keyresult[p2i][p1j];
        }
        enCodeStr = enCodeStr + coord1 + coord2;
    }
    cout << enCodeStr << endl;
    return enCodeStr;
}

void deCodeCipher() {
    string deCodeStr = "";
    string text;
    string error = "Warning!!! String is empty";
    string text1 = cipher();
    if (text1 == "") {
        cout << error << endl;
    }
    vector<vector<char>> keyresult = processKey();
    for (size_t i = 0; i < text1.length(); i += 2) {
        char pair1 = text1[i];
        char pair2 = text1[i + 1];
        int p1i, p1j, p2i, p2j;
        for (size_t stroka = 0; stroka < keyresult.size(); stroka++) {
            for (size_t stolbec = 0; stolbec < keyresult[stroka].size(); stolbec++) {
                if (keyresult[stroka][stolbec] == pair1) {
                    p1i = stroka;
                    p1j = stolbec;
                }
                if (keyresult[stroka][stolbec] == pair2) {
                    p2i = stroka;
                    p2j = stolbec;
                }
            }
        }
        char coord1, coord2;

        if (p1i == p2i) {
            coord1 = (p1j == 0) ? keyresult[p1i][4] : keyresult[p1i][p1j - 1];
            coord2 = (p2j == 0) ? keyresult[p2i][4] : keyresult[p2i][p2j - 1];
        }
        if (p1j == p2j) {
            coord1 = (p1i == 0) ? keyresult[4][p1j] : keyresult[p1i - 1][p1j];
            coord2 = (p2i == 0) ? keyresult[4][p2j] : keyresult[p2i - 1][p2j];
        }
        if (p1i != p2i && p1j != p2j) {
            coord1 = keyresult[p1i][p2j];
            coord2 = keyresult[p2i][p1j];
        }
        text = text + coord1 + coord2;
    }
    text = text.substr(0, text.find_last_of('X'));
    cout << text << endl;
}

int main() {
    cipher();
    deCodeCipher();
    return 0;
}
