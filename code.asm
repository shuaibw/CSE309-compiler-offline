.MODEL SMALL
.STACK 400H
.DATA
f PROC
PUSH AX
PUSH BX
PUSH CX ; save gprs
PUSH BP
MOV BP, SP ; save stack pointer
PUSH 0 ; line 2 declare variable k, offset: 2
PUSH 5
POP AX
MOV [BP-2], AX ; line 3: k assigned
PUSH AX ; k=5 expression stored
POP AX ; expression end
@L1: ; while condition check label
PUSH [BP-2] ; k pushed in stack 
PUSH 0
POP BX ; line 4 relop 
POP AX
CMP AX, BX
JG @L4
PUSH 0
JMP @L5
@L4:
PUSH 1
@L5: ; k>0 parsed
POP AX ; pop condition value
CMP AX, 0
JNE @L2
JMP @L3
@L2: ; while body label
PUSH [BP--10] ; a pushed
INC WORD PTR[BP--10]
POP AX ; expression end
PUSH [BP-2] ; k pushed
DEC WORD PTR[BP-2]
POP AX ; expression end
JMP @L1
@L3: ; while exit label
PUSH 3
PUSH [BP--10] ; a pushed in stack 
POP BX
POP AX
CWD ; line 8 MULOP
IMUL BX
PUSH AX
PUSH 7
POP BX
POP AX
SUB AX, BX
PUSH AX
POP DX ; save return value in dx
JMP @L0
PUSH 9
POP AX
MOV [BP--10], AX ; line 9: a assigned
PUSH AX ; a=9 expression stored
POP AX ; expression end
@L0: ; to handle recursion
MOV SP, BP ; restore stack pointer
POP BP
POP CX
POP BX
POP AX ; restore registers 
RET 2 ; offset stack to clean up parameters
f ENDP

g PROC
PUSH AX
PUSH BX
PUSH CX ; save gprs
PUSH BP
MOV BP, SP ; save stack pointer
PUSH 0 ; line 14 declare variable x, offset: 2
PUSH 0 ; line 14 declare variable i, offset: 4
PUSH [BP--12] ; a pushed in stack 
CALL f ; line 15 , function call
PUSH DX ; return value pushed
PUSH [BP--12] ; a pushed in stack 
POP BX
POP AX
ADD AX, BX
PUSH AX
PUSH [BP--10] ; b pushed in stack 
POP BX
POP AX
ADD AX, BX
PUSH AX
POP AX
MOV [BP-2], AX ; line 15: x assigned
PUSH AX ; x=f(a)+a+b expression stored
POP AX ; expression end
PUSH 0
POP AX
MOV [BP-4], AX ; line 17: i assigned
PUSH AX ; i=0 expression stored
POP AX ; expression end
@L7: ; condition check label
PUSH [BP-4] ; i pushed in stack 
PUSH 7
POP BX ; line 17 relop 
POP AX
CMP AX, BX
JL @L11
PUSH 0
JMP @L12
@L11:
PUSH 1
@L12: ; i<7 parsed
POP AX ; expression end
CMP AX, 0
JNE @L8 ; if true then enter body
JMP @L10 ; else exit
@L9: ; update label
PUSH [BP-4] ; i pushed
INC WORD PTR[BP-4]
POP AX ; pop update expression
JMP @L7 ; check if condition holds
@L8: ; for body label
PUSH [BP-4] ; i pushed in stack 
PUSH 3
POP BX
POP AX
CWD ; line 18 MULOP
NOP
IDIV BX
PUSH DX
PUSH 0
POP BX ; line 18 relop 
POP AX
CMP AX, BX
JE @L13
PUSH 0
JMP @L14
@L13:
PUSH 1
@L14: ; i%3==0 parsed
POP AX
CMP AX, 0
JE @L15
PUSH [BP-2] ; x pushed in stack 
PUSH 5
POP BX
POP AX
ADD AX, BX
PUSH AX
POP AX
MOV [BP-2], AX ; line 19: x assigned
PUSH AX ; x=x+5 expression stored
POP AX ; expression end
JMP @L16
@L15: ; else block 
PUSH [BP-2] ; x pushed in stack 
PUSH 1
POP BX
POP AX
SUB AX, BX
PUSH AX
POP AX
MOV [BP-2], AX ; line 22: x assigned
PUSH AX ; x=x-1 expression stored
POP AX ; expression end
@L16:
JMP @L9
@L10:
PUSH [BP-2] ; x pushed in stack 
POP DX ; save return value in dx
JMP @L6
@L6: ; to handle recursion
MOV SP, BP ; restore stack pointer
POP BP
POP CX
POP BX
POP AX ; restore registers 
RET 4 ; offset stack to clean up parameters
g ENDP

