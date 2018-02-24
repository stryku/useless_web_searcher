#pragma once

#include "common/communication/context.hpp"
#include "common/db/url_id.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <easylogging/easylogging++.h>

#include <zmq.hpp>

#include <string>
#include <sstream>

namespace usl::common::db
{
    class url_db_interface
    {
    public:
        explicit url_db_interface(const std::string& db_address);

        std::string insert(const std::string& url);
        std::string get(common::db::url_id_t id);
        std::string update_state_as_processed(common::db::url_id_t id);

    private:
        template <typename T, typename = std::enable_if_t<!std::is_same<T, std::string>::value>>
        std::string send_and_recv(const std::string& type, const std::string& field, const T& field_value)
        {
            return send_and_recv(type, field, std::to_string(field_value));
        }

        std::string send_and_recv(const std::string& type, const std::string& field, const std::string& field_value);

    private:
        zmq::socket_t m_socket;
    };
}
