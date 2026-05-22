# FeedbackAnalyzer Feature QA Final Report

## 1. QA 종합 결과

이번 QA 활동은 FeedbackAnalyzer C++ 프로젝트의 신규 CSV 결과 저장 기능과 키워드 카운트/가중치 기반 감정 판단 기능을 대상으로 수행했다. 테스트는 GoogleTest, CTest, ApprovalTest를 함께 사용했으며, 기능 테스트와 Golden Master 회귀 테스트를 모두 통과했다.

| 항목 | 결과 |
| --- | ---: |
| 전체 CTest | 72/72 PASS |
| 신규 기능 테스트 | 10/10 PASS |
| ApprovalTest | 2/2 PASS |
| 테스트 증가 | 61개 -> 72개, +11개 |
| 테스트 통과율 | 100% |
| 릴리스 차단 결함 | 0건 |

검증 명령:

```text
cmake --build build
ctest --test-dir build --output-on-failure
cmake --build build-gcov --target sentiment_tests
ctest --test-dir build-gcov --output-on-failure
```

## 2. 테스트 완료율 및 커버리지

### 테스트 완료율

기능 관점의 테스트 완료율은 목표 대비 충족 상태다. CSV 저장 기능은 파일명, 분석 컬럼, 필터 미적용 다운로드, CSV 이스케이프, UTF-8 BOM을 검증했다. 감정 판단 변환 기능은 긍정/부정 카운트 비교, 가중치, 동점 중립, 중립 문맥 우선순위를 검증했다.

| 테스트 범위 | 목표 | 결과 | 판정 |
| --- | ---: | ---: | --- |
| CSV 결과 저장 기능 | 5개 PASS | 5/5 PASS | 충족 |
| 가중치 감정 판단 기능 | 5개 PASS | 5/5 PASS | 충족 |
| 신규 Golden Master | 1개 PASS | 1/1 PASS | 충족 |
| 기존 Golden Master 유지 | 1개 PASS | 1/1 PASS | 충족 |
| 전체 회귀 테스트 | 100% PASS | 72/72 PASS | 충족 |

### gcov/lcov 커버리지

최신 `build-gcov` 실행 후 `coverage.updated.src.info` 기준 핵심 테스트 대상 소스의 커버리지는 다음과 같다.

| 파일 | Line Coverage | Function Coverage | 평가 |
| --- | ---: | ---: | --- |
| `Constants.cpp` | 100% | 100% | 충족 |
| `CsvExporter.cpp` | 98.1% | 100% | 충족 |
| `Feedback.h` | 100% | 100% | 충족 |
| `TextAnalyzer.cpp` | 95.5% | 100% | 충족 |
| 합계 | 97.3% | 100% | 충족 |

목표 대비 평가는 다음과 같다.

| 영역 | 목표 | 현재 수치 | 판정 |
| --- | ---: | ---: | --- |
| 핵심 Domain/Data 라인 커버리지 | 95% 이상 | 97.3% | 충족 |
| 핵심 함수 커버리지 | 90% 이상 | 100% | 충족 |
| Branch Coverage | 90% 목표 | lcov branch data 없음 | 추가 설정 필요 |
| 전체 App 라인 커버리지 | 85~90% 목표 | 기존 산출물 기준 2.1% | 미충족 |
| Boundary 라인 커버리지 | 90% 목표 | 기존 산출물 기준 0.0% | 미충족 |

주의할 점은 최신 높은 수치가 `sentiment_tests` 타깃에 포함된 핵심 소스 기준이라는 점이다. 전체 앱 기준으로는 `FeedbackController`, `FeedbackServer`, `HtmlRenderer`, `CsvParser`, `FormParser`, `Session` 등 Boundary/Control 모듈이 아직 충분히 실행되지 않는다. 다음 QA 단계에서는 이 레이어를 별도 테스트 타깃에 포함해야 한다.

## 3. 결함 패턴 분석

이번 활동에서 확인된 결함 패턴은 크게 네 가지다.

| 패턴 | 사례 | 영향 | 대응 상태 |
| --- | --- | --- | --- |
| Data/CSV 계약 누락 | 고정 파일명, 분석 컬럼 누락, 특수문자 미이스케이프 | 다운로드 결과 신뢰성 저하 | 수정 및 테스트 고정 |
| Domain 판정 방식 한계 | 단순 포함/우선순위 방식으로 카운트와 가중치 미반영 | 감정 오판 가능 | 점수 비교 방식으로 전환 |
| 부분 문자열 오탐 | `불편합니다` 안의 `편합니다` 매칭 | 동점 중립 정책 실패 | 좁은 보정 적용 |
| 회귀 보호 범위 부족 | Boundary/Control 커버리지 낮음 | UI 흐름 회귀 발견 지연 | 추가 단계 필요 |

Severity 관점에서는 사용자 기능에 직접 영향을 주는 CSV 출력과 감정 판단 결함이 `Major`에 해당한다. 빌드 실패나 서버 실행 불가 수준의 `Critical` 결함은 현재 발견되지 않았다.

## 4. 개선 필요 단계

다음 단계의 우선순위는 Boundary/Control 테스트 확장이다.

