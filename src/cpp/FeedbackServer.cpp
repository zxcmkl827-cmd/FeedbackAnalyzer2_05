#include "FeedbackServer.h"

#include "Logger.h"

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
        res.set_header("Content-Disposition", "attachment; filename=\"filtered_feedback.csv\"");
        res.set_content(controller_.downloadCsv(), "text/csv; charset=UTF-8");
    });
}

void FeedbackServer::setHtml(httplib::Response& res, const std::string& html) {
    res.set_content(html, "text/html; charset=UTF-8");
}
