#pragma once

#include "ApplicationContext.h"
#include "FeedbackController.h"
#include "httplib.h"

#include <string>

class FeedbackServer {
public:
    explicit FeedbackServer(ApplicationContext& app);

    bool run(const std::string& host, int port);

private:
    httplib::Server server_;
    FeedbackController controller_;

    void registerRoutes();
    static void setHtml(httplib::Response& res, const std::string& html);
};
