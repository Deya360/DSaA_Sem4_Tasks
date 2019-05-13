#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H

#include<iostream>

using namespace std;


template <typename T>
class Node {

public:
    T Data;
    Node<T>* Next;

    Node() {Next = NULL;}
    Node(T data) {Data = data; Next = NULL;}
};

template<typename T>
class CustomList {

private:
    Node<T>* m_head = NULL;
    Node<T>* m_current = NULL;

    void DeleteTail() {

        Node<T>* current = m_head;
        Node<T>* previous = current;

        if(current == NULL)
        {
            return;
        }

        if(current->Next == NULL)
        {

            //cout << "Deleting: " << current->Data << endl;
            delete current;
            current = NULL;
            m_head = NULL;
            return;
        }

        while(current->Next != NULL)
        {
            previous = current;
            current = current->Next;
        }

        if(previous != NULL)
        {
//            cout << "Deleting: " << current->Data << endl;
            delete current;
            previous->Next = NULL;
        }

        DeleteTail();

    }
public:
    CustomList() {}
    ~CustomList() {
        DeleteTail();
    }
    CustomList(const CustomList &c2) {m_head = c2.m_head; m_current = c2.m_current;}

    void push_back(T data)
    {
        if(m_head == NULL)
        {
            m_head = new Node<T>(data);
        }
        else
        {
            Node<T>* current = m_head;
            while(current->Next != NULL)
            {
                current = current->Next;
            }
            current->Next = new Node<T>(data);
        }
    }
    T Head()
    {
        int data = -1;
        if(m_head != NULL)
            data = m_head->Data;

        return data;
    }
    T at(int index)
    {
        int currentIndex = 0;
        Node<T> *current = m_head;
        T data;

        while(currentIndex != index && current != NULL)
        {
            current = current->Next;
            currentIndex++;
        }

        if(current != NULL && currentIndex == index)
        {
            data = current->Data;
        }

        if(current == NULL )
        {
            throw -777;
        }

        return data;
    }

    void clear()
    {
        Node<T>* curr = m_head;
        while(m_head) {
            curr = m_head;
            m_head = m_head->Next;
            delete curr;
        }
        m_head = m_current = nullptr;
    }
    int size() {
        int count = 0;
        while(HasNext()) {
            Next();
            count++;
        }
        return count;
    }
    bool contains(T query) {
        while(HasNext()) {
            if(Next() == query) return true;
        }
        return false;
    }

    T First()
    {
        m_current = m_head;
        return m_head->Data;
    }
    T Next()
    {
        T data;
        if(m_current != NULL){
            m_current = m_current->Next;
            return m_current->Data;
        }

        if(m_current != NULL){
            return m_current->Data;
        }

        return data;
    }
    bool HasNext()
    {
        return (m_current != NULL && m_current->Next != NULL);
    }
};

#endif // CUSTOMLIST_H
