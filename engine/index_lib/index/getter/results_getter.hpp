#pragma once

namespace usl::index
{
    namespace page_rank
    {
        class page_rank;
    }

    namespace getter
    {
        class results_getter
        {
        public:
            explicit results_getter(page_rank::page_rank& page_rank);

        private:
            page_rank::page_rank& m_page_rank;
        };
    }
}
