#include <iostream>
#include "node.h"
#include "is_nil.h"
#include "print.h"
#include "push_back.h"
#include "list_ops.h"
#include <type_traits>

typedef node<1, nil> list_1;
typedef node<1, node<2, nil>> list_12;
typedef node<1, node<2, node<3, nil>>> list_123;
typedef node<2, node<3, nil>> list_23;
typedef node<3, nil> list_3;

typedef node<3, node<2, node<1, nil>>> list_321;
typedef node<3, node<2, nil>> list_32;
typedef node<1, node<3, nil>> list_13;

typedef node<3, node<2, node<1, node<0, nil>>>> list_3210;
typedef node<0, node<1, node<2, node<3, nil>>>> list_0123;



#if defined(_MSC_VER)                                                 \
 || defined(__GNUC__) && __GNUC__ < 6
// MSVC and GCC (pre 6.x) don't support C++17 terse static assert
#define static_assert(x) static_assert(x, #x)
#endif

static_assert(list_1::data == 1   && is_nil<list_1::next>::value);
static_assert(list_12::data == 1  && list_12::next::data == 2  && is_nil<list_12::next::next>::value);
static_assert(list_123::data == 1 && list_123::next::data == 2 && list_123::next::next::data == 3 && is_nil<list_123::next::next::next>::value);

static_assert((std::is_same<list_12, push_back<list_1, 2>::result>::value));
static_assert((std::is_same<list_123, push_back<list_12, 3>::result>::value));

// pushfront asserted
static_assert((std::is_same<list_123, push_front<list_23, 1>::result>::value));
static_assert((std::is_same<list_123, push_front<push_front<list_3, 2>::result, 1>::result>::value));

// popfront asserted
static_assert((std::is_same<list_23, pop_front<list_123>::result>::value));
static_assert((std::is_same<list_3, pop_front<list_23>::result>::value));
static_assert((std::is_same<nil, pop_front<list_1>::result>::value));

static_assert((std::is_same<std::integral_constant<int, pop_front<list_1>::data>,
        std::integral_constant<int, 1>>::value));

// popback asserted
static_assert((std::is_same<list_12, pop_back<list_123>::result>::value));
static_assert((std::is_same<list_1, pop_back<list_12>::result>::value));

// len asserted
static_assert(3 == size<list_123>::result);
static_assert(2 == size<list_12>::result);

// erase asserted
static_assert((std::is_same<list_23, erase<list_123, 0>::result>::value));
static_assert((std::is_same<list_13, erase<list_123, 1>::result>::value));

// insert asserted
static_assert((std::is_same<list_123, insert<list_23, 0, 1>::result>::value));
static_assert((std::is_same<list_123, insert<list_13, 1, 2>::result>::value));

// reverse asserted
static_assert((std::is_same<list_123, reverse<list_321>::result>::value));
static_assert((std::is_same<list_23, reverse<list_32>::result>::value));
static_assert((std::is_same<list_0123, reverse<list_3210>::result>::value));


int main()
{
    typedef pop_front<pop_back<list_123>::result>::result r;
    std::cout << r();
}


/*
 * spec:
 * push_front
 * pop_(back|front)
 * size
 * erase (index)
 * insert (index)
 * reverse (O(n))
 */