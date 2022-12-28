//
// Created by nfrmtk on 04.12.2022.
//

#include "task.hpp"
#include <unordered_map>
#include <userver/utils/assert.hpp>
namespace fs = std::filesystem;
std::vector<fs::directory_entry> eng_learning::GetAllTasksByType(
    const std::string& task_type) {
  std::vector<fs::directory_entry> answer;
  auto path_to_tasks = fs::path("/eng_learning/tasks") / task_type;
  for (const auto& entry : fs::directory_iterator(path_to_tasks)) {
    if (entry.path().extension() == ".json") answer.push_back(entry);
  }
  return answer;
}
