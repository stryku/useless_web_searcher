#include "common/index/index_interface.hpp"

#include "common/index/request_keys.hpp"

namespace usl::common::index
{

    index_interface::index_interface(const std::string &index)
        : common::communication::server::server_interface{ index }
    {}

    std::string index_interface::process_sentences(const std::string &site_data)
    {
        return send_and_recv(request_keys::k_process_sentences, "site_data", site_data);
    }
}
