package packPerson;

public interface Person {
    public int limitYearOfBirth = 1900;

    public void setSurname(String surname);
    public void setName(String name);
    public void setFathername(String fathername);
    public void setBirthday(int year, int month, int day);

    public String getSurname();
    public String getName();
    public String getFathername();
    public java.util.Date getBirthday();
}
