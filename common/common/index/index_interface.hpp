#pragma once

#include "common/communication/server/server_interface.hpp"
#include "common/db/url_id.hpp"

#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace usl::common::index
{
    class index_interface : public communication::server::server_interface
    {
    public:
        explicit index_interface(const std::string& index_address);

        std::string process_sentences(const std::vector<std::vector<std::string>>& sentences,
                                      const std::unordered_set<common::db::url_id_t>& extracted_urls,
                                      common::db::url_id_t id);

        using get_results_result = std::unordered_map<common::db::url_id_t, double>;

        get_results_result get_results(const std::vector<std::string>& words);

    private:
        std::string format_process_sentences_msg(const std::vector<std::vector<std::string>>& sentences,
                                                 const std::unordered_set<common::db::url_id_t>& extracted_urls,
                                                 common::db::url_id_t id) const;

        std::string format_get_results(const std::vector<std::string>& words) const;
    };
}
