	TITLE	util.asm
	.386
	.model	flat, stdcall
	option	casemap	:none
;==========================================
;include	defines
;==========================================
include         windows.inc
include         user32.inc
includelib      user32.lib
include         kernel32.inc
includelib      kernel32.lib

data	segment
	dwCounter	dd	?
	szCaption				db			'A MessageBox !', 0
	szText					db			'Hello, world !', 0
data	ends

;=============================================
;Here must use '.code', I didn't find anyother
;better way to use 'code segment'
;=============================================
.code

;===========================
;dll	entry
;===========================
DllEntry	proc	hInstance:HINSTANCE, dwReason:DWORD, dwReserved:DWORD
	mov		eax,TRUE
	ret
DllEntry	endp

;============================
;control num be 0 to 10
;============================
CheckCounter	proc
	mov		eax,dwCounter
	cmp 	eax,0
	jge		@F
	xor 	eax,eax
	@@:
	cmp 	eax,10
	jle 	@F
	mov 	eax,10
	@@:
	mov 	dwCounter,eax
	ret
CheckCounter	endp

;===========================
;dll export@1
;===========================
IncCounter		proc	export
	inc 	dwCounter
	call	CheckCounter
	ret
IncCounter 	endp

;============================
;dll export@2
;============================
DecCounter		proc	export
	dec 	dwCounter
	call 	CheckCounter
	ret
DecCounter 	endp

;=============================
;dll export@3
;=============================
GetMod 	proc	export	uses ecx edx dwNum1:DWORD, dwNum2:DWORD
	xor 	edx,edx
	mov 	eax,dwNum1
	mov 	ecx,dwNum2
	.if 	ecx
			div ecx
			mov eax,edx
	.endif
	ret
GetMod 	endp
;===================================
Hello	proc
	invoke	MessageBox,NULL,offset szText,\
							offset	szCaption,MB_OK
	ret
Hello	endp
;==================================
AAdd 	proc	export	uses ecx edx left:DWORD, rt:DWORD
	pushad
	mov 	eax, left
	popad
	ret
AAdd		endp
;====================================
MkMem	proc	export	uses ecx edx amount:DWORD
	int 	49h
	xor 	eax, eax
	xor 	ebx, ebx
	mov 	ebx, amount
	int 	48h
	ret

MkMem	endp
;================================
end 	DllEntry

