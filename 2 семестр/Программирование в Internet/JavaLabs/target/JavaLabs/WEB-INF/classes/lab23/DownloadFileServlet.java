package lab23;

import javax.servlet.*;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.*;
import java.io.*;

@MultipartConfig(fileSizeThreshold = 1024 * 1024,
        maxFileSize = 1024 * 1024 * 5,
        maxRequestSize = 1024 * 1024 * 5 * 5)
public class DownloadFileServlet extends HttpServlet implements Servlet {
    public DownloadFileServlet() {
        super();
        System.out.println("DownloadFileServlet: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("DownloadFileServlet:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("DownloadFileServlet:destroy");
    }

    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        var dir = req.getServletContext().getInitParameter("doc-dir");
        System.out.println(dir);

        var fileName = req.getParameter("file");

        if(fileName.equals("")) {
            resp.getWriter().write("No file provided");
            System.out.println("No file provided");
            return;
        }

        System.out.println("Getting file " + dir + "/" + fileName);

        File file = new File(dir + "/" + fileName);
        OutputDoc(file, resp);

        resp.getWriter().write("File " + fileName);
    }

    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        final Part filePart = req.getPart("file");
        final String fileName = getFileName(filePart);
        var dir = req.getServletContext().getInitParameter("doc-dir");

        OutputStream out = null;
        InputStream filecontent = null;
        final PrintWriter writer = resp.getWriter();

        try {
            out = new FileOutputStream(new File(dir + File.separator  + fileName));
            filecontent = filePart.getInputStream();

            int read = 0;
            final byte[] bytes = new byte[1024];

            while ((read = filecontent.read(bytes)) != -1) {
                out.write(bytes, 0, read);
            }
            writer.println("New file " + fileName + " created at " + dir);
        } catch (FileNotFoundException fne) {
            writer.println("You either did not specify a file to upload or are "
                    + "trying to upload a file to a protected or nonexistent "
                    + "location.");
            writer.println("<br/> ERROR: " + fne.getMessage());

        } finally {
            if (out != null) {
                out.close();
            }
            if (filecontent != null) {
                filecontent.close();
            }
            if (writer != null) {
                writer.close();
            }
        }
    }

    protected void OutputDoc(File doc, HttpServletResponse rs)
            throws IOException {
        rs.setContentType("application/msword");
        rs.addHeader("Content-Disposition", "attachment; filename="+ doc.getName());
        rs.setContentLength((int) doc.length());

        try(FileInputStream in = new FileInputStream(doc);)
        {
            BufferedInputStream buf = new BufferedInputStream(in);
            ServletOutputStream out = rs.getOutputStream();
            int readBytes = 0;
            while ((readBytes = buf.read()) != -1)
                out.write(readBytes);
        }

    }

    private String getFileName(final Part part) {
        final String partHeader = part.getHeader("content-disposition");
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(
                        content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}
