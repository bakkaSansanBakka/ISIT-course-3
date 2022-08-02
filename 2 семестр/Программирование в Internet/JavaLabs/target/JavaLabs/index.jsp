<%@ page import="JSPClasses.Regimex" %>
<%@ page import="java.time.LocalDateTime" %>
<%@ page import="java.time.format.DateTimeFormatter" %>
<%@ page import="Utils.FileChooser" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <title>Time of day</title>
    <script
            src="https://code.jquery.com/jquery-2.2.4.min.js"
            integrity="sha256-BbhdlvQf/xTY9gja0Dq3HiwQF8LaCRTXxZKRutelT44="
            crossorigin="anonymous"></script>
    <%! String name = null;
        Regimex regimex = new Regimex();
        Integer n = regimex.GetHOUR();
        protected String Salutation(Integer h) {
            String rc = "Good ";
            if ((h > 0) && (h <= 5))
                rc += "night";
            else if ((h > 5) && (h <= 12))
                rc += "morning";
            else if ((h > 12) && (h <= 17))
                rc += "afternoon";
            else
                rc += "evening";
            return rc;
        }
    %>
    <%!
        protected String showContentOfTimePage(Integer h) {
            if ((h > 0) && (h <= 5))
                return "night.jsp";
            else if ((h > 5) && (h <= 12))
                return "morning.jsp";
            else if ((h > 12) && (h <= 17))
                return "afternoon.jsp";
            else
                return "evening.jsp";
        }
    %>
    <%
        final int TIME_TABLE_LEN = 7;
        LocalDateTime[] timeTable = new LocalDateTime[TIME_TABLE_LEN];
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy");
        for (int i = 0; i < TIME_TABLE_LEN; i++) {
            timeTable[i] = java.time.LocalDateTime.now().plusDays(i);
        }
    %>
</head>
<body style="font-size: 20px">
<%=Salutation(n)%>
<table>
    <thead>
    <th>Day</th>
    <th>Day of week</th>
    </thead>
    <tbody>
    <% for (LocalDateTime time : timeTable) {%>
    <tr>
        <td>
            <%=time.format(formatter)%>&nbsp;
        </td>
        <td>
            <%=time.getDayOfWeek()%>
        </td>
    </tr>
    <%}%>
    </tbody>
</table>
<form>
    <input type="submit" name = "T5" value="Press"/>
</form>

<% if("Press".equals(request.getParameter("T5"))){ %>
    <%if ((n >= 0) && (n <= 6)){%>
        <jsp:include page="night.jsp"/>
<%--        <%@ include file="night.jsp" %>--%>
    <%}else if ((n > 6) && (n <= 12)){%>
<%--        <%@ include file="morning.jsp" %>--%>
        <jsp:include page="morning.jsp"/>
    <%}else if ((n > 12) && (n <= 17)){%>
<%--        <%@ include file="afternoon.jsp" %>--%>
        <jsp:include page="afternoon.jsp"/>
    <%}else{%>
<%--        <%@ include file="evening.jsp" %>--%>
        <jsp:include page="evening.jsp"/>
    <%}%>
<%}%>

<form>
    <input type="submit" name = "T7" value="Add afternoon Servlet Contents"/>
</form>

<% if ("Add afternoon Servlet Contents".equals(request.getParameter("T7"))) { %>
    <jsp:include page="afternoon"/>
<%}%>

<form>
    <input type="submit" name = "T8" value="jsp:forward to afternoon servlet"/>
</form>

<% if ("jsp:forward to afternoon servlet".equals(request.getParameter("T8"))) { %>
<jsp:forward page="afternoon"></jsp:forward>
<%}%>

<br><a href="Jjj">Go to Jjj servlet</a>

<br><a href="Jjj">GET afternoon.jsp from Jjj servlet</a>

<form action="Jjj" method="post">
    <p><button type="submit">Press to send POST request to Jjj servlet</button></p>
</form>

<br><a href="TttUseTags.jsp">Go to TttUseTags.jsp page</a>

<br><p style="color:red">lab 6 - INITIALIZATION PARAMETERS</p>
<a href="InitParamsServlet?urln=1">Go to InitParamsServlet with urln = 1</a>
<br><a href="InitParamsServlet?urln=2">Go to InitParamsServlet with urln = 2</a>
<br><a href="InitParamsServlet">Go to InitParamsServlet with urln = null</a>

<br><br><a href="pages/lab6/GetInitialisationParameters.jsp?parm=ppp">Go to GetInitialisationParameters.jsp page</a>

<br><br><a href="CccContextAtributesServlet?CBean=old">
    Go to CccContextAttributesServlet with old CBean</a>

<br><a href="CccContextAtributesServlet?CBean=new&Value1=111&Value2=123">
    Go to CccContextAttributesServlet with new CBean, Value1 and Value2 initialised</a>

