package com.szw.fresh;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;


import com.szw.fresh.databinding.ActivityMainBinding;
import com.szw.jsskia.JsSkiaJNI;
import com.szw.jsskia.SkiaRenderView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        new JsSkiaJNI();
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        SkiaRenderView skiaRenderView = new SkiaRenderView(MainActivity.this);
        binding.frameContainer.addView(skiaRenderView);
    }

    String loadScript() {
        try {
            InputStream inputStream = getAssets().open("test.js");
            int length = inputStream.available();
            char[] buf = new char[length];
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            reader.read(buf);
            return new String(buf);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

}