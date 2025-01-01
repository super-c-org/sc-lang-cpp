#include "calc.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("CalculatorTest - Add", "[Calculator]") {
    Calculator calc;
    REQUIRE(calc.add(2, 3) == 5);
    REQUIRE(calc.add(-2, 3) == 1);
    REQUIRE(calc.add(0, 0) == 0);
}