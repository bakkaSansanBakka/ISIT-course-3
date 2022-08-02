package packPerson.packStudent.packA;
import java.util.Date;

public class AAA implements packPerson.packStudent.Student {
    public int MaxUniversityLength = 100;
    public int limitYearOfBirth = 1900;
    private String university;
    private String surname;
    private String name;
    private String fathername;
    private Date birthday;
    private Date firstDate;

    public void setFirstDate(Date date) {
        firstDate = date;
    }
    public void setUniversity(String university) {
        this.university = university;
    }
    public void setSurname(String surname) {
        this.surname = surname;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setFathername(String fathername) {
        this.fathername = fathername;
    }
    public void setBirthday(int year, int month, int day) {
        this.birthday = new Date(year, month, day);
    }

    public String getSurname() {
        return surname;
    }
    public String getUniversity() {
        return university;
    }
    public String getName() {
        return name;
    }
    public String getFathername() {
        return fathername;
    }
    public Date getBirthday() {
        return birthday;
    }
    public Date getFirstDate() {
        return firstDate;
    }
}
