#pragma once

#include <string>

namespace usl::common::communication::server
{
    class server;

    class server_factory
    {
    public:
        server create(std::string_view bind_address) const;
    };
}
