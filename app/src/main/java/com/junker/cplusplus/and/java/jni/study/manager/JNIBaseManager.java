package com.junker.cplusplus.and.java.jni.study.manager;

import android.util.Log;

import com.junker.cplusplus.and.java.jni.study.bean.DataBean;

import java.util.List;
import java.util.Map;

public class JNIBaseManager {
    private static final String TAG = JNIBaseManager.class.getSimpleName();

    private static boolean sIsLoadLibrarySuccess = false;

    private int num;
    private char ch;
    private String str;
    private int[] numS;
    private DataBean bean;
    private List<Integer> list;
    private List<String> listString;
    private List<int[]> listIntArray;
    private List<DataBean> listObject;
    private Map<Integer,Integer> mapInteger;
    private Map<String,String> mapString;
    private Map<Integer,int[]> mapIntegerArray;
    private Map<Integer,DataBean> mapObject;
    private List<List<DataBean>> listList;
    private Map<Integer,Map<Integer,DataBean>> mapMap;

    static {
        try {
            sIsLoadLibrarySuccess = loadIMLibrary();
        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }
    }

    private static boolean loadIMLibrary() {
        if (sIsLoadLibrarySuccess) {
            return true;
        }
        try {
            System.loadLibrary("study");
            sIsLoadLibrarySuccess = true;
            Log.i(TAG, "system load so library success, libStudy.so");
        } catch (UnsatisfiedLinkError e) {
            sIsLoadLibrarySuccess = false;
            Log.e(TAG, "system load so library failed, " + e.getMessage());
        } catch (Exception e) {
            sIsLoadLibrarySuccess = false;
            Log.e(TAG, "system load so library failed, " + e.getMessage());
        }
        return sIsLoadLibrarySuccess;
    }

    private static class JavaNativeMethodHolder {
        private static final JNIBaseManager nativeMethod = new JNIBaseManager();
    }

    public static JNIBaseManager getInstance() {
        return JNIBaseManager.JavaNativeMethodHolder.nativeMethod;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * 默认生成的native方法
     */
    public native String stringFromJNI();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //############## 由浅入深-至上而下 ################

    /**
     * 传参类型：整型(int/long/short/...)
     */
    public native int integerFromJNI(int num);

    /**
     * 传参类型：char
     */
    public native char charFromJNI(char ch);

    /**
     * 传参类型：string
     */
    public native String stringFromJNI(String str);

    /**
     * 传参类型：数组( int[]/ string[]/ ...)
     */
    public native int[] intArrayFromJNI(int[] num);

    /**
     * 传参类型：对象
     */
    public native DataBean objectFromJNI(DataBean obj);

    /**
     * 传参类型：集合-List<整型>
     */
    public native List<Integer> listIntegerFromJNI(List<Integer> list);

    /**
     * 传参类型：集合-List<String>
     */
    public native List<String> listStringFromJNI(List<String> listString);

    /**
     * 传参类型：集合-List<int[]>
     */
    public native List<int[]> listIntArrayFromJNI(List<int[]> listIntArray);

    /**
     * 传参类型：集合-List<Object>
     */
    public native List<DataBean> listObjectFromJNI(List<DataBean> listObject);

    /**
     * 传参类型：Map数组-Map<整型>
     */
    public native Map<Integer,Integer> mapIntegerFromJNI(Map<Integer,Integer> mapInteger);

    /**
     * 传参类型：Map数组-Map<String>
     */
    public native Map<String,String> mapStringFromJNI(Map<String,String> mapString);

    /**
     * 传参类型：Map数组-Map<int[]>
     */
    public native Map<Integer,int[]> mapIntegerArrayFromJNI(Map<Integer,int[]> mapIntegerArray);

    /**
     * 传参类型：Map数组-Map<Object>
     */
    public native Map<Integer,DataBean> mapObjectFromJNI(Map<Integer,DataBean> mapObject);

    /**
     * 传参类型：集合嵌套集合-List<List>
     */
    public native List<List<DataBean>> listListFromJNI(List<List<DataBean>> listList);

    /**
     * 传参类型：Map嵌套Map-Map<Map>
     */
    public native Map<Integer,Map<Integer,DataBean>> mapMapFromJNI(Map<Integer,Map<Integer,DataBean>> mapMap);

}