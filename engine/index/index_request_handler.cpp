#include "index_request_handler.hpp"

#include <easylogging/easylogging++.h>

namespace usl::index
{
    zmq::message_t index_request_handler::handle(const zmq::message_t &req)
    {
        LOG(INFO) << "index_request_handler handling";

        return zmq::message_t();
    }
}
