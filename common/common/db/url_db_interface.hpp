#pragma once

#include "common/communication/context.hpp"

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
        std::string get(size_t id);

    private:
        zmq::socket_t m_socket;
    };
}
