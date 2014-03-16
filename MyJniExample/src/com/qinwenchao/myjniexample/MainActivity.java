package com.qinwenchao.myjniexample;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends Activity {
    private String TAG="Qinwenchao";
	private int ival;
	private float fval;
	private String str;
	private Person person=null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		TextView tv = new TextView(this);
		tv.setText(stringFromJNIDynamic() + "\r\n" /*+ stringFromJNIStatic()*/);
		setContentView(tv);
		    
		    Log.d(TAG, "onCreate");
	        // 获取从jni传来的整数
	        ival = intFromJni();
	        Log.d(TAG, "ival="+ival);
	        // 将整数传递到jni
	        intToJni((int)123); 
	        // 获取从jni传来的float
	        fval = floatFromJni();
	        Log.d(TAG, "fval="+fval);
	        // 将float传递到jni
	        floatToJni((float)456.78);
	        // 获取从jni传来的string
	        str = stringFromJni(); 
	        Log.d(TAG, "str="+str);
	        // 将string传递到jni
	        stringToJni("Hello From Java");
	        
	        
	        person = new Person();
	        for (int i=0; i<3; i++) {
	            getPersonInfoByIndex(person, i);
	            Log.d(TAG, "person["+i+"] -- "+person);
	            person.sayHello();
	        }
	}

	/*
	 * A native method that is implemented by the 'hello-jni' native library,
	 * which is packaged with this application.
	 */
	public native String stringFromJNIStatic();

	/*
	 * This is another native method declaration that is *not* implemented by
	 * 'hello-jni'. This is simply to show that you can declare as many native
	 * methods in your Java code as you want, their implementation is searched
	 * in the currently loaded native libraries only the first time you call
	 * them.
	 * 
	 * Trying to call this function will result in a
	 * java.lang.UnsatisfiedLinkError exception !
	 */
	public native String stringFromJNIDynamic();

	/*
	 * this is used to load the 'hello-jni' library on application startup. The
	 * library has already been unpacked into
	 * /data/data/com.example.hellojni/lib/libhello-jni.so at installation time
	 * by the package manager.
	 */
	static {
		//System.loadLibrary("hello-jni");
		System.loadLibrary("controller-jni");
	}
	  // jni中注册的方法
    private native int intFromJni();
    private native void intToJni(int val);
    private native float floatFromJni();
    private native void floatToJni(float val);
    private native String stringFromJni();
    private native void stringToJni(String val);
    private native int getPersonInfoByIndex(Person person, int index);
    @Override
    public void onBackPressed() {
    	finish();
    }
}
