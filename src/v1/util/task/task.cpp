//
// Created by nfrmtk on 04.12.2022.
//

#include "task.hpp"
#include <unordered_map>
#include <userver/utils/assert.hpp>
namespace fs = std::filesystem;
std::vector<fs::directory_entry> eng_learning::GetAllTasksByType(
    const std::string& task_type) {
  std::vector<fs::directory_entry> answer = {};
  static std::unordered_map<std::string, TaskType> mapping = {
      {"ALL", TaskType::kALL},
      {"FUTURE_SIMPLE", TaskType::kFutureSimple},
      {"PAST_SIMPLE", TaskType::kPastSimple},
      {"PRESENT_SIMPLE", TaskType::kPresentSimple}};

  constexpr std::string_view TASKS_DIR = "/eng_learning/tasks";
  std::string_view thing = "asg";
  auto type = mapping[task_type];
  switch (type) {
    case TaskType::kALL: {
      for (const auto& item : fs::directory_iterator(TASKS_DIR)) {
        if (item.is_directory()) {
          for (const auto& entry : fs::directory_iterator(item)) {
            if (entry.path().extension() == ".json") answer.push_back(entry);
          }
        }
      }
      return answer;
    }
    case TaskType::kPastSimple: {
      auto past_simple_path = (fs::path)TASKS_DIR / "past-simple";
      for (const auto& entry : fs::directory_iterator(past_simple_path)) {
        if (entry.path().extension() == ".json") answer.push_back(entry);
      }
      return answer;
    }
    case TaskType::kPresentSimple: {
      auto present_simple_path = (fs::path)TASKS_DIR / "present-simple";

      for (const auto& entry : fs::directory_iterator(present_simple_path)) {
        if (entry.path().extension() == ".json") answer.push_back(entry);
      }
      return answer;
    }
    case TaskType::kFutureSimple: {
      auto future_simple_path = (fs::path)TASKS_DIR / "future-simple";
      for (const auto& entry : fs::directory_iterator(future_simple_path)) {
        if (entry.path().extension() == ".json") answer.push_back(entry);
      }
      return answer;
    }
  }
}
