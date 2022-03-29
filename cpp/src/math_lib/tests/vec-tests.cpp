#include "vec.hpp"
#include <string>

enum class Status {
    Ok = 0,
    Err = 1,
};

enum class Tests {
    Vec3Construct = 0,
};

auto Vec3Construct() -> Status {
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
    case Tests::Vec3Construct:
        ret = Vec3Construct(); break;
    default:
        break;
    }

    return static_cast<int>(ret);
}
