# Windows-CodeDemo
<h1>Mini C Runtimes Library<br></h1>

Input below in cmd : <br>
(You can get 'cl' by adding %vs_path%\VC\bin\ to your "Path") <br>
(if hint "Windows.h" : no include path set, you can input "vcvars32")<br>
cl /c /DWIN32 /GS- entry.c malloc.c printf.c stdio.c string.c <br>
lib entry.obj malloc.obj printf.obj stdio.obj string.obj /OUT:minicrt.lib <br>
<br>
Run test.c :<br>
cl /c /DWIN32 test.c <br>
link test.obj minicrt.lib kernel32.lib /NODEFAULTLIB /entry:mini_crt_entry<br>
test.exe arg1 123 arg3