;Es tracte de l'estructura del MenuPrincipal
;i la forma d'efectuar les trucades a les sub-rutines
;
; Segment de dades
DADES       SEGMENT
m1    	    DB      13,10,"Menu Principal$"
opcio1      DB      13,10,"1. Crear directori$"
opcio2      DB      13,10,"2. Eliminar directori$"
opcio3      DB      13,10,"3. Crear Email+PWD$"
opcio4      DB      13,10,"4. Sortir$"
triaOpc     DB      13,10,"Entra una opcio: ","$"
merror	    DB      13,10,"Opcio no valida Prem una tecla per MenuP ","$"
mNomArxiu   DB      13,10,"Introdueix nom del arxiu: $"
mCreat      DB      13,10,"Arxiu creat $"
mElimina    DB      13,10,"Arxiu eliminat $"
mNomCogn    DB      13,10,"Introdueix el Nom i el Cognom:",13,10,"$" 
mTecla      DB      13,10,"Prem una tecla per continuar... $"
mAnyActu    DB      13,10,"Any Actual: ","$" 
mAnyNaix    DB      13,10,"Introdueix el teu any de naixement: ","$"
mCorreu     DB      13,10,"Correu: $"
mContra     DB      13,10,"Contrassenya: $"
Var_Ent 	DB 	    250,?,250 dup (?) ; Buffer amb llargada maxima, llargada real, array de 250
Var_Sort    DB      250 dup (?)
Var_Nom     DB      250 dup (?)
Var_Cogn    DB      250 dup (?)
Var_email   DB      250 dup (?)
Var_Any     DW      1122h
anyActual   DW      1122h
Var_Edat    DB      250 dup (?)
domini      DB      "@gmail.com",13,10,"$"
Var_Hash    DB      250 dup (?)
Password    DB      250 dup (?)
n_line      DB      13,10,"$"
dades       ENDS  

; Segment de codi
CODI    SEGMENT
PROG    PROC  NEAR
        ASSUME CS:CODI, DS:DADES, ES:DADES
   
		MOV AX, DADES           ; Situar registres de segment a lloc
		MOV DS, AX
		MOV ES, AX
		
MENU:	CALL MENUP		        ; Presenta MenuP
		
		                        ; espera char entrada teclat
		CALL LLEGIRCHR          ; en AL el caracter entrat
		
		CMP AL, '1' ;31h        ; '1' Codi ASCII de 1
		JE OP_CREAARXIU         ; Crear Arxiu
		
		CMP AL, '2' ;32h        ; '2' Codi ASCII de 2
		JE OP_ELIMINAARXIU      ; Eliminar Arxiu
		
		CMP AL, '3' ;33h        ; '3' Codi ASCII de 3
		JE OP_ENVIAMAIL         ; Enviar Correu
		
		CMP AL, '4' ;34h        ; '4' Codi ASCII de 4
		JE OP_SORTIR            ;Sortir de la execucio
		
        CALL ERROR
		JMP MENU
		
OP_CREAARXIU:
        CALL CREARDIR
        JMP MENU

OP_ELIMINAARXIU:
        CALL ELIMINADIR
        JMP MENU        		

OP_ENVIAMAIL:
        CALL ENVIAMAIL
        JMP MENU
        
OP_SORTIR:
        CALL SURT		
		
PROG	ENDP		
		
;===================Implementacio de Rutines o procediments ===============================		
		
MENUP PROC NEAR
        CALL    CLS
        PUSH    OFFSET m1
		CALL    ESCRIU
		ADD     SP, 2
		PUSH    OFFSET opcio1
		CALL    ESCRIU
		ADD     SP, 2
		PUSH    OFFSET opcio2
		CALL    ESCRIU
		ADD     SP, 2
		PUSH    OFFSET opcio3
		CALL    ESCRIU
		ADD     SP, 2
		PUSH    OFFSET opcio4
		CALL    ESCRIU
		ADD     SP, 2
		PUSH    OFFSET triaOpc
		CALL    ESCRIU
		ADD     SP, 2
		RET
MENUP ENDP  

ERROR PROC NEAR
        PUSH    OFFSET merror   ; Missatge error
        CALL    escriu
        ADD     SP, 2
        CALL    LLEGIRCHR       ; PAUSE - Espera una tecla
        RET
ERROR ENDP  

