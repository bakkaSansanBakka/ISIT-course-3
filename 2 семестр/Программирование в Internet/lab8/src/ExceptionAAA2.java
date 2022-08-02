public class ExceptionAAA2 extends Exception{

    public String getMessage() {
        return "value cannot equal 0";
    }

    public void printStackTrace() {
        this.printStackTrace();
    }

    public String toString() {
        return "ExceptionAAA2";
    }
}
