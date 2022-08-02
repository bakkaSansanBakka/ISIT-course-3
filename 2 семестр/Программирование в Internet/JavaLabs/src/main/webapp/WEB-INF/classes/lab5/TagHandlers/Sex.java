package lab5.TagHandlers;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;
import java.io.IOException;

public class Sex extends TagSupport {
    static String in = "<label>Sex</label>"
            + "<input name =\"sex\" type = \"radio\" width = \"150\" value = \"male\" checked = \"checked\" "
            + " maxlength= \"30\" />male "
            + "<input name =\"sex\" type = \"radio\" width = \"150\" value = \"female\" "
            + " maxlength= \"30\" />female";

    public int doStartTag() throws JspException {
        JspWriter out = pageContext.getOut();
        try
        {
            out.print(in);
        }
        catch (IOException e) {
            System.out.println("TagHandlers.Sex: error: " + e);
        }
        return SKIP_BODY;
    }
}
