//
// Created by cat on 03.11.16.
//

#include "node.h"
#include <type_traits>

#ifndef MPL_DEMO_LISTOPS_H
#define MPL_DEMO_LISTOPS_H

template <typename L, int V>
struct push_front {
    typedef node<V, L> result;
};

template <typename L>
struct pop_front {
    typedef typename L::next result;
    static int const data = L::data;
};

template <>
struct pop_front<nil> {
    typedef nil result;
};


template <typename L, bool = is_nil<typename L::next>::value>
struct pop_back;

template <typename L>
struct pop_back<L, false> {
    typedef node<L::data, typename pop_back<typename L::next>::result> result;
    static int const data = pop_back<typename L::next>::data;
};

template <typename L>
struct pop_back<L, true> {
    typedef nil result;
    static int const data = L::data;
};


template <typename Node, int PrevData>
struct pop_back_impl
{};

template <int PrevData>
struct pop_back_impl<nil, PrevData>
{};

template <typename L>
struct size {
    static int const result = 1 + size<typename L::next>::result;
};

template <>
struct size<nil> {
    static int const result = 0;
};

template <typename L, int at>
struct erase {
    typedef node<L::data, typename erase<typename L::next, at - 1>::result> result;
};

template <typename L>
struct erase<L, 0> {
    typedef typename L::next result;
};

template <typename L, int at, int val>
struct insert {
    typedef node<L::data, typename insert<typename L::next, at - 1, val>::result> result;
};

template <typename L, int val>
struct insert<L, 0, val> {
    typedef node<val, L> result;
};

template <typename L, typename R = nil>
struct reverse {
    typedef typename reverse<typename L::next, node<L::data, R>>::result result;
};

template <typename R>
struct reverse<nil, R> {
    typedef R result;
};


#endif //MPL_DEMO_LISTOPS_H
