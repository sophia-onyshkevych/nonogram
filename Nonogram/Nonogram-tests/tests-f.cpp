#include <catch.hpp>
#include "tests.h"



#ifdef TEST_MODE


TEST_CASE("f() test")
{
    // Arrange.
    int expectedResult = 5;

    // Act.
    int actualResult = f();
    
    // Assert.
    REQUIRE(expectedResult == actualResult);
}


#endif // TEST_MODE
