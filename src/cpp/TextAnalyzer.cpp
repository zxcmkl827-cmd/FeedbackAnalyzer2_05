#include "TextAnalyzer.h"

std::map<std::string, int> TextAnalyzer::globalSent;
std::map<std::string, int> TextAnalyzer::globalKw;

namespace {

const std::vector<std::string>& neutralContexts() {
    static const std::vector<std::string> contexts = {
        u8"좋아요 버튼",
        u8"최고 등급",
        u8"감사 로그",
        u8"추천 목록",
        u8"굿즈",
        u8"환불 정책",
        u8"교환 안내",
        u8"문제 유형",
        u8"불량 기준",
        u8"불편 신고"
    };

    return contexts;
}

const std::vector<std::string>& sentimentPriority() {
    static const std::vector<std::string> priority = {
        u8"부정",
        u8"긍정"
    };

    return priority;
}

}  // namespace

bool TextAnalyzer::containsAny(const std::string& text, const std::vector<std::string>& keywords) {
    for (const auto& kw : keywords) {
        if (text.find(kw) != std::string::npos) return true;
    }
    return false;
}

bool TextAnalyzer::isNeutralContext(const std::string& text) {
    return containsAny(text, neutralContexts());
}

std::string TextAnalyzer::classifySentiment(const std::string& text) {
    if (isNeutralContext(text)) {
        return u8"중립";
    }

    for (const auto& sentiment : sentimentPriority()) {
        if (containsAny(text, Constants::SENTIMENT_KEYWORDS[sentiment])) {
            return sentiment;
        }
    }

    return u8"중립";
}

std::map<std::string, int> TextAnalyzer::makeEmptySentimentCounts() {
    std::map<std::string, int> result;
    result[u8"긍정"] = 0;
    result[u8"중립"] = 0;
    result[u8"부정"] = 0;
    return result;
}

std::map<std::string, int> TextAnalyzer::sent(const std::vector<Feedback>& feedbacks) {
    std::map<std::string, int> res = makeEmptySentimentCounts();

    for (const auto& f : feedbacks) {
        const std::string s = classifySentiment(f.getText());
        res[s]++;
    }

    globalSent = res;
    return res;
}

std::map<std::string, int> TextAnalyzer::kw(const std::vector<Feedback>& feedbacks) {
    std::map<std::string, int> res2;
    for (const auto& entry : Constants::CATEGORY_KEYWORDS) {
        res2[entry.first] = 0;
    }

    for (const auto& f : feedbacks) {
        const std::string& txt = f.getText();
        for (const auto& entry : Constants::CATEGORY_KEYWORDS) {
            const std::string& cat = entry.first;
            if (entry.second.count("main")) {
                const auto& kws = entry.second.at("main");
                if (containsAny(txt, kws)) {
                    res2[cat]++;
                }
            }
        }
    }

    globalKw = res2;
    return res2;
}
