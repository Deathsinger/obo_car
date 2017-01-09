//
// Created by Microsoft on 2017/1/3.
//
#include "curl_worker.h"

CurlWorker::CurlWorker(string url)
{
    _curl = curl_easy_init();
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    /* 将此https请求 编程忽略验证CA证书模式 */
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, false);
}
CurlWorker::~CurlWorker()
{
    curl_easy_cleanup(_curl);
}

/* 执行curl请求，requestData就是curl的post数 */
bool CurlWorker::execute(string requestData)
{
    CURLcode ret;
    curl_easy_setopt(_curl, CURLOPT_POST, true);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, requestData.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, CurlWorker::dealResponse);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this);
    ret = curl_easy_perform(_curl);
    __android_log_print(ANDROID_LOG_ERROR, curlTag, "curl result = %d", ret);
    if (ret != CURLE_OK){
        return false;
    }
    return true;
}

size_t CurlWorker::dealResponse(char *ptr, int m, int n, void *args)
{
    CurlWorker *curlWorker = (CurlWorker *)args;
    int count = m * n;
    copy(ptr, ptr + count, back_inserter(curlWorker->_responseData));
    return count;
}

string CurlWorker::getResponseData()
{
   return this->_responseData;
}