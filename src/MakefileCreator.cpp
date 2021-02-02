#include "MakefileCreator.hpp"
#include <fstream>
#include "ProjectGenerator.hpp"
#include "CodeGenerator.hpp"

bool UnixMakefileCreator::registered = ProjectGeneratorFactory::registerMakefileCreator("make", [](ProjectDirCreator const& projectDir, CodeGenerator const& code) -> std::unique_ptr<MakefileCreator> {return std::make_unique<UnixMakefileCreator>(projectDir, code); });

bool CMakeCreator::registered = ProjectGeneratorFactory::registerMakefileCreator("cmake", [](ProjectDirCreator const& projectDir, CodeGenerator const& code) -> std::unique_ptr<MakefileCreator> {return std::make_unique<UnixMakefileCreator>(projectDir, code); });

void UnixMakefileCreator::writeMakefile() const
{
    auto const& projectDirInfo = dynamic_cast<CppProjectDirCreator const&>(projectDir);
    std::ofstream makefile{ projectDirInfo.getRootDir()+"Makefile" };
    makefile << "# Makefile for " << projectDirInfo.projectName << " (compiling a single file project)\n\n\n\n"
        << "CFLAGS=-g -Wall\n"
        << "SRCS = " << projectDirInfo.source << '/' << code.getGeneratedFilename() << '\n'
        << "OBJS = $(SRCS:.c=.o)\n"
        << "all: \n"
        << "\tcc $(CFLAGS) $(SRCS) -o " << projectDirInfo.build << '/' << projectDirInfo.projectName;
}

void CMakeCreator::writeMakefile() const
{
    auto const& projectDirInfo = reinterpret_cast<CppProjectDirCreator const&>(projectDir);
    std::ofstream makefile{ projectDirInfo.getRootDir() + "CMakeLists.txt" };
    makefile << "cmake_minimum_required(VERSION 3.0.0)\n"
        << "project(" << projectDirInfo.projectName << ")\n"
        << "add_executable(" << projectDirInfo.projectName << ' ' << code.getGeneratedFilename() << '\n';
}

std::string MakefileCreator::getMakefileType()
{
    std::cout << "Makefile type (default = \"make\"): ";
    std::string makefileType;
    std::getline(std::cin, makefileType);
    return makefileType;
}
