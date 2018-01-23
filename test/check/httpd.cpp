//
//  check_httpd.cpp
//  test
//
//  Created by Takamasa Yano on 2018/01/21.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#include "httpd.hpp"

namespace check
{
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
    
    int httpd(const char *url) {
        CURL *curl;
        CURLcode code;
        std::string readBuffer;
        std::string header;
        
        std::cout << "Check URL:" << url << std::endl;
        
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
                arr = str::split(header, '\n');
                std::cout << arr.at(0) << std::endl;
            } else {
                return -1;
            }
        }
        return 0;
    }
}
