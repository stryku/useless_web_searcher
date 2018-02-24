#include <boost/shared_ptr.hpp>
#include <parser/response/unique_response.hpp>
#include "parser/data/parse_data_and_response.hpp"
#include "parse_data.hpp"

namespace usl::parser::data
{
    const parse_data &parse_data_and_response::data() const
    {
        return m_data;
    }

    parse_data_and_response::parse_data_and_response(private_creation_t,
                                                     parse_data data,
                                                     std::unique_ptr<response::unique_response> response)
        : m_data(data)
        , m_response{ std::move(response) }
    {}

    std::shared_ptr<parse_data_and_response> parse_data_and_response::create(parse_data data,
                                                                             std::unique_ptr<response::unique_response> response)
    {
        return std::make_shared<parse_data_and_response>(private_creation_t{},
                                                         data,
                                                         std::move(response));
    }
}
