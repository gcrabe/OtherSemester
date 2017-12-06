

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
				SPACE 168
				DCD TIM2_Handler
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

SaveContext 	PROC
					EXPORT SaveContext
					; POINER TO CONTEXT IN R0 (argument)
					
					LDR r1, [sp, #12] ; r0 from stack -> r1
					STR r1, [r0, #0x00] ; r1 (temp) -> context.gpr;
					
					LDR r1, [sp, #12+4] ; r1 from stack -> r1
					STR r1, [r0, #0x04] ; r1 (temp) -> context.gpr;
					
					LDR r1, [sp, #12+8] ; r2 from stack -> r1
					STR r1, [r0, #0x08]  ; r1 (temp) -> context.gpr;
					
					LDR r1, [sp, #12+12] ; r3 from stack -> r1
					STR r1, [r0, #0x0C] ; r1 (temp) -> context.gpr;
					
					STR r4, [r0, #0x10] ; r4 (temp) -> context.gpr;
					STR r5, [r0, #0x14] ; r5 (temp) -> context.gpr;
					STR r6, [r0, #0x18] ; r6 (temp) -> context.gpr;
					STR r7, [r0, #0x1C] ; r7 (temp) -> context.gpr;
					STR r8, [r0, #0x20] ; r8 (temp) -> context.gpr;
					STR r9, [r0, #0x24] ; r9 (temp) -> context.gpr;
					STR r10, [r0, #0x28] ; r10 (temp) -> context.gpr;
					STR r11, [r0, #0x2C] ; r11 (temp) -> context.gpr;
					
					LDR r1, [sp, #12+16] ; r12 from stack -> r1
					STR r1, [r0, #0x30] ; r1 (temp) -> context.gpr;
					
					LDR r1, [sp, #12+24] ; PC (ReturnAdderss()) from stack -> r1
					STR r1, [r0, #0x34] ; r1 (temp) -> context.pc;
					
					LDR r1, [sp, #12+20] ; LR from stack -> r1
					STR r1, [r0, #0x38] ; r1 (temp) -> context.lr;
					
					MOV r1, sp
					STR r1, [r0, #0x3c] ; r1 (temp) -> context.sp;
					
					LDR r1, [sp, #12+28] ; xPSR from stack -> r1
					STR r1, [r0, #0x40] ; r1 (temp) -> context.psw;
	
					BX LR
				ENDP
					
RestoreContext 	PROC
					EXPORT RestoreContext
					LDR R2,[sp, #0] ; sp from struct -> r1
					LDR R3,[sp, #4]
					LDR R4,[sp, #8]
					
					LDR R1,[r0, #0x3c] ; sp from struct -> r1
					mov SP,R1			; r1 -> sp
					
					STR R2,[sp, #0] ; sp from struct -> r1
					STR R3,[sp, #4]
					STR R4,[sp, #8]
					
					
					LDR r1, [r0, #0x00] ; r0 from context.gpr -> r1
					STR r1, [sp, #12] ; r1 (temp) -> stack;
					
					LDR r1, [r0, #0x04] ; r1 from  context.gpr-> r1
					STR r1, [sp, #12+4] ; r1 (temp) ->stack context.gpr;
					
					LDR r1, [r0, #0x08] ; r2 from stack -> r1
					STR r1, [sp, #12+8]   ; r1 (temp) -> context.gpr;
					
					LDR r1, [r0, #0x0C] ; r3 from stack -> r1
					STR r1, [sp, #12+12] ; r1 (temp) -> context.gpr;
					
					LDR r1 ,[r0, #0x10] ; r4 (temp) -> context.gpr;
					mov r4,r1;
					LDR r1 ,[r0, #0x14] ; r4 (temp) -> context.gpr;
					mov r5,r1;
					LDR r1 ,[r0, #0x18] ; r4 (temp) -> context.gpr;
					mov r6,r1;
					LDR r1 ,[r0, #0x1C] ; r4 (temp) -> context.gpr;
					mov r7,r1;
					LDR r1 ,[r0, #0x20] ; r4 (temp) -> context.gpr;
					mov r8,r1;
					LDR r1 ,[r0, #0x24] ; r4 (temp) -> context.gpr;
					mov r9,r1;
					LDR r1 ,[r0, #0x28] ; r4 (temp) -> context.gpr;
					mov r10,r1;
					LDR r1 ,[r0, #0x2C] ; r4 (temp) -> context.gpr;
					mov r11,r1;
					
					LDR r1, [r0, #0x30] ; r12 from stack -> r1
					STR r1, [sp, #12+16] ; r1 (temp) -> context.gpr;
					
					LDR r1, [r0, #0x34] ; PC (ReturnAdderss()) from stack -> r1
					STR r1, [sp, #12+24] ; r1 (temp) -> context.pc;
					
					LDR r1, [r0, #0x38] ; LR from stack -> r1
					STR r1, [sp, #12+20] ; r1 (temp) -> context.lr;

					
					LDR r1, [r0, #0x40] ; xPSR from stack -> r1
					STR r1,[sp, #12+28]  ; r1 (temp) -> context.psw;
	
					
					
					BX LR
				ENDP

TIM2_Handler 	PROC
					IMPORT OSkernel
					
					MOV R0, LR
					PUSH {R0}
					
					BL OSkernel
					
					POP {R0}
					MOV LR, R0
	
					LDR R0, =0x40000000
					LDR R1, [R0, #0x10]
					LDR R2, =~0x00000001
					AND R1, R2
					STR R1, [R0, #0x10]
					
					;LDR R0, =0x48001000
					;LDR R1, [R0, #0x14]
					;LDR R2, =0x00000800
					;EOR R1,R2
					;STR R1,[R0,#0x14]
					
					ISB
					
					BX LR			
				ENDP

; Reset handler
Reset_Handler    PROC
				 
					EXPORT  Reset_Handler             [WEAK]
					
					IMPORT OSinit
					
					
					
					
					 ; init
					 ; SystemInit()
					 
					 ; rcc start
					 ; mod led port
					 LDR R0, =0x40021000
					 LDR R1, [R0, #0x14]
					 LDR R2, =0x00200000
					 ORR R1,R2
					 STR R1,[R0,#0x14]
					 
					 ; mod timer port
					 LDR R0, =0x40021000
					 LDR R1, [R0, #0x1C]
					 LDR R2, =0x00000001
					 ORR R1,R2
					 STR R1,[R0,#0x1C]
					 
					 ; timer counter settings
					 ; cnt reg
					 LDR R0, =0x40000000
					 LDR R2, =0x00000000
					 STR R2, [R0, #0x24]
					 
					 ; arr reg
					 LDR R0, =0x40000000
					 LDR R2, = 1000
					 STR R2, [R0, #0x2C]
					 
					 ; psc reg
					 LDR R0, =0x40000000
					 LDR R2, = 0 ;400
					 STR R2, [R0, #0x28]
					 
					 ; dier reg
					 LDR R0, =0x40000000
					 LDR R2, =0x00000001
					 STR R2, [R0, #0x0C]
					 
					 ; nvic_iser
					 LDR R0, =0xE000E100
					 LDR R2, =0x10000000
					 STR R2, [R0, #0x00]
					 
					 ; cr1 reg
					 LDR R0, =0x40000000
					 LDR R1, [R0, #0x00]
					 LDR R2, =0x00000001
					 ORR R1,R2
					 STR R1,[R0,#0x00]
					 

					 
					 ; moder on
					 LDR R0, =0x48001000
					 LDR R1, [R0, #0x00]
					 LDR R2, =0x40400000
					 ORR R1,R2
					 STR R1,[R0,#0x00]
					 
					 					 ;include from main.c
										 
										 
										 
					BL OSinit
					
					 IMPORT main
					 LDR R0,=main
					 BLX R0
					 
loop_off_true
					 ; block
					 CPSID I
					 
					 ; loop start conditions
					 LDR R11, =0x000F4240
					 LDR R12, =0x000F4240
					 
					 ; odr on
					 LDR R1, [R0, #0x14]
					 LDR R2, =0x00008000
					 
					 ; waiting loop start consitions
					 LDR R9,  =0x00051615

loop_wait_false
					 ; wait actions
					 SUB R9, #0x00000001
					 CMP R9, #0x00000000
					 BNE loop_wait_false
					 
					 ;continue odr on
					 ORR R1,R2
					 STR R1,[R0,#0x14]
					 
					 ; unblock
					 CPSIE I
					 
loop_on_false		 
					 ; wait off loop		 
					 SUB R11, #0x00000001
					 CMP R11, #0x00000000
					 BEQ loop_on_true
					 BNE loop_on_false
					 
loop_on_true
					 ; odr off
					 LDR R1, [R0, #0x14]
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
