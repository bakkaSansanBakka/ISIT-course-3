<%@ page import="lab6.JavaBeans.CBean" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>CccContextAttributes page</title>
</head>
<body>
<%
    CBean cBean = (CBean)request.getAttribute("atrCBean");
%>
<% if(cBean == null) { %>
<span>Bean is null</span>
<%} else {%>
<%=request.getParameter("CBean")%>
<p>Value1 = <%=cBean.GetValue1()%></p>
<p>Value2 = <%=cBean.GetValue2()%></p>
<p>Value3 = <%=cBean.GetValue3()%></p>
<%}%>
</body>
</html>
