import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

public class PppRedirect extends HttpServlet implements Servlet {
    public PppRedirect() {
        super();
        System.out.println("PppRedirect: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("PppRedirect:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("PppRedirect:destroy");
    }

    protected void service(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {

        String phoneNumber = rq.getParameter("phoneNumber");
        String email = rq.getParameter("emailAddr");
        System.out.println("PppRedirect:service:phone number = " + phoneNumber);
        System.out.println("PppRedirect:service:email = " + email);

        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();
        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "PppRedirect:service: phone number = " + phoneNumber +
                "<br>PppRedirect:service: email = " + email +
                "</body>" + "</html>");

        rs.sendRedirect("http://localhost:8080/JavaLabs/GggRedirect");
    }

    protected void doGet(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {

        System.out.println("PppRedirect:doGet");

        String param = rq.getParameter("param");
        System.out.println("PppRedirect:param = " + param);

        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();
        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "PppRedirect:doGet: param = " + param +
                "</body>" + "</html>");

        rs.sendRedirect("http://localhost:8080/JavaLabs/GggRedirect?param=" + param);
    }
}
