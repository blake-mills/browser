#pragma once

// Curl includes
#include <curlcpp/curl_easy.h>
#include <curlcpp/curl_ios.h>
#include <curlcpp/curl_exception.h>

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_ios;

// libxml2 includes
#include <libxml/HTMLparser.h>
#include <libxml/tree.h>

// nlohmann includes
#include "../../include/json.hpp"

using json = nlohmann::json;

// stdlib includes
#include <sstream>
#include <string>
#include <string_view>
#include <optional>

using std::ostringstream;

// Local includes
#include "../util/XMLUtils.hpp"

class Network
{
public:
    Network() = delete;
    static std::optional<json> get(const std::string& url);
private:
    static std::optional<json> parseHTML(const std::string& html);
    static std::optional<json> htmlNodeToJSON(xmlNode* node);
};