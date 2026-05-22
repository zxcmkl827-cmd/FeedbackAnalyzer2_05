#include "ApplicationContext.h"

#include "Constants.h"

void ApplicationContext::init() {
    Constants::init();
    Filters::initFilterKeywords();
}

TextAnalyzer& ApplicationContext::analyzer() {
    return textAnalyzer_;
}

Filters& ApplicationContext::filters() {
    return filters_;
}

std::vector<Feedback>& ApplicationContext::filteredFeedbacks() {
    return filteredFeedbacks_;
}
