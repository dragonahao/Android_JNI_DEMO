#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>
#include <android/log.h>  

// 获取数组的大小
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
// 指定要注册的类，对应完整的java类名
#define JNIREG_CLASS "com/qinwenchao/myjniexample/MainActivity"
#define JNIPAR_CLASS "com/qinwenchao/myjniexample/Person"

// log标签
#define  TAG    "Qinwenchao"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)



// jfieldID结构体，用于保存类“Person.java”的filedID
struct PersonOffsets
{
    jfieldID    name;
    jfieldID    age;
    jfieldID    height;
} gPersonOffsets;

// 与“Person.java”对应的结构体，用于保存数据，并将数据赋值给Person.java的成员
typedef struct tagPerson
{
    char    mName[10];
    int     mAge;
    float   mHeight;
}Person;


// 定义了3个Person
static Person gPersons[] = {
    {"skywang", 25, 175},
    {"eman"   , 30, 166},
    {"Dan"    , 51, 172},
};

 
#define GPERSON_NUM NELEM(gPersons)

/* 
 * 根据index获取Person信息。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        person : 输入参数，java对象
 *        index : 输入参数，序列号。
 */
JNIEXPORT jint JNICALL getPersonInfoByIndex(JNIEnv *env, jobject clazz, jobject person, jint index)
{

    // 若index无效，则直接返回-1。
    if ((int)index<0 || (int)index>=GPERSON_NUM)
        return -1;

    // 将Person数组(gPersons)中的第index个成员赋值给pPerson指针
    Person *pPerson = &gPersons[index];

    // 设置java对象person的mName
    jstring name = (*env)->NewStringUTF(env, pPerson->mName);
    (*env)->SetObjectField(env, person, gPersonOffsets.name, name);
    // 设置java对象person的mAge
    (*env)->SetIntField(env, person, gPersonOffsets.age, pPerson->mAge);
    // 设置java对象person的mHeight
    (*env)->SetFloatField(env, person, gPersonOffsets.height, pPerson->mHeight);

    LOGD("%s index:%d  mName:%s, mAge:%d, mHeight:%f\n", 
            __func__, index, pPerson->mName, pPerson->mAge, pPerson->mHeight);

    return 0;
}


// 初始化函数，用于获取Java中各个成员对应的fieldID。
static void nativeClassInit (JNIEnv *env)
{   
    jclass personClass = (*env)->FindClass(env, JNIPAR_CLASS);       
    // 获取Person的mName成员对应的FieldID，并保存到gPersonOffsets中
    gPersonOffsets.name     = (*env)->GetFieldID(env, personClass, "mName"  , "Ljava/lang/String;");        
    // 获取Person的mAge成员对应的FieldID，并保存到gPersonOffsets中
    gPersonOffsets.age      = (*env)->GetFieldID(env, personClass, "mAge"   , "I");
    // 获取Person的mHeight成员对应的FieldID，并保存到gPersonOffsets中
    gPersonOffsets.height   = (*env)->GetFieldID(env, personClass, "mHeight", "F");
}


/* 
 * 将字符串由JNI传递给Java
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 */
JNIEXPORT jstring JNICALL stringFromJni(JNIEnv *env, jobject clazz)
{
    // 将“Hello From jni”转行成jstring类型
    jstring str = (*env)->NewStringUTF(env, "Hello From Jni");
    return str;
}


/* 
 * 将字符串从java从到jni层。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        val : java传递给jni的string类型值。
 */
JNIEXPORT void JNICALL stringToJni(JNIEnv *env, jobject clazz, jstring val)
{
    // 将java传递给jni的string转行成char *类型。
    // const char * GetStringUTFChars(JNIEnv *env, jstring string, jboolean *isCopy);
    // env:JNI 接口指针。
    // string:Java 字符串对象。
    // isCopy:指向布尔值的指针，JNI_TRUE或JNI_FALSE。
    //         JNI_TRUE  —— 开新内存，然后把java中的string拷贝到这个内存中，然后返回指向这个内存地址的指针。
    //         JNI_FALSE —— 直接返回指向java中String内存的指针，这个时候千万不要改变这个内存的内容，这将破坏String在java中始终是常量这个原则。
    char *str = (char *)(*env)->GetStringUTFChars(env, val, JNI_FALSE);
    LOGD("%s str=%s\n", __func__, str);
}

/* 
 * 将“浮点数”由JNI传递给Java
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 */
JNIEXPORT jfloat JNICALL floatFromJni(JNIEnv *env, jobject clazz)
{
    return (jfloat)1.34;
}
/* 
 * 将“浮点数”从Java从到JNI层。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        val : java传递给jni的浮点数。
 */
JNIEXPORT void JNICALL floatToJni(JNIEnv *env, jobject clazz, jfloat val)
{
    float f = (float)val;
    LOGD("%s f=%f\n", __func__, f);
}

