#include "Stylesheet.hpp"

std::optional<json> Stylesheet::stylesheet = std::nullopt;

void Stylesheet::parse(const std::string &source)
{
    py::scoped_interpreter guard{};
    try
    {
        // Get the absolute path to the python directory
        std::filesystem::path pythonDir = std::filesystem::absolute("../src/python");
        std::string pythonDirStr = pythonDir.string();

        // Append the absolute path to sys.path
        py::module::import("sys").attr("path").attr("append")(pythonDirStr);

        // Ensure the virtual environment is used
        // TODO: Make a script that sets up a python environment if none is found.
        //       It should also then link to it and then store the config in a JSON file which can
        //       be parsed so I don't re-create the environment and I can store python modules if needed.
        py::module::import("sys").attr("path").attr("insert")(0, "/Volumes/2TB SSD/Resume Projects/git/browser/virtualenv/pythonEnv/lib/python3.12/site-packages");
        py::module parser = py::module::import("cssParser");
        py::object result = parser.attr("parse_css")(source);
        auto jsonString = result.cast<std::string>();
        json parsedCSS = json::parse(jsonString);

        json formattedStylesheet = json::object();
        if (parsedCSS.is_array())
        {
            json innerJSON;
            for (auto& e : parsedCSS)
            {
                innerJSON["properties"] = e["properties"];
                std::string selectorName = e["selector"];

                // Handle multi-selector names
                std::vector<std::string> tokens = StringUtils::split(e["selector"], ",");

                // For every token (name) we see in the selector,
                // just use the same inner JSON.
                // This does technically create bloat though...
                // TODO: Maybe fix bloat and find a better way to search in the JSON.
                for (auto& token : tokens)
                {
                    token = StringUtils::strip(token);
                    formattedStylesheet[token] = innerJSON;
                }
            }
        }

        // If the stylesheet already exists, then merge it with
        // the results to create a big dictionary.
        // TODO: How to reconcile conflicting selectors?....
        if (stylesheet.has_value())
        {
            stylesheet->merge_patch(formattedStylesheet);
        }
        else
        {
            stylesheet = std::make_optional<json>(formattedStylesheet);
        }

    } catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::optional<json> Stylesheet::get(const std::string &selector)
{
    if (stylesheet.has_value())
    {
        return (*stylesheet)[selector];
    }
    return std::nullopt;
}

int Stylesheet::emToPx(std::string size)
{
    if (size.ends_with("em"))
    {
        std::string numericSubstr = size.substr(0, size.find("em"));
        return (int)(std::stof(numericSubstr) * (float)EM_TO_PX_CONVERSION);
    }
    return 0;
}

int Stylesheet::asPx(std::string size)
{
    if (size.ends_with("em"))
    {
        return Stylesheet::emToPx(size);
    }
    if (size.ends_with("px"))
    {
        return std::stoi(StringUtils::stripEnd(size, "px"));
    }

    return 0;
}

void Stylesheet::getPythonExecutableVersion()
{
    py::scoped_interpreter guard{};
    py::object sys = py::module::import("sys");
    std::string python_executable = sys.attr("executable").cast<std::string>();
    std::cout << "Using Python executable: " << python_executable << std::endl;
}