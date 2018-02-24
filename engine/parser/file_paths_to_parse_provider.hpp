#pragma once

#include <zmq.hpp>

namespace usl::parser
{
    namespace data
    {
        class parse_data_handler;
    }

    class file_paths_to_parse_provider
    {
    public:
        explicit file_paths_to_parse_provider(const std::string& parse_frontier_address);

        std::string get();

    private:
        zmq::socket_t m_socket;
    };
}