CREARDIR PROC NEAR        
        LEA     AX, [mNomArxiu] ; Demana el nom del directori a crear (nom sabem si existeix o no)
        PUSH    AX 
        CALL    ESCRIU
        ADD     SP, 2
        PUSH    OFFSET Var_Ent
		CALL    LLEGIRCAD
		ADD     SP, 2
		
		PUSH    OFFSET Var_Ent  ; Guarda el String llarg en un de la seva mida "temporal"
		PUSH    OFFSET Var_Sort
		CALL    TRACTA
		ADD     SP, 4
		
		PUSH    OFFSET Var_Sort ; Crea el directori
        CALL    MKDIR
        ADD     SP, 2
        
        LEA     AX, [mTecla]    ; PAUSE - Espera una tecla
        PUSH    AX
        CALL    ESCRIU
        ADD     SP, 2
        CALL    LLEGIRCHR 
        
        RET
CREARDIR ENDP

ELIMINADIR PROC NEAR
        LEA     AX, [mNomArxiu] ; Demana el nom del directori a borrar (nom sabem si existeix o no)
        PUSH    AX 
        CALL    ESCRIU
        ADD     SP, 2
        PUSH    OFFSET Var_Ent
		CALL    LLEGIRCAD
		ADD     SP, 2
		
		PUSH    OFFSET Var_Ent  ; Guarda el String llarg en un de la seva mida "temporal"
		PUSH    OFFSET Var_Sort
		CALL    TRACTA
		ADD     SP, 4
		
		PUSH    OFFSET Var_Sort ; Elimina el directori
        CALL    RMDIR
        ADD     SP, 2
        
        LEA     AX, [mTecla]    ; PAUSE - Espera una tecla
        PUSH    AX
        CALL    ESCRIU
        ADD     SP, 2
        CALL    LLEGIRCHR 
        
        RET
ELIMINADIR ENDP

ENVIAMAIL PROC NEAR
        LEA     AX, [mNomCogn]
        PUSH    AX
        CALL    ESCRIU
        ADD     SP, 2
        PUSH    OFFSET Var_Ent
		CALL    LLEGIRCAD
		ADD     SP, 2
		                        ; Extreu 1a lletra del nom de la cadena "tot minuscula"
		PUSH    OFFSET Var_Ent
		PUSH    OFFSET Var_Nom
		CALL    EXTREUNOM
		ADD     SP, 4
		                        ; Extreu cognom de la cadena "tot minuscula"
		PUSH    OFFSET Var_Ent
		PUSH    OFFSET Var_Cogn
		CALL    EXTREUCOGNOM
		ADD     SP, 4
		                        ; Llegeix el any actual i el tracta com a hexadecimal
		LEA     AX, [mAnyActu]
        PUSH    AX
        CALL    ESCRIU
        ADD     SP, 2
        PUSH    OFFSET anyActual
        CALL    SCAN_NUM
        ADD     SP, 2
		                        ; Llegeix el any de naixement i el tracta com a hexadecimal
		LEA     AX, [mAnyNaix]
        PUSH    AX
        CALL    ESCRIU
        ADD     SP, 2
        PUSH    OFFSET Var_Any 
        CALL    SCAN_NUM
        ADD     SP, 2
		                        ; Extreu la edat
		PUSH    anyActual
		PUSH    Var_Any
		PUSH    OFFSET Var_Edat
		CALL    TRACTAEDAT
		ADD     SP, 6
		                        ; Concatena nom i cognom
		PUSH    OFFSET Var_Nom     
		PUSH    OFFSET Var_Cogn    
		PUSH    OFFSET Var_email   
	    CALL    CONCATSTRINGS      
		ADD     SP, 6
		                        ; Crea el "HASH" fent ASCII + 2
		PUSH    OFFSET Var_email
		PUSH    OFFSET Var_Hash
		CALL    CREARPWD
		ADD     SP, 4
		
				                ; Concatena contrassenya y edat 
		PUSH    OFFSET Var_Edat
		PUSH    OFFSET Var_Hash
		PUSH    OFFSET Password
		CALL    CONCATSTRINGS      
		ADD     SP, 6
		                        ; Concatena email i domini 
		PUSH    OFFSET Var_email
		PUSH    OFFSET domini
		PUSH    OFFSET Var_email
		CALL    CONCATSTRINGS      
		ADD     SP, 6
		                        ; Treure el salt de linia de la contrassenya
		PUSH    OFFSET Password  
		CALL    CLEARVAR
		ADD     SP, 2
		                        ; Treure el salt de linia del correu
		PUSH    OFFSET Var_email  
		CALL    CLEARVAR
		ADD     SP, 2
		                        ; forcar nova linia
		CALL    NEWLINE
                                ; Mostrar email per pantalla
        PUSH    OFFSET mCorreu
        CALL    ESCRIU
        ADD     SP, 2           
        PUSH    OFFSET Var_email
        CALL    ESCRIU
        ADD     SP, 2
                                ; Mostrar password
        PUSH    OFFSET mContra
        CALL    ESCRIU
        ADD     SP, 2                        
        PUSH    OFFSET Password
        CALL    ESCRIU
        ADD     SP, 2
                                ; forcar nova linia
        CALL    NEWLINE
				                ; PAUSE - Espera una tecla
		LEA     AX, [mTecla]    
        PUSH    AX
        CALL    ESCRIU
        ADD     SP, 2
        CALL    LLEGIRCHR 
        
        RET
