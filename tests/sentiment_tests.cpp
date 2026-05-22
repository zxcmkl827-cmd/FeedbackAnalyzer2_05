#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "Constants.h"
#include "CsvExporter.cpp"
#include "Feedback.h"
#include "TextAnalyzer.h"

TEST(SentimentAnalyzerTest, test_positive_01) {
    // Given: 긍정 키워드 "좋아요"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"제품이 정말 좋아요.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_02) {
    // Given: 긍정 키워드 "만족"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"서비스에 만족합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_03) {
    // Given: 긍정 키워드 "감사"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"빠른 답변 감사합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_04) {
    // Given: 긍정 키워드 "최고"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"이번 구매는 최고입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_05) {
    // Given: 긍정 키워드 "좋은"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"좋은 품질의 제품입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_06) {
    // Given: 긍정 키워드 "훌륭"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"마감이 훌륭합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_07) {
    // Given: 긍정 키워드 "추천"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"친구에게 추천하고 싶습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_08) {
    // Given: 긍정 키워드 "좋았어요"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"배송 경험이 좋았어요.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_09) {
    // Given: 긍정 키워드 "만족스럽"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"전체적으로 만족스럽습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_10) {
    // Given: 긍정 키워드 "굿"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"가격 대비 굿입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_negative_01) {
    // Given: 부정 키워드 "나쁘"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"제품 상태가 나쁘네요.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_02) {
    // Given: 부정 키워드 "불만"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"응대에 불만이 있습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_03) {
    // Given: 부정 키워드 "실망"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"기대보다 실망스러웠습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_04) {
    // Given: 부정 키워드 "최악"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"배송 경험이 최악이었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_05) {
    // Given: 부정 키워드 "별로"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"품질이 별로입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_06) {
    // Given: 부정 키워드 "불편"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"사용하기 불편합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_07) {
    // Given: 부정 키워드 "문제"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"결제 과정에 문제가 있었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_08) {
    // Given: 부정 키워드 "불량"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"불량품이 도착했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_09) {
    // Given: 부정 키워드 "환불"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"환불을 요청하고 싶습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_10) {
    // Given: 부정 키워드 "짜증"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"계속 오류가 나서 짜증납니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_neutral_01) {
    // Given: 감정 키워드가 없는 배송 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"배송")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_02) {
    // Given: 감정 키워드가 없는 품질 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"품질")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_03) {
    // Given: 감정 키워드가 없는 가격 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"가격 안내를 확인했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_04) {
    // Given: 감정 키워드가 없는 서비스 문의 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"문의 답변을 받았습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_05) {
    // Given: 감정 키워드가 없는 사용성 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"사용방법을 확인했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_06) {
    // Given: 감정 키워드가 없는 주문 번호 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"주문 번호는 12345입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_07) {
    // Given: 감정 키워드가 없는 날짜 정보 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"2026년 5월 22일에 접수했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_08) {
    // Given: 감정 키워드가 없는 배송 상태 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"택배가 이동 중입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_09) {
    // Given: 감정 키워드가 없는 제품 설명 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"제품 구성은 본체와 설명서입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_10) {
    // Given: 감정 키워드가 없는 빈 입력 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback("")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_11) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "빠릅니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"배송 처리가 빠릅니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_12) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "친절합니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"고객 응대가 친절합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_13) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "저렴합니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"가격이 저렴합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_14) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "깔끔합니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"포장이 깔끔합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_15) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "정확합니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"안내 내용이 정확합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_16) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "안정적입니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"앱 실행이 안정적입니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_17) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "편합니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"결제 과정이 편합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_18) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "세련되었습니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"화면 디자인이 세련되었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_19) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "든든합니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"보증 정책이 든든합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_positive_20) {
    // Given: 긍정 의미지만 현재 긍정 키워드에 없는 "부드럽습니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"스크롤 동작이 부드럽습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_negative_11) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 "화가 납니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"배송이 늦어서 화가 납니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_12) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 "늦어요" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"배송이 늦어요.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_13) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 "차갑습니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"고객 응대가 차갑습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_14) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 "파손되었습니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"포장이 파손되었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_15) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 "누락되었습니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"상품 구성품이 누락되었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_16) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 "느립니다" 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"앱 반응이 느립니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_17) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 가격 불만 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"가격이 비싸요.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_18) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 사용성 불만 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"설명서가 어렵습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_19) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 지연 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"상담 연결이 지연되었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_negative_20) {
    // Given: 부정 의미지만 현재 부정 키워드에 없는 처리 실패 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"결제가 완료되지 않았습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(SentimentAnalyzerTest, test_neutral_11) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "좋아요"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"좋아요 버튼을 눌렀습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_12) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "최고"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"최고 등급 옵션을 선택했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_13) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "감사"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"감사 로그가 기록되었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_14) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "추천"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"추천 목록 화면을 열었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_15) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "굿"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"굿즈 배송 상태를 확인했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_16) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "환불"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"환불 정책을 읽었습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_17) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "교환"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"교환 안내 페이지를 확인했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_18) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "문제"가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"문제 유형 목록을 조회했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_19) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "불량"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"불량 기준 문서를 열람했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(SentimentAnalyzerTest, test_neutral_20) {
    // Given: 상태 설명이지만 현재 부분 문자열 규칙상 "불편"이 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"불편 신고 메뉴 위치를 확인했습니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 감정 결과는 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(CsvResultSaveTest, csv_save_01_filename_contains_feedback_result_timestamp) {
    // Given: HTTP 다운로드 경로 구현 소스가 있다.
    const auto sourcePath =
        std::filesystem::path(__FILE__).parent_path().parent_path() / "src" / "cpp" / "FeedbackServer.cpp";
    std::ifstream sourceFile(sourcePath);
    ASSERT_TRUE(sourceFile.is_open());
    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    const std::string source = buffer.str();

    // When: 다운로드 파일명 계약을 확인한다.
    const std::regex expectedFilenamePattern(R"(FeedbackResult_[0-9]{8}_[0-9]{6}\.csv)");

    // Then: 파일명은 FeedbackResult_[현재시간].csv 형식이어야 한다.
    EXPECT_TRUE(std::regex_search(source, expectedFilenamePattern));
}

