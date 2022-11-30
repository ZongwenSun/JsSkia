#include <jni.h>

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("jsengine");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("jsengine")
//      }
//    }
extern "C"
JNIEXPORT jstring JNICALL
Java_com_szw_jsengine_QuickJsEngine_evaluate(JNIEnv *env, jobject thiz, jstring script) {
    // TODO: implement evaluate()
    return script;
}