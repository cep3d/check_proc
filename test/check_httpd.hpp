//
//  check_httpd.hpp
//  test
//
//  Created by Takamasa Yano on 2018/01/21.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#ifndef check_httpd_hpp
#define check_httpd_hpp

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <curl/curl.h>

//static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
int check_httpd(const char *url);

#endif /* check_httpd_hpp */
