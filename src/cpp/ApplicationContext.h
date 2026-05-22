#pragma once

#include "Feedback.h"
#include "Filters.h"
#include "TextAnalyzer.h"

#include <vector>

class ApplicationContext {
public:
    void init();

    TextAnalyzer& analyzer();
    Filters& filters();
    std::vector<Feedback>& filteredFeedbacks();

private:
    TextAnalyzer textAnalyzer_;
    Filters filters_;
    std::vector<Feedback> filteredFeedbacks_;
};
