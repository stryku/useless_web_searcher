#pragma once

#include <boost/property_tree/ptree.hpp>

#include <zmq.hpp>

namespace usl::index
{
    class index_request_handler
    {
    public:
        zmq::message_t handle(const zmq::message_t& req);

    private:
        zmq::message_t handle_process_sentences(boost::property_tree::ptree& parsed_request);

    };
}