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

    static bool containsAny(const std::string& text, const std::vector<std::string>& keywords);
    static bool isNeutralContext(const std::string& text);
    static std::string classifySentiment(const std::string& text);
    static std::map<std::string, int> makeEmptySentimentCounts();

public:
    std::map<std::string, int> sent(const std::vector<Feedback>& feedbacks);
    std::map<std::string, int> kw(const std::vector<Feedback>& feedbacks);
};
