#include "FeedbackController.h"

#include "CsvExporter.h"
#include "CsvParser.h"
#include "FormParser.h"
#include "HtmlRenderer.h"
#include "Logger.h"
#include "Session.h"

#include <exception>
#include <map>

FeedbackController::FeedbackController(ApplicationContext& app) : app_(app) {}

std::string FeedbackController::home() {
    Session::initSessionStateUgly();
    auto& feedbacks = Session::getOldDataFromSession("current_feedbacks");
    return HtmlRenderer::renderPage(u8"피드백 분석기 시작", "", "", {}, {}, feedbacks);
}

std::string FeedbackController::analyze(const std::string& body) {
    try {
        auto& feedbacks = Session::getCurrentFeedbacks();
        auto params = FormParser::parse(body);
        const std::string text = trim(params["text"]);

        if (!text.empty()) {
            feedbacks.push_back(Feedback(text));
        }

        logFeedbackTexts(feedbacks);
        Logger::logInfo(u8"현재 " + std::to_string(feedbacks.size()) + u8"개의 피드백이 입력되었습니다.");

        std::map<std::string, int> sentimentResults;
        std::map<std::string, int> keywordResults;
        if (!feedbacks.empty()) {
            sentimentResults = app_.analyzer().sent(feedbacks);
            keywordResults = app_.analyzer().kw(feedbacks);
            Logger::logInfo(u8"감성 분석 완료");
            Logger::logInfo(u8"키워드 분석 완료");
        }

        return HtmlRenderer::renderPage(successMessage(feedbacks.size()), "", "", sentimentResults, keywordResults, feedbacks);
    } catch (const std::exception& e) {
        Logger::logError(std::string(u8"오류 발생: ") + e.what());
        return renderError(u8"처리 중 오류가 발생했습니다.");
    }
}

std::string FeedbackController::upload(bool hasFile, const std::string& fileContent) {
    try {
        auto& feedbacks = Session::getCurrentFeedbacks();
        if (hasFile && !fileContent.empty()) {
            const auto uploadedFeedbacks = CsvParser::parseFeedbacks(fileContent);
            feedbacks.insert(feedbacks.end(), uploadedFeedbacks.begin(), uploadedFeedbacks.end());
            Logger::logInfo(u8"파일이 성공적으로 업로드되었습니다.");
        }

        return HtmlRenderer::renderPage(successMessage(feedbacks.size()), "", "", {}, {}, feedbacks);
    } catch (const std::exception& e) {
        Logger::logError(std::string(u8"파일 업로드 오류: ") + e.what());
        return renderError(u8"파일 업로드 중 오류가 발생했습니다.");
    }
}

std::string FeedbackController::filter(const std::string& body) {
    try {
        auto& feedbacks = Session::getCurrentFeedbacks();
        auto params = FormParser::parse(body);
        const std::string sentiment = params["sentiment"];
        const std::string keyword = params["keyword"];

        if (feedbacks.empty()) {
            Logger::logWarning(u8"분석할 피드백이 없습니다.");
            return HtmlRenderer::renderPage("", u8"분석할 피드백이 없습니다.", "", {}, {}, {});
        }

        auto filtered = app_.filters().fil(feedbacks, sentiment, keyword);
        if (filtered.empty()) {
            Logger::logWarning(u8"필터링 결과가 없습니다.");
            return HtmlRenderer::renderPage("", u8"필터링 결과가 없습니다.", "", {}, {}, {});
        }

        app_.filteredFeedbacks () = filtered;
        auto sentimentResults = app_.analyzer().sent(filtered);
        auto keywordResults = app_.analyzer().kw(filtered);
        Logger::logInfo(u8"필터링 결과: " + std::to_string(filtered.size()) + u8"개의 피드백");
        return HtmlRenderer::renderPage("", "", "", sentimentResults, keywordResults, filtered);
    } catch (const std::exception& e) {
        Logger::logError(std::string(u8"오류 발생: ") + e.what());
        return renderError(u8"처리 중 오류가 발생했습니다.");
    }
}

std::string FeedbackController::downloadCsv() const {
    const auto& selectedFeedbacks = app_.filteredFeedbacks ();
    if (!selectedFeedbacks.empty()) {
        return CsvExporter::exportFeedbacks(selectedFeedbacks);
    }
    return CsvExporter::exportFeedbacks(Session::getCurrentFeedbacks());
}

std::string FeedbackController::trim(const std::string& text) {
    const auto start = text.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }

    const auto end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

std::string FeedbackController::successMessage(std::size_t feedbackCount) {
    return std::to_string(feedbackCount) + u8"개의 피드백이 입력되었습니다.";
}

std::string FeedbackController::renderError(const std::string& message) {
    return HtmlRenderer::renderPage("", "", message, {}, {}, {});
}

void FeedbackController::logFeedbackTexts(const std::vector<Feedback>& feedbacks) {
    for (const auto& fb : feedbacks) {
        Logger::logInfo(fb.getText());
    }
}