ENVIAMAIL ENDP

;=================Sub Metodes per tractar dades=====================
TRACTA  PROC NEAR		
		PUSH    BP
		PUSH    AX
		PUSH    SI
		PUSH    DI
		MOV     BP, SP
		
		MOV     SI, [BP+12] 	; Apuntar origen  (cadena entrada)	
		MOV     DI, [BP+10]     ; Apuntar desti, cadena tractada
		
		LODSB         	        ; Llegir llargada maxima
		LODSB 			        ; Llegir llargada real
		
BUCLE:	LODSB		  	        ; llegir un char
		CMP     AL, 0Dh         ; Final de cadena (Enter) ?
		JZ      FI		        ; Hem acabat
		JMP     GUARDA		 
		SUB     AL, 20h
GUARDA: STOSB			        ; Guardar
		JMP     BUCLE           ; Tracta el seguent	
FI:		
		MOV     AL, 0		    ; Situar CR LF al final
		STOSB
		
		POP     DI
		POP     SI
		POP     AX
		POP     BP
		RET
TRACTA	ENDP

CLEARVAR PROC NEAR
        PUSH    BP
		PUSH    AX
		PUSH    SI
		PUSH    DI
		MOV     BP, SP
		
		MOV     SI, [BP+10] 	; Apuntar origen  (cadena a tractar)
		MOV     DI, [BP+10]	    ; Apuntar desti, cadena tractada
		
CLEAR:	LODSB		  	        ; llegir un char
		CMP     AL, 0Dh         ; Final de cadena (Enter) ?
		JZ      FCLEAR		    ; Hem acabat
		JMP     SCLEAR		 
		SUB     AL, 20h
SCLEAR: STOSB			        ; Guardar
		JMP     CLEAR           ; Tracta el seguent	
FCLEAR:		
		MOV     AL, '$'		    ; Situar CR LF al final
		STOSB
		MOV     AL, 0		    ; Situar CR LF al final
		STOSB
		MOV     AL, 0		    ; Situar CR LF al final
		STOSB
		
		POP     DI
		POP     SI
		POP     AX
		POP     BP
		RET
CLEARVAR ENDP

EXTREUNOM PROC NEAR
        PUSH    BP
		PUSH    AX
		PUSH    SI
		PUSH    DI
		MOV     BP, SP
		
		MOV     SI, [BP+12] 	; Apuntar origen  (cadena entrada)	
		MOV     DI, [BP+10]     ; Apuntar desti, cadena tractada
		
		LODSB         	        ; Llegir llargada maxima
		LODSB 			        ; Llegir llargada real
		
	    LODSB		  	        ; Llegir un char 
		CMP     AL, 'A'
		JAE     ABZ
ABZ:    CMP     AL, 'Z'
        JBE     MIN_ABZ     
		JMP     SNOM

MIN_ABZ:ADD     AL, 20h         ; Si es majuscula el transforma en minuscula

SNOM:	STOSB
	
		MOV     AL, 13		    ; Situar CR LF al final
		STOSB
		MOV     AL, 10
		STOSB
		MOV     AL, '$'		    ; Situar CR LF al final
		STOSB
		
		POP     DI
		POP     SI
		POP     AX
		POP     BP
		RET
EXTREUNOM ENDP

EXTREUCOGNOM PROC NEAR
        PUSH    BP
		PUSH    AX
		PUSH    SI
		PUSH    DI
		MOV     BP, SP
		
		MOV     SI, [BP+12] 	; Apuntar origen  (cadena entrada)	
		MOV     DI, [BP+10]     ; Apuntar desti, cadena tractada
		
		LODSB         	        ; Llegir llargada maxima
		LODSB 			        ; Llegir llargada real
		
