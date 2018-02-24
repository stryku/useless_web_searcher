#pragma once

#include "common/communication/server/server_interface.hpp"
#include "common/db/url_id.hpp"

#include <string>
#include <sstream>

namespace usl::common::index
{
    class index_interface : public communication::server::server_interface
    {
    public:
        explicit index_interface(const std::string& db_address);

        std::string process_sentences(const std::string& site_data);
    };
}
