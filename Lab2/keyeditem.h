#ifndef KEYEDITEM_H
#define KEYEDITEM_H

#include <iostream>

typedef std::string KeyType;

class KeyedItem {
private:
        KeyType searchKey;

public:
        KeyedItem() { }
        KeyedItem(const KeyType& keyValue) : searchKey(keyValue) { }

        KeyType getKey() const {
            return searchKey;
        }

        bool operator==(const KeyedItem& other) {
            return !searchKey.compare(other.getKey());
        }
};


#endif // KEYEDITEM_H
