#include "MakefileGenerator/CMakeGenerator.hpp"
#include "ProjectGenerator.hpp"
#include "ProjectDirCreator/CppProjectDirCreator.hpp"
#include "CodeGenerator/CodeGenerator.hpp"
#include <fstream>
#include <typeinfo>//for std::bad_cast


bool CMakeGenerator::registered = ProjectGenerator::registerMakefileCreator(
    "cmake", 
    [](ProjectDirCreator const& projectDir, CodeGenerator const& code) -> std::unique_ptr<MakefileGenerator> 
    {return std::make_unique<CMakeGenerator>(projectDir, code); }
);



void CMakeGenerator::writeMakefile() const
{
    try 
    {
        auto const& projectDirInfo = reinterpret_cast<CppProjectDirCreator const&>(projectDir);
        std::ofstream makefile{ projectDirInfo.getRootDir() + "CMakeLists.txt" };
        makefile << "cmake_minimum_required(VERSION 3.0.0)\n"
            << "project(" << projectDirInfo.projectName << ")\n"
            << "add_executable(" << projectDirInfo.projectName << ' ' << projectDirInfo.source <<"/" << code.getGeneratedFilename() << ")\n";
    }
    catch (std::bad_cast const&)
    {
        throwErrorMessage(name);
    }
}

