#pragma once

#include <zmq.hpp>

namespace usl::parser
{
    namespace content
    {
        class content_parser;
    }

    namespace poller
    {
        class file_paths_to_parse_provider
        {
        public:
            explicit file_paths_to_parse_provider();

            void run(const std::string& parse_frontier_address, content::content_parser& parser);

        private:
            zmq::socket_t m_socket;
        };
    }
}