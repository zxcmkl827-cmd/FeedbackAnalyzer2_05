#include "Filters.h"

#include "Constants.h"

#include <set>

std::map<std::string, std::vector<std::string>> Filters::S_KEYWORDS;

namespace {

int keywordWeight(const std::string& keyword) {
    if (keyword == u8"최고" || keyword == u8"최고입니다") {
        return 2;
    }
    return 1;
}

int scoreKeywords(const std::string& text, const std::vector<std::string>& keywords) {
    std::set<std::string> matchedKeywords;
    int score = 0;

    for (const auto& keyword : keywords) {
        if (text.find(keyword) == std::string::npos) {
            continue;
        }
        if (matchedKeywords.insert(keyword).second) {
            score += keywordWeight(keyword);
        }
    }

    return score;
}

}  // namespace

void Filters::initFilterKeywords() {
    S_KEYWORDS[u8"긍정"] = {
        u8"좋아요", u8"만족", u8"감사", u8"친절", u8"좋다", u8"좋았", u8"좋은", u8"우수",
        u8"빠르", u8"정확", u8"신속", u8"안전", u8"괜찮", u8"인상적", u8"추천", u8"기대 이상",
        u8"합리", u8"꼼꼼", u8"뛰어납니다", u8"만족스럽", u8"좋았습니다", u8"좋습니다",
        u8"만족합니다", u8"굿", u8"최고", u8"최고입니다", u8"감사합니다"
    };
    S_KEYWORDS[u8"부정"] = {
        u8"나쁘", u8"불만", u8"실망", u8"최악", u8"별로", u8"불편", u8"불만족", u8"문제",
        u8"불량", u8"불량품", u8"환불", u8"교환", u8"불만족스럽", u8"실망스럽",
        u8"비싸", u8"불친절", u8"늦다"
    };
    S_KEYWORDS[u8"중립"] = {
        u8"괜찮", u8"보통", u8"평범", u8"무난", u8"그냥", u8"전반적", u8"완료",
        u8"적당", u8"나쁘지 않", u8"특별", u8"없"
    };
}

bool Filters::containsAny(const std::string& text, const std::vector<std::string>& keywords) {
    for (const auto& kw : keywords) {
        if (text.find(kw) != std::string::npos) return true;
    }
    return false;
}

std::string Filters::classifySentiment(const std::string& text) {
    const int positiveScore = scoreKeywords(text, S_KEYWORDS[u8"긍정"]);
    const int negativeScore = scoreKeywords(text, S_KEYWORDS[u8"부정"]);
    const int neutralScore = scoreKeywords(text, S_KEYWORDS[u8"중립"]);

    if (positiveScore > negativeScore && positiveScore > neutralScore) {
        return u8"긍정";
    }
    if (negativeScore > positiveScore && negativeScore > neutralScore) {
        return u8"부정";
    }
    if (neutralScore > positiveScore && neutralScore > negativeScore) {
        return u8"중립";
    }

    return u8"중립";
}

std::vector<Feedback> Filters::filterBySentiment(const std::vector<Feedback>& dataList,
                                                 const std::string& sFilter) {
    if (sFilter == u8"전체") {
        return dataList;
    }

    std::vector<Feedback> filtered;
    for (const auto& item : dataList) {
        if (classifySentiment(item.getText()) == sFilter) {
            filtered.push_back(item);
        }
    }
    return filtered;
}

std::vector<Feedback> Filters::filterByKeyword(const std::vector<Feedback>& dataList,
                                               const std::string& kFilter) {
    if (kFilter == u8"전체") {
        return dataList;
    }

    std::vector<Feedback> filtered;
    if (!Constants::CATEGORY_KEYWORDS.count(kFilter)) {
        return filtered;
    }

    const auto& catMap = Constants::CATEGORY_KEYWORDS[kFilter];
    for (const auto& item : dataList) {
        const std::string& txt = item.getText();
        for (const auto& subEntry : catMap) {
            if (subEntry.first == "main") continue;
            if (containsAny(txt, subEntry.second)) {
                filtered.push_back(item);
                break;
            }
        }
    }
    return filtered;
}

std::vector<Feedback> Filters::fil(const std::vector<Feedback>& dataList,
                                   const std::string& sFilter,
                                   const std::string& kFilter) {
    return filterByKeyword(filterBySentiment(dataList, sFilter), kFilter);
}
