package lab6.JavaBeans;

public class CBean {
    protected String value1 = null;
    protected String value2 = null;
    protected String value3 = null;

    public CBean(String val1, String val2, String val3) {
        value1 = val1;
        value2 = val2;
        value3 = val3;
    }

    public CBean () {}

    public String GetValue1() {
        return value1;
    }

    public String GetValue2() {
        return value2;
    }

    public String GetValue3() {
        return value3;
    }

    public void SetValue1(String val1) {
        value1 = val1;
    }

    public void SetValue2(String val2) {
        value2 = val2;
    }

    public void SetValue3(String val3) {
        value3 = val3;
    }
}
