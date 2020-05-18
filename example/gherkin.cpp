//
// Copyright (c) 2019-2020 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/ut.hpp>
#include <fstream>
#include <streambuf>
#include <string>

boost::ut::bdd::steps steps = [](auto& steps) {
  using namespace boost::ut;

  steps.feature("*") = [&] {
    steps.scenario("*") = [&] {
      steps.given("I have {}") = [&](int value) {
        auto i = value;
        steps.when("I increase it by {}") = [&](int value) { i += value; };
        steps.then("I expect {}") = [&](int result) {
          expect(that % i == result);
        };
      };
    };
  };
};

int main() {
  using namespace boost::ut;

  // clang-format off
  "gherkin text"_test = steps |
    R"(
      Feature: Feature
        Scenario: Scenario 1
          Given I have 42
          When I increase it by 1
          Then I expect 43
        Scenario: Scenario 2
          Given I have 12345
          When I increase it by 5
          Then I expect 12350
    )";
  // clang-format on

  std::ifstream file{"feature.gherkin"};
  "gherkin file"_test =
      steps | std::string{(std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>()};
}
