#pragma once

#include "file_to_parse_provider.hpp"

#include <zmq.hpp>

#include <experimental/string_view>

namespace usl::parse_frontier
{
    class request_message_handler
    {
    public:
        explicit request_message_handler(std::experimental::string_view working_directory);

        zmq::message_t handle(const zmq::message_t&);

    private:
        file_to_parse_provider m_file_provider;
    };
}