NOM:	LODSB		  	        ; Llegir un char
		CMP     AL, ' '         ; Final de cadena (Enter) ?
		JZ      COGNOM
		JMP     NOM
				 	
COGNOM:	LODSB
        CMP     AL,0Dh          ; Final de cadena (Enter) ?
		JZ      FICOGN          ; Hem acabat
		CMP     AL, 'A'
		JA      AZ
		
AZ:	    CMP     AL, 'Z'
        JB      MIN_AZ     
		JMP     SCOGN
		
MIN_AZ: ADD     AL, 20h 		; Si es majuscula el transforma en minuscula 

SCOGN:  STOSB			        ; Guardar
		JMP     COGNOM          ; Tracta el següent	
FICOGN:		
		MOV     AL, 13		    ; Situar CR LF al final
		STOSB
		MOV     AL, 10
		STOSB
		MOV     AL, '$'		    ; Situar CR LF al final
		STOSB
		
		POP     DI
		POP     SI
		POP     AX
		POP     BP
		RET
EXTREUCOGNOM ENDP

TRACTAEDAT PROC NEAR
		PUSH    BP
		PUSH    AX
		PUSH    BX
		PUSH    DI
		MOV     BP, SP
		
		MOV     DI, [BP+10]
		
		XOR     AX, AX
        XOR     BX, BX
        MOV     AX, [BP+14]
        MOV     BX, [BP+12]
        
        SUB     AX, BX          ; Resta en valor Hexadecimal
        
        PUSH    AX
        PUSH    DI 
        CALL    HEXaDEC         ; Transformacio a decimal
        
        POP     DI
        POP     AX     
        
        CMP     AX, 9h
        JBE     FUNIT
        CMP     AX, 63h
        JBE     FDES      
FCENT:  INC     DI
FDES:   INC     DI
FUNIT:  INC     DI

FEDAT:       
        MOV     AL, 13		    ; Situar CR LF al final
		STOSB
		MOV     AL, 10
		STOSB
		MOV     AL, '$'		    ; Situar CR LF al final
		STOSB
        
		POP     DI
		POP     BX
		POP     AX
		POP     BP
		RET
TRACTAEDAT ENDP

CREARPWD PROC NEAR
                PUSH    BP
		PUSH    AX
		PUSH    SI
		PUSH    DI
		MOV     BP, SP
		
		MOV     SI, [BP+12] 	; Apuntar origen  (cadena entrada)	
		MOV     DI, [BP+10]     ; Apuntar desti, cadena tractada
		
PASS:   LODSB		  	        ; Llegir un char 
		CMP     AL, 0Dh         ; Final de cadena (Enter) ?
		JZ      FIPASS 
		ADD     AL, 2h          ; ASCII + 2
        STOSB
        JMP     PASS
FIPASS:	
        DEC     SI
        DEC     SI
        LODSB
        ADD     AL, 2h     
        SUB     AL, 20h
        DEC     DI
        STOSB
        
	    MOV     AL, 13		    ; Situar CR LF al final
		STOSB
		MOV     AL, 10
		STOSB
		MOV     AL, '$'		    ; Situar CR LF al final
		STOSB
		
		POP     DI
		POP     SI
		POP     AX
		POP     BP
		RET
CREARPWD ENDP

;=================Primitives (Printf, scanf, cls,...) =====================
ESCRIU PROC NEAR
		PUSH    BP
		PUSH    AX
		PUSH    DX
		MOV     BP, SP
		MOV     DX, [BP+8]
		MOV     AH, 09
		INT     21h
		POP     DX
		POP     AX
		POP     BP
		RET
ESCRIU	ENDP

NEWLINE PROC NEAR
        PUSH    AX
		PUSH    DX
        LEA     DX, n_line
        MOV     AH, 09
        INT     21h
        POP     DX
		POP     AX
		RET
NEWLINE ENDP

MKDIR PROC NEAR
        PUSH    BP
		PUSH    AX
		PUSH    DX
		MOV     BP, SP
		MOV     DX, [BP+8]
		MOV     AH, 39h
		INT     21h
		POP     DX
		POP     AX
		POP     BP
		RET
MKDIR ENDP

RMDIR PROC NEAR
        PUSH    BP
		PUSH    AX
		PUSH    DX  
		MOV     BP, SP
		MOV     DX, [BP+8]
		MOV     AH, 3Ah
		INT     21h
		POP     DX
		POP     AX
		POP     BP
		RET
RMDIR ENDP

