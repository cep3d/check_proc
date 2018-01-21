//
//  check_mysqld.cpp
//  test
//
//  Created by Takamasa Yano on 2018/01/21.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#include "check_mysqld.hpp"


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
