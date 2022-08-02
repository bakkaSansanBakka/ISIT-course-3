import p1.P1Class;
import p1.p2.P2Class;
import p1.p2.p3.P3Class;
import p1.p2.p3.p4.P4Class;

public class MMM {

    public static void main(String[] args) {
        p1.P1Class p1Class = new P1Class();
        p1.p2.P2Class p2Class = new P2Class();
        p1.p2.p3.P3Class p3Class = new P3Class();
        p1.p2.p3.p4.P4Class p4Class = new P4Class();
        AAA aaa = new AAA();

        p1Class.printClassname();
        p2Class.printClassname();
        p3Class.printClassname();
        p4Class.printClassname();
        aaa.printClassname();
        aaa.printHello();
    }
}
