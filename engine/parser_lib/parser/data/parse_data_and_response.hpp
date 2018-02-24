#pragma once

#include "common/utils/enable_private_creation.hpp"
#include "parser/data/parse_data.hpp"
#include "parser/response/unique_response.hpp"

#include <memory>

namespace usl::parser::data
{
    class parse_data_and_response_factory;

    class parse_data_and_response : protected enable_private_creation<parse_data_and_response>
    {
    private:
        using this_t = parse_data_and_response;
        using private_creation_t = enable_private_creation<this_t>;

    public:
        parse_data_and_response(private_creation_t,
                                parse_data data,
                                response::unique_response response);

        parse_data_and_response(const parse_data_and_response&) = delete;
        parse_data_and_response& operator=(const parse_data_and_response&) = delete;

        parse_data_and_response(parse_data_and_response&&) = default;
        parse_data_and_response& operator=(parse_data_and_response&&) = default;

        const parse_data& data() const;


    private:
        friend class parse_data_and_response_factory;

        static std::shared_ptr<parse_data_and_response> create(parse_data data, response::unique_response response);

    private:
        const parse_data& m_data;
        const response::unique_response m_response;
    };
}
