#include <igl/opengl/glfw/Viewer.h>
#include <fmt/core.h>
#include <vector>
#include <string>
#include <map>

Eigen::RowVector3d RandomColor() {
    return 0.5*Eigen::RowVector3d::Random().array() + 0.5;
}

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

    std::map<int, Eigen::RowVector3d> colors;
    
    igl::opengl::glfw::Viewer viewer;
    for(const auto& f : files) {
        viewer.load_mesh_from_file(fmt::format("{}/{}", filepath, f));
        colors.emplace(viewer.data().id, RandomColor());
    }
    // Assign random colors to each mesh
    for (auto &data : viewer.data_list) {
        data.set_colors(colors[data.id]);
    }
    int x{};
    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer &vr) {
        return false;
    };

    viewer.core().is_animating = true;
    viewer.core().animation_max_fps = 30.f;
    viewer.launch();

    return 0;
}
