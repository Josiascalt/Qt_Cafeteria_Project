#ifndef API_H
#define API_H

#pragma once

#include "request_handler.h"

namespace cafeteria_app {
    using CoreHandler = cafeteria_app::request::RequestHandler;

    CoreHandler Start();
} //namespace cafeteria_app
#endif //API_H
