# Feature Defect Report

## 1. 결함 분류 체계

Severity는 사용자 영향도와 릴리스 차단 여부를 기준으로 분류한다. ItemType은 결함이 발생한 기능 영역 또는 품질 활동 대상을 기준으로 분류한다.

| Severity \ ItemType | Requirement | Domain Logic | Boundary/UI | Data/CSV | Test/Build |
| --- | --- | --- | --- | --- | --- |
| Critical | 핵심 요구사항 누락으로 기능 사용 불가 | 감정 판단 결과가 전체적으로 잘못 산출됨 | 주요 화면/다운로드 진입 불가 | 데이터 손실 또는 잘못된 파일 생성 | 빌드 실패, 전체 테스트 실행 불가 |
| Major | 요구사항 일부 미충족으로 주요 시나리오 실패 | 특정 감정/가중치/중립 규칙 오판 | 필터/다운로드 등 주요 유스케이스 실패 | CSV 컬럼/이스케이프/BOM 계약 위반 | 회귀 테스트 또는 ApprovalTest 실패 |
| Minor | 명세 문구 불명확, 예외 조건 누락 | 경계 케이스 일부 오판 | 메시지, 표시 순서, 경미한 UX 문제 | 일부 특수문자 처리 미흡 | 테스트명, 테스트 데이터, 리포트 보완 필요 |
| Info | 개선 제안 또는 추적 필요 사항 | 향후 알고리즘 개선 아이디어 | UI 개선 제안 | 출력 포맷 개선 제안 | 커버리지/자동화 개선 제안 |

ItemType 정의:

- `Requirement`: 요구사항, 인수 조건, 정책 정의 관련 결함
- `Domain Logic`: 감정 분석, 키워드 카운트, 가중치, 중립 문맥 등 도메인 판단 결함
- `Boundary/UI`: HTTP 라우팅, 화면 출력, 다운로드 응답 등 Boundary 계층 결함
- `Data/CSV`: CSV 입력/출력, 인코딩, 파일명, 컬럼, 이스케이프 결함
- `Test/Build`: GoogleTest, CTest, ApprovalTest, CMake, 빌드/CI 결함

## 2. 결함 보고서 템플릿

```markdown
## DEF-YYYY-NNN: [간단한 결함 제목]

- Severity: Critical | Major | Minor | Info
- ItemType: Requirement | Domain Logic | Boundary/UI | Data/CSV | Test/Build
- 발견 단계: 요구사항 분석 | 테스트 설계 | 구현 | 회귀 테스트 | 릴리스 검증
- 발견자:
- 발견일:
- 관련 테스트:
- 관련 파일:

### 재현 절차
1. 
2. 
3. 

### 기대 결과

### 실제 결과

### 원인 분석

### 수정 내용

### 검증 방법
- 실행 명령:
- 통과 테스트:
- 추가 회귀 확인:

### 상태
Open | In Progress | Fixed | Verified | Deferred | Won't Fix
```

## 3. 품질 메트릭 수집 계획

### 테스트 통과율

목적은 기능 추가 및 변환 기능 변경 후 회귀 안정성을 수치로 확인하는 것이다.

- 수집 대상: GoogleTest, CTest, ApprovalTest
- 산식: `통과 테스트 수 / 전체 테스트 수 * 100`
- 기준: 로컬 및 CI 모두 100% 통과를 릴리스 최소 기준으로 설정
- 수집 명령 예시:

```text
ctest --test-dir build --output-on-failure
```

### 커버리지

목적은 신규 기능과 변경된 도메인 로직이 테스트로 보호되는지 확인하는 것이다.

| Language | Tool | 수집 대상 | 기준 예시 |
| --- | --- | --- | --- |
| C++ | gcov/lcov | Domain, Boundary, CSV 출력 로직 | Domain 90% 이상, Boundary 80% 이상 |
| Java | JaCoCo | Service, Controller, DTO 변환 | 라인 80% 이상, 브랜치 70% 이상 |
| Python | pytest-cov | Business logic, API adapter | 라인 85% 이상, 핵심 모듈 90% 이상 |

C++ 수집 명령 예시:

```text
cmake -S . -B build-gcov -DCMAKE_BUILD_TYPE=Debug --coverage
cmake --build build-gcov
ctest --test-dir build-gcov --output-on-failure
lcov --capture --directory build-gcov --output-file coverage.info
genhtml coverage.info --output-directory coverage-report
```

### 단계별 결함 발견율

목적은 결함이 늦은 단계에서 발견되는 비율을 낮추는 것이다.

| 단계 | 수집 항목 | 목표 |
| --- | --- | --- |
| 요구사항 분석 | 모호성, 누락, 충돌 결함 | 전체 결함의 20% 이상 조기 발견 |
| 테스트 설계 | 인수 조건 누락, 경계값 누락 | 주요 시나리오 결함 사전 발견 |
| 구현 | 단위 테스트 실패, 컴파일 실패 | Critical 0건 유지 |
| 회귀 테스트 | 기존 기능 회귀, Approval diff | Major 이하로 관리 |
| 릴리스 검증 | 환경 차이, 배포 설정 문제 | 릴리스 차단 결함 0건 |

산식:

```text
단계별 결함 발견율 = 해당 단계 발견 결함 수 / 전체 발견 결함 수 * 100
```

추적 지표:

- Severity별 결함 수
- ItemType별 결함 수
- 결함 평균 수정 시간
- 재오픈율
- ApprovalTest 실패 건수
- 회귀 결함 비율

## 4. GitHub Issues 연동 워크플로우

GitHub Issues를 사용하는 경우 결함은 테스트 실패와 연결해 추적한다.

### 라벨 체계

- `severity:critical`
- `severity:major`
- `severity:minor`
- `severity:info`
- `type:requirement`
- `type:domain`
- `type:boundary`
- `type:data-csv`
- `type:test-build`
- `status:triage`
- `status:verified`

### 운영 흐름

1. 결함 발견 시 `feature_defect_report.md` 템플릿을 기반으로 Issue를 생성한다.
2. 실패 테스트명, CTest 출력, Approval received/approved diff를 첨부한다.
3. Severity와 ItemType 라벨을 지정한다.
4. 수정 PR에는 Issue 번호와 재현 테스트를 연결한다.
5. CI에서 GoogleTest, CTest, ApprovalTest를 실행한다.
6. 수정 후 담당 QA가 재현 절차와 회귀 테스트 결과를 확인하고 `status:verified`로 변경한다.

### Issue 제목 예시

```text
[Major][Data/CSV] CSV 다운로드 파일명이 FeedbackResult timestamp 형식을 따르지 않음
[Major][Domain Logic] 긍정/부정 키워드 동점 시 중립으로 판정되지 않음
[Minor][Boundary/UI] 필터 미적용 상태에서 다운로드 결과가 비어 있음
```

### PR 체크리스트

- [ ] 결함 재현 테스트가 추가되었는가?
- [ ] 수정 후 실패 테스트가 PASS로 전환되었는가?
- [ ] 기존 ApprovalTest가 유지되었는가?
- [ ] 신규 출력 계약 변경 시 승인 파일이 갱신되었는가?
- [ ] 전체 CTest가 통과했는가?
- [ ] 결함 보고서 또는 Issue 상태가 갱신되었는가?
