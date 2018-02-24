#pragma once

#include <boost/property_tree/ptree.hpp>

#include <zmq.hpp>

namespace usl::url_db
{
    class url_db;

    class url_db_req_message_handler
    {
    public:
        explicit url_db_req_message_handler(url_db& db);

        zmq::message_t handle(const zmq::message_t& req);

    private:
        zmq::message_t get_for_processing(boost::property_tree::ptree& parsed_req);
        zmq::message_t get(boost::property_tree::ptree& parsed_req);
        zmq::message_t insert(boost::property_tree::ptree& parsed_req);
        zmq::message_t update_state_as_processed(boost::property_tree::ptree& parsed_req);

        zmq::message_t get_ok_message() const;

    private:
        url_db& m_db;
    };
}
