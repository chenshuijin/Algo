exe = main.exe
objs = rsa.obj test.obj main.obj
incs = 
libs = 
res = 

link_flag = 

cl_flag = -c

$(exe) : $(objs) $(res)
	link $(link_flag) -out:$(exe) $(objs) $(res) $(libs)

.c.obj:
	cl $(cl_flag) $<

clean:
	del *.obj
	del *.res

rm:
	del *.obj
	del *.res
	del *.exe
