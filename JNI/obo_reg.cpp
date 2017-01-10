//
// Created by Microsoft on 2017/1/10.
//
#include "obo_jni.h"
#include "obo_config_reader.h"
#include "json_worker.h"
#include "curl_worker.h"

#define JNI_REG_TAG "obo_reg"


extern "C"
{
JNIEXPORT jboolean JNICALL Java_obo_org_obo_1car_OboJni_oboReg(JNIEnv *env, jobject j_obj, jstring j_username, jstring j_password, jstring j_email, jstring j_phone, jstring j_idCard, jboolean j_isDriver)
{
    const char *username = env->GetStringUTFChars(j_username, NULL);
    const char *password = env->GetStringUTFChars(j_password, NULL);
    const char *email = env->GetStringUTFChars(j_email, NULL);
    const char *phone = env->GetStringUTFChars(j_phone, NULL);
    const char *idCard = env->GetStringUTFChars(j_idCard, NULL);
    const char *isDriver = j_isDriver == JNI_TRUE ? "yes" : "no";
    bool        reg_result = false;
//    const char *url = "https://192.168.23.21:8080/reg";
    const char *post_str = NULL;
    string      url;


    /* CURL 访问https://ip:port/reg */
    do{
        if (!GetValue("reg_url", url))
            break;
        __android_log_print(ANDROID_LOG_ERROR, JNI_REG_TAG, "username = %s, password = %s, isDriver = %s", username, password, isDriver);

        /* 组织JSON */
        Json regJson;
        regJson.insert("username", username);
        regJson.insert("password", password);
        regJson.insert("driver", isDriver);
        regJson.insert("tel", phone);
        regJson.insert("email", email);
        regJson.insert("id_card", idCard);
        string tmp = regJson.print();
        post_str = tmp.c_str();
        __android_log_print(ANDROID_LOG_ERROR, JNI_REG_TAG, "post_str = %s", post_str);

        /* 组织CURL */
        CurlWorker  curl(url);
        bool        ret = curl.execute(post_str);

        if (!ret)
        {
            __android_log_print(ANDROID_LOG_ERROR, JNI_REG_TAG, "reg execute 失败");
            break;
        }

        /* 处理应答值 */
        __android_log_print(ANDROID_LOG_ERROR, JNI_REG_TAG, "response Data: %s", curl.getResponseData().c_str());
        Json ret_json;
        ret_json.parse(curl.getResponseData());
        string result = ret_json.getValue("result");
        if (result == "ok")
        {
            __android_log_print(ANDROID_LOG_ERROR, JNI_REG_TAG, "注册成功");
            reg_result = true;
        }
        else
        {
            /* login failed */
            string reason = ret_json.getValue("reason");
            if (reason == "") {
                __android_log_print(ANDROID_LOG_ERROR, JNI_REG_TAG, "注册失败，未知错误");

            }
            else {
                __android_log_print(ANDROID_LOG_ERROR, JNI_REG_TAG, "注册失败，%s", reason.c_str());

            }
            reg_result = false;
        }
    }while(0);

    /* 释放字符串资源 */
    env->ReleaseStringUTFChars(j_username, username);
    env->ReleaseStringUTFChars(j_password, password);
    env->ReleaseStringUTFChars(j_email, email);
    env->ReleaseStringUTFChars(j_phone, phone);
    return reg_result ? JNI_TRUE : JNI_FALSE;
}

}

