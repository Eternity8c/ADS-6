// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
    struct ITEM {
        T data;
        ITEM* next;
        explicit ITEM(const T& value) : data(value), next(nullptr) {}
    };

    ITEM* head;

 public:
    TPQueue() : head(nullptr) {}
    void push(const T& value) {
        ITEM* newItem = new ITEM(value);
        if (head == nullptr || value.prior > head->data.prior) {
            newItem->next = head;
            head = newItem;
            return;
        }
        ITEM* current = head;
        while (current->next != nullptr &&
            current->next->data.prior >= value.prior) {
            current = current->next;
        }
        newItem->next = current->next;
        current->next = newItem;
    }

    T pop() {
        if (head == nullptr) {
            throw std::runtime_error("Queue is empty");
        }
        ITEM* temp = head;
        T result = temp->data;
        head = head->next;
        delete temp;
        return result;
    }

    ~TPQueue() {
        while (head != nullptr) {
            ITEM* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
