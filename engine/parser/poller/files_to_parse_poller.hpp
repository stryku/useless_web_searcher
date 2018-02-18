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
        class files_to_parse_poller
        {
        public:
            explicit files_to_parse_poller();

            void run(const std::string& parse_frontier_address, content::content_parser& parser);

        private:
            zmq::socket_t m_socket;
        };
    }
}