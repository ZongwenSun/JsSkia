package com.szw.jsskia;



public class JsSkiaJNI {
    static {
        System.loadLibrary("js_skia");
    }

    public JsSkiaJNI() {
        nativeInit();
    }


    private native void nativeInit();

}
