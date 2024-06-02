#include <iostream>
#include <string>

#define ASIO_STANDALONE
#include "crow_all.h"

#include "utils.h"
#include "index.h"

int main(int argc, char** argv) {
    crow::App<crow::CORSHandler> app;

    // Customize CORS
    auto& cors = app.get_middleware<crow::CORSHandler>();

    // clang-format off
    cors
        .global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
        .methods("POST"_method, "GET"_method)
        .origin("*");

    startCacheThread();

    CROW_ROUTE(app, "/")([]() {
        return indexFile;
        });

    CROW_ROUTE(app, "/data")([]() {
        crow::json::wvalue x({});
        x["cores"] = getCpuCores();
        x["cpu"] = getCpuUssage();
        x["memory"] = getMemUssage();
        x["swap"] = getSwapUssage();
        x["uptime"] = getUptime();

        return x;
        });

    app.port(18080).multithreaded().run();
}