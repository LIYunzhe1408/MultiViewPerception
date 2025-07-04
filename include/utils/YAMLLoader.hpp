#pragma once
#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>

namespace perception::utils {

std::vector<std::string> load_class_names_from_yaml(const std::string& path);

}
