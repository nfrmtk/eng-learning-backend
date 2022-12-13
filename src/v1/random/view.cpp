//
// Created by nfrmtk on 04.12.2022.
//
#include "view.hpp"
#include "../util/task/task.hpp"
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <random>
namespace eng_learning {
namespace {
class Random final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-random";

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext& context) const override {
    auto& response = request.GetHttpResponse();

    if (!request.HasHeader("code") ||
        request.GetHeader("code") != getenv("CODE")) {
      response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
      return {};
    }
    if (!request.HasHeader("count")){
      response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
      return {};
    }
    size_t needed_tasks_amount;
    try{
      needed_tasks_amount = std::stoul(request.GetHeader("count"));
    }
    catch (const std::exception& err){
      response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
      return {};
    }
    std::vector<std::filesystem::directory_entry> all_tasks =
        GetAllTasksByType(request.GetHeader("task-type"));

    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());

    std::vector<size_t> permutation;
    for (size_t i = 0; i < all_tasks.size(); ++i){
      permutation.push_back(i);
    }
    std::shuffle(permutation.begin(), permutation.end(), re);
    userver::formats::json::ValueBuilder builder;
    for (size_t i =0 ; i < std::min(needed_tasks_amount, all_tasks.size()); ++i){
      builder.PushBack(userver::formats::json::blocking::FromFile(all_tasks[permutation[i]].path()));
    }
    return userver::formats::json::ToString( builder.ExtractValue());
  }
};
}  // namespace
void AppendRandom(userver::components::ComponentList& components) {
  components.Append<Random>();
}

}  // namespace eng_learning
