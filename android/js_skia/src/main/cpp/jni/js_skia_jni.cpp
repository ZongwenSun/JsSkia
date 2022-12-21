#include <jni.h>
#include <cstdlib>

//
// Created by 孙宗文 on 2022/12/21.
//

extern "C"
JNIEXPORT void JNICALL
Init(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeInit()
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4);

    static const JNINativeMethod methods[] = {
            {
                    .name = "nativeInit",
                    .signature = "()V",
                    .fnPtr = reinterpret_cast<void *>(&Init),
            },
    };

    jclass clazz = env->FindClass("com/szw/jsskia/JsSkiaJNI");

    if (clazz == nullptr) {
        return false;
    }

    env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0]));

    return JNI_VERSION_1_4;
}

