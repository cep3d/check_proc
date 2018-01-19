//
//  main.cpp
//  test
//
//  Created by Mikan2081 on 2018/01/19.
//  Copyright © 2018 Minak2081. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <curl/curl.h>
#include <mysql.h>

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

int check_mysqld() {
  MYSQL *con;
  MYSQL_RES *res;
  MYSQL_ROW rows;
  const char *host = "localhost";
  const char *user = "root";
  const char *pass = "";
  const char *db = "mysql";
  unsigned int port = 3306;
  const char *socket = NULL;
  unsigned long flag = 0;
  int result = 0;
  
#if DEBUG
  std::cout << "Start Connecting..." << std::endl;
#endif
  
  // initalize
  con = mysql_init(NULL);
  // connection
  if (!mysql_real_connect(con, host, user, pass, db, port, socket, flag)) {
    std::cerr << mysql_error(con) << std::endl;
    result = -1;
  }
  
  // query
  const char *query = "SHOW ENGINE INNODB STATUS";
  if (mysql_real_query(con, query, strlen(query))) {
    std::cerr << mysql_error(con) << std::endl;
    result = -1;
  }
  if (result < 0) {
#if DEBUG
    std::cerr << "Connection failed" << std::endl;
#endif
    return result;
  }

  res = mysql_use_result(con);
  
  int i = 0;
  long fields = 0;
  fields = mysql_num_fields(res);
  while ((rows = mysql_fetch_row(res)) != NULL) {
    for (i = 0; i < fields; ++i) {
      char *row = rows[i];
      std::cout << row << std::endl;
    }
  }
  
  // release
  mysql_free_result(res);
  
  // close connection
  mysql_close(con);
  return result;
}

int check_httpd() {
  CURL *curl;
  CURLcode code;
  std::string readBuffer;
  std::string header;
  
#if DEBUG
  std::cout << "Obtaining proccess http and mysql..." << std::endl;
#endif
  
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://google.co.jp");
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


int main(int argc, const char * argv[]) {

  int httpd, mysqld;
  
  httpd = check_httpd();
  mysqld = check_mysqld();
  
  return 0;
}
