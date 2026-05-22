#pragma once

#include "Feedback.h"

#include <string>
#include <vector>

class CsvParser {
public:
    static std::vector<std::string> parseLine(const std::string& line);
    static std::vector<Feedback> parseFeedbacks(const std::string& content);
};
