#include "ApplicationContext.h"
#include "FeedbackServer.h"
#include "Logger.h"

int main() {
    ApplicationContext app;
    app.init();

    FeedbackServer server(app);
    if (!server.run("0.0.0.0", 8080)) {
        Logger::logError(u8"서버 시작에 실패했습니다.");
        return 1;
    }

    return 0;
}
