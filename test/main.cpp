//
//  main.cpp
//  test
//
//  Created by Mikan2081 on 2018/01/19.
//  Copyright © 2018 Minak2081. All rights reserved.
//

#include <iostream>
#include "check_mysqld.hpp"
#include "check_httpd.hpp"


int main(int argc, const char * argv[]) {

  int httpd, mysqld;
  
  mysqld = check_mysqld();
  httpd = check_httpd("http://google.com");
  
  return 0;
}
