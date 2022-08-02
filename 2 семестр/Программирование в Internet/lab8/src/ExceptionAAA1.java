public class ExceptionAAA1 extends Exception{

    public String getMessage() {
        return "value cannot be null";
    }

    public void printStackTrace() {
        this.printStackTrace();
    }

    public String toString() {
        return "ExceptionAAA1";
    }
}
