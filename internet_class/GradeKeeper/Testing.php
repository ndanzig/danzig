

<html>

    <head>
        <title>Something</title>
        <link href="Style.css" rel="Stylesheet" type="text/css" />
    </head>
    <body>
        <script language="javascript">
            function ShowEdit(studentID, assignmentID)
            {
                document.getElementById("spnView_" + studentID + "_" + assignmentID).style.display = 'none';
                document.getElementById("spnEdit_" + studentID + "_" + assignmentID).style.display = 'block';
            }
            function HideEdit(studentID, assignmentID)
            {
                document.getElementById("spnView_" + studentID + "_" + assignmentID).style.display = 'block';
                document.getElementById("spnEdit_" + studentID + "_" + assignmentID).style.display = 'none';
            }
            function SubmitGrade(value, studentID, assignmentID)
            {
                //document.getElementById("spnView_" + studentID + "_" + assignmentID).style.display = 'block';
                //document.getElementById("spnEdit_" + studentID + "_" + assignmentID).style.display = 'none';
            }
        
        </script>
        <span id="spnView_0_0" onclick="javascript:ShowEdit(0,0);">
            65
        </span>
        <span id="spnEdit_0_0" style="display: none">
            <input type="text" value="65" style="width: 30px" id="txtGrade_0_0" />
            <a href="javascript:HideEdit(0,0);">x</a>
            <a href="javascript:SubmitGrade(document.getElementById('txtGrade_0_0').value,0,0);">ok</a>
        </span>
        
    </body>
</html>