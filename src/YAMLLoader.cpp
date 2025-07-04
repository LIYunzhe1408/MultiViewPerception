#include "utils/YAMLLoader.hpp"
#include <iostream>

namespace perception::utils {

std::vector<std::string> load_class_names_from_yaml(const std::string& path) {
    std::vector<std::string> class_names;

    try {
        YAML::Node config = YAML::LoadFile(path);
        const YAML::Node& names = config["names"];
        class_names.resize(80);  // you can also auto-resize based on max key

        for (YAML::const_iterator it = names.begin(); it != names.end(); ++it) {
            int id = it->first.as<int>();
            std::string name = it->second.as<std::string>();
            if (id >= class_names.size()) class_names.resize(id + 1);
            class_names[id] = name;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load YAML file: " << e.what() << std::endl;
    }

    return class_names;
}

}
