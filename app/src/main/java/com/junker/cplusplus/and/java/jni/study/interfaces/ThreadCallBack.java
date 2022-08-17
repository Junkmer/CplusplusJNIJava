package com.junker.cplusplus.and.java.jni.study.interfaces;

import com.junker.cplusplus.and.java.jni.study.bean.DataBean;

public interface ThreadCallBack {
    void onSuccess(DataBean bean);
    void onError(int code,String desc);
}
