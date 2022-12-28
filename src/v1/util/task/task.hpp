//
// Created by nfrmtk on 04.12.2022.
//
#include <filesystem>
#include <vector>
namespace eng_learning {
std::vector<std::filesystem::directory_entry> GetAllTasksByType(
    const std::string& task_type);
}  // namespace eng_learning
