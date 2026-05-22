# Feedback Analyzer 코드 품질 분석 보고서

## 분석 기준

- 관점: 시니어 C++ 아키텍트 + 모던 C++ 리뷰어
- 대상: `src/cpp` 기존 C++17 구현
- 기준: SOLID, Code Smell, 테스트 가능성, C++17 리팩토링 적합성
- 우선순위: `1`이 가장 먼저 처리해야 할 항목, `5`가 상대적으로 후순위

## SOLID / Code Smell 분석

| 문제점 | 위반 원칙/스멜 | 영향 | 개선 방향 | 우선순위 |
|---|---|---|---|---|
| `main.cpp`가 HTTP 라우팅, HTML 렌더링, form 파싱, CSV 파싱, 분석 실행, 필터링, 다운로드 응답, 서버 실행을 모두 담당한다. | SRP 위반, God Function, Long Method | 변경 이유가 다른 코드가 한 파일에 집중되어 UI 변경, CSV 규칙 변경, 분석 규칙 변경이 모두 `main.cpp` 수정을 유발한다. 단위 테스트도 HTTP 서버와 렌더링에 묶인다. | `AppController`, `HtmlRenderer`, `CsvParser`, `FeedbackService`, `DownloadHandler`로 책임을 분리한다. `main()`은 조립과 서버 시작만 담당하게 만든다. | 1 |
| `renderPage()`가 HTML 구조, CSS, 사용자 메시지, 필터 옵션, 분석 결과 출력까지 직접 문자열로 조립한다. | SRP 위반, Long Method, Primitive Obsession | 화면 일부 변경에도 긴 문자열 조립 코드를 수정해야 하며, HTML escaping 누락이나 출력 계약 변경을 발견하기 어렵다. | `HtmlRenderer` 클래스로 이동하고, `PageModel`, `AlertModel`, `AnalysisSummary` 같은 출력 모델을 입력받게 한다. HTML 출력은 Approval Test로 고정한다. | 2 |
| `/analyze`, `/upload`, `/filter` 라우트 람다가 요청 파싱, 예외 처리, 도메인 호출, 응답 렌더링을 반복한다. | Duplicated Code, Long Method, SRP 위반 | 성공/경고/오류 응답 경로가 라우트마다 흩어져 정책이 달라질 수 있다. 오류 처리 메시지와 HTTP status 설정도 일관되기 어렵다. | 라우트 핸들러는 `Result<PageModel, Error>` 형태의 application service를 호출하고, 공통 응답 변환 함수를 둔다. C++17에서는 `std::variant<Success, Warning, Error>` 또는 작은 결과 타입을 사용할 수 있다. | 2 |
| `TextAnalyzer::sent()`와 `Filters::fil()`이 감정 판단 로직을 각각 구현한다. | Duplicated Code, OCP 위반 | 분석 결과와 필터 결과가 서로 다른 기준으로 동작할 수 있다. 예를 들어 `Filters`에는 중립 키워드가 있지만 `TextAnalyzer`는 중립 키워드를 직접 사용하지 않는다. | `SentimentClassifier`를 추출해 분석과 필터가 동일한 분류기를 사용하게 한다. 감정은 `enum class Sentiment`로 표현하고 문자열 변환은 경계 계층에서만 수행한다. | 1 |
| `Constants::SENTIMENT_KEYWORDS`와 `Filters::S_KEYWORDS`가 별도 저장소로 관리된다. | OCP 위반, Shotgun Surgery, Duplicated Data | 키워드 추가/삭제 시 여러 위치를 수정해야 하며, 누락 시 회귀 버그가 발생한다. 동일 의미의 규칙이 서로 다르게 진화할 가능성이 높다. | 키워드 규칙을 하나의 `KeywordRepository` 또는 `RuleSet`으로 통합한다. 초기 단계는 `inline const std::map`/`std::array` 기반 테이블, 이후 File DB 로딩으로 확장한다. | 1 |
| `Constants::CATEGORY_KEYWORDS` 내부에서 `"main"`, `"time"`, `"type"` 같은 문자열 key로 분기한다. | Magic String, Primitive Obsession, 조건문 복잡도 | 오타가 컴파일 타임에 잡히지 않고, `"main"`을 특별 취급하는 코드가 여러 곳에 생긴다. 새 카테고리 구조 추가 시 조건문 수정이 필요하다. | `struct CategoryRule { CategoryId id; std::vector<std::string> primaryKeywords; std::vector<KeywordGroup> groups; }`처럼 타입이 있는 테이블로 바꾼다. `main` 문자열 대신 명시적 필드를 사용한다. | 2 |
| `Filters::fil()`이 감정 필터와 키워드 필터를 순차 처리하면서 중첩 루프와 문자열 비교를 반복한다. | 조건문 복잡도, Long Method, SRP 위반 | 필터 조건이 추가될수록 `if`/`else`가 증가한다. 감정 필터, 카테고리 필터, 디버그 출력이 한 함수에 섞여 테스트 경계가 흐려진다. | `FilterCriteria` 값 객체와 `FeedbackPredicate` 조합으로 분리한다. 감정/카테고리 조건은 독립 predicate로 만들고 `std::copy_if` 또는 ranges 유사 패턴으로 적용한다. | 2 |
| `Session`이 `static std::vector<Feedback>`를 전역 세션처럼 사용하고, `getOldDataFromSession(key)`는 `key`를 무시한다. | SRP 위반, Global Mutable State, Hidden Dependency | 요청 간 데이터가 섞이고 동시 접속에 취약하다. 테스트 간 상태 누적이 발생하며, API 이름과 실제 동작이 달라 유지보수자가 오해하기 쉽다. | `SessionStore` 또는 `FeedbackRepository`를 인스턴스로 만들고 라우터에 의존성 주입한다. 단일 사용자 앱이라도 `AppState`로 명시해 테스트에서 교체 가능하게 한다. | 1 |
| `main.cpp`의 `fil_data`, `textAnalyzer`, `filters`, `fileHandler`가 파일 범위 `static` 전역 객체로 존재한다. | Global Mutable State, Hidden Coupling | 객체 수명과 상태 변경 시점이 암묵적이다. 다운로드는 마지막 필터 결과에 의존하므로 필터 전 다운로드 또는 다중 사용자 상황에서 오작동할 수 있다. | 요청 흐름별 상태를 `AppContext`에 모으고, 다운로드 대상은 명시적 결과 ID 또는 현재 세션 상태에서 가져온다. 사용하지 않는 `fileHandler`는 제거하거나 실제 저장 책임으로 이동한다. | 1 |
| CSV 업로드 파싱이 `main.cpp`의 `parseCsvLine()`와 `/upload` 람다 내부에 직접 구현되어 있고 헤더 검증 없이 첫 줄을 건너뛴다. | SRP 위반, Primitive Obsession, 경계값 취약 | `text` 컬럼 요구사항과 다르게 첫 번째 컬럼만 사용한다. quoted field, 개행, 따옴표 escaping, 컬럼 순서 변경에 취약하다. | `CsvParser`를 분리하고 `text` 헤더를 명시적으로 찾는다. `ParseResult`에 성공 데이터와 행별 오류를 담고 Google Test로 빈 파일, 헤더 누락, quoted comma를 고정한다. | 2 |
| `/download`가 CSV를 직접 만들며 `iter.getText() << "\n"`만 수행한다. | SRP 위반, CSV Escaping 누락, Output Contract 취약 | 피드백 텍스트에 쉼표, 따옴표, 개행이 포함되면 다운로드 CSV가 깨진다. 필터 결과가 없을 때도 계약이 불명확하다. | `CsvExporter`를 만들고 RFC4180에 맞춰 따옴표 escaping을 처리한다. UTF-8 BOM, 헤더명, 줄바꿈 정책은 상수화하고 Approval Test로 고정한다. | 2 |
| `Constants::init()`가 mutable static map을 런타임에 채우며, 중복 키워드가 포함되어 있다. | Magic Constant, Mutable Global State, Duplicated Data | 초기화 호출 누락 시 빈 규칙으로 동작한다. 중복 키워드는 의도를 흐리고 분석 결과 변경 시 원인을 추적하기 어렵다. | C++17에서는 `inline const` 규칙 테이블 또는 함수 내부 `static const`로 초기화 순서를 단순화한다. 중복 제거 검증 테스트를 추가한다. | 3 |
| 감정값, 카테고리, 라우트, MIME type, 파일명, 호스트, 포트가 문자열/숫자로 흩어져 있다. | Magic Number, Magic String | `"전체"`, `"긍정"`, `"중립"`, `"부정"`, `"text/html; charset=UTF-8"`, `"filtered_feedback.csv"`, `8080` 변경 시 전역 검색이 필요하다. 오타가 런타임 버그로 이어진다. | `AppConfig`, `Routes`, `ContentTypes`, `Labels` 등으로 상수화한다. 포트와 host는 설정값으로 분리하고 테스트에서는 주입 가능한 값으로 둔다. | 3 |
| `Logger`가 정적 함수와 `std::cout`/`std::cerr`에 직접 의존하고, `debugMode` 기본값이 true이다. | SRP 위반, Hidden Global State, 테스트 어려움 | 테스트에서 로그 출력이 섞이고, 로그 레벨 제어 요구사항을 확장하기 어렵다. 운영 환경에서 debug 로그가 기본 노출될 수 있다. | `ILogger` 인터페이스 또는 sink 주입 구조를 도입한다. `enum class LogLevel`과 최소 출력 레벨을 사용하고, console sink는 구현체로 분리한다. | 4 |
| `FileHandler::saveResult()`는 실제 파일 저장 없이 콘솔 출력만 수행하고, `main.cpp`의 `fileHandler`는 사용되지 않는다. | Dead Code, Lava Flow, Misleading Abstraction | 존재만으로 저장 기능이 구현된 것처럼 보이며, 유지보수자가 잘못된 확장 지점으로 사용할 수 있다. | 사용하지 않는 전역 객체와 죽은 코드를 제거한다. 저장 기능이 필요하면 `ResultWriter` 인터페이스와 `CsvExporter` 구현으로 명확히 재정의한다. | 4 |
| `TextAnalyzer`, `Filters`, `Logger`, `Session`, `FileHandler`에 비정적 구현이 헤더에 많이 포함되어 있다. | Header Implementation Smell, Compile Coupling | include 범위가 커지고 변경 시 재컴파일 영향이 커진다. 클래스 책임과 ABI 경계가 흐려진다. | 헤더에는 선언만 두고 구현은 `.cpp`로 이동한다. 작은 getter나 trivial 생성자만 헤더에 남긴다. | 4 |
| `Feedback`가 텍스트만 가진 얇은 데이터 객체이고 분석 결과, 카테고리, 감정은 외부 map으로만 관리된다. | Anemic Domain Model 가능성, Primitive Obsession | 분석된 피드백의 의미가 `map<string, int>`와 화면 렌더링에 흩어진다. 결과 단위 테스트와 확장이 어려워진다. | `AnalyzedFeedback { Feedback feedback; Sentiment sentiment; std::vector<CategoryId> categories; }` 같은 명시적 도메인 모델을 도입한다. | 3 |
| `std::map<std::string, int>`가 감정/카테고리 집계 결과로 반복 사용된다. | Primitive Obsession, Type Safety 부족 | 존재하지 않는 key, 오타, 누락 초기화가 컴파일 타임에 잡히지 않는다. UI 출력 순서도 map 정렬에 의존한다. | 감정 집계는 `std::array<int, SentimentCount>` 또는 `struct SentimentSummary`로 표현한다. 카테고리는 `CategoryId` 기반 map 또는 순서가 고정된 vector summary를 사용한다. | 3 |
| 키워드 매칭이 `std::string::find()` 부분 문자열 검색에만 의존한다. | 조건 분기 취약, 요구사항 불명확 | 대소문자, 조사/어미, 부분 단어 매칭, UTF-8 문자 단위 기준이 명확하지 않다. 새로운 분석 규칙 추가 시 `if` 분기가 늘어난다. | 초기 리팩토링은 공통 `KeywordMatcher`로 통합하고, 이후 전략 패턴으로 `SubstringMatcher`, `CaseInsensitiveMatcher`, `TokenMatcher`를 교체 가능하게 한다. | 3 |
| `parseForm()`과 `urlDecode()`가 직접 구현되어 있으며 잘못된 percent encoding, 중복 key, 빈 key 정책이 불명확하다. | Boundary Logic Smell, Edge Case 취약 | 입력 경계에서 예외/오류 정책이 모호하고 보안/인코딩 이슈가 도메인 흐름으로 전파될 수 있다. | cpp-httplib의 form parsing 기능 사용 가능성을 우선 검토하고, 직접 유지한다면 `FormParser`로 분리해 실패 케이스를 테스트한다. | 4 |
| `catch (const std::exception&)` 이후 항상 HTML 200 응답처럼 처리한다. | Error Handling Smell, Boundary 정책 불명확 | 클라이언트와 테스트가 성공/실패를 HTTP 상태로 구분하기 어렵다. 오류 종류별 대응도 불가능하다. | `ValidationError`, `ParseError`, `InternalError` 등 오류 타입을 나누고 HTTP status와 사용자 메시지를 매핑한다. C++17에서는 `std::variant` 기반 오류 결과도 가능하다. | 4 |
| `UIComponents::CATS`와 `Constants::CATEGORY_KEYWORDS`가 카테고리 목록을 중복으로 가진다. | Duplicated Data, OCP 위반 | 카테고리를 추가할 때 UI 목록과 분석 규칙을 둘 다 수정해야 하며, 누락 시 분석은 되지만 UI 필터에는 보이지 않는 상태가 생긴다. | UI 카테고리는 `CategoryRule` 테이블에서 파생한다. 표시명과 내부 ID를 함께 가진 단일 source of truth를 둔다. | 2 |

