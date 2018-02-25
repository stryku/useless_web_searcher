#include "parser/response/unique_response.hpp"

#include "common/db/url_db_interface.hpp"
#include "common/index/index_interface.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::response
{
    unique_response::unique_response(const std::string &db_address,
                                     const std::string& index_address,
                                     common::db::url_id_t processed_id)
        : m_db_address{ db_address }
        , m_processed_id{ processed_id }
        , m_index_address{ index_address }
    {
        LOG(INFO) << "unique_response: " << m_processed_id;
    }

    unique_response::~unique_response()
    {
        LOG(INFO) << "~unique_response: " << m_processed_id;

        common::index::index_interface index_interface{ m_index_address };
        index_interface.process_sentences(m_sentences, m_extracted_urls, m_processed_id);

        common::db::url_db_interface db_interface{ m_db_address };
        (void)db_interface.update_state_as_processed(m_processed_id);
    }

    void unique_response::set_sentences(std::vector<std::vector<std::string>> sentences)
    {
        m_sentences = std::move(sentences);
    }

    void unique_response::set_extracted_urls(std::unordered_set<common::db::url_id_t> urls)
    {
        m_extracted_urls = std::move(urls);
    }
}

