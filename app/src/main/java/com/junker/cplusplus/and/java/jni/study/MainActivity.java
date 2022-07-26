package com.junker.cplusplus.and.java.jni.study;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.junker.cplusplus.and.java.jni.study.bean.DataBean;
import com.junker.cplusplus.and.java.jni.study.databinding.ActivityMainBinding;
import com.junker.cplusplus.and.java.jni.study.interfaces.ThreadCallBack;
import com.junker.cplusplus.and.java.jni.study.manager.JNIBaseManager;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = MainActivity.class.getSimpleName();

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
                num = JNIBaseManager.getInstance().nativeInteger(80);
                binding.sampleText.setText("nativeInteger = " + num);
                break;
            case 1:// 传参类型：char
                char ch;
                ch = JNIBaseManager.getInstance().nativeChar("a".toCharArray()[0]);
                binding.sampleText.setText("nativeChar = " + ch);
                break;
            case 2:// 传参类型：string
                String str = "";
                str = JNIBaseManager.getInstance().nativeString("hello");
                binding.sampleText.setText("nativeString = " + str);
                break;
            case 3:// 传参类型：数组( int[]/ string[]/ ...)
                int[] nums;
                nums = JNIBaseManager.getInstance().nativeIntArray(new int[]{1, 2, 3});
                StringBuilder value = new StringBuilder();
                for (int i = 0; i < nums.length; i++) {
                    value.append(nums[i]).append(",");
                    Log.e("TAG", nums[i] + "");
                }
                binding.sampleText.setText("nativeIntArray = " + value);
                break;
            case 4:// 传参类型：对象
                DataBean bean;
                bean = JNIBaseManager.getInstance().nativeObject(new DataBean("Junker", 27));
                binding.sampleText.setText("nativeObject = " + bean.toString());
                break;
            case 5:// 传参类型：集合-List<整型>
                List<Integer> list;
                List<Integer> oldList = new ArrayList<>();
                oldList.add(10068);
                oldList.add(12580);
                list = JNIBaseManager.getInstance().nativeListInteger(oldList);
                StringBuilder text = new StringBuilder();
                for (int i = 0; i < list.size(); i++) {
                    text.append(list.get(i)).append(",");
                }
                binding.sampleText.setText("nativeListInteger = " + text);
                break;
            case 6:// 传参类型：集合-List<String>
                List<String> listString;
                List<String> oldListString = new ArrayList<>();
                oldListString.add("one");
                oldListString.add("two");
                listString = JNIBaseManager.getInstance().nativeListString(oldListString);
                StringBuilder texListString = new StringBuilder();
                for (int i = 0; i < listString.size(); i++) {
                    texListString.append(listString.get(i)).append(",");
                }
                binding.sampleText.setText("nativeListString = " + texListString);
                break;
            case 7:// 传参类型：集合-List<int[]>
                List<int[]> listIntArray;
                List<int[]> oldListIntArray = new ArrayList<>();
                oldListIntArray.add(new int[]{1, 2});
                oldListIntArray.add(new int[]{11, 12});
                listIntArray = JNIBaseManager.getInstance().nativeListIntArray(oldListIntArray);
                StringBuilder textListIntArray = new StringBuilder();
                for (int i = 0; i < listIntArray.size(); i++) {
                    int[] itemListIntArray = listIntArray.get(i);
                    for (int j = 0; j < itemListIntArray.length; j++) {
                        textListIntArray.append(itemListIntArray[j]).append(",");
                    }
                }
                binding.sampleText.setText("nativeListIntArray = " + textListIntArray);
                break;
            case 8:// 传参类型：集合-List<Object>
                List<DataBean> listObject;
                List<DataBean> oldListObject = new ArrayList<>();
                oldListObject.add(new DataBean("小明", 16));
                oldListObject.add(new DataBean("张三", 17));
                listObject = JNIBaseManager.getInstance().nativeListObject(oldListObject);
                StringBuilder textListObject = new StringBuilder();
                for (int i = 0; i < listObject.size(); i++) {
                    DataBean itemListObject = listObject.get(i);
                    textListObject.append(itemListObject.toString()).append(",");
                }
                binding.sampleText.setText("nativeListObject = " + textListObject);
                break;
            case 9:// 传参类型：Map数组-Map<整型>
                Map<Integer, Integer> mapInteger;
                Map<Integer, Integer> oldMapInteger = new HashMap<>();
                oldMapInteger.put(1, 123);
                oldMapInteger.put(2, 456);
                mapInteger = JNIBaseManager.getInstance().nativeMapInteger(oldMapInteger);
                StringBuilder textMapInteger = new StringBuilder();
                for (Map.Entry<Integer, Integer> entry : mapInteger.entrySet()) {
                    textMapInteger.append("key=").append(entry.getKey()).append("|value=").append(entry.getValue()).append(",");
                }
                binding.sampleText.setText("nativeMapInteger = " + textMapInteger);
                break;
            case 10:// 传参类型：Map数组-Map<String>
                Map<String, String> mapString;
                Map<String, String> oldMapString = new HashMap<>();
                oldMapString.put("one", "张三");
                oldMapString.put("two", "李四");
                mapString = JNIBaseManager.getInstance().nativeMapString(oldMapString);
                StringBuilder textMapString = new StringBuilder();
                for (Map.Entry<String, String> entry : mapString.entrySet()) {
                    textMapString.append("key=").append(entry.getKey()).append("|value=").append(entry.getValue()).append(",");
                }
                binding.sampleText.setText("nativeMapString = " + textMapString);
                break;
            case 11:// 传参类型：Map数组-Map<int[]>
                Map<Integer, int[]> mapIntArray;
                Map<Integer, int[]> oldMapIntArray = new HashMap<>();
                oldMapIntArray.put(1, new int[]{123, 456});
                oldMapIntArray.put(2, new int[]{789, 1000});
                mapIntArray = JNIBaseManager.getInstance().nativeMapIntegerArray(oldMapIntArray);
                StringBuilder textMapIntArray = new StringBuilder();
                for (Map.Entry<Integer, int[]> entry : mapIntArray.entrySet()) {
                    int[] itemMapIntArray = entry.getValue();
                    textMapIntArray.append("key=").append(entry.getKey()).append("|value=");
                    for (int j = 0; j < itemMapIntArray.length; j++) {
                        textMapIntArray.append(itemMapIntArray[j]).append(":");
                    }
                    textMapIntArray.append(",");
                }
                binding.sampleText.setText("nativeMapIntegerArray = " + textMapIntArray);
                break;
            case 12:// 传参类型：Map数组-Map<Object>
                Map<Integer, DataBean> mapObject;
                Map<Integer, DataBean> oldMapObject = new HashMap<>();
                oldMapObject.put(1, new DataBean("小明", 16));
                oldMapObject.put(2, new DataBean("张三", 17));
                mapObject = JNIBaseManager.getInstance().nativeMapObject(oldMapObject);
                StringBuilder textMapObject = new StringBuilder();
                for (Map.Entry<Integer, DataBean> entry : mapObject.entrySet()) {
                    textMapObject.append("key=").append(entry.getKey()).append("|value=").append(entry.getValue().toString()).append(",");
                }
                binding.sampleText.setText("nativeMapObject = " + textMapObject);
                break;
            case 13:// 传参类型：集合嵌套集合-List<List>
                List<List<DataBean>> listList;
                List<List<DataBean>> oldListList = new ArrayList<>();
                List<DataBean> itemList1 = new ArrayList<>();
                itemList1.add(new DataBean("小明", 25));
                itemList1.add(new DataBean("张三", 26));
                oldListList.add(itemList1);
                List<DataBean> itemList2 = new ArrayList<>();
                itemList2.add(new DataBean("小亮", 14));
                itemList2.add(new DataBean("小红", 12));
                oldListList.add(itemList2);
                listList = JNIBaseManager.getInstance().nativeListList(oldListList);
                StringBuilder textListList = new StringBuilder();
                for (int i = 0; i < listList.size(); i++) {
                    List<DataBean> dataBeans = listList.get(i);
                    for (int j = 0; j < dataBeans.size(); j++) {
                        DataBean itemBean = dataBeans.get(i);
                        textListList.append(itemBean.toString()).append(":");
                    }
                    textListList.append(",");
                }
                binding.sampleText.setText("nativeListList = " + textListList);
                break;
            case 14:// 传参类型：Map嵌套Map-Map<Map>
                Map<Integer, Map<Integer, DataBean>> mapMap;
                Map<Integer, Map<Integer, DataBean>> oldMapMap = new HashMap<>();
                Map<Integer, DataBean> itemMap1 = new HashMap<>();
                itemMap1.put(1, new DataBean("小亮", 14));
                itemMap1.put(2, new DataBean("小明", 25));
                oldMapMap.put(11, itemMap1);
                Map<Integer, DataBean> itemMap2 = new HashMap<>();
                itemMap2.put(1, new DataBean("张三", 26));
                itemMap2.put(2, new DataBean("小红", 12));
                oldMapMap.put(22, itemMap2);
                mapMap = JNIBaseManager.getInstance().nativeMapMap(oldMapMap);
                StringBuilder textMapMap = new StringBuilder();
                for (Map.Entry<Integer, Map<Integer, DataBean>> entry : mapMap.entrySet()) {
                    textMapMap.append("key=").append(entry.getKey()).append("value=");
                    for (Map.Entry<Integer, DataBean> itemEntry : entry.getValue().entrySet()) {
                        textMapMap.append("itemKey=").append(itemEntry.getKey()).append("itemValue=").append(itemEntry.getValue());
                    }
                    textMapMap.append(",");
                }
                binding.sampleText.setText("nativeMapMap = " + textMapMap);
                break;
            case 15:// 线程交互处理
                Log.e(TAG,"Thread-TAG - get application main-thread | threadID = " + Looper.getMainLooper().getThread().getId());
                JNIBaseManager.getInstance().nativeThreadInteraction(new ThreadCallBack() {
                    @Override
                    public void onSuccess(DataBean bean) {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Log.e(TAG,"Thread-TAG - get current-thread | callBack->UiThread | threadID = " + Thread.currentThread().getId());
                                binding.sampleText.setText("nativeThread CallBack success!  bean = " + bean.toString());
                            }
                        });
                        Log.e(TAG,"Thread-TAG - get current-thread | callBack | threadID = " + Thread.currentThread().getId());
                        Log.e(TAG,"nativeThread CallBack success!  bean = " + bean.toString());
                    }

                    @Override
                    public void onError(int code, String desc) {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                binding.sampleText.setText("nativeThread callBack error!  code=" + code + "|desc=" + desc);
                            }
                        });
                        Log.e(TAG,"nativeThread callBack error!  code=" + code + "|desc=" + desc);
                    }
                });
                break;
            case 16:// JNI动态注册
                String context = JNIBaseManager.getInstance().nativeDynamicRegisterMethod();
                binding.sampleText.setText("nativeDynamicRegisterMethode = " + context);
                break;
        }
    }
}