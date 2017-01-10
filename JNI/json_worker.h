//
// Created by Microsoft on 2017/1/3.
//

#ifndef BLACK_MOCAR_JSON_WORKER_H
#define BLACK_MOCAR_JSON_WORKER_H

#include "obo_jni.h"

/*
 * 自定义封装json接口
 */
class Json
{
public:
    Json();
    ~Json();

    /* 给json插入一对key value */
    void insert(string key, string value);
    /* 将json结构体转换成字符串 */
    string print();
    /* 将json字符串转换成json结构体 */
    void parse(string json_str);
    /* 由key得到value */
    string getValue(string key);

private:
    /* 防止json对象之间的相互拷贝 */
    Json(const Json &);
    Json &operator=(const Json &);
    /* cJSON数据的根句柄 */
    cJSON *_root;
};

#endif //BLACK_MOCAR_JSON_WORKER_H
