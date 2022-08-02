package lab5.TagHandlers;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;
import java.io.IOException;

public class Submit extends TagSupport {

    public int doStartTag() throws JspException {
        String in = "<label>Submit</label>"
                + "<input name =\"pressOK\" type = \"submit\" width = \"150px\" value = \"OK\" />"
                + "<input name =\"pressCancel\" type = \"submit\" width = \"150px\" value = \"Cancel\" />";

        JspWriter out = pageContext.getOut();
        try
        {
            out.print(in);
        }
        catch (IOException e) {
            System.out.println("TagHandlers.Submit: error: " + e);
        }
        return SKIP_BODY;
    }
}
