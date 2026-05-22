#include <gtest/gtest.h>

#include <ApprovalTests.hpp>

#include <filesystem>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Constants.h"
#include "Feedback.h"
#include "TextAnalyzer.h"

#ifndef GOLDEN_MASTER_EXPECTED_PATH
#define GOLDEN_MASTER_EXPECTED_PATH "tests/golden_master_expected.txt"
#endif

namespace {

class GoldenMasterNamer : public ApprovalTests::ApprovalNamer {
public:
    explicit GoldenMasterNamer(std::filesystem::path approvedPath)
        : approvedPath_(std::move(approvedPath)),
          receivedPath_(approvedPath_.parent_path() / "golden_master_received.txt") {}

    std::string getApprovedFile(std::string) const override {
        return approvedPath_.string();
    }

    std::string getReceivedFile(std::string) const override {
        return receivedPath_.string();
    }

private:
    std::filesystem::path approvedPath_;
    std::filesystem::path receivedPath_;
};

namespace ApprovalTest {

class Test {
public:
    static void verify(const std::string& actual, const std::filesystem::path& expectedPath) {
        const auto namer = std::make_shared<GoldenMasterNamer>(expectedPath);
        ApprovalTests::Approvals::verify(
            actual,
            ApprovalTests::Options(ApprovalTests::AutoApproveIfMissingReporter()).withNamer(namer));
    }
};

}  // namespace ApprovalTest

std::string buildGoldenMasterOutput() {
    Constants::init();
    TextAnalyzer analyzer;

    const std::vector<Feedback> feedbacks{
        Feedback(u8"배송이 빠릅니다."),
        Feedback(u8"제품 마감이 훌륭합니다."),
        Feedback(u8"가격이 비싸요."),
        Feedback(u8"응대에 불만이 있습니다."),
        Feedback(u8"사용법이 어렵습니다."),
        Feedback(u8"좋아요 버튼 위치를 확인했습니다."),
        Feedback(u8"환불 정책 안내 문서입니다."),
        Feedback(u8"일반 문의 내용입니다."),
    };

    const auto sentiment = analyzer.sent(feedbacks);
    const auto categories = analyzer.kw(feedbacks);

    std::ostringstream output;
    output << "Golden Master: TextAnalyzer output\n";
    output << "input_count=" << feedbacks.size() << "\n\n";

    output << "[Inputs]\n";
    for (std::size_t i = 0; i < feedbacks.size(); ++i) {
        if (i + 1 < 10) {
            output << '0';
        }
        output << (i + 1) << '|' << feedbacks[i].getText() << '\n';
    }

    output << "\n[Sentiment]\n";
    for (const std::string& key : {std::string(u8"긍정"), std::string(u8"중립"), std::string(u8"부정")}) {
        output << key << '=' << sentiment.at(key) << '\n';
    }

    output << "\n[Categories]\n";
    for (const std::string& key : {
             std::string(u8"가격"),
             std::string(u8"배송"),
             std::string(u8"사용성"),
             std::string(u8"서비스"),
             std::string(u8"품질"),
         }) {
        output << key << '=' << categories.at(key) << '\n';
    }

    return output.str();
}

}  // namespace

TEST(GoldenMasterTest, ApproveTextAnalyzerOutput) {
    const std::filesystem::path expectedPath = GOLDEN_MASTER_EXPECTED_PATH;
    ApprovalTest::Test::verify(buildGoldenMasterOutput(), expectedPath);
}
