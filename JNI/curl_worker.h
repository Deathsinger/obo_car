//
// Created by Microsoft on 2017/1/3.
//

#ifndef BLACK_MOCAR_CURL_WORKER_H
#define BLACK_MOCAR_CURL_WORKER_H

#include "lw_jni.h"

#define curlTag "CurlWorker"

class CurlWorker
{
public:
    CurlWorker(string url);
    ~CurlWorker();

    /* 执行curl请求，requestData就是curl的post数 */
    bool execute(string requestData);

    static size_t dealResponse(char *ptr, int m, int n, void *args);

    string getResponseData();

private:
    CURL *_curl; //句柄
    string _responseData;
};

#endif //BLACK_MOCAR_CURL_WORKER_H
