import packPerson.packStudent.packA.*;
import packPerson.packStudent.*;
import packPerson.*;

import java.util.Date;

public class Main {

    public static void main(String[] args) {
        AAA aaa = new AAA();

        Date firsDate = new Date(2019, 9, 1);

        aaa.setName("Igor");
        aaa.setSurname("Nikolaev");
        aaa.setFathername("Alexandrovich");
        aaa.setBirthday(2001, 11, 14);
        aaa.setUniversity("BSTU");
        aaa.setFirstDate(firsDate);

        System.out.println("Name: " + aaa.getName());
        System.out.println("Surname: " + aaa.getSurname());
        System.out.println("Fathername: " + aaa.getFathername());
        System.out.println("Birthday: " + aaa.getBirthday());
        System.out.println("University: " + aaa.getUniversity());
        System.out.println("First date of university: " + aaa.getFirstDate());
    }
}
