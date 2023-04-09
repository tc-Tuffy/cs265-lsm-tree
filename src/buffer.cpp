#include <iostream>

#include "buffer.h"

using namespace std;
// 用迭代器找到对应的key，返回对应val的指针。
VAL_t * Buffer::get(KEY_t key) const {
    entry_t search_entry;
    set<entry_t>::iterator entry;
    VAL_t *val;

    search_entry.key = key;
    entry = entries.find(search_entry);

    if (entry == entries.end()) {
        return nullptr;
    } else {
        val = new VAL_t;
        *val = entry->val;
        return val;
    }
}

vector<entry_t> * Buffer::range(KEY_t start, KEY_t end) const {
    entry_t search_entry;
    set<entry_t>::iterator subrange_start, subrange_end;
    // 利用迭代器的二分查找函数，获取上界和下界。
    search_entry.key = start;
    subrange_start = entries.lower_bound(search_entry);

    search_entry.key = end;
    subrange_end = entries.upper_bound(search_entry);
    // 用迭代器构造vector对象返回
    return new vector<entry_t>(subrange_start, subrange_end);
}

bool Buffer::put(KEY_t key, VAL_t val) {
    entry_t entry;
    set<entry_t>::iterator it;
    bool found;

    if (entries.size() == max_size) {
        return false;
    } else {
        entry.key = key;
        entry.val = val;
        // std::tie函数用于解包pair对象，set不能插入相同key的元素，失败返回false和对应相同key的迭代器。
        tie(it, found) = entries.insert(entry);

        // Update the entry if it already exists
        if (found == false) {
            entries.erase(it);
            entries.insert(entry);
        }

        return true;
    }
}

void Buffer::empty(void) {
    entries.clear();
}
