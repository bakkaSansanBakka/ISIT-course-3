package lab24;

import org.apache.catalina.servlets.WebdavServlet;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.net.URLEncoder;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class WebDavServlet extends WebdavServlet {
    final String WebDavServerUrl = "https://webdav.yandex.ru/";

    HttpRequest.Builder initClient() {
        var builder = HttpRequest.newBuilder();
        var token = getServletContext().getInitParameter("webdavtoken");
        var base64Token = Base64.getEncoder().encodeToString(token.getBytes());
        builder.setHeader("Authorization", "Basic " + base64Token);
        return builder;
    }

    protected void OutputDoc(String fileName, HttpResponse<InputStream> webdavResponse, HttpServletResponse rs)
            throws IOException {
        rs.setContentType(webdavResponse.headers().firstValue("Content-Type").orElse("application/msword"));
        rs.addHeader("Content-Disposition", "attachment; filename=" + fileName);
        rs.setContentLength(Integer.parseInt(webdavResponse.headers().firstValue("Content-Length").orElse("0")));

        BufferedInputStream buf = new BufferedInputStream(webdavResponse.body());
        ServletOutputStream out = rs.getOutputStream();
        int readBytes = 0;
        while ((readBytes = buf.read()) != -1) out.write(readBytes);

    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws IOException, ServletException {
        HttpClient client = HttpClient.newHttpClient();

        var encodedFilePath = URLEncoder.encode(req.getParameter("file"), StandardCharsets.UTF_8);
        var reqBuilder = initClient().uri(URI.create(WebDavServerUrl + encodedFilePath));

        reqBuilder.GET();

        HttpResponse<InputStream> httpResponse = null;
        try {
            httpResponse = client.send(reqBuilder.build(), HttpResponse.BodyHandlers.ofInputStream());
            if (httpResponse.statusCode() == 200) {
                OutputDoc(req.getParameter("file"), httpResponse, resp);
            } else {
                resp.sendError(httpResponse.statusCode());

                return;
            }
        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void doDelete(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpClient client = HttpClient.newHttpClient();

        var encodedFilePath = URLEncoder.encode(req.getParameter("file"), StandardCharsets.UTF_8);
        var reqBuilder = initClient().uri(URI.create(WebDavServerUrl + encodedFilePath));

        reqBuilder.DELETE();

        HttpResponse<InputStream> httpResponse = null;
        try {
            httpResponse = client.send(reqBuilder.build(), HttpResponse.BodyHandlers.ofInputStream());
            if (IsStatusValid(httpResponse.statusCode())) {
                resp.getWriter().println(httpResponse.statusCode());
            } else {
                resp.sendError(httpResponse.statusCode());
                return;
            }
        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void doMkcol(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpClient client = HttpClient.newHttpClient();

        var encodedFilePath = URLEncoder.encode(req.getParameter("path"), StandardCharsets.UTF_8);
        var reqBuilder = initClient().uri(URI.create(WebDavServerUrl + encodedFilePath));

        reqBuilder.method("MKCOL", HttpRequest.BodyPublishers.noBody());
        HttpResponse<String> httpResponse = null;

        try {
            httpResponse = client.send(reqBuilder.build(), HttpResponse.BodyHandlers.ofString());
            if (IsStatusValid(httpResponse.statusCode())) {
                resp.getWriter().println(httpResponse.statusCode());

            } else {
                resp.sendError(httpResponse.statusCode());

                return;
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    @Override
    protected void doPut(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpClient client = HttpClient.newHttpClient();

        var encodedFilePath = URLEncoder.encode(req.getParameter("path"), StandardCharsets.UTF_8);
        var reqBuilder = initClient().uri(URI.create(WebDavServerUrl + encodedFilePath));

        reqBuilder.method("PUT", HttpRequest.BodyPublishers.ofByteArray(req.getInputStream().readAllBytes()));
        HttpResponse<String> httpResponse = null;

        try {
            httpResponse = client.send(reqBuilder.build(), HttpResponse.BodyHandlers.ofString());
            if (IsStatusValid(httpResponse.statusCode())) {

                resp.getWriter().println(httpResponse.statusCode());

            } else {
                resp.sendError(httpResponse.statusCode());

                return;
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    @Override
    protected void doCopy(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        HttpClient client = HttpClient.newHttpClient();

        var encodedFilePath = URLEncoder.encode(req.getParameter("from"), StandardCharsets.UTF_8);
        var reqBuilder = initClient().uri(URI.create(WebDavServerUrl + encodedFilePath));

        reqBuilder.method("COPY", HttpRequest.BodyPublishers.ofByteArray(req.getInputStream().readAllBytes()));
        reqBuilder.setHeader("Destination", WebDavServerUrl + req.getParameter("to"));
        reqBuilder.setHeader("Overwrite", "T");
        HttpResponse<String> httpResponse = null;

        try {
            httpResponse = client.send(reqBuilder.build(), HttpResponse.BodyHandlers.ofString());
            if (IsStatusValid(httpResponse.statusCode())) {
                resp.getWriter().println(httpResponse.statusCode());

                return;
            } else {
                resp.sendError(httpResponse.statusCode());

                return;
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    Boolean IsStatusValid(int status) {
        return status >= 200 && status < 300;
    }
}
