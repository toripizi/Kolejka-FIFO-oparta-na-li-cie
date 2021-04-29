#include <iostream>
#include <string>

using namespace std;

class Node {
    int value = NULL;
    Node* next = nullptr;
    Node* prev = nullptr;
public:
    Node(int startValue) : value(startValue) {}
    Node(int startValue, Node* startNext, Node* startPrev) : value(startValue), next(startNext), prev(startPrev) {}

    void setValue(int newValue) {
        value = newValue;
    }
    void setNext(Node* newNext) {
        next = newNext;
    }
    void setPrev(Node* newPrev) {
        prev = newPrev;
    }
    const int getValue() {
        return value;
    }
    Node* getNext() {
        return next;
    }
    Node* getPrev() {
        return prev;
    }
};

//lista dwukierunkowa
class List {
public:
    Node* first = nullptr;
    Node* last = nullptr;
    
    int size() {
        if (first == nullptr) return 0;
        else {
            int liczba = 1;
            Node* temporary = first;
            while (temporary != last) {
                temporary = temporary->getNext();
                liczba++;
            }
            return liczba;
        }
    }
    void ADD_BEG(int newValue) {
        if (!size()) {
            Node* newNode = new Node(newValue);
            newNode->setNext(newNode);
            newNode->setPrev(newNode);
            first = newNode;
            last = newNode;
        }
        else if (size() == 1) {
            Node* newNode = new Node(newValue, first, last);
            last->setNext(newNode);
            last->setPrev(newNode);
            first = newNode;
        }
        else {
            Node* newNode = new Node(newValue, first, last);
            last->setNext(newNode);
            first->setPrev(newNode);
            first = newNode;
        }
    }
    void ADD_END(int newValue) {
        if (!size()) {
            ADD_BEG(newValue);
        }
        else if (size() == 1) {
            Node* newNode = new Node(newValue, first, last);
            first->setNext(newNode);
            first->setPrev(newNode);
            last = newNode;
        }
        else {
            Node* newNode = new Node(newValue, first, last);
            last->setNext(newNode);
            first->setPrev(newNode);
            last = newNode;
        }
    }
    
    //dodaje nowy węzęł z daną wartością przed podany węzęł.
    void ADD_ACT(int newValue, Node* actual) {
        if (!size()) {
            Node* newNode = new Node(newValue);
            newNode->setNext(newNode);
            newNode->setPrev(newNode);
            first = newNode;
            last = newNode;
        }
        else if (size() == 1) {
            Node* newNode = new Node(newValue, first, last);
            last->setNext(newNode);
            last->setPrev(newNode);
            first = newNode;
        }
        else {
            Node* newNode = new Node(newValue, actual, actual->getPrev());
            actual->getPrev()->setNext(newNode);
            actual->setPrev(newNode);
            if (actual == first) first = newNode;
        }
    }

    void PRINT_FORWARD() {
        if (!size()) cout << "NULL" << endl;
        else {
            Node* temporary = first;
            cout << temporary->getValue() << " ";
            while (temporary != last) {
                temporary = temporary->getNext();
                cout << temporary->getValue() << " ";
            }
            cout << endl;
        }
    }
    void PRINT_BACKWARD() {
        if (!size()) cout << "NULL" << endl;
        else {
            Node* temporary = last;
            cout << temporary->getValue() << " ";
            while (temporary != first) {
                temporary = temporary->getPrev();
                cout << temporary->getValue() << " ";
            }
            cout << endl;
        }
    }
    void DEL_BEG() {
        if (first == last) {
            delete first;
            first = nullptr;
            last = nullptr;
        }
        else if (first != nullptr) {
            Node* prev = first->getPrev();
            Node* next = first->getNext();
            delete first;
            next->setPrev(prev);
            prev->setNext(next);
            first = next;
        }
    }
    void DEL_END() {
        if (first == last) {
            delete first;
            first = nullptr;
            last = nullptr;
        }
        else if (first != nullptr) {
            Node* prev = last->getPrev();
            Node* next = last->getNext();
            delete last;
            next->setPrev(prev);
            prev->setNext(next);
            last = prev;
        }
    }
};

class Kolejka {
public:
    Node* front = nullptr;
    Node* end = nullptr;
    
    int count() {
        if (!front) return 0;
        else {
            int count = 1;
            Node* temp = front;
            while (temp != end) {
                temp = temp->getPrev();
                count++;
            }
            return count;
        }
    }
   
    void PUSH(List &lista, int value) {
        //rozmiar listy == rozmiar kolejki, więc dodaje element na lewo od END
        if (lista.size() == count()) {
            lista.ADD_ACT(value, end);
            if (!count()) {
                end = lista.last;
                front = lista.first;
            }
            else {
                end = end->getPrev();
            }
        }
        else {
            if (!count()) {
                end = lista.last;
                front = lista.last;
                end->setValue(value);
            }
            else {
                end = end->getPrev();
                end->setValue(value);
            }
        }
    }
    
