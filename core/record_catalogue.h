#pragma once

#include <deque>

#include "domain.h"

namespace cafeteria_app {
    namespace database {
        using namespace domain::standardized_types;

        class RecordCatalogue {
        public:
            RecordCatalogue(/* args */);
            ~RecordCatalogue();
        private:
            std::deque<domain::standardized_types::Session> sessions_;
            std::deque<domain::components::Identifiable::Type> buffer_;
        };
    } //namespace database
} //namespace cafeteria_app


