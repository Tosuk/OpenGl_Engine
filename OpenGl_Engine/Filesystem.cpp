#include "Filesystem.h"

std::string Filesystem::get_Path(const std::string& path)
{
    static std::string(*pathBuilder)(std::string const &) = getPathBuilder();
    return std::string();
}

std::string const& Filesystem::getRoot()
{
    // TODO: hier return-Anweisung eingeben
    static char const* envRoot = getenv("C:/Users/Max/Documents/Visual Studio 2017/Projects/OpenGl_Engine/OpenGl_Engine/"); // Set the root path
    static char const * givenRoot = (envRoot != nullptr ? envRoot : logl_root); // Set the root path
    static std::string root = (givenRoot != nullptr ? givenRoot : ""); // Set the root path
    return root;
}
 