LLEGIRCAD PROC NEAR
		PUSH    BP
		PUSH    AX
		PUSH    DX
		MOV     BP, SP
		MOV     DX, [BP+8]
		MOV     AH, 0ah
		INT     21h
		POP     DX
		POP     AX
		POP     BP
		RET
LLEGIRCAD ENDP   
		
LLEGIRCHR PROC NEAR
		MOV     AH, 01
		INT     21h
		RET
LLEGIRCHR ENDP

CONCATSTRINGS PROC NEAR
        PUSH    BP
		PUSH    AX
		PUSH    SI
		PUSH    DI
		MOV     BP, SP
		
	    MOV     SI, [BP+14]
		MOV     DI, [BP+10]
		
COPY1:  LODSB
		CMP     AL, 0Dh         ; Final de cadena (Enter) ? 0Dh = 13,10,
		JZ      FICONC1		    ; Hem acabat
        STOSB			        ; Guardar
		JMP     COPY1           ; Tracta el seguent	
FICONC1:	
        MOV     SI, [BP+12]
		
COPY2:  LODSB
		CMP     AL, 0Dh         ; Final de cadena (Enter) ?
		JZ      FICONC2		    ; Hem acabat 
        STOSB			        ; Guardar
		JMP     COPY2
FICONC2:			
		MOV     AL, 13		    ; Situar CR LF al final
		STOSB
		MOV     AL, 10
		STOSB
		MOV     AL, '$'		    ; Situar CR LF al final
		STOSB                   
		
		POP     DI
		POP     SI
		POP     AX
		POP     BP
		RET
CONCATSTRINGS ENDP		
		
SURT	PROC NEAR		
		MOV     AX, 4c00h	    ; Funcio de finalitzar i retorn al DOS
		INT     21h
		RET
SURT	ENDP		
		
CLS		PROC NEAR
		PUSH    AX
		MOV     AH, 00
		MOV     AL, 3
		INT     10h
		POP     AX
		RET
CLS		ENDP

SCAN_NUM PROC NEAR
        PUSH    BP
        PUSH    AX
        PUSH    DI        
        PUSH    CX
        
        MOV     BP, SP        
        MOV     CX, 0

NEXT_DIGIT:                        
        MOV     AH, 00h         ; Llegir caracter del teclat:
        INT     16h             ; Into AL:
                                
        MOV     AH, 0Eh
        INT     10h             ; Mostrar-lo per pantalla:
                        
        CMP     AL, 13          ; Es un ENTER:
        JNE     OK_DIGIT        ; ENTER?
        JMP     STOP_INPUT
 
OK_DIGIT:
                                ; Multiplica CX per 10 (el primer cop donara zero)
        PUSH    AX
        MOV     AX, CX
        MUL     CS:TEN          ; DX:AX = AX*10
        MOV     CX, AX
        POP     AX
               
        SUB     AL, 30h         ; Convertir de codi ASCII:

        MOV     AH, 0        
        ADD     CX, AX

        JMP     NEXT_DIGIT
            
STOP_INPUT:
        
        MOV     DI, [BP+10]        
        MOV     [DI], CX        ; Guarda el resultat a variable
        
        POP     CX
        POP     DI
        POP     AX
        POP     BP
        RET

TEN     DW      10              ; S'utilitza per multiplicar.
SCAN_NUM ENDP

HEXaDEC PROC NEAR
        PUSH    AX
        PUSH    BX
        PUSH    CX
        PUSH    DX
        PUSH    SI
        PUSH    BP
        
        MOV     BP, SP
		
	    MOV     SI, [BP+16]
	    MOV     AX, SI          ; Treballarem amb AX "numero a tractar"
		MOV     DI, [BP+14]
        
        MOV     CX, 0
        MOV     BX, 10
   
LOOP1:  MOV     DX, 0
        DIV     BX
        ADD     DL, 30h         ; Convertir de codi ASCII: 
        PUSH    DX
        INC     CX
        CMP     AX, 9
        JG      LOOP1           ; Mentres el numero sigui mes gran de una desena 
        
        ADD     AL, 30h         ; Convertir de codi ASCII:
        MOV     [DI], AL        ; Guardem digit al resultat
     
LOOP2:  POP     AX
        INC     DI
        MOV     [DI], AL        ; Guardem digit al resultat
        LOOP    LOOP2
        
        POP     BP
        POP     SI
        POP     DX
        POP     CX
        POP     BX
        POP     AX
        RET
HEXaDEC ENDP

CODI	ENDS                    ; final de codi
		END   PROG              ; Final del programa (marca l'inici)
