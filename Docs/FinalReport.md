# Feedback Analyzer 최종 작업 보고서

## 1. 작업 개요

| 항목 | 내용 |
| --- | --- |
| 프로젝트 | `c:\DEV\FeedbackAnalyzer2_05` |
| 브랜치 | `refactoring` |
| 원격 저장소 | `origin/refactoring` |
| 작업일 | 2026-05-22 |
| 작업자 | Cursor AI / GPT-5.5 |
| 최신 업로드 커밋 | `99cfcc2 refactor(app): separate ECB layers` |
| 주요 목적 | 테스트 보호 상태에서 ECB 구조 리팩토링, Golden Master 회귀 보호, 커버리지 점검 |

이번 작업은 기존 `main.cpp` 중심 구조를 ECB(Entity-Control-Boundary) 관점으로 분리하고, 기존 테스트와 Approval Golden Master가 모두 통과하는지 확인하는 것을 목표로 수행했다.

## 2. 완료된 To-Do 항목 요약

| 구분 | 완료 내용 |
| --- | --- |
| 테스트 기준선 확인 | 리팩토링 전 `ctest --test-dir build --output-on-failure` 실행, `61/61 PASS` 확인 |
| 코드 스멜 분석 | `src/cpp` 전체의 SRP 위반, if-else 체인, 긴 함수, 미사용 코드 확인 |
| ECB 분석 | `main.cpp`의 Entity, Control, Boundary 책임 혼재 식별 |
| 리팩토링 계획 | 우선순위별 대상, 후보 목록, 테스트 선행 항목, 검증 명령 정리 |
| Domain 리팩토링 | `TextAnalyzer`, `Filters` 구현을 헤더에서 `.cpp`로 이동 |
| Boundary 분리 | `FormParser`, `CsvParser`, `CsvExporter`, `HtmlRenderer`, `FeedbackServer` 추가 |
| Control 분리 | `ApplicationContext`, `FeedbackController` 추가 |
| Dead Code 제거 | 미사용 `FileHandler.h`, `Session::internalData`, `Session::filterOptions` 제거 |
| 회귀 검증 | 전체 테스트, Golden Master 테스트, 정적 검색 확인 |
| 보고서 작성 | `Report/06.FeedbackAnalyzer_ECB_Refactoring_Report.md`, `Report/FinalReport.md` 작성 |
| GitHub 업로드 | `refactor(app): separate ECB layers` 커밋 후 `origin/refactoring`에 push |

## 3. RED 단계 결과

이번 세션에서는 새 기능 추가 없이 리팩토링을 수행했기 때문에, 새로운 RED 테스트를 추가해 의도적으로 실패시키는 작업은 진행하지 않았다.

다만 리팩토링 보호를 위해 기존 테스트를 RED/GREEN 안전망으로 사용했다.

| 테스트 파일 | 테스트 성격 | 실패 확인 여부 |
| --- | --- | --- |
| `tests/sentiment_tests.cpp` | 감정 분석 회귀 테스트 60건 | 현재 기준 모두 PASS. 신규 RED 실패는 생성하지 않음 |
| `tests/golden_master_tests.cpp` | `TextAnalyzer` 출력 계약 Approval Test | 현재 기준 PASS. 출력 불변성 검증에 사용 |
| `tests/golden_master_expected.txt` | Golden Master 기준 출력 | Approval 기준 파일로 사용 |

RED 단계에서 별도로 실패를 만든 테스트가 없었던 이유는 사용자의 요청이 "새 기능 추가 금지", "테스트 삭제·완화 금지", "리팩토링"에 집중되어 있었기 때문이다.

## 4. GREEN 단계 결과

리팩토링 전후 모두 전체 테스트를 실행해 GREEN 상태를 확인했다.

### 4.1 전체 테스트

실행 명령:

```powershell
ctest --test-dir build --output-on-failure
```

결과:

```text
100% tests passed, 0 tests failed out of 61
```

### 4.2 Approval Golden Master

실행 명령:

```powershell
ctest --test-dir build -R GoldenMasterTest.ApproveTextAnalyzerOutput -V
```

결과:

