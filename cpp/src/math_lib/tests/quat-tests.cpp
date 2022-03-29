#include "quat.hpp"
#include "testbench.hpp"

enum class Tests {
    QuatConstruct = 0,
};

auto QuatConstruct() -> Status {
    return Status::Err;
}


auto main(int argc, char* argv[]) -> int {
    if(argc != 2) {
        return static_cast<int>(Status::Err);
    }
    auto test = static_cast<Tests>(std::stoi(argv[1]));

    Status ret = Status::Err;

    switch (test)
    {
    case Tests::QuatConstruct:
        ret = QuatConstruct(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
