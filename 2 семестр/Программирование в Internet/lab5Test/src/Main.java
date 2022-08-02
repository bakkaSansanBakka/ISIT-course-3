package com.dufilt;
import B2.B3.B4.B4_1;
import B1.B1_1;
import B2.*;
import com.dufilt.A1.A1_1;
import com.dufilt.A1.A2.A2_1;
import com.dufilt.A1.A2.A2_2;
import com.dufilt.A1.A2.A3.A4.A4_1;


public class Main {

    public static void main(String[] args) {
        var a4_1 = new A4_1(41);
        var a1_1 = new A1_1(11);
        var a2_1 = new A2_1(21);
        var a2_2 = new A2_2(22);

        var b4_1 = new B4_1(41);
        var b1_1 = new B1_1(11);
        var b2_1 = new B2_1(21);
        var b2_2 = new B2_2(22);

        a4_1.Print();
        a1_1.Print();
        a2_1.Print();
        a2_2.Print();

        b4_1.Print();
        b1_1.Print();
        b1_1.A(a2_1);
        b2_1.Print();
        b2_2.Print();

        var a4_1_b2 = new A4_1(412);
        a4_1_b2.Print();
    }
}
