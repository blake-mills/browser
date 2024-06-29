#pragma once

// libxml2 includes
#include <libxml/HTMLparser.h>
#include <libxml/tree.h>

// stdlib includes
#include <string>

namespace XMLUtils
{
    static bool isWhitespaceOnly(const xmlChar *content)
    {
        std::string text = reinterpret_cast<const char *>(content);
        return std::all_of(text.begin(), text.end(), ::isspace);
    }
}