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
