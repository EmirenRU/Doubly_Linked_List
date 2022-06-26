
#include <iostream>
#include <cassert>

using namespace std;

class List{
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* start;
    Node* finish;
    int size;

public:

    List() : start(nullptr), finish(nullptr), size(0) {}

    void push_back(int newValue) {
        Node* newNode = new Node;
        newNode->value = newValue;
        newNode->next = nullptr;
        if (size > 0) {
            finish->next = newNode;
        } else {
            start = newNode;
        }
        finish = newNode;
        ++size;
    }

    Node* operator[](int index) {
        assert(index < this->size);

        Node* tmp = start;

        for (int i = 0; i < index; ++i) {
            tmp = tmp->next;
        }
        return tmp;
    }

    int getSize() const {
        return size;
    }

    void pop_front() {
        if (size > 0) {
            Node* old_start = start;
            start = start->next;
            delete old_start;
            --size;
        }
    }

    void Print() const {
        Node* tmp = start;
        while (tmp) {
            cout << tmp->value << ' ';
            tmp = tmp->next;
        }
        cout << endl;
    }

    void clear() {
        while(size) {
            pop_front();
        }
    }

    void deleteByIndex(int index) {
        assert(index < size);
        if (index == 0) {
            pop_front();
        }
        else if (index != size - 1) {
            Node* prev = (*this)[index - 1];
            Node* target = prev->next;
            prev->next = target->next;
            delete target;
            --size;
        }
    }

    void operator+(int newValue) {
        push_back(newValue);
    }

    void operator+(List& other) {
        finish->next = other.start;
        size += other.size;
        finish = other.finish;
        other.start = nullptr;
        other.finish = nullptr;
        other.size = 0;
    }

    int find_value(int target_value) {
        Node* tmp = start;
        for (int i = 0; i < size; ++i, tmp = tmp->next) {
            if (tmp->value == target_value) {
                return i;
            }
        }
        return -1;
    }

    ~List() {
        clear();
    }


};

int main() {

    {
        List list;

        for (int i = 0; i < 5; ++i) {
            list.push_back(i);
        }

        list.Print();
        list.deleteByIndex(3);
        list.Print();

        list + 5;
        list.Print();

        List list_2;
        for (int i = 6; i < 9; ++i) {
            list_2.push_back(i);
        }

        list_2.Print();

        list + list_2;
        list.Print();

        list.push_back(5);
        list.Print();
        cout << "try to find index of element with value 5: ";
        cout << list.find_value(5) << endl;
    }




    return 0;
}
