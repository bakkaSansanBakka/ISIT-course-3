package packPerson.packStudent;
import java.util.Date;

public interface Student extends packPerson.Person {
    public int MaxUniversityLength = 100;

    public void setFirstDate(Date date);
    public Date getFirstDate();
    public void setUniversity(String university);
    public String getUniversity();
}
