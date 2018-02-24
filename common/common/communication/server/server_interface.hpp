#pragma once

#include "common/communication/context.hpp"

#include <zmq.hpp>

#include <string>

namespace usl::common::communication::server
{
    class server_interface
    {
    public:
        explicit server_interface(const std::string& address);

    protected:
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
