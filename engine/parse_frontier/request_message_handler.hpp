#pragma once

#include <zmq.hpp>

namespace usl::parse_frontier
{
    class request_message_handler
    {
    public:
        zmq::message_t handle(const zmq::message_t&);
    };
}
