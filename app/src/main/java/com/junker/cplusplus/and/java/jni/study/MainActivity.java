package com.junker.cplusplus.and.java.jni.study;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.junker.cplusplus.and.java.jni.study.bean.DataBean;
import com.junker.cplusplus.and.java.jni.study.databinding.ActivityMainBinding;
import com.junker.cplusplus.and.java.jni.study.manager.JNIBaseManager;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.zip.Inflater;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;

        tv.setText("显示回调结果");

        initData();
    }

    private void initData() {
        final String[] nativeMethods = getResources().getStringArray(R.array.nativeMethod);
        ArrayAdapter<String> adapter = new ArrayAdapter<>(MainActivity.this, android.R.layout.simple_expandable_list_item_1, nativeMethods);
        binding.mainList.setAdapter(adapter);

        binding.mainList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                itemClick(i);
            }
        });
    }

    /**
     * 处理item click响应事件
     */
    @SuppressLint("SetTextI18n")
    private void itemClick(int position) {
        switch (position) {
            case 0:// 传参类型：整型(int/long/short/...)
                int num = 0;
                num = JNIBaseManager.getInstance().integerFromJNI(80);
                binding.sampleText.setText("integerFromJNI = " + num);
                break;
            case 1:// 传参类型：char
                char ch = 1;
                ch = JNIBaseManager.getInstance().charFromJNI("a".toCharArray()[0]);
                binding.sampleText.setText("charFromJNI = " + ch);
                break;
            case 2:// 传参类型：string
                String str = "";
                str = JNIBaseManager.getInstance().stringFromJNI("hello");
                binding.sampleText.setText("stringFromJNI = " + str);
                break;
            case 3:// 传参类型：数组( int[]/ string[]/ ...)
                int[] nums;
                nums = JNIBaseManager.getInstance().intArrayFromJNI(new int[]{1, 2, 3});
                StringBuilder value = new StringBuilder();
                for (int i = 0; i < nums.length; i++) {
                    value.append(nums[i]).append(",");
                    Log.e("TAG", nums[i] + "");
                }
                binding.sampleText.setText("intArrayFromJNI = " + value);
                break;
            case 4:// 传参类型：对象
                DataBean bean;
                bean = JNIBaseManager.getInstance().objectFromJNI(new DataBean("Junker", 27));
                binding.sampleText.setText("objectFromJNI = " + bean.toString());
                break;
            case 5:// 传参类型：集合-List<整型>
                List<Integer> list;
                List<Integer> oldList = new ArrayList<>();
                oldList.add(10068);
                oldList.add(12580);
                list = JNIBaseManager.getInstance().listIntegerFromJNI(oldList);
                String text = "";
                for (int i = 0; i < list.size(); i++) {
                    text += list.get(0) + ",";
                }
                binding.sampleText.setText("listIntegerFromJNI = " + text);
                break;
            case 6:// 传参类型：集合-List<String>
//                listStringFromJNI(List<String> mapInt);
                break;
            case 7:// 传参类型：集合-List<int[]>
//                listIntArrayFromJNI(List<int[]> listIntArray);
                break;
            case 8:// 传参类型：集合-List<Object>
//                listObjectFromJNI(List<Object> listObject);
                break;
            case 9:// 传参类型：Map数组-Map<整型>
//                mapIntegerFromJNI(Map<Integer,Integer> mapInteger);
                break;
            case 10:// 传参类型：Map数组-Map<String>
//                mapStringFromJNI(Map<String,String> mapString);
                break;
            case 11:// 传参类型：Map数组-Map<int[]>
//                mapIntegerArrayFromJNI(Map<Integer,int[]> mapIntegerArray);
                break;
            case 12:// 传参类型：Map数组-Map<Object>
//                mapObjectFromJNI(Map<Integer,Object> mapObject);
                break;
            case 13:// 传参类型：集合嵌套集合-List<List>
//                listListFromJNI(List<List<Object>> listList);
                break;
            case 14:// 传参类型：Map嵌套Map-Map<Map>
//                mapMapFromJNI(Map<Integer,Map<Integer,Object>> mapMap);
                break;
        }
    }
}