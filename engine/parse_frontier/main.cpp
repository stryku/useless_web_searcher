#include "common/communication/server/server_factory.hpp"
#include "common/communication/server/server.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        std::cout << "usage: parse_frontier working_directory_path bind_ip";
        return 1;
    }


    const auto working_directory = argv[1];
    const auto bind_address = argv[2];
    auto server = usl::common::communication::server::server_factory{}.create(bind_address);

    return 0;
}