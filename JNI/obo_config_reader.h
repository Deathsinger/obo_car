//
// Created by Microsoft on 2017/1/10.
//

#ifndef OBO_CAR_OBO_CONFIG_READER_H
#define OBO_CAR_OBO_CONFIG_READER_H


/****************************************************************************
*   作者:  jasitzhang
*   日期:  2011-10-2
*   目的:  读取配置文件的信息，以map的形式存入
*   要求:  配置文件的格式，以#作为行注释，配置的形式是key = value，中间可有空格，也可没有空格
*****************************************************************************/
#ifndef _GET_CONFIG_H_
#define _GET_CONFIG_H_

#include <string>
#include <map>
#define conf_path "obo_conf.properties"
using namespace std;

#define COMMENT_CHAR '#'

bool ReadConfig(const string & filename, map<string, string> & m);
void PrintConfig(const map<string, string> & m);
bool GetValue(const string key, string &value);
#endif

#endif //OBO_CAR_OBO_CONFIG_READER_H
