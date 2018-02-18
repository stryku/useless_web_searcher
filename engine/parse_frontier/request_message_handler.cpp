#include "request_message_handler.hpp"

#include "file_to_parse_provider.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parse_frontier
{
    request_message_handler::request_message_handler(std::experimental::string_view working_directory)
        : m_file_provider{ working_directory.data() }
    {}

    zmq::message_t request_message_handler::handle(const zmq::message_t&)
    {
        LOG(INFO) << "Parse frontier handling message";

        boost::optional<std::string> file_to_parse;

        do
        {
            file_to_parse = m_file_provider.get_file_to_parse();
        } while(!file_to_parse);

        LOG(INFO) << "Parse frontier returning response with path: " << *file_to_parse;

        return zmq::message_t{ std::begin(*file_to_parse), std::end(*file_to_parse) };
    }
}
