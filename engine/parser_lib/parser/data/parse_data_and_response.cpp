#include "parser/data/parse_data_and_response.hpp"

namespace usl::parser::data
{
    const parse_data &parse_data_and_response::data() const
    {
        return m_data;
    }

    parse_data_and_response::parse_data_and_response(parse_data data, response::unique_response response)
        : m_data(std::move(data))
        , m_response{ std::move(response) }
    {}
}
