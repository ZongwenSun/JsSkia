package com.szw.jsengine;



public class QuickJsEngine {
    static {
        System.loadLibrary("jsengine");
    }

    public QuickJsEngine() {
        init();
    }

    private native void init();

    public native String evaluate(String script);

}
