#pragma once

#ifdef slots
#undef slots
#endif

#include <pybind11/embed.h>

#ifndef slots
#define slots Q_SLOTS
#endif

#include <iostream>
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

#include "../gfx/HTMLElements/HTMLElement.hpp"
#include "../../util/StringUtils.h"

#ifndef EM_TO_PX_CONVERSION
#define EM_TO_PX_CONVERSION 16
#endif

namespace py = pybind11;
using json = nlohmann::json;

class Stylesheet
{
public:
    Stylesheet() = delete;
    static void parse(const std::string& source);
    static std::optional<json> get(const std::string& selector);

public:
    template <typename T> static T computeAuto(T cV, T pV)
    {
        return (T)((pV - cV) / (T)2);
    }
    static int emToPx(std::string size);
    static int asPx(std::string size);

    template <typename T> static std::vector<T> forEach(json& props, std::string key, std::function<T(const std::string& s, int index)> f, std::string sep = " ")
    {
        std::vector<std::string> components = StringUtils::split(props[key], sep);
        std::vector<T> output;
        int index = 0;
        for (auto& c : components)
        {
            T result = f(c, index);
            ++index;
            output.push_back(result);
        }

        return output;
    }

private:
    static void getPythonExecutableVersion();
    static std::optional<json> stylesheet;
};

