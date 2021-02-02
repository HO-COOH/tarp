#pragma once

#include <filesystem>
struct ProjectDirCreator
{
    std::string const projectName;
    ProjectDirCreator(std::string root) : projectName{std::move(root)} { std::filesystem::create_directories(root); }
    ProjectDirCreator(std::filesystem::path&& root) : ProjectDirCreator(root.filename().string()) {}
    ProjectDirCreator(char const* root):ProjectDirCreator(std::string{root}){}
    virtual void create() = 0;
    virtual ~ProjectDirCreator() = default;
    [[nodiscard]] auto getRootDir() const { return projectName + '/'; }
};

struct CppProjectDirCreator:public ProjectDirCreator
{
private:
    static bool registered;
public:
    //Make it static instead of constexpr, so we can change it in the future
    inline static auto bin = "bin";
    inline static auto source = "src";
    inline static auto lib = "lib";
    inline static auto build = "build";
    inline static auto doc = "doc";
    inline static auto include = "include";

    CppProjectDirCreator(std::string root)              :ProjectDirCreator(std::move(root)){}
    CppProjectDirCreator(std::filesystem::path&& root)  :ProjectDirCreator(std::move(root)){}
    CppProjectDirCreator(char const* root)              :ProjectDirCreator(root){}

    [[nodiscard]] auto getBinDir() const { return projectName + '/' + bin; }
    [[nodiscard]] auto getSourceDir() const { return projectName + '/' + source; }
    [[nodiscard]] auto getLibDir() const { return projectName + '/' + lib; }
    [[nodiscard]] auto getBuildDir() const { return projectName + '/' + build; }
    [[nodiscard]] auto getDocDir() const { return projectName + '/' + doc; }
    [[nodiscard]] auto getIncludeDir() const { return projectName + '/' + include; }

    void create() override;
};