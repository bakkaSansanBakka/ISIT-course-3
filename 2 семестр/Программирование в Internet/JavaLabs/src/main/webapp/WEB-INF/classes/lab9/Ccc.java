package lab9;

import lab6.JavaBeans.CBean;

import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class Ccc extends HttpServlet implements Servlet {
    CBean cBean;

    public Ccc() {
        super();
        System.out.println("Ccc: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("Ccc:init");

        cBean = new CBean();
    }

    public void destroy() {
        super.destroy();
        System.out.println("Ccc:destroy");
    }

    protected void service (HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException
    {
        String CBeanParam = rq.getParameter("CBean");
        String Value1 = rq.getParameter("Value1");
        String Value2 = rq.getParameter("Value2");
        String Value3 = rq.getParameter("Value3");

        HttpSession session = rq.getSession();
        String sessionId = session.getId();

        if (CBeanParam.equals("new"))
        {
            cBean = new CBean();
        }

        if (!(Value1 == null))
        {
            cBean.SetValue1(Value1);
        }

        if (!(Value2 == null))
        {
            cBean.SetValue2(Value2);
        }

        if (!(Value3 == null))
        {
            cBean.SetValue3(Value3);
        }

        if (session.getAttribute(sessionId) == null) {
            session.setAttribute(sessionId, cBean);
        }

        rq.getRequestDispatcher("/pages/lab7/CccSessionAttributesPage.jsp").forward(rq, rs);
    }
}
