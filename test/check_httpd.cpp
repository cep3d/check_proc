//
//  check_httpd.cpp
//  test
//
//  Created by Takamasa Yano on 2018/01/21.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#include "check_httpd.hpp"

/**
 * split a string
 * @see - https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
 */
std::vector<std::string> split(const std::string& s, char demiliter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(s);
    while (std::getline(token_stream, token, demiliter)) {
        tokens.push_back(token);
    }
    return tokens;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int check_httpd(const char *url) {
    CURL *curl;
    CURLcode code;
    std::string readBuffer;
    std::string header;
    
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
        code = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        std::vector<std::string> arr;
        
        if (code == CURLE_OK) {
            arr = split(header, '\n');
            std::cout << arr.at(0) << std::endl;
        } else {
            return -1;
        }
    }
    return 0;
}
