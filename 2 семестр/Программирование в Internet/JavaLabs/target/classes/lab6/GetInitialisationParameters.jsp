<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Get initialisation parameters page</title>
</head>
<body>
<% String parm = request.getParameter("parm");
    String url1 = getServletConfig().getServletContext().getInitParameter("URL1");
    String url2 = getServletConfig().getServletContext().getInitParameter("URL2");
%>
Parameter parm = <%=parm%>
<br> URL1 = <%=url1%>
<br> URL2 = <%=url2%>
</html>
