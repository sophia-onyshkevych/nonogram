#include <catch.hpp>
#include "tests.h"

#include <FileReader.h>
#include <Problem.h>



#ifdef TEST_MODE


// Helper functions
// --------------------------------------------

void RunForNonFile(const std::string& filename)
{
    // Arrange.

    const std::string expectedCatalogue = "\"test-problem-files\"";
    const std::string expectedTitle     = "\"test-non-1.non\"";
    const std::string expectedBy        = "\"Ivan Mykhailiuk <iv.mykh@gmail.com>\"";
    const std::string expectedCopyright = "\"2021 Ivan Mykhailiuk <iv.mykh@gmail.com>\"";
    const std::string expectedLicense   = "GPL-2.0";

    const int expectedHeight            = 4;
    const int expectedWidth             = 3;

    const ngm::DimensionData expectedRowsData = {
        { 2, 1 },
        { 3 },
        { 3, 3, 1 },
        { 2 }
    };

    const ngm::DimensionData expectedColumnsData = {
        { 1 },
        { 2, 3 },
        { 4 }
    };

    ngm::NonFileReader nonFileReader;

    // Act.
    
    auto problem = nonFileReader.ReadFile(filename);

    // Assert.

    REQUIRE(expectedCatalogue   == problem->GetCatalogue());
    REQUIRE(expectedTitle       == problem->GetTitle());
    REQUIRE(expectedBy          == problem->GetBy());
    REQUIRE(expectedCopyright   == problem->GetCopyright());
    REQUIRE(expectedLicense     == problem->GetLicense());
    REQUIRE(expectedHeight      == problem->GetHeight());
    REQUIRE(expectedWidth       == problem->GetWidth());
    REQUIRE(expectedRowsData    == problem->GetRowsData());
    REQUIRE(expectedColumnsData == problem->GetColumnsData());
}

// ============================================



TEST_CASE(".NON file - 1")
{
    RunForNonFile(R"(test-problem-files\test-non-1.non)");
}

TEST_CASE(".NON file - 2")
{
    RunForNonFile(R"(test-problem-files\test-non-2.non)");
}

TEST_CASE(".NON file - 3")
{
    RunForNonFile(R"(test-problem-files\test-non-3.non)");
}

TEST_CASE(".NON file - 4")
{
    RunForNonFile(R"(test-problem-files\test-non-4.non)");
}


#endif // TEST_MODE