<br><p style="color:red">lab 7 - REQUEST AND SESSION ATTRIBUTES</p>
<a href="CccRequestAttributes?CBean=old&Value1=352">
    Go to CccRequestAttributes servlet with old CBean</a>
<br><a href="CccRequestAttributes?CBean=new&Value1=111&Value2=123">
    Go to CccRequestAttributes servlet with new CBean, Value1 and Value2 initialised</a>
<br><br><a href="CccSessionAttributes?CBean=old&Value1=352">
    Go to CccSessionAttributes servlet with old CBean</a>
<br><a href="CccSessionAttributes?CBean=new&Value1=111&Value2=123">
    Go to CccSessionAttributes servlet with new CBean, Value1 and Value2 initialised</a>

<br><p style="color:red">lab 8 - REQUEST AND RESPONSE HEADERS</p>
<p>Form POST request to Aaa servlet and get response from Bbb servlet with headers</p>
<form action="Aaa" method="post">
    <input type = "submit" name="press" value = "OK" size = "20">
</form>

<br><p style="color:red">lab 9 - FILTERS AND EVENT LISTENERS</p>
<a href="Ccc?CBean=old">Go to Ccc servlet without F1 filter block</a>
<br><a href="Ccc?block1=true">Go to Ccc servlet with F1 filter block</a>
<br><a href="Ccc?block2=true">Go to Ccc servlet with F2 filter block</a>
<br><a href="Ccc?block3=true">Go to Ccc servlet with F3 filter block</a>

<br><br><a href="pages/lab7/CccSessionAttributesPage.jsp">Go to CccSessionAttributesPage without F2 filter block</a>
<br><a href="pages/lab7/CccSessionAttributesPage.jsp?block2=true">Go to CccSessionAttributesPage with F2 filter block</a>

<br><p style="color:red">lab 10 - JDBC</p>
<a href="JDBCServlet">Go to JDBCServlet without specified book name</a>
<br><a href="JDBCServlet?bookName=Оно">Go to JDBCServlet with specified book name</a>
<br><a href="JDBCProcedureServlet?bookName=Оно">Go to JDBCProcedureServlet with book name and get its price</a>

<br><p style="color:red">lab 21 - AJAX</p>
<p>Task 1 - Servlet with request headers and response headers, JS for packing headers and send request to servlet</p>
<form id="simplesumform" name="FHeader" action="#" method="POST">
    x: <input name="x" type="text" value="0" size="5" maxlength="5" /><br>
    y: <input name="y" type="text" value="0" size="5" maxlength="5" /><br>
    <input name="add" value="Sum" type="button" size="10" maxlength="10" /><br>
    z: <input name="z" id="z" type="text" value="0" />
</form>

<p>Task 2 - Servlet with request header XRand-N that forms array of random numbers, then send xml doc to client</p>
<form id="nformxml" name="NHeader" action="#" method="POST">
    <input name="n" type="number" value="0"  />
    <input name="get" value="Get Array" type="button" size="10" /><br>
    <span id="xml" class="h2">xml array</span>
</form>

<p>Task 3 - Servlet with request header XRand-N that forms array of random numbers, then send JSON doc to client</p>
<form id="nformjson" name="NHeader" action="#" method="POST">
    <input name="n" type="number" value="0"  />
    <input name="get" value="Get" type="button" size="10" />
    <span id="json" class="h2">json array</span>
</form>

<p>Task 4 - Synchronous execution of form</p>
<form id="combined" method="POST">
    x: <input name="x" type="text" value="0" size="5" maxlength="5" /><br>
    y: <input name="y" type="text" value="0" size="5" maxlength="5" /><br>
    z: <input name="z" id="zz" type="text" value="0" /><br><br>

    <input name="nxml" type="number" value="0"  /><br>
    <span id="xml2" class="h2">xml array</span><br><br>

    <input name="njson" type="number" value="0"  /><br>
    <span id="json2" class="h2">json array</span><br>

    <input name="start" value="Do" type="button" size="10" />
</form>

<br><p style="color:red">lab 22 - JAAS</p>
<a href="JAASBasicAuthServlet">JAAS Basic Authentication</a>
<br><a href="JAASFormAuthServlet">JAAS Form Authentication</a>

<br><p style="color:red">lab 23 - Working with files</p>
<p>File download</p>
<%
    String d = getServletConfig().getServletContext().getInitParameter("doc-dir");
    FileChooser ch = new FileChooser(d);
    String ll = null;
    for (int i = 0; i < ch.files.length; i++) {
        ll = ch.files[i];
%>
        <a href="DownloadFileServlet?file=<%=ll%>"> <%=ll%> </a>
        <br>
    <%}%>

<p>File upload</p>
<form action="DownloadFileServlet" method="post" enctype="multipart/form-data">
    <input name="file" type="file" title="Upload"/><br>
    <input type="submit"/>
</form>

<script type="text/javascript" src="js/lab21.js"></script>
</body>
</html>