/* 
 * 将“整数”由JNI传递给Java
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 */
JNIEXPORT jint JNICALL intFromJni(JNIEnv *env, jobject clazz)
{
    return (jint)25;
}
/* 
 * 将“整数”从Java从到JNI层。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        val : java传递给jni的整数。
 */
JNIEXPORT void JNICALL intToJni(JNIEnv *env, jobject clazz, jint val)
{
    int i = (int)val;
    LOGD("%s i=%d\n", __func__, i);
}


// 返回字符串"hello load jni"
JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass clazz)
{
    return (*env)->NewStringUTF(env, "hello All");
}


JNIEXPORT void JNICALL sayHello(JNIEnv *env, jobject clazz){  
    //因为test不是静态函数，所以传进来的就是调用这个函数的对象  
    //否则就传入一个jclass对象表示native()方法所在的类  
    jclass person_clazz = (*env)->GetObjectClass(env,clazz);  
    //得到jfieldID  
    jfieldID fieldID_name = (*env)->GetFieldID(env,person_clazz,"mName","Ljava/lang/String;");  
    jfieldID fieldID_age = (*env)->GetFieldID(env,person_clazz,"mAge","I");  
    jfieldID fieldID_height = (*env)->GetFieldID(env,person_clazz,"mHeight","F");
    jfieldID fieldID_count = (*env)->GetStaticFieldID(env,person_clazz,"count","I");
  
    //得到jmethodID  
    jmethodID getInfoPublic_func=(*env)->GetMethodID(env,person_clazz,"getInfoPublic","()Ljava/lang/String;");  
    //得到jmethodID  
    jmethodID getInfoPrivate_func=(*env)->GetMethodID(env,person_clazz,"getInfoPrivate","()Ljava/lang/String;");  
    //得到jmethodID  
    jmethodID getInfoStatic_func=(*env)->GetStaticMethodID(env,person_clazz,"getInfoStatic","(I)Ljava/lang/String;");  
     

    //调用方法  
    jobject result1 = (*env)->CallObjectMethod(env,clazz,getInfoPublic_func);  
    char *str1 = (char *)(*env)->GetStringUTFChars(env, (jstring)result1, JNI_FALSE);
    LOGD("调用java公有函数result：%s\n",str1);

    jobject result2 = (*env)->CallObjectMethod(env,clazz,getInfoPrivate_func);  
    char *str2 = (char *)(*env)->GetStringUTFChars(env, (jstring)result2, JNI_FALSE);
    LOGD("调用java私有函数result：%s\n",str2  );

    //得到count属性
    jint count = (*env)->GetStaticIntField(env,person_clazz,fieldID_count);
    count++;
    LOGD("count值:%d\n",(int)count);

    jobject result3 = (*env)->CallStaticObjectMethod(env,person_clazz,getInfoStatic_func,count);  
    char *str3 = (char *)(*env)->GetStringUTFChars(env, (jstring)result3, JNI_FALSE);
    LOGD("调用java静态函数result：%s\n",str3);
    //得到name属性  
    jobject name = (*env)->GetObjectField(env,clazz,fieldID_name);  
    
    char *str = (char *)(*env)->GetStringUTFChars(env, (jstring)name, JNI_FALSE);
    LOGD("name：%s\n",str);
    //得到age属性  
    jint age= (*env)->GetIntField(env,clazz,fieldID_age);   
    //得到height属性
    jfloat height= (*env)->GetFloatField(env,clazz,fieldID_height);  
    LOGD("修改age值前： age=%d\n", (int)age);
    //修改number属性的值  
    (*env)->SetIntField(env,clazz,fieldID_age,50);    
    age= (*env)->GetIntField(env,clazz,fieldID_age);    
    LOGD("修改age值后： age=%d\n", (int)age);
 }  


// Java和JNI函数的绑定表
static JNINativeMethod method_table[] = {
    { "stringFromJNIDynamic", "()Ljava/lang/String;", (void*)native_hello },//绑定
    { "intFromJni", "()I", (void*)intFromJni},
    { "intToJni", "(I)V", (void*)intToJni},
    { "floatFromJni", "()F", (void*)floatFromJni},
    { "floatToJni", "(F)V", (void*)floatToJni},
    { "stringFromJni", "()Ljava/lang/String;", (void*)stringFromJni},
    { "stringToJni", "(Ljava/lang/String;)V", (void*)stringToJni},
    { "getPersonInfoByIndex", "(Lcom/qinwenchao/myjniexample/Person;I)I", (void*)getPersonInfoByIndex},
};


static JNINativeMethod method_table1[] = {
   {"sayHello", "()V", (void*)sayHello},
};

// 注册native方法到java中
static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

int register_ndk_load(JNIEnv *env)
{
    nativeClassInit(env);
    // 调用注册方法
    registerNativeMethods(env, JNIPAR_CLASS,
            method_table1, NELEM(method_table1));
    return registerNativeMethods(env, JNIREG_CLASS,
            method_table, NELEM(method_table));
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1; 

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }   

    register_ndk_load(env);

    // 返回jni的版本
    return JNI_VERSION_1_4;
}


 