

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

TIM2_Handler 	PROC
					;работа с прерывани€ми
					LDR R0, =0x40000000
					LDR R1, [R0, #0x10]
					LDR R2, =~0x00000001
					AND R1, R2
					STR R1, [R0, #0x10]
					
					LDR R0, =0x48001000
					LDR R1, [R0, #0x14]
					LDR R2, =0x00000800
					EOR R1,R2
					STR R1,[R0,#0x14]
					
					
					BX LR			
				ENDP

; Reset handler
Reset_Handler    PROC
	
                 EXPORT  Reset_Handler             [WEAK]
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
					 ; cnt reg счЄтчик
					 LDR R0, =0x40000000
					 LDR R2, =0x00000000
					 STR R2, [R0, #0x24]
					 
					 ; arr reg регистр автоперезагрузки
					 LDR R0, =0x40000000
					 LDR R2, = 0x8000
					 STR R2, [R0, #0x2C]
					 
					 ; psc reg частотный регистр
					 LDR R0, =0x40000000
					 LDR R2, = 400
					 STR R2, [R0, #0x28]
					 
					 ; dier reg // включить обновление прерываний
					 LDR R0, =0x40000000
					 LDR R2, =0x00000001
					 STR R2, [R0, #0x0C]
					 
					 ; nvic_iser
					 LDR R0, =0xE000E100
					 LDR R2, =0x10000000
					 STR R2, [R0, #0x00]
					 
					 ; cr1 reg //включение счЄтчика
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
					 ;далее механика мегание лампочек 
					 
loop_off_true
					 ; block
					 CPSID I ; отключение прерывани€ 
					 
					 ; loop start conditions
					 ; величины, определ€ющие продолжительность периодов
					 ; работы и ожидани€ светодиода
					 LDR R11, =0x000F4240
					 LDR R12, =0x000F4240
					 
					 ; odr on
					 LDR R1, [R0, #0x14]
					 LDR R2, =0x00008000
					 
					 ; waiting loop start conditions
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
					 CPSIE I ;включаем прерывание
					 
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