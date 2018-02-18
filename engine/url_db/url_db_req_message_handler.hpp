#pragma once

#include <zmq.hpp>

namespace usl::url_db
{
    class url_db_req_message_handler
    {
    public:
        zmq::message_t handle(const zmq::message_t& req);

    private:
        zmq::message_t get_for_processing(const zmq::message_t& req);
        zmq::message_t get(const zmq::message_t& req);
        zmq::message_t insert(const std::string& req);
    };
}