```text
GoldenMasterTest.ApproveTextAnalyzerOutput ... Passed
100% tests passed, 0 tests failed out of 1
```

### 4.3 커밋 메시지

GitHub에 업로드한 커밋:

```text
99cfcc2 refactor(app): separate ECB layers
```

커밋 설명:

```text
Extract HTTP boundary, controller flow, and application context from main while preserving analyzer behavior and Golden Master output.
```

## 5. Refactoring 결과

### 5.1 선택 항목

| ID | 항목 | 결과 |
| --- | --- | --- |
| R-01 | `main.cpp` 라우팅/파싱/분석/출력 책임 분리 | 완료 |
| R-02 | `TextAnalyzer` 헤더 인라인 구현 제거 | 완료 |
| R-03 | `Filters` 헤더 인라인 구현 제거 및 if-else 체인 제거 | 완료 |
| R-04 | Form/CSV/HTML Boundary 분리 | 완료 |
| R-05 | Controller/Application Context 도입 | 완료 |
| R-06 | 미사용 코드 제거 | 완료 |
| R-07 | Golden Master 회귀 검증 | 완료 |

### 5.2 변경 파일

| 유형 | 파일 |
| --- | --- |
| 신규 Control | `src/cpp/ApplicationContext.h`, `src/cpp/ApplicationContext.cpp` |
| 신규 Control | `src/cpp/FeedbackController.h`, `src/cpp/FeedbackController.cpp` |
| 신규 Boundary | `src/cpp/FeedbackServer.h`, `src/cpp/FeedbackServer.cpp` |
| 신규 Boundary | `src/cpp/FormParser.h`, `src/cpp/FormParser.cpp` |
| 신규 Boundary | `src/cpp/CsvParser.h`, `src/cpp/CsvParser.cpp` |
| 신규 Boundary | `src/cpp/CsvExporter.h`, `src/cpp/CsvExporter.cpp` |
| 신규 Boundary | `src/cpp/HtmlRenderer.h`, `src/cpp/HtmlRenderer.cpp` |
| 변경 Domain | `src/cpp/TextAnalyzer.h`, `src/cpp/TextAnalyzer.cpp` |
| 변경 Domain | `src/cpp/Filters.h`, `src/cpp/Filters.cpp` |
| 변경 Utility | `src/cpp/Logger.h`, `src/cpp/Logger.cpp` |
| 변경 State | `src/cpp/Session.h`, `src/cpp/Session.cpp` |
| 변경 Entry Point | `src/cpp/main.cpp` |
| 변경 Build | `CMakeLists.txt` |
| 제거 | `src/cpp/FileHandler.h` |
| 보고서 | `Report/06.FeedbackAnalyzer_ECB_Refactoring_Report.md`, `Report/FinalReport.md` |

### 5.3 리팩토링 후 구조

```text
main.cpp
  - ApplicationContext 초기화
  - FeedbackServer 실행

ApplicationContext
  - Constants / Filters 초기화
  - TextAnalyzer, Filters, filteredFeedbacks 보유

FeedbackServer
  - httplib 라우팅
  - HTTP Request/Response 연결

FeedbackController
  - analyze / upload / filter / download 유스케이스 흐름

Boundary
  - FormParser
  - CsvParser
  - CsvExporter
  - HtmlRenderer

Domain
  - TextAnalyzer
  - Filters
  - Constants
  - Feedback
```

### 5.4 회귀 테스트 통과 여부

| 검증 | 결과 |
| --- | --- |
| CMake build | PASS |
| CTest 전체 테스트 | `61/61 PASS` |
| Approval Golden Master | PASS |
| `httplib.h` 제외 프로젝트 코드 내 `else if` 검색 | 없음 |
| `3.28084`, `1.09361` 인라인 검색 | 없음 |

## 6. 커버리지 현황

커버리지는 `build-gcov`에서 `gcov/lcov`로 수집했다.

실행 도구:

```text
gcov 15.2.0
lcov 1.15
```

### 6.1 레이어별 수치

