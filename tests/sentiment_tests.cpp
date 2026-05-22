#include <gtest/gtest.h>

#include <map>
#include <string>
#include <vector>

#include "Constants.h"
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
