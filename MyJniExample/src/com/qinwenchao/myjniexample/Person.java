package com.qinwenchao.myjniexample;

import android.R.integer;

public class Person {
	private String  mName;                     
    private int     mAge;
    private float   mHeight;
    private static int count;
    
    public String toString(){
    	count++;
        return "mName:"+mName+", mAge:"+mAge+", mHeight:"+mHeight;
    }
    
    public String getInfoPublic()
    {
    	return "PUBLIC METHOD";
    }
    
    private String getInfoPrivate()
    {
    	return "PRIVATE METHOD";
    }
    
    public static String getInfoStatic(int count)
    {
    	Person.count=count;
    	return "STATIC METHOD";
    }
    public native void sayHello(); 
}
