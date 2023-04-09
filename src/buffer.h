#include <set>
#include <vector>

#include "types.h"

using namespace std;

class Buffer {
public:
    int max_size;
    // set存储对应的条目
    set<entry_t> entries;
    Buffer(int max_size) : max_size(max_size) {};
    VAL_t * get(KEY_t) const;
    vector<entry_t> * range(KEY_t, KEY_t) const;
    bool put(KEY_t, VAL_t val);
    void empty(void);
};
