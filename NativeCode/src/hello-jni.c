/*
 * Copyright (C) 2013-2100
 * author : Qinwenchao
 * time : 2013-11-25
 */
#include <string.h>
#include <jni.h>
#include <android/log.h>  
/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */


// log标签
#define  TAG    "Qinwenchao"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

jstring Java_com_qinwenchao_myjniexample_MainActivity_stringFromJNIStatic(JNIEnv* env,
		jobject thiz) {
	 LOGI("%s info\n", __func__);
     LOGD("%s debug\n", __func__);
     LOGE("%s error\n", __func__);
	return (*env)->NewStringUTF(env, "Hello Qinwenchao, Good Afternoon !");
}
