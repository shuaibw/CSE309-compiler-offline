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
