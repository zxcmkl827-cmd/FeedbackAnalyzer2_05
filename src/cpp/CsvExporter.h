#pragma once

#include "Feedback.h"

#include <string>
#include <vector>

class CsvExporter {
public:
    static std::string exportFeedbacks(const std::vector<Feedback>& feedbacks);
};
