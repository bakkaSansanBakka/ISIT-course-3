package lab5;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class TttTagsServlet extends HttpServlet implements Servlet {
    public TttTagsServlet() {
        super();
        System.out.println("TttTagsServlet: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("TttTagsServlet:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("TttTagsServlet:destroy");
    }

    protected void doPost (HttpServletRequest rq, HttpServletResponse rs)
        throws ServletException, IOException
    {
        String surname = rq.getParameter("surname");
        String lastname = rq.getParameter("lastname");
        String sex = rq.getParameter("sex");

        System.out.println("TttTagsServlet:doPost: surname = " + surname);
        System.out.println("TttTagsServlet:doPost: lastname = " + lastname);
        System.out.println("TttTagsServlet:doPost: sex = " + sex);


        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();
        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "TttTagsServlet:doPost: surname = " + surname +
                "<br>TttTagsServlet:doPost: lastname = " + lastname +
                "<br>TttTagsServlet:doPost: sex = " + sex +
                "</body>" + "</html>");
    }
}
