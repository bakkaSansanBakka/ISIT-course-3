package lab21;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.Random;

import Utils.RandomNumberArrayGenerator;

public class RandomArrayServletXML extends HttpServlet implements Servlet {
    public RandomArrayServletXML() {
        super();
        System.out.println("RandomArrayServletXML: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("RandomArrayServletXML:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("RandomArrayServletXML:destroy");
    }

    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        if(req.getParameter("timeout") != null) {
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        Random random = new Random();
        int randomAmount = random.nextInt(10 - 5) + 5;

        var headern = req.getHeader("XRand-N");
        Integer n = Integer.parseInt(headern);
        RandomNumberArrayGenerator num = new RandomNumberArrayGenerator(n);
        resp.setContentType("text/xml");
        PrintWriter w = resp.getWriter();

        String s = "<?xml version=\"1.0\" encoding = \"utf-8\" ?><rand>" ;
        for (int i = 0; i < randomAmount; i++)
        {
            s += "<num>"+num.Get().toString()+"</num>";
        }

        s += "</rand>";
        System.out.println(s);
        w.println(s);
    }
}
