#include <gtest/gtest.h>
#include <filesystem>
#include "ProjectGenerator.hpp"

class Cleaner: public ::testing::Test
{
public:
    std::string_view projectName;
protected:
    void SetUp() override
    {
        projectName = "example";
    }

    void TearDown() override
    {
        try
        {
            auto const removedCount = std::filesystem::remove_all(projectName);
            std::cout << "Removed " << removedCount << " files\n";
        }
        catch (...)
        {
        }
    }
};

TEST_F(Cleaner, CWithMakefile)
{
    auto const language = "c";
    auto const makefile = "make";
    ProjectGenerator proj{ projectName.data(), language };
}