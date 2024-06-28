#pragma once

#include <curlcpp/curl_easy.h>
#include <curlcpp/curl_ios.h>
#include <curlcpp/curl_exception.h>
#include <sstream>
#include <string>

using std::ostringstream;

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_ios;


class Network
{
public:
    Network() {}
    static void get(const std::string& url);
private:
    
};