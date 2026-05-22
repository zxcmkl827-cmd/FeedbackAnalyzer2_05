# Feedback Analyzer
![feedback_analyzer](./feedback_analyzer.png)

고객 피드백 분석 시스템은 자연어 기반 고객 피드백 데이터를 수집, 분류, 시각화하는 기능을 제공하는 C++ (cpp-httplib) 기반 웹 애플리케이션입니다.

## 주요 기능

- 텍스트 피드백 입력 (수동/CSV 업로드)
- 키워드 기반 피드백 분류
- 감정 분석 (긍정/부정/중립)
- 피드백 필터링 및 검색
- 분석 결과 시각화
- 결과 CSV 다운로드

## To-Do List

### 1. 테스트 기반 개선 준비

- [ ] Google Test 기반 테스트 환경 구성
- [ ] Approval Test로 HTML, CSV, JSON 출력 계약 고정
- [ ] Given-When-Then 주석 구조로 테스트 작성 규칙 통일
- [ ] Domain 라인 커버리지 95%, 분기 커버리지 90% 목표 설정
- [ ] Boundary 라인 커버리지 90%, Data 라인 커버리지 85% 목표 설정

### 2. Boundary-Control-Entity 구조 분리

- [ ] `boundary/`에서 입력 검증, 출력 변환, 오류 응답 책임 분리
- [ ] `control/`에서 유스케이스 흐름과 의존성 연결 책임 분리
- [ ] `entity/`에서 도메인 규칙, 불변식, 분석 결과 의미 분리
- [ ] Boundary가 Entity 내부 규칙을 직접 수정하지 않도록 의존성 정리
- [ ] Entity가 HTTP, CSV, 파일 시스템, UI에 의존하지 않도록 분리

### 3. 기존 코드 스멜 제거

- [ ] `main.cpp`의 라우팅, HTML 렌더링, 데이터 처리 책임 분리
- [ ] `TextAnalyzer`와 `Filters`의 중복 키워드 검사 로직 제거
- [ ] `Constants`에 하드코딩된 감정/분류 키워드 외부화
- [ ] 전역 mutable 상태를 상태 객체 또는 명시적 의존성으로 대체
- [ ] 사용하지 않는 파일 처리 코드와 죽은 코드 정리

### 4. C++ 코드 품질 정리

- [ ] clang-format 적용
- [ ] 타입은 PascalCase, 함수와 변수는 camelCase 네이밍 적용
- [ ] 상수는 kPascalCase 네이밍 적용
- [ ] 헤더에는 선언만 두고 구현은 소스 파일로 분리
- [ ] 헤더의 불필요한 include를 전방 선언으로 대체
- [ ] `std::cout`, `std::cerr` 디버그 출력 남발 제거
- [ ] `catch(...)` 무분별 사용 제거
- [ ] raw pointer 소유권을 명확한 RAII 구조로 정리

### 5. 기능 개선 및 회귀 보호

- [ ] 중립 감정 필터 오류 수정
- [ ] 텍스트 입력창이 multi-line 입력을 받을 수 있도록 개선
- [ ] 로그 표시를 warning, error 등 level별로 제어
- [ ] Trend 시각화 기능 추가
- [ ] 감정 분석 필터 규칙을 File DB 기반으로 관리
- [ ] 출력 계약 변경 시 Approval Test 승인 파일 변경으로 추적

### RED 단계 To-Do 리스트 결함 목록

- [ ] 긍정 의미 표현이 중립으로 분류되는 결함 10건 수정 (`Docs/defect_list.md`의 `DEF-001` ~ `DEF-010`)
- [ ] 부정 의미 표현이 중립으로 분류되는 결함 10건 수정 (`Docs/defect_list.md`의 `DEF-011` ~ `DEF-020`)
- [ ] 중립 문맥이 긍정 또는 부정으로 오탐되는 결함 10건 수정 (`Docs/defect_list.md`의 `DEF-021` ~ `DEF-030`)
- [ ] `TextAnalyzer::sent()`의 단순 부분 문자열 매칭으로 인한 감정 오탐 방지
- [ ] `Constants::SENTIMENT_KEYWORDS`의 긍정/부정 표현 누락 보강

## Golden Master 회귀 안전장치

> Refactoring 시작 전 구축. GREEN 완료 후 즉시 적용.

### 기준 파일 생성
- [ ] GM-01: golden_master_expected.txt 생성 
- [ ] GM-02: 시나리오 추가

