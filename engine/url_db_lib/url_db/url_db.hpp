#pragma once

#include "common/string_view.hpp"

#include "db_entry.hpp"

#include <boost/optional.hpp>

#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <string>
#include <vector>

namespace usl
{
    namespace url_db
    {
        class url_db
        {
        public:
            using id_t = uint64_t;
            using url_t = std::string;

            static url_db load_from_data(const std::vector<uint8_t>& data);

        private:
            using offset_t = uint64_t;

            static boost::optional<db_entry> load_next_entry(const std::vector<uint8_t>& data, offset_t pos);

            std::unordered_map<id_t, offset_t> m_id_to_offset;
            std::unordered_set<url_t> m_urls;
        };
    }
}
