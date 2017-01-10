#设置LOCAL_PATH环境变量
LOCAL_PATH:=$(call my-dir)

#将libcurl.a集成到libobojni.so中
include $(CLEAR_VARS)
LOCAL_MODULE := libcurl
LOCAL_SRC_FILES := libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

#libobojni.so
include $(CLEAR_VARS)
LOCAL_MODULE := obojni
LOCAL_SRC_FILES := obo_login.cpp obo_reg.cpp obo_config_reader.cpp cJson.cpp json_worker.cpp curl_worker.cpp
LOCAL_LDLIBS := -llog -lz
LOCAL_STATIC_LIBRARIES := libcurl

#表示生成的是so文件
include $(BUILD_SHARED_LIBRARY)