package lab8;

import lab3.InOutServlet;
import org.apache.commons.httpclient.*;
import org.apache.commons.httpclient.methods.PostMethod;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;

public class Aaa extends HttpServlet implements Servlet {
    public Aaa() {
        super();
        System.out.println("Aaa: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("Aaa:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("Aaa:destroy");
    }

    protected void doPost(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {
        System.out.println("Aaa:doPost: forming POST request in servlet to Bbb remote servlet");

        HttpClient hc = new HttpClient();

        PostMethod pm = new PostMethod("http://192.168.140.92:8080/JavaLabs_war/Bbb?press=OK");

        NameValuePair[] parms = { new NameValuePair("Header1", "header1Value"),
                new NameValuePair("Header2", "header2Value"),
                new NameValuePair("Header3", "header3Value")};
        pm.addParameters(parms);

        pm.addRequestHeader("Header1", "header1Value");
        pm.addRequestHeader("Header2", "header2Value");
        pm.addRequestHeader("Header3", "header3Value");

        hc.executeMethod(pm);
        PrintWriter pw = rs.getWriter();

        pw.println(new String(pm.getResponseBody()));
        pw.println("<br>response headers: ");

        var enh = pm.getResponseHeaders();
        for (org.apache.commons.httpclient.Header header : enh) {
            pw.println(header.getName() + " = " + header.getValue() + "<br>");
        }
    }
}