| 우선순위 | 개선 단계 | 목적 |
| --- | --- | --- |
| 높음 | `CsvParser`, `CsvExporter` 독립 테스트 타깃화 | CSV 입출력 계약을 app 전체와 분리해 보호 |
| 높음 | `FeedbackController` 유스케이스 테스트 | analyze/upload/filter/download 흐름 검증 |
| 높음 | `HtmlRenderer` ApprovalTest 추가 | 사용자 화면 출력 계약 고정 |
| 중간 | `FeedbackServer` 라우트 테스트 전략 수립 | HTTP header, content-type, download filename 검증 |
| 중간 | branch coverage 활성화 | 동점, 예외, 빈 입력 등 분기 누락 확인 |
| 중간 | `Filters`와 `TextAnalyzer` 감정 판단 중복 축소 | 분석 결과와 필터 결과 불일치 방지 |
| 낮음 | coverage 산출물과 build 디렉터리 정리 | 저장소 노이즈와 측정 혼선 방지 |

## 5. 다음 레거시 프로젝트 Best Practice

1. Golden Master를 먼저 고정한다. 레거시 코드는 의도된 동작과 우연한 동작이 섞여 있으므로, 변경 전 사용자 출력과 핵심 계산 결과를 ApprovalTest로 잠근다.

2. Boundary와 Domain 테스트를 분리한다. Domain은 입력/출력 중심의 빠른 단위 테스트로 보호하고, Boundary는 CSV/HTML/HTTP header처럼 외부 계약을 ApprovalTest로 보호한다.

3. RED 테스트는 결함 패턴별로 작게 만든다. CSV 파일명, BOM, 이스케이프, 동점 정책처럼 하나의 실패 이유만 갖는 테스트가 수정 범위를 줄인다.

4. 커버리지는 레이어별로 본다. 전체 앱 커버리지 하나만 보면 리스크가 숨겨진다. Domain, Boundary, Data, Control로 나누어 목표와 미달 영역을 추적한다.

5. 문서와 테스트를 함께 갱신한다. 새 요구사항은 테스트 설계, 결함 관리 문서, Golden Master 보고서에 동시에 남겨야 다음 변경자가 맥락을 잃지 않는다.

## 6. Cursor AI 활용 효과

### 정량 요약

| 항목 | Before | After | 효과 |
| --- | ---: | ---: | --- |
| 전체 테스트 수 | 61 | 72 | +11개, +18.0% |
| ApprovalTest 수 | 1 | 2 | +100% |
| 신규 기능 테스트 | 0 | 10 | CSV/Data + Domain 보호 추가 |
| 전체 테스트 통과율 | 100% | 100% | 회귀 없이 유지 |
| 핵심 소스 라인 커버리지 | 기존 Domain 60.3% | 핵심 대상 97.3% | +37.0%p 수준 개선 |
| 핵심 함수 커버리지 | 기존 Domain 60.0% | 핵심 대상 100% | +40.0%p 수준 개선 |
| 초기 신규 테스트 실패 | 7/10 FAIL | 0/10 FAIL | 결함 조기 발견 후 해소 |

커버리지 비교는 측정 범위가 완전히 동일하지 않다. 기존 Domain 수치는 `Constants/TextAnalyzer/Filters` 묶음이고, 최신 핵심 수치는 테스트 타깃에 포함된 `Constants/CsvExporter/Feedback/TextAnalyzer` 기준이다. 다만 신규 기능의 직접 영향 범위에서는 보호 수준이 크게 올라갔다.

### 정성 요약

Cursor AI는 테스트 설계, 실패 예측, 코드 수정, ApprovalTest 추가, 문서화를 한 흐름으로 연결하는 데 효과가 있었다. 특히 신규 기능을 먼저 실패 테스트로 표현하고, 그 실패를 기준으로 구현을 좁게 진행한 점이 결함 조기 발견에 도움이 됐다.

효과가 컸던 부분은 다음과 같다.

- 테스트 케이스를 기능별로 5개씩 빠르게 분해해 누락 조건을 줄였다.
- CSV 이스케이프, BOM, 파일명처럼 수동 검토에서 빠지기 쉬운 출력 계약을 테스트로 고정했다.
- 감정 판단 로직의 우선순위 결함과 부분 문자열 오탐을 조기에 드러냈다.
- ApprovalTest 승인 파일을 분리해 기존 Golden Master를 훼손하지 않고 신규 계약만 추가했다.
- QA 산출물(`NewFeatureReport`, `NewFeatureGoldenMaster`, `feature_defect_report`)을 테스트 결과와 연결해 추적성을 높였다.

한계도 있다. 커버리지 산출물은 빌드 타깃 구성에 크게 의존하므로 AI가 생성한 수치라도 측정 범위 검토가 필요하다. 또한 `Filters`와 `TextAnalyzer`처럼 중복 로직이 있는 레거시 구조에서는 단순 기능 추가가 장기 유지보수 부채로 이어질 수 있다.

## 7. 최종 판단

신규 CSV 결과 저장 기능과 감정 판단 변환 기능은 현재 테스트 기준으로 릴리스 가능한 품질 상태다. 전체 CTest와 ApprovalTest가 모두 통과했고, 핵심 소스 커버리지 역시 목표를 충족한다.

다만 전체 앱 품질 관점에서는 Boundary/Control 커버리지 미달이 가장 큰 잔여 리스크다. 다음 스프린트에서는 `FeedbackController`, `FeedbackServer`, `HtmlRenderer`, `CsvParser`, `FormParser`를 테스트 타깃에 포함하고, branch coverage를 활성화해 실제 릴리스 품질 기준을 더 엄격하게 맞추는 것이 필요하다.
