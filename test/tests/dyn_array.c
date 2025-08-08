#define CU_IMPL
#define DS_IMPL
#include <cutils.h>
#include <ds.h>

int main() {

    dynArray(u32) ints = {GlobalAllocator};

    for (u32 i = 0; i < 10; i++) { dynPush(ints, i); }
    for (u32 i = 0; i < 10; i++) { assert(ints.data[i] == i); }

    assert(dynBack(ints) == 9);

    dynReserve(ints, 20);
    assert(ints.cap == 20);

    dynResize(ints, 30);
    for (u32 i = 10; i < 30; i++) { assert(ints.data[i] == 0); }

    dynFree(ints);
}
