#include "FeedbackServer.h"

#include "Logger.h"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace {

std::tm toLocalTime(std::time_t time) {
    std::tm localTime{};
#if defined(_MSC_VER)
    localtime_s(&localTime, &time);
#else
    localTime = *std::localtime(&time);
#endif
    return localTime;
}

std::string makeFeedbackResultFilename() {
    // Expected format example: FeedbackResult_20260522_132800.csv
    const auto now = std::time(nullptr);
    const auto localTime = toLocalTime(now);
    std::ostringstream filename;
    filename << "FeedbackResult_" << std::put_time(&localTime, "%Y%m%d_%H%M%S") << ".csv";
    return filename.str();
}

}  // namespace

FeedbackServer::FeedbackServer(ApplicationContext& app) : controller_(app) {
    registerRoutes();
}

bool FeedbackServer::run(const std::string& host, int port) {
    Logger::logInfo(u8"서버가 http://localhost:" + std::to_string(port) + u8" 에서 시작됩니다.");
    return server_.listen(host, port);
}

void FeedbackServer::registerRoutes() {
    server_.Get("/", [this](const httplib::Request&, httplib::Response& res) {
        setHtml(res, controller_.home());
    });

    server_.Post("/analyze", [this](const httplib::Request& req, httplib::Response& res) {
        setHtml(res, controller_.analyze(req.body));
    });

    server_.Post("/upload", [this](const httplib::Request& req, httplib::Response& res) {
        bool hasFile = req.form.has_file("file");
        std::string content;
        if (hasFile) {
            content = req.form.get_file("file").content;
        }
        setHtml(res, controller_.upload(hasFile, content));
    });

    server_.Post("/filter", [this](const httplib::Request& req, httplib::Response& res) {
        setHtml(res, controller_.filter(req.body));
    });

    server_.Get("/download", [this](const httplib::Request&, httplib::Response& res) {
        res.set_header("Content-Disposition", "attachment; filename=\"" + makeFeedbackResultFilename() + "\"");
        res.set_content(controller_.downloadCsv(), "text/csv; charset=UTF-8");
    });
}

void FeedbackServer::setHtml(httplib::Response& res, const std::string& html) {
    res.set_content(html, "text/html; charset=UTF-8");
}