TEST(CsvResultSaveTest, csv_save_02_csv_contains_analysis_result_columns) {
    // Given: 긍정, 부정, 중립 피드백이 각각 포함된 입력 데이터가 있다.
    const std::vector<Feedback> feedbacks{
        Feedback(u8"제품이 정말 좋아요."),
        Feedback(u8"가격이 비싸요."),
        Feedback(u8"일반 문의 내용입니다.")
    };

    // When: 결과 CSV를 생성한다.
    const std::string csv = CsvExporter::exportFeedbacks(feedbacks);

    // Then: CSV에는 분석 결과 컬럼이 포함되어야 한다.
    EXPECT_NE(csv.find("text"), std::string::npos);
    EXPECT_NE(csv.find("sentiment"), std::string::npos);
    EXPECT_NE(csv.find("category"), std::string::npos);
}

TEST(CsvResultSaveTest, csv_save_03_download_uses_analyzed_feedbacks_without_filtering) {
    // Given: 다운로드 컨트롤러 구현 소스가 있다.
    const auto sourcePath =
        std::filesystem::path(__FILE__).parent_path().parent_path() / "src" / "cpp" / "FeedbackController.cpp";
    std::ifstream sourceFile(sourcePath);
    ASSERT_TRUE(sourceFile.is_open());
    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    const std::string source = buffer.str();

    // When: 다운로드 데이터 소스를 확인한다.
    const bool dependsOnlyOnFilteredFeedbacks = source.find("filteredFeedbacks()") != std::string::npos;

    // Then: 필터 전 분석 데이터도 다운로드 가능해야 하므로 filteredFeedbacks에만 의존하면 안 된다.
    EXPECT_FALSE(dependsOnlyOnFilteredFeedbacks);
}

