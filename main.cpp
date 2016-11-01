#include <iostream>
#include "node.h"
#include "is_nil.h"
#include "print.h"
#include "push_back.h"

typedef node<1, nil> list_1;
typedef node<1, node<2, nil>> list_12;
typedef node<1, node<2, node<3, nil>>> list_123;

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

int main()
{
    std::cout << list_1() << std::endl;
    std::cout << list_12() << std::endl;
    std::cout << list_123() << std::endl;
}
