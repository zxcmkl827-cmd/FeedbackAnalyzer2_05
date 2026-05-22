#pragma once
#include <string>
#include <vector>
#include <map>
#include "Feedback.h"

class Filters {
private:
    static std::map<std::string, std::vector<std::string>> S_KEYWORDS;

    static bool containsAny(const std::string& text, const std::vector<std::string>& keywords);
    static std::string classifySentiment(const std::string& text);
    static std::vector<Feedback> filterBySentiment(const std::vector<Feedback>& dataList,
                                                   const std::string& sFilter);
    static std::vector<Feedback> filterByKeyword(const std::vector<Feedback>& dataList,
                                                 const std::string& kFilter);

public:
    static void initFilterKeywords();

    std::vector<Feedback> fil(const std::vector<Feedback>& dataList,
                              const std::string& sFilter,
                              const std::string& kFilter);
};
