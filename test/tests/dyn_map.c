#define CU_IMPL
#define DS_IMPL
#include <cutils.h>
#include <ds.h>

int main() {
    HashMap(u32, u32) map = {GlobalAllocator};

    for (u32 i = 1; i <= 28; i++) { HashIns(map, i, i); }

    debuglog("map:");
    for (u32 i = 0; i < map.cap; i++) {
        if (map.keys[i].m == -1)
            debuglog("\tempty");
        else
            debuglog("\t(%d %d) %d", map.keys[i].k, map.keys[i].m, map.vals[i]);
    }

    Free(map.a, map.keys, map.cap * sizeof(map.keys[0]));
    Free(map.a, map.vals, map.cap * sizeof(map.vals[0]));
}
