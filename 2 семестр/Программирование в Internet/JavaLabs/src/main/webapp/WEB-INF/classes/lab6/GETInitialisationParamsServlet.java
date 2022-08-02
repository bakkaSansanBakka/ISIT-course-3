package lab6;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.methods.GetMethod;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class GETInitialisationParamsServlet extends HttpServlet implements Servlet {
    public GETInitialisationParamsServlet() {
        super();
        System.out.println("GETInitialisationParamsServlet: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("GETInitialisationParamsServlet:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("GETInitialisationParamsServlet:destroy");
    }

    protected void doGet (HttpServletRequest rq, HttpServletResponse rs)
        throws ServletException, IOException
    {
        if("1".equals(rq.getParameter("urln")))
        {
            rs.sendRedirect(rq.getServletContext().getInitParameter("URL1"));
        }
        else if("2".equals(rq.getParameter("urln")))
        {
            rs.sendRedirect(rq.getServletContext().getInitParameter("URL2"));
        }
        else
        {
            rs.setContentType("text/html");
            PrintWriter pw = rs.getWriter();
            pw.println("parameter URLn not found");
        }
    }
}
