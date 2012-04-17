//
// Copyright (c) 2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "di/back/aux/instance.hpp"

namespace di
{
namespace back
{
namespace aux
{
namespace ut
{

using namespace boost;

class A { };
class B { };
class C
{
    int dummy;
};

template<typename T, typename TName = void>
struct named
{
    typedef T value_type;

    explicit named(T i)
        : i(i)
    { }

    T i;
};

BOOST_AUTO_TEST_CASE(instancePodvalue)
{
    const int i = 42;
    BOOST_CHECK_EQUAL(i, instance<int>(i).get());
}

BOOST_AUTO_TEST_CASE(instancePodwithvalue_type)
{
    const int i = 42;
    BOOST_CHECK_EQUAL(i, instance<named<int> >(i).get());
}

BOOST_AUTO_TEST_CASE(instanceStringvalue)
{
    const std::string s = "string";
    BOOST_CHECK_EQUAL(s, instance<std::string>(s).get());
}

BOOST_AUTO_TEST_CASE(instanceStringwithvalue_type)
{
    const std::string s = "string";
    BOOST_CHECK_EQUAL(s, instance<named<std::string> >(s).get());
}

BOOST_AUTO_TEST_CASE(instanceVariantRef)
{
    C c;
    C& ref = boost::get<C&>(instance<C>(c).get());
    BOOST_CHECK_EQUAL(&c, &ref);
}

BOOST_AUTO_TEST_CASE(instanceVariantConstRef)
{
    C c;
    const C& constRef = boost::get<const C&>(instance<C>(c).get());
    BOOST_CHECK_EQUAL(&c, &constRef);
}

BOOST_AUTO_TEST_CASE(instanceVariantSharedPtr)
{
    shared_ptr<C> c(new C);
    BOOST_CHECK_EQUAL(c, boost::get<shared_ptr<C> >(instance<C>(c).get()));
}

BOOST_AUTO_TEST_CASE(instancenamed)
{
    typedef named<shared_ptr<int>, A> c1;
    typedef named<shared_ptr<int>, B> c2;

    shared_ptr<c1> c1(new c1(make_shared<int>(42)));
    shared_ptr<c2> c2(new c2(make_shared<int>(87)));

    BOOST_CHECK((*boost::get<shared_ptr<c1> >(instance<c1>(c1).get())->i != *boost::get<shared_ptr<c2> >(instance<c2>(c2).get())->i));
}

BOOST_AUTO_TEST_CASE(instancecontext)
{
    shared_ptr<C> c1(new C);
    shared_ptr<C> c2(new C);

    BOOST_CHECK((instance<int, A>(87).get() != instance<int, B>(42).get()));
    BOOST_CHECK((boost::get<shared_ptr<C> >(instance<C, A>(c1).get()) != boost::get<shared_ptr<C> >(instance<C, B>(c2).get())));
}

} // namespace ut
} // namespace aux
} // namespace back
} // namespace di

