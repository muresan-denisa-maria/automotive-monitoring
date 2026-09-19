#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

class HttpClient
{
public:
    static bool postJson(
        const std::string& url,
        const std::string& jsonData
    );
};

#endif