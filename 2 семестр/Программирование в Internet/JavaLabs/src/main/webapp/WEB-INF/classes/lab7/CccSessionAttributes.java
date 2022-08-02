package lab7;

import lab6.JavaBeans.CBean;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class CccSessionAttributes extends HttpServlet implements Servlet {
    CBean cBean;

    public CccSessionAttributes() {
        super();
        System.out.println("CccSessionAttributes: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("CccSessionAttributes:init");

        cBean = new CBean();
    }

    public void destroy() {
        super.destroy();
        System.out.println("CccSessionAttributes:destroy");
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

        if (CBeanParam.equals("new")) {
            cBean = new CBean();
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
        }

        if (session.getAttribute(sessionId) == null) {
            session.setAttribute(sessionId, cBean);
        }

        rq.getRequestDispatcher("/pages/lab7/CccSessionAttributesPage.jsp").forward(rq, rs);
    }
}
