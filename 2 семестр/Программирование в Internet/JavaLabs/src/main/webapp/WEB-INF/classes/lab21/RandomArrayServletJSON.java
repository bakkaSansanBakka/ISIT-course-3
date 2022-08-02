package lab21;

import Utils.RandomNumberArrayGenerator;
import org.json.simple.*;


import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.Random;

public class RandomArrayServletJSON extends HttpServlet implements Servlet {
    public RandomArrayServletJSON() {
        super();
        System.out.println("RandomArrayServletJSON: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("RandomArrayServletJSON:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("RandomArrayServletJSON:destroy");
    }

    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        if(req.getParameter("timeout") != null) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        Random random = new Random();
        int randomAmount = random.nextInt(10 - 5) + 5;

        var headern = req.getHeader("XRand-N");
        System.out.println(headern);
        Integer n = Integer.parseInt(headern);
        RandomNumberArrayGenerator num = new RandomNumberArrayGenerator(n);
        resp.setContentType("application/json");
        PrintWriter w = resp.getWriter();

        JSONObject jo = new JSONObject();
        JSONArray ja = new JSONArray();
        var randoms = new RandomNumberArrayGenerator(n);
        for(var i = 0; i < randomAmount; i++) {
            ja.add(randoms.Get());
        }

        jo.put("nums", ja);
        w.write(jo.toJSONString());
    }
}
