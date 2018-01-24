//
//  check_mysqld.hpp
//  test
//
//  Created by Takamasa Yano on 2018/01/21.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#ifndef check_mysqld_hpp
#define check_mysqld_hpp

#include <iostream>
#include <string>
#include <algorithm>
#include <mysql.h>
#include <regex>
#include "../utils/str.hpp"

namespace check
{
    typedef struct mysql_options_ {
        const char *host = "localhost";
        const char *user = "root";
        const char *pass = "";
        const char *db = "";
        const char *socket = NULL;
        unsigned int port = 3306;
        unsigned long flags = 0;
    }mysql_options_t;
    
    class mysqld
    {
    private:
        std::vector<std::string> search(std::string target, const char *pattern);
    protected:
        MYSQL *conn;
        MYSQL_RES *result = NULL;
    public:
        mysqld(mysql_options_t &conf);
        virtual ~mysqld();
        
        int exec_query(const char *query);
        std::vector<std::string> fetch_rows();
        void release();
        
        //-----------------
        //BACKGROUND THREAD
        //-----------------
        void background_thread(std::string str);
        
        //----------
        //SEMAPHORES
        //----------
        void semaphores(std::string str);
        
        //------------
        //TRANSACTIONS
        //------------
        void transactions(std::string str);
        
        //--------
        //FILE I/O
        //--------
        void file_io(std::string str);
        
        //-------------------------------------
        //INSERT BUFFER AND ADAPTIVE HASH INDEX
        //-------------------------------------
        void insert_buffer(std::string str);
        void adaptive_hash_index(std::string str);
        
        //---
        //LOG
        //---
        void data_log(std::string str);
        
        //----------------------
        //BUFFER POOL AND MEMORY
        //----------------------
        void buffer_pool(std::string str);
        void buffer_memory(std::string str);
        
        //--------------
        //ROW OPERATIONS
        //--------------
        void row_operations(std::string str);
    };
    
    
  //int mysqld();
}

int check_mysqld();

#endif /* check_mysqld_hpp */
