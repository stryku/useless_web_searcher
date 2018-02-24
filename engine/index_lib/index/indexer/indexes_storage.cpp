#include "index/indexer/indexes_storage.hpp"
#include "index/indexer/index_file.hpp"
#include "index/index_file_path_builder.hpp"

#include <numeric>

#include <boost/filesystem.hpp>

namespace usl::index::indexer
{
    indexes_storage::indexes_storage(const std::string &working_directory)
        : m_indexes_dir{ working_directory + "/index/indexes" }
    {
        boost::filesystem::create_directories(m_indexes_dir);
    }


    void indexes_storage::new_hit(indexes_storage::word_iterator_t words_begin,
                                  indexes_storage::word_iterator_t words_end,
                                  common::db::url_id_t id) const
    {
        const auto path = index_file_path_builder{}.build(m_indexes_dir, words_begin, words_end);
        const auto file = index_file{ path };
        file.new_hit(id);
    }
}
