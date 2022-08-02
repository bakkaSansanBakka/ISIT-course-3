package lab5.TagHandlers;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;
import java.io.IOException;

public class Dossier extends TagSupport {
    static String in = "";
    public String action = "";

    public String getAction() {
        return this.action;
    }

    public void setAction(String action) {
        this.action = action;
    }

    public int doStartTag() throws JspException {
        String in = "<form id =\"f01\" name = \"formTag\" method = \"post\"" + " action=\"TttTagsServlet\" \"" + this.action + "\">";
        JspWriter out = pageContext.getOut();
        try {
            out.print(in);
        } catch (IOException e) {
            System.out.println("TagLibrary.Dossier: error: " + e);
        }
        return EVAL_BODY_INCLUDE;
    }

    public int doEndTag() throws JspException {
        String in = "</form>";
        JspWriter out = pageContext.getOut();
        try {
            out.print(in);
        } catch (IOException e) {
            System.out.println("TagLibrary.Dossier: " + e);
        }
        return EVAL_BODY_INCLUDE;
    }
}
