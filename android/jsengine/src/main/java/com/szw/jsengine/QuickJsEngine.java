package com.szw.jsengine;

public class QuickJsEngine {
    static {
        System.loadLibrary("jsengine");
    }

    public native String evaluate(String script);

}