### 테스트 코드
- [ ] GM-03: test_golden_master.cpp + golden_master_expected.txt 작성
- [ ] GM-04: approve 패턴 적용 (파일 없으면 생성, 있으면 비교)
- [ ] GM-05: CMake: add_test PASS 확인

### CI 연동
- [ ] GM-06: .github/workflows/golden_master.yml 작성
- [ ] GM-07: PR 머지 차단 (required status check) 설정
- [ ] GM-08: Refactoring 후 Golden Master 재실행 → PASS 확인

## 추가 기능 및 변환 기능 테스트 설계

> 실제 테스트 코드는 작성하지 않고, C++17 / CMake / GoogleTest / CTest / ApprovalTest 기준으로 작성할 테스트 시나리오와 현재 구현 기준 예상 결과를 정리한다.

### 추가 기능: 피드백 결과 CSV 저장

1. `CSV_SAVE_01`: 분석 결과 CSV 파일명이 `FeedbackResult_[현재시간].csv` 형식인지 검증한다.
   - Given: 피드백 분석 또는 필터링 결과가 존재한다.
   - When: 결과 CSV 저장 또는 다운로드를 요청한다.
   - Then: 파일명은 `FeedbackResult_YYYYMMDD_HHMMSS.csv`처럼 현재시간을 포함해야 한다.
   - 현재 구현 기준 예상 결과: FAIL. 현재 `/download` 응답은 `filtered_feedback.csv` 고정 파일명을 사용한다.

2. `CSV_SAVE_02`: CSV 내용에 피드백 원문뿐 아니라 분석 결과 컬럼이 포함되는지 검증한다.
   - Given: 긍정, 부정, 중립 피드백이 각각 포함된 입력 데이터가 있다.
   - When: 결과 CSV를 생성한다.
   - Then: CSV에는 `text`, `sentiment`, `category` 또는 집계 결과에 해당하는 분석 컬럼이 포함되어야 한다.
   - 현재 구현 기준 예상 결과: FAIL. 현재 `CsvExporter`는 UTF-8 BOM과 `text` 헤더, 피드백 원문만 출력한다.

3. `CSV_SAVE_03`: 필터를 적용하지 않은 분석 결과도 CSV로 저장 가능한지 검증한다.
   - Given: 사용자가 `/analyze`로 피드백을 입력했지만 `/filter`는 실행하지 않았다.
   - When: 결과 CSV 다운로드를 요청한다.
   - Then: 현재 입력된 전체 피드백의 분석 결과가 CSV에 포함되어야 한다.
   - 현재 구현 기준 예상 결과: FAIL. 현재 다운로드는 `ApplicationContext::filteredFeedbacks()`만 사용하므로 필터 전 데이터가 비어 있을 수 있다.

4. `CSV_SAVE_04`: CSV 특수문자 이스케이프가 올바른지 검증한다.
   - Given: 피드백 텍스트에 쉼표, 큰따옴표, 줄바꿈이 포함되어 있다.
   - When: 결과 CSV를 생성한다.
   - Then: RFC 4180 방식으로 필드가 큰따옴표 처리되고 내부 큰따옴표는 이스케이프되어야 한다.
   - 현재 구현 기준 예상 결과: FAIL. 현재 `CsvExporter`는 원문을 그대로 출력하므로 쉼표와 줄바꿈이 CSV 컬럼 구조를 깨뜨릴 수 있다.

5. `CSV_SAVE_05`: 한글 분석 결과 CSV가 Excel에서 깨지지 않도록 UTF-8 BOM을 포함하는지 검증한다.
   - Given: 한글 피드백과 한글 감정/카테고리명이 포함된 분석 결과가 있다.
   - When: 결과 CSV를 생성한다.
   - Then: CSV 시작 부분에 UTF-8 BOM이 포함되어야 한다.
   - 현재 구현 기준 예상 결과: PASS. 현재 `CsvExporter`는 CSV 시작에 UTF-8 BOM을 출력한다.

### 변환 기능: 키워드 카운트 및 가중치 기반 감정 판단

1. `WEIGHTED_SENTIMENT_01`: 긍정 키워드 수가 부정 키워드 수보다 많으면 긍정으로 판단하는지 검증한다.
   - Given: `좋아요`, `만족`, `추천`, `불편`이 포함된 피드백이 있다.
   - When: 감정 분석을 수행한다.
   - Then: 긍정 키워드 카운트가 더 많으므로 최종 감정은 긍정이어야 한다.
   - 현재 구현 기준 예상 결과: FAIL. 현재 `TextAnalyzer`는 부정을 긍정보다 먼저 검사하므로 `불편` 포함 시 부정으로 판단한다.