| 레이어 | Lines | Functions | Branches | 기준 충족 여부 |
| --- | ---: | ---: | ---: | --- |
| Domain (`Constants.cpp`, `TextAnalyzer.cpp`, `Filters.cpp`) | 60.3% | 60.0% | 39.5% | 미달 |
| Boundary (`ApplicationContext`, `Csv*`, `FormParser`, `HtmlRenderer`, `FeedbackController`, `FeedbackServer`, `main`) | 0.0% | 0.0% | 0.0% | 미달 |
| App 전체 `src/cpp` | 2.1% | 2.4% | 4.7% | 미달 |

### 6.2 파일별 주요 결과

| 파일 | Stmts | Miss | Cover | 미달 원인 | 추가 테스트 제안 |
| --- | ---: | ---: | ---: | --- | --- |
| `Constants.cpp` | 26 | 0 | 100% | 미달 없음 | 추가 불필요 |
| `TextAnalyzer.cpp` | 50 | 3 | 94.0% | 빈 입력/무매칭 경계 부족 | 빈 feedbacks, 감정 키워드 없는 일반 문장, 카테고리 키워드 없는 문장 |
| `Filters.cpp` | 45 | 45 | 0.0% | 필터 로직 테스트 없음 | 전체/긍정/부정/중립 필터, 없는 카테고리, 키워드 매칭/비매칭 |
| `ApplicationContext.cpp` | 10 | 10 | 0.0% | 앱 초기화 테스트 없음 | `init()` 후 분석/필터 사용 가능 여부 |
| `CsvExporter.cpp` | 8 | 8 | 0.0% | CSV 출력 계약 테스트 없음 | 빈 목록, BOM, 헤더, 여러 피드백 |
| `CsvParser.cpp` | 34 | 34 | 0.0% | CSV 입력 계약 테스트 없음 | 헤더 스킵, CRLF, 빈 줄, quoted comma |
| `FeedbackController.cpp` | 74 | 74 | 0.0% | 유스케이스 테스트 없음 | analyze/upload/filter/download 흐름별 계약 테스트 |
| `FeedbackServer.cpp` | 31 | 31 | 0.0% | HTTP 어댑터 테스트 없음 | 라우트별 content-type, download header |
| `FormParser.cpp` | 23 | 23 | 0.0% | form 파싱 계약 테스트 없음 | `+`, `%xx`, invalid percent, `=` 없는 pair |
| `HtmlRenderer.cpp` | 56 | 56 | 0.0% | HTML 출력 계약 테스트 없음 | success/warning/error, escape, 분석 결과 렌더링 |
| `main.cpp` | 9 | 9 | 0.0% | 서버 실행 진입점 미실행 | listen 실패 통합 테스트 또는 smoke test |

## 7. 미완료 항목 및 다음 단계 제안

| 우선순위 | 항목 | 제안 |
| --- | --- | --- |
| 높음 | `Filters.cpp` Domain 커버리지 보강 | `tests/filter_tests.cpp` 추가, `sentiment_tests` 타깃에 포함 |
| 높음 | Boundary 계약 테스트 추가 | `FormParser`, `CsvParser`, `CsvExporter`, `HtmlRenderer` 단위 테스트 추가 |
| 높음 | `FeedbackController` 테스트 추가 | HTTP 없이 controller 메서드를 직접 호출하는 유스케이스 테스트 작성 |
| 중간 | `FeedbackServer` 테스트 전략 결정 | 실제 포트 바인딩 없는 adapter 테스트 또는 통합 테스트로 분리 |
| 중간 | `Session` static 상태 개선 | 테스트 격리를 위해 명시적 `SessionStore` 객체 도입 검토 |
| 중간 | `Constants` 데이터 외부화 | 키워드 catalog 또는 설정 파일 기반 구조 검토 |
| 낮음 | 커버리지 산출물 관리 | `coverage.*.info`, `build*` 디렉터리 `.gitignore` 정리 검토 |

## 8. 발견된 이슈 및 해결 방법

