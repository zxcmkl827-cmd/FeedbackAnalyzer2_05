#pragma once

#include "ApplicationContext.h"

#include <string>
#include <vector>

class FeedbackController {
public:
    explicit FeedbackController(ApplicationContext& app);

    std::string home();
    std::string analyze(const std::string& body);
    std::string upload(bool hasFile, const std::string& fileContent);
    std::string filter(const std::string& body);
    std::string downloadCsv() const;

private:
    ApplicationContext& app_;

    static std::string trim(const std::string& text);
    static std::string successMessage(std::size_t feedbackCount);
    static std::string renderError(const std::string& message);
    static void logFeedbackTexts(const std::vector<Feedback>& feedbacks);
};
