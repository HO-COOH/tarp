#include "MakefileGenerator/UnixMakefileGenerator.hpp"
#include "ProjectGenerator.hpp"
#include "ProjectDirCreator/CppProjectDirCreator.hpp"
#include "CodeGenerator/CodeGenerator.hpp"
#include <fstream>
#include <typeinfo>//for std::bad_cast


bool UnixMakefileGenerator::registered = ProjectGenerator::registerMakefileCreator(
    "make",
    [](ProjectDirCreator const& projectDir, CodeGenerator const& code) -> std::unique_ptr<MakefileGenerator>
    {return std::make_unique<UnixMakefileGenerator>(projectDir, code); }
);

void UnixMakefileGenerator::writeMakefile() const
{
    try
    {
        auto const& projectDirInfo = dynamic_cast<CppProjectDirCreator const&>(projectDir);
        std::ofstream makefile{ projectDirInfo.getRootDir() + "Makefile" };
        makefile << "# Makefile for " << projectDirInfo.projectName << " (compiling a single file project)\n\n\n\n"
            << "CFLAGS=-g -Wall\n"
            << "SRCS = " << projectDirInfo.source << '/' << code.getGeneratedFilename() << '\n'
            << "OBJS = $(SRCS:.c=.o)\n"
            << "all: \n"
            << "\tcc $(CFLAGS) $(SRCS) -o " << projectDirInfo.build << '/' << projectDirInfo.projectName;
    }
    catch (std::bad_cast const& e)
    {
        throwErrorMessage(name);
    }
}