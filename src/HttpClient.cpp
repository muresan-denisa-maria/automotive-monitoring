#include "HttpClient.h"

#include <curl/curl.h>
#include <iostream>


bool HttpClient::postJson(
    const std::string& url,
    const std::string& jsonData
)
{
    CURL* curl =
        curl_easy_init();


    if (curl == nullptr)
    {
        return false;
    }


    struct curl_slist* headers =
        nullptr;


    headers =
        curl_slist_append(
            headers,
            "Content-Type: application/json"
        );


    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        url.c_str()
    );


    curl_easy_setopt(
        curl,
        CURLOPT_HTTPHEADER,
        headers
    );


    curl_easy_setopt(
        curl,
        CURLOPT_POSTFIELDS,
        jsonData.c_str()
    );


    CURLcode result =
        curl_easy_perform(
            curl
        );


    long responseCode =
        0;


    curl_easy_getinfo(
        curl,
        CURLINFO_RESPONSE_CODE,
        &responseCode
    );


    curl_slist_free_all(
        headers
    );


    curl_easy_cleanup(
        curl
    );


    if (result != CURLE_OK)
    {
        std::cout
            << "HTTP error: "
            << curl_easy_strerror(result)
            << std::endl;

        return false;
    }


    if (responseCode != 200)
    {
        std::cout
            << "HTTP response code: "
            << responseCode
            << std::endl;

        return false;
    }


    return true;
}