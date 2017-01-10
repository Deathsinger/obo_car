package obo.org.obo_car;

/**
 * Created by lw on 2017/1/9.
 */

public class OboJni {
    private static OboJni instance = null;
    private OboJni(){}
    public static OboJni getInstance(){
        if (instance == null){
            instance = new OboJni();
        }
        return instance;
    }

    ///>>>>>>>>>>>>>JNI API Start<<<<<<<<<<<<<///

    /* 登录 */
    public native boolean oboLogin(String username, String password, boolean isDriver);
    /* 注册 */
    public native boolean oboReg(String username, String password, String email, String tel, String idCard, boolean isDriver);

    ///>>>>>>>>>>>>>JNI API End<<<<<<<<<<<<<///

    /* 加载动态库 */
    static{
        System.loadLibrary("obojni");
    }
}
