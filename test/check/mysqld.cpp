//
//  check_mysqld.cpp
//  test
//
//  Created by Takamasa Yano on 2018/01/21.
//  Copyright © 2018 Libero_Imac. All rights reserved.
//

#include "mysqld.hpp"

namespace check
{
    mysqld::mysqld(mysql_options_t &conf) {
        this->conn = mysql_init(NULL);
        // connection
        if (!mysql_real_connect(this->conn, conf.host, conf.user, conf.pass, conf.db, conf.port, conf.socket, conf.flags)) {
            std::cerr << "MySQL Error(" << mysql_errno(this->conn) << ") ";
            std::cerr << mysql_error(this->conn) << std::endl;
            throw std::exception();
        }
    }
    
    void mysqld::release() {
        if (this->result != NULL) {
            mysql_free_result(this->result);
        }
        mysql_close(this->conn);
    }
    
    int mysqld::exec_query(const char *query) {
        if (mysql_real_query(this->conn, query, strlen(query))) {
            std::cerr << "MySQL Error(" << mysql_errno(this->conn) << ") ";
            std::cerr << mysql_error(this->conn) << std::endl;
            throw std::exception();
            return -1;
        }
        //res = mysql_use_result(this->conn);
        this->result = mysql_store_result(this->conn);
        return 0;
    }
    
    std::vector<std::string> mysqld::fetch_rows() {
        MYSQL_FIELD *field;
        MYSQL_ROW row;
        std::vector<std::string> arr;
        int num_fields, i;
        num_fields = mysql_num_fields(this->result);
        field = mysql_fetch_field(this->result);
        while ((row = mysql_fetch_row(this->result)) != NULL) {
            for (i = 0; i < num_fields; ++i) {
                std::string str1, str2;
                str1 = "Field:" + std::string(field[i].name);
                str2 = "Row: " + std::string(row[i]);
                arr.push_back(str1 + str2);
            }
        }
        
        return arr;
    }
    
    void mysqld::background_thread(std::string str) {
        
    }
    
    void mysqld::semaphores(std::string str) {
        
    }
    
    void mysqld::transactions(std::string str) {
        
    }
    
    void mysqld::file_io(std::string str) {
        
    }
    
    void mysqld::insert_buffer(std::string str) {
        
    }
    
    void mysqld::adaptive_hash_index(std::string str) {
        
    }
    
    void mysqld::data_log(std::string str) {
        
    }
    
    void mysqld::buffer_pool(std::string str) {
        
    }
    
    void mysqld::buffer_memory(std::string str) {
        
    }
    
    void mysqld::row_operations(std::string str) {
        
    }

}

int check_mysqld() {
    std::cout << "Check mysqld proc" << std::endl;
    check::mysql_options_t options;
    check::mysqld *mysqld = new check::mysqld(options);
    
    mysqld->exec_query("SHOW ENGINE INNODB STATUS");
    
    std::vector<std::string> arr;
    arr = mysqld->fetch_rows();
    std::vector<std::string>::iterator itr;
    for (itr = arr.begin(); itr != arr.end(); ++itr) {
        std::cout << *itr << std::endl;
    }
    
    mysqld->release();
    
    return 0;
}
