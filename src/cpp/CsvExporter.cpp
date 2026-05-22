#include "CsvExporter.h"

#include <sstream>

std::string CsvExporter::exportFeedbacks(const std::vector<Feedback>& feedbacks) {
    std::ostringstream csv;
    csv << "\xEF\xBB\xBF";
    csv << "text\n";
    for (const auto& feedback : feedbacks) {
        csv << feedback.getText() << "\n";
    }
    return csv.str();
}
