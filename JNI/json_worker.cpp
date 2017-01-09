//
// Created by Microsoft on 2017/1/3.
//

#include "json_worker.h"

Json::Json()
{
    _root = cJSON_CreateObject();
}
Json::~Json()
{
    cJSON_Delete(_root);
}
/* 给json插入一对key value */
void Json::insert(string key, string value)
{
    cJSON_AddStringToObject(_root, key.c_str(), value.c_str());
}
/* 将json结构体转换成字符串 */
string Json::print()
{
    char *p = cJSON_Print(_root);
    string str = string(p);
    return str;
}
/* 将json字符串转换成json结构体 */
void Json::parse(string json_str)
{
    cJSON *root = cJSON_Parse(json_str.c_str());
    cJSON_Delete(_root);
    _root = root;
}
/* 由key得到value */
string Json::getValue(string key)
{
    cJSON *obj = cJSON_GetObjectItem(_root, key.c_str());
    if (obj == NULL)
    {
        return string();
    }
    return string(obj->valuestring);
}