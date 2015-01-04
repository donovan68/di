//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//[custom_policy
//<-
#include <memory>
//->
#define BOOST_DI_CFG custom_policy
#include <boost/di.hpp>
#include <boost/di/policies/allow_ctor_types.hpp>

namespace di = boost::di;

class custom_policy : public di::config {
public:
    auto policies() const noexcept {
        using namespace di::policies;
        using namespace di::policies::operators;
        return di::make_policies(
            allow_ctor_types(is_bound<_>{})
        );
    }
};

struct example {
    example(int, double) { }
};

int main() {
    /*<<create shared_ptr `example` with per injector policy setting>>*/
    {
    auto injector = di::make_injector<custom_policy>(
        di::bind<int>.to(42)
      , di::bind<double>.to(87.0)
      , di::bind<example>
    );

    injector.create<example>();
    }

    /*<<create shared_ptr `example` with global policy setting>>*/
    {
    auto injector = di::make_injector(
        di::bind<int>.to(42)
      , di::bind<double>.to(87.0)
      , di::bind<example>
    );

    injector.create<example>();
    }

    return 0;
}

//]

