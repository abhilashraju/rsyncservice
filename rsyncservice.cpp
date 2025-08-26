#include <reactor/command_line_parser.hpp>
#include <reactor/file_watcher.hpp>
#include <reactor/logger.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
namespace net = boost::asio;
int main(int argc, const char* argv[])
{
    reactor::getLogger().setLogLevel(reactor::LogLevel::DEBUG);
    auto [src, dest] = reactor::getArgs(reactor::parseCommandline(argc, argv),
                                        "--src,-s", "--dest,-d");
    if (!src || !dest)
    {
        LOG_ERROR("Args missing: Usage {} <{}> <{}>", argv[0],
                  src.value().data(), dest.value().data());
    }
    net::io_context io_context;
    reactor::FileWatcher watcher(io_context.get_executor());
    watcher.addToWatchRecursive(src.value().data());
    std::string dests(dest.value().data());
    auto watcherFunc =
        [dests](std::string path, reactor::FileWatcher::FileStatus status) {
            LOG_INFO("Change detected: {} Event: {}", path,
                     static_cast<int>(status));

            std::string cmd =
                std::format("rsync -av --delete --relative {} {}", path, dests);
            int ret = std::system(cmd.c_str());
            if (ret != 0)
            {
                LOG_ERROR("Rsync command failed with code: {}", ret);
            }
        };

    net::co_spawn(
        io_context,
        [&]() -> net::awaitable<void> {
            co_await reactor::watchFileChanges(watcher, watcherFunc);
        },
        net::detached);
    io_context.run();

    return 0;
}
