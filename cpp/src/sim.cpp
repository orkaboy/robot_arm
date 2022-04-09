#include <igl/opengl/glfw/Viewer.h>
#include <fmt/core.h>
#include <vector>
#include <string>

auto main(int argc, char* argv[]) -> int {
    if(argc < 2) {
        fmt::print("Fail, provide a filename\n");
        return 1;
    }
    std::string filepath = argv[1];
    std::vector<std::string> files = {
        "LP_first_arm.stl",
        "LP_first_connector.stl",
        "LP_first_joint.stl",
        "LP_second_arm.stl",
        "LP_second_connector.stl",
    };

    igl::opengl::glfw::Viewer viewer;
    for(const auto& f : files) {
        viewer.load_mesh_from_file(fmt::format("{}/{}", filepath, f));
    }
    viewer.data().set_face_based(true);
    viewer.launch();

    return 0;
}
