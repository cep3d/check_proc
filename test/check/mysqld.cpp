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
    
    mysqld::~mysqld() {
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
        std::vector<std::string> arr;
        if (this->result == NULL) {
            throw std::runtime_error(mysql_error(this->conn));
        }
        MYSQL_FIELD *field;
        MYSQL_ROW row;
        int num_fields, i;
        num_fields = mysql_num_fields(this->result);
        field = mysql_fetch_field(this->result);
        while ((row = mysql_fetch_row(this->result)) != NULL) {
            for (i = 0; i < num_fields; ++i) {
                //std::string str1, str2;
                //str1 = "Field:" + std::string(field[i].name);
                //str2 = "Row: " + std::string(row[i]);
                arr.push_back(row[i]);
            }
        }
        
        return arr;
    }
    
    std::vector<std::string> mysqld::search(std::string target, const char *pattern) {
        std::vector<std::string> arr;
        std::regex re(pattern);
        std::smatch match;
        
        if (std::regex_search(target, match, re)) {
            int i = 0;
            for (i = 0; i < match.size(); ++i) {
                arr.push_back(match[i]);
            }
        }
        
        return arr;
    }
    
    void mysqld::background_thread(std::string str) {
        std::smatch matches;
        std::vector<std::string> srv_master_thread;
        std::vector<std::string> srv_shutdown;
        std::vector<std::string> srv_idle;
        
        srv_master_thread = this->search(str, "srv_master_thread loops: (\\d+)");
        srv_shutdown = this->search(str, "(\\d+) srv_shutdown");
        srv_idle = this->search(str, "(\\d+) srv_idle");
        
        std::vector<std::string>::iterator itr;
        for (itr = srv_master_thread.begin(); itr != srv_master_thread.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
        for (itr = srv_shutdown.begin(); itr != srv_shutdown.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
        for (itr = srv_idle.begin(); itr != srv_idle.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
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
    try {
        check::mysqld *mysqld = new check::mysqld(options);
        
        mysqld->exec_query("SHOW ENGINE INNODB STATUS");
        
        std::vector<std::string> arr;
        arr = mysqld->fetch_rows();
        mysqld->background_thread(arr.back());
//        std::vector<std::string>::iterator itr;
//        for (itr = arr.begin(); itr != arr.end(); ++itr) {
//            std::cout << *itr << std::endl;
//        }
        
        mysqld->release();
    } catch(std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
