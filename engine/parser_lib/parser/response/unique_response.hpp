#pragma once

#include "common/db/url_id.hpp"

#include <string>
#include <unordered_set>
#include <vector>

namespace usl::parser::response
{
    class unique_response
    {
    public:
        explicit unique_response(const std::string& db_address,
                                 const std::string& index_address,
                                 common::db::url_id_t processed_id);

        unique_response(const unique_response&) = delete;
        unique_response& operator=(const unique_response&) = delete;

        unique_response(unique_response&&) = default;
        unique_response& operator=(unique_response&&) = default;

        ~unique_response();

        void set_sentences(std::vector<std::vector<std::string>> sentences);
        void set_extracted_urls(std::unordered_set<common::db::url_id_t> urls);

    private:
        const std::string m_db_address;
        const std::string m_index_address;
        const common::db::url_id_t m_processed_id;
        std::vector<std::vector<std::string>> m_sentences;
        std::unordered_set<common::db::url_id_t> m_extracted_urls;
    };
}
