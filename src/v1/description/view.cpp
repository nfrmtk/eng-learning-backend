
#include "view.hpp"
#include <filesystem>
#include <fstream>
#include <userver/server/handlers/http_handler_base.hpp>

namespace eng_learning {
namespace {
namespace fs = std::filesystem;
using namespace std::literals;
class Description final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-type-description";

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

    auto task_type = request.GetPathArg("task-type");

    fs::path description = getenv("WORKING_DIRECTORY") + "/tasks/"s + task_type + "/DESCRIPTION.md"s;
    if (!is_regular_file(description)){
      response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
      return {};
    }
    std::ifstream istr(description);
    return {std::istreambuf_iterator<char>{istr}, {}};
  }
};
}  // namespace
void AppendDescription(userver::components::ComponentList& components) {
  components.Append<Description>();
}

}  // namespace eng_learning
