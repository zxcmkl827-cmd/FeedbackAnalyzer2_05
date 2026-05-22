#include "CsvExporter.h"

#include "Constants.h"

#include <sstream>

namespace {

bool containsAny(const std::string& text, const std::vector<std::string>& keywords) {
    for (const auto& keyword : keywords) {
        if (text.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::string escapeCsvField(const std::string& field) {
    const bool needsQuotes = field.find_first_of(",\"\r\n") != std::string::npos;
    if (!needsQuotes) {
        return field;
    }

    std::string escaped = "\"";
    for (char c : field) {
        if (c == '"') {
            escaped += "\"\"";
            continue;
        }
        escaped += c;
    }
    escaped += "\"";
    return escaped;
}

std::string classifySentimentForCsv(const std::string& text) {
    if (Constants::SENTIMENT_KEYWORDS.empty()) {
        Constants::init();
    }

    int positiveScore = 0;
    int negativeScore = 0;
    for (const auto& keyword : Constants::SENTIMENT_KEYWORDS[u8"긍정"]) {
        if (text.find(keyword) != std::string::npos) {
            positiveScore++;
        }
    }
    for (const auto& keyword : Constants::SENTIMENT_KEYWORDS[u8"부정"]) {
        if (text.find(keyword) != std::string::npos) {
            negativeScore++;
        }
    }

    if (positiveScore > negativeScore) {
        return u8"긍정";
    }
    if (negativeScore > positiveScore) {
        return u8"부정";
    }
    return u8"중립";
}

std::string classifyCategoryForCsv(const std::string& text) {
    if (Constants::CATEGORY_KEYWORDS.empty()) {
        Constants::init();
    }

    for (const auto& category : Constants::CATEGORY_KEYWORDS) {
        const auto mainKeywords = category.second.find("main");
        if (mainKeywords != category.second.end() && containsAny(text, mainKeywords->second)) {
            return category.first;
        }
    }
    return "";
}

}  // namespace

std::string CsvExporter::exportFeedbacks(const std::vector<Feedback>& feedbacks) {
    std::ostringstream csv;
    csv << "\xEF\xBB\xBF";
    csv << "text,sentiment,category\n";
    for (const auto& feedback : feedbacks) {
        csv << escapeCsvField(feedback.getText()) << ","
            << escapeCsvField(classifySentimentForCsv(feedback.getText())) << ","
            << escapeCsvField(classifyCategoryForCsv(feedback.getText())) << "\n";
    }
    return csv.str();
}
