#pragma once

#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <string>

namespace usl::url_db
{
    class url_db
    {
    public:
        using id_t = uint64_t;
        using url_t = std::string;

        static url_db load_from_file();

    private:
        using offset_t = uint64_t;

        std::unordered_map<id_t, offset_t> m_id_to_offset;
        std::unordered_set<url_t> m_urls;
    };
}
