import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

public class GggRedirect extends HttpServlet implements Servlet {
    public GggRedirect() {
        super();
        System.out.println("GggRedirect: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("GggRedirect:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("GggRedirect:destroy");
    }

    protected void doGet(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {

        String param = rq.getParameter("param");
        System.out.println("GggRedirect:doGet:param = " + param);

        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();
        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "GggRedirect:doGet: param = " + param +
                "</body>" + "</html>");

        rs.sendRedirect("http://localhost:8080/JavaLabs/servletRedirect.html");
    }

    protected void doPost(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException
    {
        System.out.println("GggRedirect:doPost");

        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();
        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "GggRedirect:doPost" +
                "</body>" + "</html>");
    }
}