main PROC
MOV AX, @DATA
MOV DS, AX ; load data segment
MOV BP, SP ; save stack pointer
PUSH 0 ; line 30 declare variable a, offset: 2
PUSH 0 ; line 30 declare variable b, offset: 4
PUSH 0 ; line 30 declare variable i, offset: 6
PUSH 1
POP AX
MOV [BP-2], AX ; line 31: a assigned
PUSH AX ; a=1 expression stored
POP AX ; expression end
PUSH 2
POP AX
MOV [BP-4], AX ; line 32: b assigned
PUSH AX ; b=2 expression stored
POP AX ; expression end
PUSH [BP-2] ; a pushed in stack 
PUSH [BP-4] ; b pushed in stack 
CALL g ; line 33 , function call
PUSH DX ; return value pushed
POP AX
MOV [BP-2], AX ; line 33: a assigned
PUSH AX ; a=g(a,b) expression stored
POP AX ; expression end
MOV AX, [BP-2]
CALL DAX ; line 34: printf(a)
PUSH 0
POP AX
MOV [BP-6], AX ; line 35: i assigned
PUSH AX ; i=0 expression stored
POP AX ; expression end
@L18: ; condition check label
PUSH [BP-6] ; i pushed in stack 
PUSH 4
POP BX ; line 35 relop 
POP AX
CMP AX, BX
JL @L22
PUSH 0
JMP @L23
@L22:
PUSH 1
@L23: ; i<4 parsed
POP AX ; expression end
CMP AX, 0
JNE @L19 ; if true then enter body
JMP @L21 ; else exit
@L20: ; update label
PUSH [BP-6] ; i pushed
INC WORD PTR[BP-6]
POP AX ; pop update expression
JMP @L18 ; check if condition holds
@L19: ; for body label
PUSH 3
POP AX
MOV [BP-2], AX ; line 36: a assigned
PUSH AX ; a=3 expression stored
POP AX ; expression end
@L24: ; while condition check label
PUSH [BP-2] ; a pushed in stack 
PUSH 0
POP BX ; line 37 relop 
POP AX
CMP AX, BX
JG @L27
PUSH 0
JMP @L28
@L27:
PUSH 1
@L28: ; a>0 parsed
POP AX ; pop condition value
CMP AX, 0
JNE @L25
JMP @L26
@L25: ; while body label
PUSH [BP-4] ; b pushed
INC WORD PTR[BP-4]
POP AX ; expression end
PUSH [BP-2] ; a pushed
DEC WORD PTR[BP-2]
POP AX ; expression end
JMP @L24
@L26: ; while exit label
JMP @L20
@L21:
MOV AX, [BP-2]
CALL DAX ; line 42: printf(a)
MOV AX, [BP-4]
CALL DAX ; line 43: printf(b)
MOV AX, [BP-6]
CALL DAX ; line 44: printf(i)
PUSH 0
POP DX ; save return value in dx
JMP @L17
@L17: ; to handle recursion
MOV AH, 004CH
INT 21H
main ENDP


; HELPER MODULES
DCHAR PROC          ; displays char stored in dl
    PUSH AX         ; save ax in stack
    MOV AH, 2
    INT 21H
    POP AX          ; load ax from stack
    RET
DCHAR ENDP

DAX PROC            ; displays signed num stored in ax
    PUSH AX         ; save gprs in stack
    PUSH BX
    PUSH CX
    PUSH DX
    
    XOR CX, CX      ; to be used in @L_2 loop control variable
    MOV BX, 10      ; dividend
    CMP AX, 0       ; print '-' if ax < 0
    JGE @L_1
    MOV DL, '-'
    CALL DCHAR
    NEG AX          ; make ax positive
    
    @L_1:
    CWD             ; extend ax to dx:ax
    DIV BX          ; ax=dx:ax/bx, dx=dx:ax%bx
    ADD DX, '0'     ; convert dl to char
    PUSH DX         ; to be printed in @L_2
    INC CX
    CMP AX, 0       ; exit if dividend=0
    JE @L_2
    JMP @L_1
    
    @L_2:
    POP DX          ; print each digit in reverse
    CALL DCHAR
    LOOP @L_2
    
    POP DX          ; load back gprs
    POP CX
    POP BX
    POP AX
    CALL NL
    RET
DAX ENDP

NL PROC             ; displays newline
    PUSH DX
    PUSH AX
    MOV AH, 2
    MOV DL, 0DH     ; carriage return
    INT 21H
    MOV DL, 0AH     ; line feed
    INT 21H
    POP DX
    POP AX
    RET
NL ENDP
END MAIN
