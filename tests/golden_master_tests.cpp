#include <gtest/gtest.h>

#include <ApprovalTests.hpp>

#include <filesystem>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Constants.h"
#include "CsvExporter.h"
#include "Feedback.h"
#include "TextAnalyzer.h"

#ifndef GOLDEN_MASTER_EXPECTED_PATH
#define GOLDEN_MASTER_EXPECTED_PATH "tests/golden_master_expected.txt"
#endif

#ifndef NEW_FEATURE_GOLDEN_MASTER_EXPECTED_PATH
#define NEW_FEATURE_GOLDEN_MASTER_EXPECTED_PATH "tests/new_feature_golden_master_expected.txt"
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

void appendSingleFeedbackSentiment(std::ostringstream& output,
                                   TextAnalyzer& analyzer,
                                   const std::string& label,
                                   const Feedback& feedback) {
    const auto sentiment = analyzer.sent({feedback});
    output << label << '|' << feedback.getText() << '|'
           << u8"긍정=" << sentiment.at(u8"긍정") << ','
           << u8"중립=" << sentiment.at(u8"중립") << ','
           << u8"부정=" << sentiment.at(u8"부정") << '\n';
}

std::string visibleBomCsv(const std::string& csv) {
    const std::string bom = "\xEF\xBB\xBF";
    if (csv.rfind(bom, 0) == 0) {
        return "<UTF8_BOM>" + csv.substr(bom.size());
    }
    return csv;
}

std::string buildNewFeatureGoldenMasterOutput() {
    Constants::init();
    TextAnalyzer analyzer;

    std::ostringstream output;
    output << "Golden Master: New Feature output\n\n";

    output << "[Weighted Sentiment]\n";
    appendSingleFeedbackSentiment(
        output,
        analyzer,
        "positive_wins_by_count",
        Feedback(u8"좋아요 만족 추천하지만 조금 불편합니다."));
    appendSingleFeedbackSentiment(
        output,
        analyzer,
        "negative_wins_by_count",
        Feedback(u8"불만 실망 문제는 있지만 상담은 좋아요."));
    appendSingleFeedbackSentiment(
        output,
        analyzer,
        "positive_wins_by_weight",
        Feedback(u8"최고입니다만 배송이 늦어요."));
    appendSingleFeedbackSentiment(
        output,
        analyzer,
        "equal_scores_are_neutral",
        Feedback(u8"좋아요 하지만 불편합니다."));
    appendSingleFeedbackSentiment(
        output,
        analyzer,
        "neutral_context_overrides_score",
        Feedback(u8"좋아요 버튼과 환불 정책 안내를 확인했습니다."));

    const std::vector<Feedback> csvFeedbacks{
        Feedback(u8"제품이 정말 좋아요."),
        Feedback(u8"가격이 비싸요."),
        Feedback(u8"배송이 빠르고, 포장이 \"좋아요\"\n다음에도 구매"),
    };

    output << "\n[CSV Export]\n";
    output << visibleBomCsv(CsvExporter::exportFeedbacks(csvFeedbacks));

    return output.str();
}

}  // namespace

TEST(GoldenMasterTest, ApproveTextAnalyzerOutput) {
    const std::filesystem::path expectedPath = GOLDEN_MASTER_EXPECTED_PATH;
    ApprovalTest::Test::verify(buildGoldenMasterOutput(), expectedPath);
}

TEST(GoldenMasterTest, ApproveNewFeatureOutput) {
    const std::filesystem::path expectedPath = NEW_FEATURE_GOLDEN_MASTER_EXPECTED_PATH;
    ApprovalTest::Test::verify(buildNewFeatureGoldenMasterOutput(), expectedPath);
}
