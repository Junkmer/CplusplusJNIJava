package com.junker.cplusplus.and.java.jni.study;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.junker.cplusplus.and.java.jni.study.databinding.ActivityMainBinding;
import com.junker.cplusplus.and.java.jni.study.manager.JavaNativeMethod;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText("aa");
    }
}