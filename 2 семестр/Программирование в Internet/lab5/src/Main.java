import BPack1.AA1;
import BPack1.BPack2.AAA2;
import BPack1.BPack2.BB2;
import BPack1.BPack2.BPack3.BPack4.AA4;
import BPack1.BPack2.BPack3.BPack4.BB4;

import pack1.A1;
import pack1.pack2.pack3.pack4.A4;

public class Main {

    public static void main(String[] args) {
        //1
        pack1.A1 a1 = new pack1.A1(10);
        a1.printInfo();

        pack1.pack2.A2 a2 = new pack1.pack2.A2(10);
        a2.printInfo();
        pack1.pack2.B2 b2 = new pack1.pack2.B2(10);
        b2.printInfo();

        pack1.pack2.pack3.pack4.A4 a4 = new pack1.pack2.pack3.pack4.A4(10);
        a4.printInfo();
        pack1.pack2.pack3.pack4.B4 b4 = new pack1.pack2.pack3.pack4.B4(10);
        b4.printInfo();

        //2
        A4 a41 = new A4(15);
        a41.printInfo();

        //3
        A1 a11 = new A1(11);
        a11.printInfo();

        //4
        //import all

        //5
        AA1 aa1 = new AA1(24);
        aa1.printInfo();

        AAA2 aaa2 = new AAA2(35);
        aaa2.printInfo();
        BB2 bb2 = new BB2(78);
        bb2.printInfo();

        AA4 aa4 = new AA4(637);
        aa4.printInfo();
        BB4 bb4 = new BB4(632);
        bb4.printInfo();

        //6
        aa1.useAClass();

        //7
        A1 newA1 = new A1(33);
        newA1.printInfo();
        newA1.useAClass();
    }
}
