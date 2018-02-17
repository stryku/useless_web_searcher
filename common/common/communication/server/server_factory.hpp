#pragma once

#include <experimental/string_view>

namespace usl::common::communication::server
{
    class server;

    class server_factory
    {
    public:
        server create(std::experimental::string_view bind_address) const;
    };
}
