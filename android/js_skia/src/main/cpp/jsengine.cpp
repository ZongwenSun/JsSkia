#include <jni.h>
#include <string.h>
#include "quickjs/quickjs-libc.h"
#include "android_log.h"

#include "jsengine.h"


JSRuntime *jsRuntime;
JSContext *jsContext;

static JSContext *JS_NewCustomContext(JSRuntime *rt) {
    JSContext *ctx = JS_NewContextRaw(rt);
    if (!ctx)
        return NULL;
    JS_AddIntrinsicBaseObjects(ctx);
    JS_AddIntrinsicDate(ctx);
    JS_AddIntrinsicEval(ctx);
    JS_AddIntrinsicStringNormalize(ctx);
    JS_AddIntrinsicRegExp(ctx);
    JS_AddIntrinsicJSON(ctx);
    JS_AddIntrinsicProxy(ctx);
    JS_AddIntrinsicMapSet(ctx);
    JS_AddIntrinsicTypedArrays(ctx);
    JS_AddIntrinsicPromise(ctx);
    JS_AddIntrinsicBigInt(ctx);
    return ctx;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_szw_jsengine_QuickJsEngine_init(JNIEnv *env, jobject thiz) {
    jsRuntime = JS_NewRuntime();
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(jsRuntime);
    jsContext = JS_NewCustomContext(jsRuntime);
    js_std_add_helpers(jsContext, 0, NULL);
}