| 이슈 | 원인 | 해결 |
| --- | --- | --- |
| `main.cpp` 책임 과다 | 라우팅, 파싱, 분석, 출력이 한 파일에 집중 | `FeedbackServer`, `FeedbackController`, Boundary 모듈로 분리 |
| `Filters` if-else 체인 | 감정 판별 규칙이 조건문에 고정 | 우선순위 목록 순회 방식으로 변경 |
| 헤더 인라인 구현 과다 | `TextAnalyzer`, `Filters`, `Logger`, `Session` 구현이 헤더에 존재 | 선언은 `.h`, 구현은 `.cpp`로 이동 |
| 미사용 코드 존재 | `FileHandler.h`, `Session` 내부 상태 미사용 | 제거 |
| MSVC `localtime` 경고 | `std::localtime` 사용 | MSVC에서는 `localtime_s`, 그 외 환경에서는 `std::localtime` 사용 |
| PowerShell `&&` / heredoc 문제 | PowerShell 문법과 Bash 문법 차이 | PowerShell 호환 순차 실행 및 `git commit -m` 방식 사용 |
| 단위 변환 관련 커버리지 요청과 실제 코드 불일치 | 프로젝트에는 meter/feet/yard 변환 로직 없음 | 실제 존재하는 Feedback Analyzer Domain/Boundary 기준으로 커버리지 분석 |
| Boundary 커버리지 0% | 분리된 Boundary 모듈이 테스트 타깃에서 실행되지 않음 | 다음 단계에서 Boundary 계약 테스트 추가 필요 |

## 9. 생성형 AI 활용 회고

### 9.1 도움이 된 순간

| 상황 | 도움이 된 점 |
| --- | --- |
| 코드 스멜 분석 | `main.cpp`, `Filters`, `TextAnalyzer`의 SRP/OCP 위반 지점을 빠르게 분류 |
| ECB 설계 | Boundary, Control, Domain 책임을 나누고 파일 구조를 제안 |
| 리팩토링 수행 | 동작 변경 없이 함수와 클래스를 추출하고 CMake 등록까지 연결 |
| 회귀 검증 | 테스트 실행, Approval Test 단독 실행, `rg` 정적 확인을 반복 |
| 보고서 작성 | 작업 흐름, 검증 결과, 남은 리스크를 문서화 |

### 9.2 한계

| 한계 | 설명 |
| --- | --- |
| 요구사항-코드 불일치 감지 필요 | 단위 변환 관련 요청은 현재 코드베이스와 맞지 않아 별도 확인이 필요했다 |
| 커버리지 해석 주의 | 어떤 파일을 Domain/Boundary로 묶느냐에 따라 수치가 달라질 수 있다 |
| 대규모 리팩토링 위험 | 테스트가 부족한 Boundary 영역은 구조 변경 후에도 동작 보장이 약하다 |
| 셸 환경 차이 | PowerShell에서 Bash heredoc, `&&` 문법이 그대로 동작하지 않았다 |

### 9.3 TC 작성 팁

| 영역 | 테스트 케이스 작성 팁 |
| --- | --- |
| Domain | 입력과 출력만 비교하고 HTTP, 파일, 콘솔에 의존하지 않는다 |
| Filters | `전체`, 특정 감정, 없는 카테고리, 키워드 매칭/비매칭을 분리한다 |
| FormParser | URL decode 정상/비정상 케이스를 작은 단위로 나눈다 |
| CsvParser | 헤더, 빈 줄, CRLF, quote, comma를 독립 케이스로 만든다 |
| CsvExporter | BOM, 헤더, 줄바꿈을 문자열 계약으로 고정한다 |
| HtmlRenderer | 전체 HTML보다 핵심 fragment 포함 여부와 escape 결과를 검증한다 |
| FeedbackController | HTTP 없이 body 문자열과 파일 content만 넘겨 유스케이스 결과를 검증한다 |
| Approval Test | 사용자에게 보이는 출력 계약이 넓을 때 Golden Master로 고정한다 |

## 10. 최종 결론

이번 작업으로 `main.cpp` 중심의 구조는 ECB 관점으로 분리되었고, 기존 `TextAnalyzer` 중심 회귀 테스트와 Approval Golden Master는 모두 통과했다.

다만 리팩토링으로 Boundary와 Control 모듈이 새로 분리되면서 해당 레이어의 테스트가 아직 부족하다. 다음 작업의 최우선 목표는 `Filters` Domain 테스트와 Boundary 계약 테스트를 추가해 Domain 95%, Boundary 85% 기준을 충족하는 것이다.