## Magic Number / Magic String 상수화 대상

| 대상 | 현재 위치 | 상수화 필요성 | 권장 이름 예시 |
|---|---|---|---|
| 서버 포트 `8080`, host `"0.0.0.0"` | `main.cpp` | 실행 환경별 변경 가능성이 높고 테스트 서버와 운영 서버 설정이 달라질 수 있다. | `AppConfig::defaultPort`, `AppConfig::defaultHost` |
| MIME type `"text/html; charset=UTF-8"`, `"text/csv; charset=UTF-8"` | `main.cpp` | 응답 생성 경로마다 반복되어 오타와 불일치 가능성이 있다. | `ContentType::htmlUtf8`, `ContentType::csvUtf8` |
| 파일명 `"filtered_feedback.csv"` | `main.cpp` | 다운로드 정책과 UI/테스트 계약에 해당한다. | `DownloadConfig::filteredFeedbackFileName` |
| CSV 헤더 `"text"` | `main.cpp`, README 요구사항 | CSV 입력/출력 계약의 핵심 값이므로 파서와 exporter가 같은 상수를 사용해야 한다. | `CsvColumns::text` |
| 감정 문자열 `"전체"`, `"긍정"`, `"중립"`, `"부정"` | `main.cpp`, `TextAnalyzer.h`, `Filters.h`, `Constants.cpp` | 도메인 분기에 직접 사용되어 오타가 런타임 버그가 된다. | `enum class Sentiment`, `FilterOption::all` |
| 카테고리 문자열 `"배송"`, `"품질"`, `"가격"`, `"서비스"`, `"사용성"` | `Constants.cpp`, `UIComponents.cpp` | UI와 분석 규칙의 중복 source가 된다. | `enum class CategoryId`, `CategoryRule::displayName` |
| 카테고리 내부 key `"main"` | `TextAnalyzer.h`, `Filters.h`, `Constants.cpp` | 특별한 의미를 가진 문자열이지만 타입으로 표현되지 않는다. | `CategoryRule::primaryKeywords` |
| HTML 스타일 수치 `1200px`, `30px`, `10px`, 색상값 | `renderPage()` | 렌더링 책임이 C++ 코드에 강하게 결합되어 UI 변경이 바이너리 변경이 된다. | CSS 파일 또는 `HtmlTemplate` |

