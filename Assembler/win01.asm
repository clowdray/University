;Aquesta DLL il?lustra la forma
;de com preparar funcions amb par?metres
;per ser trucades des de C++ C# o VB
		.386
		option casemap :none
		.model flat, stdcall
;Es necessita un apartat de dades
;en cas de voler treballar amb strings
		.data   
		
fre     dw 1
res     dw 0
un      dd 1.0
dos		dd 2.0
aux     dw 1

        .code
	              
freqRes	PROC  x:DWORD, y:DWORD
		FLD 	DWORD PTR [x]			; Recuperar float1 en st0
		FLD 	DWORD PTR [y]   		; Recuperar float2 en st1
		FMUL				    		; Suma st0=sto+st1
		FST 	DWORD PTR [fre]			; Resultat cap a memoria per poder-lo recuperar en 8086
		FLD 	DWORD PTR [fre]
		FSQRT							; Arrel quadrada del resultat anteior
		FST		DWORD PTR [fre]
		FLD		DWORD PTR [dos]
		FLDPI							; carreguem PI
		FMUL							; 2*PI
		FST		DWORD PTR [aux] 		; guardem a memoria 2*PI
		FLD		DWORD PTR [aux]
		FLD		DWORD PTR [fre]
		FMUL							; 2*PI * resultat de la arrel quadrada
	    FST 	DWORD PTR [fre]
		FLD 	DWORD PTR [un]  		; carreguem variable 1
		FLD 	DWORD PTR [fre] 		; carreguem valor resultant del denominador
		FDIV							; divisio del 1 per el valor resultant
		FST 	DWORD PTR [fre]			; Resultat cap a memòria per poder-lo recuperar en 8086
		MOV 	EAX, DWORD PTR [fre]	; Ara el puc carregar en EAX com a valor de retorn
		RET
freqRes	ENDP	

NomPropi  PROC USES EAX EDI ESI, CADE1:DWORD, CADE2:DWORD
        XOR     EAX, EAX
        MOV     ESI, CADE1				; carreguem adreca de lectura
        MOV     EDI, DWORD PTR CADE2	; carreguem adreca de guardat
        MOV     EDI, [EDI]
INOMP:  LODSB							; llegim caracter
        CMP     AL, 'a'					; si es superior o igual a "a" minuscules codi en hexa es mes gran que majuscules
        JAE     ABZ						; saltem a 2a comporbació
        JNE     SNOMP					; en cas contrari guardem la lletra
ABZ:    CMP     AL, 'z'					; comprovar si es inferior a "z"
        JBE     MAX_ABZ					; en cas positiu restar 20h per transformar en majuscula
        JMP     SNOMP 					; en cas negatiu guardar
MAX_ABZ:SUB     AL, 20h
        STOSB
BNOMP:  LODSB							; llegim a partir de la segona lletra de la paraula
        CMP     AL, 0					; comprovem si es el final de la cadena
        JZ      FNOMP					; saltem a Fi NomPropi "FNOMP"
        CMP     AL, ' '					; Mirem si hi ha un espai, significa que acaba la paraula i hi ha més paraules
        JZ      SNEXT					; guardem el espai i tornem a llegir el 1r caracter de paraula en "INOMP"
        CMP     AL, 'A'					; Mirem i es majuscula
        JAE     ZBA
        JNE     SNOMP
ZBA:    CMP     AL, 'Z'
        JBE     MIN_ZBA
        JMP     SNOMP 
MIN_ZBA:ADD     AL, 20h					; sumem per fer-la minuscula
SNOMP:  STOSB
        JMP     BNOMP
SNEXT:  STOSB 
        JMP     INOMP 
FNOMP:  MOV     AL,0					; finalitzem posant un 0 al final
        STOSB
        RET								; retorna el Nom i Cognom en la variable CADE2
NomPropi    ENDP

max  PROC  USES EBX ECX ESI, taula:DWORD
        XOR 	CX, CX					; inicialitzem a 0 ECX
		MOV 	ESI, DWORD PTR taula	; carreguem en un punter la direcció de la taula
		SUB		ESI, 4					; restem 4 a la direccio per trobar la llargada
		MOV		EBX, DWORD PTR [ESI]	; agafem la llargada i la guardem en EBX
		ADD 	ESI, 4					; tornem a la posició inicil
BMAX:   CMP		EBX, 0					; comparem si hem acabat EBX = 0 (decrementem)
		JZ		FMAX					; si acabem saltem a FI MAX -> FMAX
		MOV		AX, WORD PTR [ESI]		; agafem el valor de la taula i el guardem en EAX
		ADD 	ESI, 2					; sumem 4 a la posicio per al proxim valor
		DEC 	EBX						; decrementem el numero de iteracions de EBX
		CMP 	AX, CX					; comparem el valor llegit amb el anterior ECX, primera volta val 0
        JA  	GMAX					; si es més gran el guarda
        JMP 	BMAX					; si es igual o mes petit torna al bucle
GMAX:   MOV 	CX, AX				
        JMP 	BMAX
FMAX:   MOV 	AX, CX					; guardem el valor final en el registre EAX
        RET
max  ENDP

;Procediment necessari com a punt d'entrada de la DLL
DllMain	PROC hinstDLL:DWORD, dwReason:DWORD, lpvReserved:DWORD
		MOV 	EAX,1
		RET
DllMain ENDP

		END DllMain
	
		