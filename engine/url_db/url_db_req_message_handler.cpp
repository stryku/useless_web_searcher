#include "url_db_req_message_handler.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <easylogging/easylogging++.h>

#include <sstream>

namespace usl::url_db
{

    zmq::message_t url_db_req_message_handler::handle(const zmq::message_t& req)
    {
        const auto str_req = std::string{ req.data<const char>(), req.size() };
        std::istringstream iss{ str_req };

        namespace pt = boost::property_tree;

        pt::ptree tree;

        pt::read_json(iss, tree);

        if(tree.get<std::string>("type") == "insert")
        {
            return insert(tree.get<std::string>("url"));
        }

        return zmq::message_t();
    }

    zmq::message_t url_db_req_message_handler::get_for_processing(const zmq::message_t& req)
    {
        return zmq::message_t();
    }

    zmq::message_t url_db_req_message_handler::get(const zmq::message_t& req)
    {
        return zmq::message_t();
    }

    zmq::message_t url_db_req_message_handler::insert(const std::string& req)
    {
        return zmq::message_t();
    }
}
