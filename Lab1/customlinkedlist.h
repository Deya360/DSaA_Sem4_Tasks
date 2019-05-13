#ifndef CUSTOMLINKEDLIST_H
#define CUSTOMLINKEDLIST_H

#endif // CUSTOMLINKEDLIST_H

#include <iterator>
template <class T>
class CustomLinkedList
{
    struct Node
    {
        Node(const T& x,Node* y = 0):m_data(x),m_next(y){}
        T m_data;
        Node* m_next;
    };

    Node* m_head;
public:

    class iterator
        : public std::iterator<std::forward_iterator_tag, T>
    {
        Node* m_rep;
    public:
        friend class const_iterator;
        friend class CustomLinkedList;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;


        inline iterator(Node* x=0):m_rep(x){}
        inline iterator(const iterator& x):m_rep(x.m_rep) {}
        inline iterator& operator=(const iterator& x)
        {
            m_rep=x.m_rep; return *this;
        }
        inline iterator& operator++()
        {
            m_rep = m_rep->m_next; return *this;
        }
        inline iterator operator++(int)
        {
            iterator tmp(*this); m_rep = m_rep->m_next; return tmp;
        }
        inline reference operator*() const { return m_rep->m_data; }
        inline pointer operator->() const { return m_rep; }
        inline bool operator==(const iterator& x) const
        {
            return m_rep == x.m_rep;
        }
        inline bool operator!=(const iterator& x) const
        {
            return m_rep != x.m_rep;
        }

    };

    class const_iterator
        : public std::iterator<std::forward_iterator_tag, const T>
    {
        const Node* m_rep;
    public:
        friend class iterator;
        friend class CustomLinkedList;
        typedef T value_type;
        typedef const T& reference;
        typedef const T* pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;


        inline const_iterator(const Node* x=0):m_rep(x){}
        inline const_iterator(const const_iterator& x):m_rep(x.m_rep) {}
        inline const_iterator(const iterator& x):m_rep(x.m_rep){}
        inline const_iterator& operator=(const const_iterator& x)
        {
            m_rep=x.m_rep; return *this;
        }
        inline const_iterator& operator=(const iterator& x)
        {
            m_rep=x.m_rep; return *this;
        }
        inline const_iterator& operator++()
        {
            m_rep = m_rep->m_next; return *this;
        }
        inline const_iterator operator++(int)
        {
            const_iterator tmp(*this); m_rep = m_rep->m_next; return tmp;
        }
        inline reference operator*() const { return m_rep->m_data; }
        inline pointer operator->() const { return m_rep; }
        inline bool operator==(const const_iterator& x) const
        {
            return m_rep == x.m_rep;
        }
        inline bool operator!=(const const_iterator& x) const
        {
            return m_rep != x.m_rep;
        }



    };


    CustomLinkedList() : m_head(0) {}

    CustomLinkedList(const CustomLinkedList& L) : m_head(0)
    {
        for ( const_iterator i = L.begin(); i!=L.end(); ++i )
            push_front(*i);
        reverse();
    }

    void reverse()
    {
        Node* p = 0; Node* i = m_head; Node* n;
        while (i)
        {
            n = i->m_next;
            i->m_next = p;
            p = i; i = n;
        }
        m_head = p;
    }

    void swap(CustomLinkedList& x)
    {
        Node* tmp = m_head; m_head = x.m_head; x.m_head = tmp;
    }

    CustomLinkedList& operator=(const CustomLinkedList& x)
    {
        CustomLinkedList tmp(x);
        swap(tmp);
        return *this;
    }

    T at(const int pos) {
        Node *current = m_head;

        int index = 0;
        while (index < pos && current){
            current = current->m_next;
            index++;
        }

        if(current) return current->m_data;
    }

    bool contains(const T& other) const {
         Node *current = m_head;

         while (current && !(current->m_data == other)){
             current = current->m_next;
         }

         if(current) return true;
         return false;
    }

    ~CustomLinkedList() { clear(); }
    void clear() {
//        while (!empty())
//            pop_front();
        Node *current = m_head;
        while(m_head) {
            current = m_head;
            m_head = m_head->m_next;
            delete current;
        }
        m_head = nullptr;
    }

    int size() {
        int count =0;
        for ( const_iterator i = begin(); i!= end(); ++i ) count++;
        return count;
    }


    inline void push_front(const T&x)
    {
        Node* tmp = new Node(x);
        tmp->m_next = m_head;
        m_head = tmp;
    }

    inline void push_back(const T&x)
    {
        Node *current = m_head;
        if (current) {
            while (current){
                current = current->m_next;
            }

            Node* tmp = new Node(x);
            current->m_next = tmp;

        } else current=m_head;
    }

    inline void pop_front()
    {
        if (m_head)
        {
            Node* newhead = m_head->m_next;
            delete m_head;
            m_head = newhead;
        }
    }
    inline bool empty() { return m_head; }

    inline T& front() { return *begin(); }
    inline const T& front() const { return *begin(); }

    inline iterator begin() { return iterator(m_head); }
    inline iterator end() { return iterator(); }
    inline const_iterator begin() const { return m_head; }
    inline const_iterator end() const { return const_iterator(); }

};

