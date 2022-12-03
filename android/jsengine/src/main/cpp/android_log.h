//
// Created by 孙宗文 on 2022/12/3.
//

#ifndef FRESH_ANDROID_LOG_H
#define FRESH_ANDROID_LOG_H

#include <android/log.h>

#define LOG_TAG "FreshJS"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#endif //FRESH_ANDROID_LOG_H
