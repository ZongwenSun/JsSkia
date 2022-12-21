package com.szw.fresh;

import android.app.Application;

import com.szw.jsskia.JsSkiaJNI;

public class MainApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        JsSkiaJNI jsSkiaJNI = new JsSkiaJNI();
    }
}
