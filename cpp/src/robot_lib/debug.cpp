#include "debug.hpp"
#include <fmt/core.h>

namespace ARC {

static bool DEBUG_ = false;

void DEBUG(bool value) {
    DEBUG_ = value;
    fmt::print("[DEBUG] Setting debug mode to {}.\n", value);
    if(value) {
        fmt::print("[DEBUG] Servos will not actuate.\n");
    }
}
auto DEBUG() -> bool {
    return DEBUG_;
}

}
