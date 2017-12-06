

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
	
                 EXPORT  Reset_Handler             [WEAK]
					 ; rcc start
					 LDR R0, =0x40021000
					 LDR R1, [R0, #0x14]
					 LDR R2, =0x00200000
					 ORR R1,R2
					 STR R1,[R0,#0x14]
					 
					 ; moder on
					 LDR R0, =0x48001000
					 LDR R1, [R0, #0x00]
					 LDR R2, =0x40000000
					 ORR R1,R2
					 STR R1,[R0,#0x00]
loop_off_true
					 ; loop start conditions
					 LDR R11, =0x002DC6C1
					 LDR R12, =0x002DC6C1
					 
					 ; odr on
					 LDR R1, [R0, #0x14]
					 LDR R2, =0x00008000
					 ORR R1,R2
					 STR R1,[R0,#0x14]
					 
loop_on_false
					 ; wait off loop		 
					 SUB R11, #0x00000001
					 CMP R11, #0x00000000
					 BEQ loop_on_true
					 BNE loop_on_false
					 
loop_on_true
					 ; odr off
					 LDR R2, =~0x00008000
					 AND R1,R2
					 STR R1,[R0,#0x14]
					 
loop_off_false		 ; wait off loop	
					 SUB R12, #0x00000001
					 CMP R12, #0x00000000
					 BEQ loop_off_true
					 BNE loop_off_false
					 B .
			
                 ENDP


                 ALIGN


                 END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