    //usuwa pierwszy element z kolejki
    void POP() {
        if (!count()) {
            cout << "NULL" << endl;
        }
        else if (count() == 1) {
            cout << front->getValue() << endl;
            end = nullptr;
            front = nullptr;
        }
        else {
            cout << front->getValue() << endl;
            front = front->getPrev();
        }
    }

    //ustawiwa zera elementom poza kolejką
    void GARBAGE_SOFT(List& lista) {
        if (!count()) {
            Node* temp = lista.first;
            temp->setValue(0);
            while (temp != lista.last) {
                temp = temp->getNext();
                temp->setValue(0);
            }
        }
        else {
            Node* temp = front->getNext();
            while (temp != end) {
                temp->setValue(0);
                temp = temp->getNext();
            }
        }
    }
    
    //usuwa elementy poza kolejką
    void GARBAGE_HARD(List& lista) {
        if (!count()) {
            Node* temp = lista.first;
            Node* next = temp->getNext();
            while (temp != lista.last) {
                delete temp;
                temp = next;
                next = temp->getNext();
            }
            delete temp;
            temp = next;
            lista.first = nullptr;
            lista.last = nullptr;
        }
        else {
            Node* temp = front->getNext();
            Node* next = temp->getNext();
            while (temp != end) {
                if (temp == lista.last || temp == lista.first) {
                    lista.first = end;
                    lista.last = front;
                }
                delete temp;
                temp = next;
                next = temp->getNext();
            }
            front->setNext(end);
            end->setPrev(front);
        }
    }
    
    void PRINT_QUEUE() {
        if (!count()) cout << "NULL" << endl;
        else {
            Node* temp = front;
            cout << temp->getValue() << " ";
            while (temp != end) {
                temp = temp->getPrev();
                cout << temp->getValue() << " ";
            }
            cout << endl;
        }
    }

    //sprawdza, czy nie został usunięty element,
    //który jest początkiem lub końcem kolejki.
    //Jeśli został, to przesuwa wskaźnik odpowiedni 
    void DEL_BEG(List& lista) {
        if (lista.size() == 1) {
            front = nullptr;
            end = nullptr;
        }
        else if (lista.first == front) {
            if (count() == 1) {
                front = nullptr;
                end = nullptr;
            }
            else {
                front = front->getPrev();
            }
        }
        else if (lista.first == end) {
            if (count() == 1) {
                front = nullptr;
                end = nullptr;
            }
            else {
                end = end->getNext();
            }
        }
        lista.DEL_BEG();
    }
    void DEL_END(List& lista) {
        if (lista.size() == 1) {
            front = nullptr;
            end = nullptr;
        }
        else if (lista.last == front) {
            if (count() == 1) {
                front = nullptr;
                end = nullptr;
            }
            else {
                front = front->getPrev();
            }
        }
        else if (lista.last == end) {
            if (count() == 1) {
                front = nullptr;
                end = nullptr;
            }
            else {
                end = end->getNext();
            }
        }
        lista.DEL_END();
    }
};

int main()
{
    List lista;
    Kolejka kolejka;

    string commend;
    int value = NULL;

    while (!cin.eof())
    {
        commend = "";
        cin >> commend;
        if (commend == "ADD_BEG") {
            cin >> value;
            lista.ADD_BEG(value);
        }
        else if (commend == "ADD_END") {
            cin >> value;
            lista.ADD_END(value);
        }
        else if (commend == "PRINT_FORWARD") {
            lista.PRINT_FORWARD();
        }
        else if (commend == "PRINT_BACKWARD") {
            lista.PRINT_BACKWARD();
        }
        else if (commend == "DEL_BEG") {
            kolejka.DEL_BEG(lista);
        }
        else if (commend == "DEL_END") {
            kolejka.DEL_END(lista);
        }
        else if (commend == "SIZE") {
            cout << lista.size() << endl;
        }
        //kolejka
        else if (commend == "PUSH") {
            cin >> value;
            kolejka.PUSH(lista, value);
        }
        else if (commend == "COUNT") {
            cout << kolejka.count() << endl;
        }
        else if (commend == "POP") {
            kolejka.POP();
        }
        else if (commend == "PRINT_QUEUE") {
            kolejka.PRINT_QUEUE();
        }
        else if (commend == "GARBAGE_SOFT") {
            kolejka.GARBAGE_SOFT(lista);
        }
        else if (commend == "GARBAGE_HARD") {
            kolejka.GARBAGE_HARD(lista);
        }
    }
    return 0;
}