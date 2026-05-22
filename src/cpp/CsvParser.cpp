#include "CsvParser.h"

#include <sstream>

std::vector<std::string> CsvParser::parseLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
            continue;
        }

        if (c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
            continue;
        }

        field += c;
    }
    fields.push_back(field);
    return fields;
}

std::vector<Feedback> CsvParser::parseFeedbacks(const std::string& content) {
    std::vector<Feedback> feedbacks;
    std::istringstream stream(content);
    std::string line;
    bool firstLine = true;
    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (line.empty()) continue;

        auto fields = parseLine(line);
        if (!fields.empty() && !fields[0].empty()) {
            feedbacks.push_back(Feedback(fields[0]));
        }
    }
    return feedbacks;
}
