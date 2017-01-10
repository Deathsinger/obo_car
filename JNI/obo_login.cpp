//
// Created by Microsoft on 2017/1/10.
//

#include "obo_jni.h"
#include "obo_config_reader.h"
#include "json_worker.h"
#include "curl_worker.h"

#define JNI_LOGING_TAG "obo_login"

extern "C"
{

JNIEXPORT jboolean JNICALL Java_obo_org_obo_1car_OboJni_oboLogin
        (JNIEnv *env, jobject j_obj, jstring j_username, jstring j_password, jboolean j_isDriver)
{
    const char  *username = env->GetStringUTFChars(j_username, NULL);
    const char  *password = env->GetStringUTFChars(j_password, NULL);
    const char  *isDriver = j_isDriver == JNI_TRUE ? "yes" : "no";
    bool        login_result = false;
    const char  *post_str = NULL;
    //const char *url = "https://192.168.23.21:8080/login";
    string      url;

    do
    {
        if (!GetValue("login_url", url))
            break;
        /* 发送http协议 url指令 */
        __android_log_print(ANDROID_LOG_ERROR, JNI_LOGING_TAG, "username = %s, password = %s, isDriver = %s", username, password, isDriver);
        /* CURL/JSON */
        Json loginjson;
        loginjson.insert("username", username);
        loginjson.insert("password", password);
        loginjson.insert("driver", isDriver);
        string tmp = loginjson.print();
        post_str = tmp.c_str();
        __android_log_print(ANDROID_LOG_ERROR, JNI_LOGING_TAG, "post_str = %s", post_str);

        CurlWorker curl(url);
        bool ret = curl.execute(post_str);

        if (ret == false)
        {
            /* login success */
            __android_log_print(ANDROID_LOG_ERROR, JNI_LOGING_TAG, "execute 失败");
            break;
        }
        __android_log_print(ANDROID_LOG_ERROR, JNI_LOGING_TAG, "response Data: %s", curl.getResponseData().c_str());
        Json ret_json;
        ret_json.parse(curl.getResponseData());
        string result = ret_json.getValue("result");
        // __android_log_print(ANDROID_LOG_ERROR, JNI_LOG_TAG, "CURL result: %s", result.c_str());
        if (result == "ok")
        {
            __android_log_print(ANDROID_LOG_ERROR, JNI_LOGING_TAG, "登录成功");
            login_result = true;
        }
        else
        {
            /* login failed */
            string reason = ret_json.getValue("reason");
            if (reason == "") {
                __android_log_print(ANDROID_LOG_ERROR, JNI_LOGING_TAG, "登陆失败，未知错误");

            }
            else {
                __android_log_print(ANDROID_LOG_ERROR, JNI_LOGING_TAG, "登陆失败，%s", reason.c_str());

            }
            login_result = false;
        }
    }while(0);

    env->ReleaseStringUTFChars(j_username, username);
    env->ReleaseStringUTFChars(j_password, password);
    return login_result == true ? JNI_TRUE : JNI_FALSE;
}

}
