#include "request_message_handler.hpp"

namespace usl::parse_frontier
{
    zmq::message_t request_message_handler::handle(const zmq::message_t&)
    {
        return zmq::message_t{};
    }
}