2. `WEIGHTED_SENTIMENT_02`: 부정 키워드 수가 긍정 키워드 수보다 많으면 부정으로 판단하는지 검증한다.
   - Given: `불만`, `실망`, `문제`, `좋아요`가 포함된 피드백이 있다.
   - When: 감정 분석을 수행한다.
   - Then: 부정 키워드 카운트가 더 많으므로 최종 감정은 부정이어야 한다.
   - 현재 구현 기준 예상 결과: PASS. 현재 구현도 부정 키워드를 먼저 발견하면 부정으로 판단한다.

3. `WEIGHTED_SENTIMENT_03`: 키워드 개수가 같을 때 가중치가 높은 감정으로 판단하는지 검증한다.
   - Given: 긍정 키워드 1개와 부정 키워드 1개가 있고, 긍정 키워드의 가중치가 더 높은 피드백이 있다.
   - When: 감정 분석을 수행한다.
   - Then: 가중 점수 합산 결과에 따라 최종 감정은 긍정이어야 한다.
   - 현재 구현 기준 예상 결과: FAIL. 현재 구현에는 키워드별 가중치 개념이 없다.

4. `WEIGHTED_SENTIMENT_04`: 긍정 점수와 부정 점수가 동점이면 중립으로 판단하는지 검증한다.
   - Given: 긍정 키워드와 부정 키워드가 동일 점수로 포함된 피드백이 있다.
   - When: 감정 분석을 수행한다.
   - Then: 동점 정책에 따라 최종 감정은 중립이어야 한다.
   - 현재 구현 기준 예상 결과: FAIL. 현재 구현은 동점 계산 없이 우선순위에 따라 부정 또는 긍정 중 하나로 조기 반환한다.

5. `WEIGHTED_SENTIMENT_05`: 중립 문맥 예외가 가중치 계산보다 우선 적용되는지 검증한다.
   - Given: `좋아요 버튼`, `환불 정책`처럼 감정 키워드가 있지만 중립 문맥으로 등록된 피드백이 있다.
   - When: 감정 분석을 수행한다.
   - Then: 키워드 점수와 무관하게 최종 감정은 중립이어야 한다.
   - 현재 구현 기준 예상 결과: PASS. 현재 `TextAnalyzer`는 `isNeutralContext()`를 먼저 검사해 중립으로 반환한다.

## 요구사항

- C++17 이상 지원 컴파일러 (MSVC, GCC, Clang)
- CMake 3.14 이상

## 설치 방법
저장소 클론
```
git clone [repository-url]
cd feedback_analyzer_cpp
```

## 빌드 방법
```
rmdir /q /s build
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:\mingw64\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-14.0.0-r7\mingw64\bin\g++.exe
cmake --build build
```

## 실행 방법
```
build\feedback_analyzer.exe
```

## 프로젝트 구조

```
feedback_analyzer_cpp/
├── src/cpp/
│   ├── main.cpp           # HTTP 서버 및 라우팅 (cpp-httplib 기반)
│   ├── httplib.h           # cpp-httplib 헤더 라이브러리
│   ├── Feedback.h          # 피드백 데이터 모델
│   ├── TextAnalyzer.h/cpp  # 텍스트 분석 로직
│   ├── Filters.h/cpp       # 필터링
│   ├── UIComponents.h/cpp  # UI 컴포넌트
│   ├── Session.h/cpp       # 상태 관리
│   ├── Logger.h/cpp        # 로깅
│   ├── Constants.h/cpp     # 상수 정의
│   └── FileHandler.h       # 파일 처리
├── CMakeLists.txt          # CMake 빌드 설정
├── project_purpose.md      # 프로젝트 목적 문서
└── README.md               # 프로젝트 설명
```

## 사용 방법

1. 웹 브라우저에서 `http://localhost:8080` 접속
2. 피드백 텍스트 입력 또는 CSV 파일 업로드
3. 감정/키워드 필터로 결과 필터링
4. 필요시 결과 다운로드

## CSV 파일 형식

입력 CSV 파일은 다음과 같은 형식이어야 합니다:
- 필수 컬럼: `text`
- 텍스트 컬럼에 피드백 내용 포함
