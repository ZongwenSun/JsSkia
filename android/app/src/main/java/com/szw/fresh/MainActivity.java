package com.szw.fresh;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;


import com.szw.fresh.databinding.ActivityMainBinding;
import com.szw.jsengine.QuickJsEngine;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;
    private QuickJsEngine quickJsEngine;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        quickJsEngine = new QuickJsEngine();

        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        String str = quickJsEngine.evaluate("hello world from jni aaa");
        binding.tvHello.setText(str);

    }

}