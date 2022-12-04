//
// Created by nfrmtk on 04.12.2022.
//
#include <filesystem>
#include <vector>
namespace eng_learning {
enum class TaskType { kALL, kPresentSimple, kPastSimple, kFutureSimple };

std::vector<std::filesystem::directory_entry> GetTasks(
    const std::string& task_type);
}  // namespace eng_learning
