#include <iostream>
#include <thread>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

int main(int argc, char* argv[])
{
    auto logger = spdlog::rotating_logger_mt("logger", "log/2022-08-27", 2 * 1024 * 1024, 10);
    logger->set_level(spdlog::level::debug);
    logger->sinks().push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

    logger->debug("This is debug information");
    logger->info("started");

    std::vector<std::thread> ts;
    for(int i = 0; i < 4; ++i) {
        std::thread t([logger](int id){
            for (int i = 0; i < 10; ++i) {
                logger->info("thread: {}, count: {}", id, i);
            }
        }, i);

        ts.push_back(std::move(t));
    }

    for(auto &t: ts) {
        t.join();
    }
    
    logger->info("finished");

    return 0;
}
