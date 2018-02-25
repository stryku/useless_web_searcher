#include "common/communication/server/server_factory.hpp"
#include "common/communication/server/server.hpp"
#include "common/communication/context.hpp"

#include <utility>

namespace usl::common::communication::server
{
    server server_factory::create(const std::string& bind_address) const
    {
        server s{ context };
        s.bind(bind_address);
        return std::move(s);
    }
}
