#pragma once
#include <vector>
#include <string>
#include "Feedback.h"

class Session {
private:
    static std::vector<Feedback> currentFeedbacks;

public:
    static void initSessionStateUgly();

    static std::vector<Feedback>& getOldDataFromSession(const std::string& key);

    static void updateCurrentFeedbacks(const std::vector<Feedback>& feedbacks);

    static std::vector<Feedback>& getCurrentFeedbacks();
};
