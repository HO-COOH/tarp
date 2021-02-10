#pragma once

#include <fstream>

//#include "ProjectDirCreator/ProjectDirCreator.hpp"
//Forward declaration
struct ProjectDirCreator;


/**
 * @brief Class for initializing git and adding git ignore file
 */
class GitInitializer
{
    ProjectDirCreator const& projectDir;
    std::ofstream gitIgnore;

    /**
     * @brief Call "git init" in the projectDir
     */
    void init() const;
public:
    
    /**
     * @brief Construct the GitInitializer with a projectDir, will call "git init" upon construction
     * @param projectDir providing project directory info
     */
    GitInitializer(ProjectDirCreator const& projectDir);


    /**
     * @brief Ignore a single file to .gitignore
     * @param fname Relative path from project root -> to the file name
     */
    void addIgnoreFile(char const* fname);


    /**
     * @brief Ignore some files that has the extension using ignore patterns to .gitignore
     * @param extension The extension of files to be ignored
     */
    void addIgnoreExtension(char const* extension);


    /**
     * @brief Ignore a directory to .gitIgnore
     * @param dirName Relative path from project root -> to the directory
     */
    void addIgnoreDir(char const* dirName);
};