#ifndef SORT_BY_MULTI_FIELDS_HPP
#define SORT_BY_MULTI_FIELDS_HPP

#include <algorithm>
#include <vector>
#include <iostream>

namespace play {

struct Item
{
    int seq;
    int tm;
};

namespace test {
    
    void sort_by_multi_fields() {
        std::vector<Item> items {{0, 262},{0, 3},{1, 36},{0, 572},{2, 634},{0, 2673},{0, 352},{3, 235},{0, 1},{0, 1},{0, 2351},{4, 63},{0, 1}};

        std::sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
            if (a.seq == 0 && b.seq == 0) {
                return a.tm >= b.tm;
            } else if (a.seq != 0 && b.seq != 0) {
                return a.seq < b.seq;
            } else if (a.seq != 0) {
                return true;
            } else if (b.seq != 0) {
                return false;
            }
            return false;
        });

        std::for_each(items.begin(), items.end(), [](const Item &a){
            std::cout << a.seq << ", " << a.tm << std::endl;
        });
    }

}
}

#endif
