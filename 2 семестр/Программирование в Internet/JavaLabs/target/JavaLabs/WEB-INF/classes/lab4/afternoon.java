package lab4;

import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class afternoon extends HttpServlet implements Servlet {
    public afternoon() {
        super();
        System.out.println("afternoon: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("afternoon:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("afternoon:destroy");
    }

    protected void service (HttpServletRequest rq, HttpServletResponse rs)
        throws ServletException, IOException
    {
        System.out.println("Servlet: Good Afternoon");

        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();
        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "Servlet: Good Afternoon" +
                "</body>" + "</html>");
    }
}
