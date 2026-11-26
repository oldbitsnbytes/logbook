#include "playground.h"


auto main() -> int {
    auto r = playground::run();
    std::cout << "playground::run() returned: " << rem::to_string(r) << std::endl;
    return !!r ? 0:-1;
}
