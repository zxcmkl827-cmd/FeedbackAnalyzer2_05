# New Feature Golden Master

## 작업 개요

추가 기능과 변환 기능에 대한 ApprovalTest 기반 Golden Master를 추가했다. 기존 `GoldenMasterTest.ApproveTextAnalyzerOutput` 테스트와 `tests/golden_master_expected.txt` 승인 파일은 유지하고, 신규 기능 전용 테스트와 승인 파일만 별도로 추가했다.

## 추가된 ApprovalTest

신규 테스트는 `GoldenMasterTest.ApproveNewFeatureOutput`이다. 테스트 실행은 기존 Golden Master 테스트와 동일하게 `ApprovalTest::Test::verify` 메서드를 사용한다.

승인 기준 파일:

```text
tests/new_feature_golden_master_expected.txt
```

검증 대상은 다음과 같다.

- 키워드 카운트 기반 긍정 판정
- 키워드 카운트 기반 부정 판정
- 가중치 기반 긍정 판정
- 긍정/부정 점수 동점 시 중립 판정
- 중립 문맥 우선 판정
- CSV 출력의 UTF-8 BOM 표시 계약
- CSV `text,sentiment,category` 헤더 계약
- CSV 분석 컬럼 값 계약
- 쉼표, 큰따옴표, 줄바꿈 포함 피드백의 CSV 이스케이프 계약

## CMake 반영

새 승인 파일 경로는 CMake compile definition으로 고정했다.

```text
NEW_FEATURE_GOLDEN_MASTER_EXPECTED_PATH="${CMAKE_CURRENT_SOURCE_DIR}/tests/new_feature_golden_master_expected.txt"
```

이 설정으로 테스트 실행 위치가 빌드 디렉터리여도 ApprovalTest가 소스 트리의 승인 파일을 기준으로 비교한다.

## 검증 결과

실행 명령:

```text
cmake --build build --target sentiment_tests
ctest --test-dir build -R "GoldenMasterTest" --output-on-failure
ctest --test-dir build --output-on-failure
```

결과:

```text
GoldenMasterTest.ApproveTextAnalyzerOutput: PASS
GoldenMasterTest.ApproveNewFeatureOutput: PASS
100% tests passed, 0 tests failed out of 72
```

## 변경 파일

- `tests/golden_master_tests.cpp`
- `tests/new_feature_golden_master_expected.txt`
- `CMakeLists.txt`
- `Docs/NewFeatureGoldenMaster.md`
