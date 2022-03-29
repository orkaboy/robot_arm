#include "bezier.hpp"
#include <string>

enum class Status {
    Ok = 0,
    Err = 1,
};

enum class Tests {
    BezierConstruct = 0,
};

auto BezierConstruct() -> Status {
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
    case Tests::BezierConstruct:
        ret = BezierConstruct(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
