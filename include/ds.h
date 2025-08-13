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

// INFO(ELI): This macro can't be included in expressions and must be
// on its own line. This is due to the loops which I could fix if
// I added more global functions but I decided I preferred to not
// do that.
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

// INFO(ELI): These Macros cannot be part of expressions since they require
// loops.

#define dynIns(array, idx, val)                                                \
    do {                                                                       \
        dynResize(array, array.size + 1);                                      \
        for (i64 i = array.size - 1; i >= idx; i--) {                          \
            array.data[i + 1] = array.data[i];                                 \
        }                                                                      \
        array.data[idx] = val;                                                 \
    } while (0)

#define dynDel(array, idx)                                                     \
    do {                                                                       \
        for (u32 i = idx; i < ints.size - 1; i++) {                            \
            array.data[i] = array.data[i + 1];                                 \
        }                                                                      \
        dynResize(array, array.size - 1);                                      \
    } while (0)

#define dynExt(array, vals, num)                                               \
    do {                                                                       \
        dynResize(array, array.size + num);                                    \
        for (u64 i = array.size - num; i < array.size; i++) {                  \
            array.data[i] = vals[i - array.size + num];                        \
        }                                                                      \
    } while (0)

/*
    HashMap
*/

#define HashMap(key, val)                                                      \
    struct {                                                                   \
        Allocator a;                                                           \
        u64 cap;                                                               \
        u64 size;                                                              \
        struct {                                                               \
            key k;                                                             \
            u8 m;                                                              \
        } *keys;                                                               \
        val *vals;                                                             \
    }

#define HashIns(map, key, val)
#define HashDel(map, key, val)
#define HashGet(map, key)

#define HashResize(map, newsize)

#define DS_IMPL
#ifdef DS_IMPL

#endif
#endif