## C++17 스타일 개선 방향 요약

1. `enum class Sentiment`, `enum class CategoryId`를 도입해 문자열 기반 분기를 도메인 타입 기반 분기로 바꾼다.
2. `SentimentClassifier`, `CategoryClassifier`, `KeywordMatcher`를 추출해 분석과 필터가 동일한 전략을 공유하게 한다.
3. 키워드와 카테고리는 `CategoryRule`/`SentimentRule` 테이블로 관리하고, UI 필터 옵션도 이 테이블에서 생성한다.
4. `main.cpp`는 composition root로 축소하고, 라우팅/렌더링/CSV/분석/상태 저장을 별도 클래스로 분리한다.
5. 요청 처리 결과는 `std::variant<SuccessPage, WarningPage, ErrorPage>` 또는 명시적 `Result` 타입으로 표현해 오류 흐름을 테스트 가능하게 만든다.
6. `std::map<std::string, int>` 대신 `SentimentSummary`, `CategorySummary` 같은 의미 있는 결과 타입을 사용한다.
7. 전역 mutable 상태를 제거하고 `AppContext` 또는 의존성 주입된 store를 사용해 테스트와 동시성 위험을 낮춘다.
8. CSV 입력/출력, HTML 출력은 각각 `CsvParser`, `CsvExporter`, `HtmlRenderer`로 분리하고 Google Test 및 Approval Test로 계약을 고정한다.

## 리팩토링 우선순위

| 순위 | 작업 | 이유 |
|---|---|---|
| 1 | 전역 상태 제거와 공통 분류기 추출 | 현재 구조의 가장 큰 장애물은 `Session`, `fil_data`, 중복 감정 규칙이다. 이 부분을 먼저 정리해야 테스트 격리와 회귀 보호가 가능하다. |
| 2 | `main.cpp` 책임 분리 | 라우팅, 렌더링, CSV, 분석이 한곳에 있어 이후 모든 변경의 충돌 지점이 된다. 분리 후 각 모듈을 독립 테스트할 수 있다. |
| 3 | 키워드/카테고리 테이블 기반 구조화 | OCP 위반과 magic string 문제를 줄이고, File DB 기반 규칙 관리 요구사항으로 확장하기 쉬워진다. |
| 4 | CSV/HTML 출력 계약 고정 | 사용자 입력이 외부로 나가는 경계이므로 escaping, 헤더, 인코딩 정책을 빠르게 테스트로 고정해야 한다. |
| 5 | Logger/FileHandler/헤더 구현 정리 | 핵심 기능 리스크보다는 낮지만, 장기 유지보수성과 빌드 의존성 개선을 위해 후속 정리가 필요하다. |
