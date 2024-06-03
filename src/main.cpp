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
        return getIndexPage();
        });

    CROW_ROUTE(app, "/data")([]() {
        return "'/data' is deprecated. Use websockets '/ws'";
        });

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onaccept([&](const crow::request& req, void** userdata) {
            return true;
            })
        .onmessage([&](crow::websocket::connection& conn, const std::string& message, bool is_binary) {
            if (!is_binary && message == "update") {
                conn.send_text(getJson().dump());
                return true;
            }
            return true;
            });

    app.port(18080).multithreaded().run();
}