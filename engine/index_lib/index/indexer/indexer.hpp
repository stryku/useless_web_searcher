#pragma once

#include <string>

namespace usl::index::indexer
{
    struct parsed_site_data;

    class indexer
    {
    public:
        // Accepts json: { url: id, referenced_urls: { url: id, url: id... }, sentences [ sentence, sentence... ] }
        void index(const std::string& site_data);

    private:
        parsed_site_data parse_site_data(const std::string& site_data) const;
    };
}