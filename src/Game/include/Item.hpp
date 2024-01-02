#pragma once

/* Special Items:
 *  - MONEY -> id=1
 */

struct Item {
public:
    static const Item INVALID; // 0
    static const Item MONEY;  // 1
    static const Item POTION;  // 2
    int id;
    inline bool operator<(const Item& right)const {return id < right.id;}
    inline bool operator==(const Item& right)const {return id == right.id;}
};