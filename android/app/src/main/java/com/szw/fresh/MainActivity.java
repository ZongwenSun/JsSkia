package com.szw.fresh;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;


import com.szw.fresh.databinding.ActivityMainBinding;
import com.szw.jsengine.QuickJsEngine;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;
    private QuickJsEngine quickJsEngine;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        quickJsEngine = new QuickJsEngine();

        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        String script = loadScript();
        String str = quickJsEngine.evaluate(script);
        binding.tvHello.setText(str);

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