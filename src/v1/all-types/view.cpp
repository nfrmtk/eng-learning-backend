//
// Created by nfrmtk on 04.12.2022.
//
#include "view.hpp"

#include <filesystem>
#include <random>
#include <userver/formats/json/serialize.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
namespace eng_learning {
namespace {
namespace fs = std::filesystem;
class AllTypes final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-all-types";

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

    userver::formats::json::ValueBuilder builder;
    for (auto& entry : fs::directory_iterator("/eng_learning/tasks")) {
      LOG_DEBUG() << fmt::format("hello from for loop =), {} is the ",
                                 entry.path().string());
      userver::formats::json::ValueBuilder name;
      if (!entry.is_directory()) continue;
      std::string thing = entry.path().filename();
      // thing = thing.substr(1, thing.size() - 2);
      name["name"] = thing;
      builder.PushBack(std::move(name));
    }
    return userver::formats::json::ToString(builder.ExtractValue());
  }
};
}  // namespace
void AppendAllTypes(userver::components::ComponentList& components) {
  components.Append<AllTypes>();
}

}  // namespace eng_learning
