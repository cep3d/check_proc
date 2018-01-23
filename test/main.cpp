//
//  main.cpp
//  test
//
//  Created by Mikan2081 on 2018/01/19.
//  Copyright © 2018 Minak2081. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include "check/mysqld.hpp"
#include "check/httpd.hpp"

int main(int argc, char *argv[]) {

  int result = 0, cmd;
  
  while ((cmd = getopt(argc, argv, "a:h")) != -1) {
    switch (cmd) {
      case 'a':
        result = check_mysqld();
        result = check::httpd(optarg);
        break;
      case 'h':
        std::cout << "Usage: ";
        std::cout << "./test [-a] http://google.co.jp" << std::endl;
        break;
    }
  }
  
  return result;
}
