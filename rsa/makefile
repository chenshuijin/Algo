exe = main.exe
objs = tool.obj asnber.obj des.obj calc.obj test.obj main.obj
incs = d:\sw\asm\include
dll =  util
libs = util.lib
res = 

link_flag = 
cl_flag = -c #-Fa
ml_flag = /c /coff /I $(incs)
dll_link_flag = /subsystem:windows /Dll

$(exe):$(objs) $(res) $(dll).dll
	link $(link_flag) -out:$(exe) $(objs) $(res) 

$(dll).dll:
	ml $(ml_flag) $(dll).asm
	link $(dll_link_flag) /Def:$(dll).def $(dll).obj

.c.obj:
	cl $(cl_flag) $<

clean:
	del *.obj
	del *.res
	del *.lib
	del *.exp

rm:
	del *.obj
	del *.res
	del *.exe
	del *~
	del *.lib
	del *.exp
	del *.dll
