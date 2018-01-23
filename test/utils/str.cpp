//
//  str.cpp
//  test
//
//  Created by Libero_Imac on 2018/01/23.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#include "str.hpp"

/**
 * split a string
 * @see - https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
 */
std::vector<std::string> str::split(const std::string& s, char demiliter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(s);
    while (getline(token_stream, token, demiliter)) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 *
 * search string
 * @see - https://cpplover.blogspot.jp/2015/01/c-stdregex.html
 */
std::vector<std::string> str::search(const std::string &text, const std::regex &re) {
    std::vector<std::string> result;
    std::sregex_iterator itr(text.cbegin(), text.cend(), re);
    std::sregex_iterator end;
    
    for (;itr != end;++itr) {
        result.push_back(itr->str());
    }
    return result;
}

