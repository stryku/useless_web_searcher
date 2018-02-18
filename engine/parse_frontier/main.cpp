#include "common/communication/server/server_factory.hpp"
#include "common/communication/server/server.hpp"
#include "request_message_handler.hpp"

#include <easylogging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        LOG(ERROR) << "usage: parse_frontier working_directory_path bind_ip";
        return 1;
    }

    const auto working_directory = argv[1];
    const auto bind_address = argv[2];
    auto server = usl::common::communication::server::server_factory{}.create(bind_address);

    server.set_message_handler(usl::parse_frontier::request_message_handler{});

    server.run();

    return 0;
}