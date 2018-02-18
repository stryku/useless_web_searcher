#include "url_db_req_message_handler.hpp"

#include "url_db/url_db.hpp"
#include "url_db/db_entry_to_process.hpp"

#include <boost/property_tree/json_parser.hpp>

#include <easylogging/easylogging++.h>

#include <iterator>
#include <sstream>

namespace usl::url_db
{
    url_db_req_message_handler::url_db_req_message_handler(url_db& db)
        : m_db{ db }
    {}

    zmq::message_t url_db_req_message_handler::handle(const zmq::message_t& req)
    {
        const auto str_req = std::string{ req.data<const char>(), req.size() };
        std::istringstream iss{ str_req };

        boost::property_tree::ptree tree;
        boost::property_tree::read_json(iss, tree);

        const auto msg_type = tree.get<std::string>("type");
        if(msg_type == "insert")
        {
            return insert(tree);
        }
        if(msg_type == "get_for_processing")
        {
            return get_for_processing(tree);
        }

        return zmq::message_t();
    }

    zmq::message_t url_db_req_message_handler::get_for_processing(boost::property_tree::ptree& parsed_req)
    {
        auto to_process = m_db.get_for_processing();
        if(!to_process)
        {
            return zmq::message_t();
        }

        boost::property_tree::ptree tree;
        tree.put("url", to_process->url);
        tree.put("id", to_process->id);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);
        const auto str_resp = oss.str();
        LOG(INFO) << "url_db_req_message_handler get_for_processing sending: " << str_resp;

        return zmq::message_t{ std::cbegin(str_resp), std::cend(str_resp) };
    }

    zmq::message_t url_db_req_message_handler::get(boost::property_tree::ptree& parsed_req)
    {
        return zmq::message_t();
    }

    zmq::message_t url_db_req_message_handler::insert(boost::property_tree::ptree& parsed_req)
    {
        const auto url = parsed_req.get<std::string>("url");

        m_db.insert(url);

        const auto ok = string_view{ "ok" };

        return zmq::message_t{ std::cbegin(ok), std::cend(ok) };
    }
}