TEST(CsvResultSaveTest, csv_save_04_csv_escapes_comma_quote_and_newline) {
    // Given: CSV 특수문자를 포함한 피드백이 있다.
    const std::vector<Feedback> feedbacks{
        Feedback(u8"배송이 빠르고, 포장이 \"좋아요\"\n다음에도 구매")
    };

    // When: 결과 CSV를 생성한다.
    const std::string csv = CsvExporter::exportFeedbacks(feedbacks);

    // Then: 쉼표, 큰따옴표, 줄바꿈이 포함된 필드는 RFC 4180 방식으로 이스케이프되어야 한다.
    EXPECT_NE(csv.find(u8"\"배송이 빠르고, 포장이 \"\"좋아요\"\"\n다음에도 구매\""), std::string::npos);
}

TEST(CsvResultSaveTest, csv_save_05_csv_starts_with_utf8_bom) {
    // Given: 한글 피드백이 포함된 입력 데이터가 있다.
    const std::vector<Feedback> feedbacks{Feedback(u8"제품이 정말 좋아요.")};

    // When: 결과 CSV를 생성한다.
    const std::string csv = CsvExporter::exportFeedbacks(feedbacks);

    // Then: Excel 호환성을 위해 UTF-8 BOM으로 시작해야 한다.
    ASSERT_GE(csv.size(), 3U);
    EXPECT_EQ(static_cast<unsigned char>(csv[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(csv[1]), 0xBB);
    EXPECT_EQ(static_cast<unsigned char>(csv[2]), 0xBF);
}

TEST(WeightedSentimentAnalyzerTest, weighted_sentiment_01_positive_wins_by_keyword_count) {
    // Given: 긍정 키워드 3개와 부정 키워드 1개가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"좋아요 만족 추천하지만 조금 불편합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 긍정 키워드 카운트가 더 많으므로 최종 감정은 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(WeightedSentimentAnalyzerTest, weighted_sentiment_02_negative_wins_by_keyword_count) {
    // Given: 부정 키워드 3개와 긍정 키워드 1개가 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"불만 실망 문제는 있지만 상담은 좋아요.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 부정 키워드 카운트가 더 많으므로 최종 감정은 부정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 1);
}

TEST(WeightedSentimentAnalyzerTest, weighted_sentiment_03_higher_positive_weight_wins_on_same_count) {
    // Given: 긍정 키워드 1개와 부정 키워드 1개가 있고 긍정 가중치가 더 높아야 하는 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"최고입니다만 배송이 늦어요.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 가중 점수 합산 결과에 따라 최종 감정은 긍정이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 1);
    EXPECT_EQ(result.at(u8"중립"), 0);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(WeightedSentimentAnalyzerTest, weighted_sentiment_04_equal_weight_scores_are_neutral) {
    // Given: 긍정 키워드와 부정 키워드가 동일 점수로 포함된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{Feedback(u8"좋아요 하지만 불편합니다.")};

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 동점 정책에 따라 최종 감정은 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}

TEST(WeightedSentimentAnalyzerTest, weighted_sentiment_05_neutral_context_overrides_weighted_score) {
    // Given: 감정 키워드가 있지만 중립 문맥으로 등록된 피드백이 있다.
    Constants::init();
    TextAnalyzer analyzer;
    const std::vector<Feedback> feedbacks{
        Feedback(u8"좋아요 버튼과 환불 정책 안내를 확인했습니다.")
    };

    // When: 감정 분석을 수행한다.
    const std::map<std::string, int> result = analyzer.sent(feedbacks);

    // Then: 키워드 점수와 무관하게 최종 감정은 중립이어야 한다.
    EXPECT_EQ(result.at(u8"긍정"), 0);
    EXPECT_EQ(result.at(u8"중립"), 1);
    EXPECT_EQ(result.at(u8"부정"), 0);
}
