.MODEL SMALL
.STACK 400H
.DATA
foo PROC
PUSH AX
PUSH BX
PUSH CX ; save gprs
PUSH BP
MOV BP, SP ; save stack pointer
PUSH [BP--12] ; a pushed in stack 
PUSH [BP--10] ; b pushed in stack 
POP BX
POP AX
ADD AX, BX
PUSH AX
PUSH 5
POP BX ; line 2 relop 
POP AX
CMP AX, BX
JLE @L1
PUSH 0
JMP @L2
@L1:
PUSH 1
@L2: ; a+b<=5 parsed
POP AX
CMP AX, 0
JE @L3
PUSH 7
POP DX ; save return value in dx
JMP @L0
JMP @L4
@L4: ; if condition false
@L3:
PUSH [BP--12] ; a pushed in stack 
PUSH 2
POP BX
POP AX
SUB AX, BX
PUSH AX
PUSH [BP--10] ; b pushed in stack 
PUSH 1
POP BX
POP AX
SUB AX, BX
PUSH AX
CALL foo ; line 5 , function call
PUSH DX ; return value pushed
PUSH 2
PUSH [BP--12] ; a pushed in stack 
PUSH 1
POP BX
POP AX
SUB AX, BX
PUSH AX
PUSH [BP--10] ; b pushed in stack 
PUSH 2
POP BX
POP AX
SUB AX, BX
PUSH AX
CALL foo ; line 5 , function call
PUSH DX ; return value pushed
POP BX
POP AX
CWD ; line 5 MULOP
MUL BX
PUSH AX
POP BX
POP AX
ADD AX, BX
PUSH AX
POP DX ; save return value in dx
JMP @L0
@L0: ; to handle recursion
MOV SP, BP ; restore stack pointer
POP BP
POP CX
POP BX
POP AX ; restore registers 
RET 4 ; offset stack to clean up parameters
foo ENDP

main PROC
MOV AX, @DATA
MOV DS, AX ; load data segment
MOV BP, SP ; save stack pointer
PUSH 0 ; line 10 declare variable i, offset: 2
PUSH 0 ; line 10 declare variable j, offset: 4
PUSH 0 ; line 10 declare variable k, offset: 6
PUSH 7
POP AX
MOV [BP-2], AX ; line 11: i assigned
; PEEP --> PUSH AX ; i=7 expression stored
; PEEP --> POP AX ; expression end
PUSH 3
POP AX
MOV [BP-4], AX ; line 12: j assigned
; PEEP --> PUSH AX ; j=3 expression stored
; PEEP --> POP AX ; expression end
PUSH [BP-2] ; i pushed in stack 
PUSH [BP-4] ; j pushed in stack 
CALL foo ; line 14 , function call
PUSH DX ; return value pushed
POP AX
MOV [BP-6], AX ; line 14: k assigned
; PEEP --> PUSH AX ; k=foo(i,j) expression stored
; PEEP --> POP AX ; expression end
MOV AX, [BP-6]
CALL DAX ; line 15: printf(k)
PUSH 0
POP DX ; save return value in dx
JMP @L5
@L5: ; to handle recursion
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
