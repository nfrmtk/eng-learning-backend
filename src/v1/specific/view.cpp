//
// Created by nfrmtk on 04.12.2022.
//
#include "view.hpp"
#include <random>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include "../util/task/task.hpp"
namespace eng_learning {
namespace {
class Specific final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-type-all";

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
    std::vector<std::filesystem::directory_entry> all_tasks =
        GetAllTasksByType(request.GetPathArg("task-type"));

    userver::formats::json::ValueBuilder builder;
    for (auto& file : all_tasks) {
      userver::formats::json::ValueBuilder tmp{
          userver::formats::json::blocking::FromFile(file.path())};
      builder.PushBack(std::move(tmp));
    }
    return userver::formats::json::ToString(builder.ExtractValue());
  }
};
}  // namespace
void AppendSpecific(userver::components::ComponentList& components) {
  components.Append<Specific>();
}

}  // namespace eng_learning
