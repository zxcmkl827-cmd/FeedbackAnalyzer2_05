#pragma once
#include <string>
#include <vector>
#include <map>
#include "Feedback.h"
#include "Constants.h"

class TextAnalyzer {
private:
    static std::map<std::string, int> globalSent;
    static std::map<std::string, int> globalKw;

    static bool containsAny(const std::string& text, const std::vector<std::string>& keywords) {
        for (const auto& kw : keywords) {
            if (text.find(kw) != std::string::npos) return true;
        }
        return false;
    }

    static bool isNeutralContext(const std::string& text) {
        static const std::vector<std::string> neutralContexts = {
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

        return containsAny(text, neutralContexts);
    }

public:
    std::map<std::string, int> sent(const std::vector<Feedback>& feedbacks) {
        std::map<std::string, int> res;
        res[u8"긍정"] = 0;
        res[u8"중립"] = 0;
        res[u8"부정"] = 0;

        for (const auto& f : feedbacks) {
            std::string txt = f.getText();
            std::string s = u8"중립";
            if (isNeutralContext(txt)) {
                s = u8"중립";
            } else if (containsAny(txt, Constants::SENTIMENT_KEYWORDS[u8"부정"])) {
                s = u8"부정";
            } else if (containsAny(txt, Constants::SENTIMENT_KEYWORDS[u8"긍정"])) {
                s = u8"긍정";
            }
            res[s]++;
        }

        globalSent = res;
        return res;
    }

    std::map<std::string, int> kw(const std::vector<Feedback>& feedbacks) {
        std::map<std::string, int> res2;
        for (const auto& entry : Constants::CATEGORY_KEYWORDS) {
            res2[entry.first] = 0;
        }

        for (const auto& f : feedbacks) {
            std::string txt = f.getText();
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
};
