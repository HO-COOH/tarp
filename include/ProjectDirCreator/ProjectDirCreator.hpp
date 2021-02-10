/*****************************************************************//**
 * \file   ProjectDirCreator.hpp
 * \brief  
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/

#pragma once

#include <filesystem>
#include <string>

/**
 * @brief The abstract class for generating the project folder structure
 * @details Any subclass of this class should override:
 *      void create();
 */
struct ProjectDirCreator
{
    std::string const projectName;

    /**
     * @brief Constructor taking a string as the project name to be the root of the project
     * @param root The project name
     */
    ProjectDirCreator(std::string root) : projectName{std::move(root)} { std::filesystem::create_directories(root); }

    /**
     * @brief Constructor taking a std::filesystem::path as the root of the project
     * @param root The root path of the project
     */
    ProjectDirCreator(std::filesystem::path&& root) : ProjectDirCreator(root.filename().string()) {}

    /**
     * @brief Constructor taking a string as the project name to be the root of the project
     * @param root The project name
     */
    ProjectDirCreator(char const* root):ProjectDirCreator(std::string{root}){}

    /**
     * @brief Get the root directory of the project
     * @return normally "<projectName>/"
     */
    [[nodiscard]] auto getRootDir() const { return projectName + '/'; }

    /**
     * @brief Create a language-specific project folder structure
     */
    virtual void create() = 0;

    /**
     * @brief Virtual destructor
     */
    virtual ~ProjectDirCreator() = default;
};