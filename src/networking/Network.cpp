#include "./Network.hpp"

std::optional<json> Network::get(const std::string &url)
{
    ostringstream stream;
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(stream);

    // Declaration of an easy object
    curl_easy easy(ios);

    // Add some option to the curl_easy object.
    easy.add<CURLOPT_URL>(url.c_str());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try
    {
        easy.perform();

        auto responseCode = easy.get_info<CURLINFO_RESPONSE_CODE>();
        if (responseCode.get() == 200)
        {
            return parseHTML(stream.str());
        } else
        {
            std::cerr << "Got not 200 response code back: " << responseCode.get() << std::endl;
            return std::nullopt;
        }

    } catch (curl_easy_exception &error)
    {
        std::cerr << error.what() << std::endl;
        error.print_traceback();
        return std::nullopt;
    }
}

std::optional<json> Network::parseHTML(const std::string &html) {
    htmlDocPtr doc = htmlReadMemory(html.c_str(), (int)html.size(), nullptr, nullptr, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == nullptr) {
        return std::nullopt;
    }

    xmlNode* root_element = xmlDocGetRootElement(doc);
    std::optional<json> result = htmlNodeToJSON(root_element);

    xmlFreeDoc(doc);
    xmlCleanupParser();

    return result;
}

std::optional<json> Network::htmlNodeToJSON(xmlNode* node) {
    json j;

    try {
        for (xmlNode* cur = node; cur; cur = cur->next) {
            if (cur->type == XML_ELEMENT_NODE) {
                json element;
                element["type"] = "element";
                element["tag"] = reinterpret_cast<const char*>(cur->name);

                json attributes = json::object();
                for (xmlAttr* attr = cur->properties; attr; attr = attr->next) {
                    xmlChar* value = xmlNodeListGetString(cur->doc, attr->children, 1);
                    attributes[reinterpret_cast<const char*>(attr->name)] = reinterpret_cast<const char*>(value);
                    xmlFree(value);
                }
                element["attributes"] = attributes;

                element["children"] = htmlNodeToJSON(cur->children).value_or(json::array());
                j.push_back(element);
            } else if (cur->type == XML_TEXT_NODE) {
                if (!XMLUtils::isWhitespaceOnly(cur->content)) {
                    json text;
                    text["type"] = "text";
                    text["text"] = reinterpret_cast<const char*>(cur->content);
                    j.push_back(text);
                }
            } else if (cur->type == XML_COMMENT_NODE) {
                json comment;
                comment["type"] = "comment";
                comment["text"] = reinterpret_cast<const char*>(cur->content);
                j.push_back(comment);
            } else if (cur->type == XML_PI_NODE || cur->type == XML_CDATA_SECTION_NODE) {
                // Handle processing instructions and CDATA sections
                json pi;
                pi["type"] = "pi";
                pi["text"] = reinterpret_cast<const char*>(cur->content);
                j.push_back(pi);
            }
        }
    } catch (std::exception& e) {
        return std::nullopt;
    }

    return std::make_optional(j);
}