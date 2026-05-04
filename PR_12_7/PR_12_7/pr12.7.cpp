#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Node {
    string word;
    Node* next;
};

Node* createNode(string value) {
    Node* newNode = new Node;
    newNode->word = value;
    newNode->next = nullptr;
    return newNode;
}

void addToList(Node*& head, Node*& tail, string value) {
    Node* newNode = createNode(value);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список порожній." << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << "[" << current->word << "]";
        if (current->next != nullptr) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

void clearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

vector<string> extractWords(string str) {
    vector<string> words;
    stringstream ss(str);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

bool canConnect(string first, string second) {
    if (first.empty() || second.empty()) return false;
    return tolower(first.back()) == tolower(second.front());
}

bool findChain(vector<string>& words, vector<bool>& used, vector<string>& result) {
    if (result.size() == words.size()) return true;

    for (int i = 0; i < words.size(); i++) {
        if (!used[i]) {
            if (result.empty() || canConnect(result.back(), words[i])) {
                used[i] = true;
                result.push_back(words[i]);
                if (findChain(words, used, result)) return true;
                result.pop_back();
                used[i] = false;
            }
        }
    }
    return false;
}

void buildListFromVector(Node*& head, Node*& tail, const vector<string>& words) {
    for (const string& w : words) {
        addToList(head, tail, w);
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    string input;
    cout << "Введіть рядок тексту: ";
    getline(cin, input);

    vector<string> words = extractWords(input);
    if (words.empty()) {
        cout << "Слів не знайдено." << endl;
        return 0;
    }

    Node* head = nullptr;
    Node* tail = nullptr;
    vector<string> chainResult;
    vector<bool> used(words.size(), false);

    if (findChain(words, used, chainResult)) {
        cout << "\nЗнайдено ланцюжок (останні літери відповідають першим):" << endl;
        buildListFromVector(head, tail, chainResult);
    }
    else {
        cout << "\nЛанцюжок побудувати неможливо. Сортування за алфавітом:" << endl;
        sort(words.begin(), words.end());
        buildListFromVector(head, tail, words);
    }

    printList(head);
    clearList(head);

    return 0;
}