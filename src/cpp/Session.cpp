#include "Session.h"

std::vector<Feedback> Session::currentFeedbacks;

void Session::initSessionStateUgly() {
    // Already initialized as static storage.
}

std::vector<Feedback>& Session::getOldDataFromSession(const std::string& key) {
    (void)key;
    return currentFeedbacks;
}

void Session::updateCurrentFeedbacks(const std::vector<Feedback>& feedbacks) {
    currentFeedbacks = feedbacks;
}

std::vector<Feedback>& Session::getCurrentFeedbacks() {
    return currentFeedbacks;
}
