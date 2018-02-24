#pragma once

#include "parser/data/parse_data.hpp"
#include "parser/response/unique_response.hpp"

namespace usl::parser::data
{
    class parse_data_and_response
    {
    public:
        parse_data_and_response(const parse_data_and_response&) = delete;
        parse_data_and_response& operator=(const parse_data_and_response&) = delete;

        parse_data_and_response(parse_data_and_response&&) = default;
        parse_data_and_response& operator=(parse_data_and_response&&) = default;

        const parse_data& data() const;


    private:
        parse_data_and_response(parse_data data, response::unique_response m_response);


        const parse_data& m_data;
        const response::unique_response m_response;
    };
}
