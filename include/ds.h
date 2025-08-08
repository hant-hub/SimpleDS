#ifndef DS_H
#include <cutils.h>

/*
    Dynamic arrays
*/

#define dynArray(type)                                                         \
    struct {                                                                   \
        Allocator a;                                                           \
        u64 size;                                                              \
        u64 cap;                                                               \
        type *data;                                                            \
    }

#define dynPush(array, val)                                                    \
    ((array.size + 1 > array.cap)                                              \
         ? (array.data = Realloc(                                              \
                array.a, array.data, array.cap * sizeof(array.data[0]),        \
                (array.cap ? array.cap * 2 : 4) * sizeof(array.data[0])),      \
            array.cap = array.cap ? array.cap * 2 : 4)                         \
         : 0,                                                                  \
     array.data[array.size++] = val)

#define dynReserve(array, size)                                                \
    ((array.cap < size)                                                        \
         ? (array.data = Realloc(array.a, array.data,                          \
                                 array.cap * sizeof(array.data[0]),            \
                                 size * sizeof(array.data[0])),                \
            array.cap = size)                                                  \
         : 0)

//INFO(ELI): This macro can't be included in expressions and must be
//on its own line. This is due to the loops which I could fix if
//I added more global functions but I decided I preferred to not
//do that.
#define dynResize(array, newsize)                                              \
    do {                                                                       \
        if (array.cap < newsize) {                                             \
            u64 oldsize = array.cap;                                           \
            while (array.cap < newsize) {                                      \
                array.cap = array.cap ? array.cap * 2 : 4;                     \
            }                                                                  \
            array.data =                                                       \
                Realloc(array.a, array.data, oldsize * sizeof(array.data[0]),  \
                        array.cap * sizeof(array.data[0]));                    \
        }                                                                      \
                                                                               \
        if (array.size < newsize) {                                            \
            memset(&array.data[array.size], 0,                                 \
                   (newsize - array.size) * sizeof(array.data[0]));            \
        }                                                                      \
        array.size = newsize;                                                  \
    } while (0);

#define dynBack(array) (array.data[array.size - 1])

#define dynFree(array)                                                         \
    (Free(array.a, array.data, array.cap * sizeof(array.data[0])))

//TODO(ELI):

#define dynIns(array, val, idx)
#define dynDel(array, idx)
#define dynExt(array, vals, num)

#define DS_IMPL
#ifdef DS_IMPL

#endif
#endif
