#pragma once

#include "common/string_view.hpp"
#include "url_db/url_db_offset.hpp"

#include <vector>

namespace usl::url_db
{
    class url_db_storage
    {
    public:
        using data_t = std::vector<uint8_t>;

        explicit url_db_storage(string_view working_directory);

        const data_t& data() const;
        const uint8_t* ptr(offset_t offset) const;

        void insert(const std::string& url);

    private:
        data_t m_data;
        const std::string m_data_file_path;
    };
}
