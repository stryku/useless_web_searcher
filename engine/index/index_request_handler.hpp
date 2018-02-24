#pragma once

#include <zmq.hpp>

namespace usl::index
{
    class index_request_handler
    {
    public:
        zmq::message_t handle(const zmq::message_t& req);
    };
}