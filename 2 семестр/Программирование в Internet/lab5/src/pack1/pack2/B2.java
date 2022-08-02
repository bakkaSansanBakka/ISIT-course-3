package pack1.pack2;

public class B2 {
    public int numField;

    public B2(int num) {
        numField = num;
    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }
}
