# New Feature Report

## 작업 개요

신규 CSV 결과 저장 기능과 키워드 카운트/가중치 기반 감정 판단 기능을 기존 코드에 직접 추가했다. 별도 리팩토링은 수행하지 않았고, 기존 클래스의 책임 범위 안에서 필요한 메서드와 로직만 보강했다.

## CSV 결과 저장 기능

CSV 출력은 기존 `CsvExporter`를 확장해 `text`, `sentiment`, `category` 컬럼을 포함하도록 변경했다. 한글 Excel 호환을 위한 UTF-8 BOM은 유지했고, 쉼표, 큰따옴표, 줄바꿈이 포함된 피드백은 CSV 필드 규칙에 맞게 큰따옴표로 감싸고 내부 큰따옴표를 이스케이프하도록 처리했다.

다운로드 파일명은 `FeedbackResult_YYYYMMDD_HHMMSS.csv` 형식으로 생성한다. 기존 필터 결과가 있는 경우에는 필터 결과를 CSV로 내보내고, 필터를 적용하지 않은 경우에는 현재 세션의 전체 피드백을 CSV로 내보내도록 보강했다.

## 감정 판단 변환 기능

`TextAnalyzer`의 감정 판단은 단순 우선순위 포함 검사에서 키워드 점수 비교 방식으로 변경했다. 긍정/부정 키워드를 각각 카운트하고, 일부 강한 긍정 표현에는 가중치를 부여한다. 긍정 점수와 부정 점수가 같거나 둘 다 없는 경우에는 중립으로 판단한다.

기존 중립 문맥 예외는 유지했다. 따라서 `좋아요 버튼`, `환불 정책`, `불편 신고`처럼 감정 키워드를 포함하더라도 사전에 정의된 중립 문맥이면 중립으로 우선 판정한다.

## 테스트 결과

추가된 테스트는 다음 범위를 검증한다.

- CSV 파일명 형식: `FeedbackResult_[현재시간].csv`
- CSV 분석 컬럼 포함 여부
- 필터 미적용 상태의 CSV 다운로드 가능 여부
- CSV 특수문자 이스케이프
- UTF-8 BOM 유지
- 긍정/부정 키워드 카운트 비교
- 키워드 가중치 반영
- 동점 시 중립 판정
- 중립 문맥 우선 판정

검증 명령:

```text
cmake --build build --target sentiment_tests
ctest --test-dir build -R "CsvResultSaveTest|WeightedSentimentAnalyzerTest" --output-on-failure
ctest --test-dir build --output-on-failure
```

최종 결과:

```text
100% tests passed, 0 tests failed out of 71
```

## 변경 파일

- `src/cpp/CsvExporter.cpp`
- `src/cpp/TextAnalyzer.cpp`
- `src/cpp/Filters.cpp`
- `src/cpp/FeedbackController.cpp`
- `src/cpp/FeedbackServer.cpp`
- `Docs/NewFeatureReport.md`
