//
//  str.hpp
//  test
//
//  Created by Libero_Imac on 2018/01/23.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#ifndef str_hpp
#define str_hpp

#include <string>
#include <vector>
#include <sstream>
#include <regex>

namespace str
{
    std::vector<std::string> split(const std::string& s, char demiliter);
    std::vector<std::string> search(const std::string &text, const std::regex &re);
}


#endif /* str_hpp */
