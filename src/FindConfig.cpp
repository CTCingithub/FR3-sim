#include <string>
#include <filesystem>
#include <pybind11/pybind11.h>

#include "yaml-cpp/yaml.h"

std::string FindConfigFile(const std::filesystem::path &CurrentPath)
{
    if (CurrentPath.filename() == "bin")
    {
        return CurrentPath.parent_path().string() + "/config/PD_Control.yaml";
    }
    else
    {
        return CurrentPath.string() + "/config/PD_Control.yaml";
    }
}

YAML::Node GetConfig(const std::string &ConfigurationFile)
{
    YAML::Node config = YAML::LoadFile(ConfigurationFile);
    return config;
}

PYBIND11_MODULE(find_config, m1)
{
    m1.doc() = "FindConfigFile";
    m1.def("FindConfigFile", &FindConfigFile, "Find default configuration file");
}

PYBIND11_MODULE(get_config, m2)
{
    m2.doc() = "GetConfig";
    m2.def("GetConfig", &GetConfig, "Get specific configuration file");
}
