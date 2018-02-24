#pragma once

#include <boost/property_tree/ptree.hpp>

#include <zmq.hpp>

namespace usl::index
{
    namespace indexer
    {
        class indexer;
    }

    class index_request_handler
    {
    public:
        explicit index_request_handler(indexer::indexer& indexer);

        zmq::message_t handle(const zmq::message_t& req);

    private:
        zmq::message_t handle_process_sentences(boost::property_tree::ptree& parsed_request);
        zmq::message_t handle_get(boost::property_tree::ptree& parsed_request);

    private:
        indexer::indexer& m_indexer;
    };
}