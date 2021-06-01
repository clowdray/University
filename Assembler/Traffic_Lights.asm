#start=Traffic_Lights.exe#

name "Part_ES - Traffic Lights"


data segment
    config_times        db  250,250 dup (?)
    yellow_and_green    equ 0000_0110b
    red                 equ 0000_0001b
    yellow_and_red      equ 0000_0011b
    green               equ 0000_0100b
    all_red             equ 0010_0100_1001b
    null_color          equ 0000_0000_0000b
    config              db  2               ; configuracio "2" default
    config2             db  0
ends

code segment
    
start:                              ; punt d'entrada
    mov     ax, data                ; Segments a lloc
    mov     ds, ax
    mov     es, ax
    
    xor     ax,ax
    mov     es,ax                   ; Per apuntar 

; -----------Preparar Rutina de Config 90h
    xor     bx, bx
    mov     al, 90h                 ; INT 90
    mov     bl, 4h                  ; multiplicar per 4 --> Obtenir posicio en taula       
    mul     bl
    mov     bx, ax                 
    mov     si, offset [Config90]   ; Offset de la nostra rutina servei01
    mov     es:[bx], si			    ; Offset b--> Taula Vector[01]		
    add     bx, 2   			    ; Que BX apunti al Segment (+2 de Offset)
    mov     ax, cs     			    ; CS --> Reg segment de la Rutina Servei01	
    mov     es:[bx], ax 		    ; Segment cap a la Taula Vector[01+02]  
         
; -----------Preparar Rutina de Per defecte 91h
    xor     bx, bx
    mov     al, 91h                 ; INT 90
    mov     bl, 4h                  ; multiplicar per 4 --> Obtenir posicio en taula       
    mul     bl
    mov     bx, ax                 
    mov     si, offset [defecte91]  ; Offset de la nostra rutina servei01
    mov     es:[bx], si			    ; Offset b--> Taula Vector[01]		
    add     bx, 2   			    ; Que BX apunti al Segment (+2 de Offset)
    mov     ax, cs     			    ; CS --> Reg segment de la Rutina Servei01	
    mov     es:[bx], ax 		    ; Segment cap a la Taula Vector[01+02]  

; -----------Preparar Rutina de Intermitent 92h
    xor     bx, bx
    mov     al, 92h                 ; INT 90
    mov     bl, 4h                  ; multiplicar per 4 --> Obtenir posicio en taula       
    mul     bl
    mov     bx, ax                 
    mov     si, offset [Inter92]    ; Offset de la nostra rutina servei01
    mov     es:[bx], si			    ; Offset b--> Taula Vector[01]		
    add     bx, 2   			    ; Que BX apunti al Segment (+2 de Offset)
    mov     ax, cs     			    ; CS --> Reg segment de la Rutina Servei01	
    mov     es:[bx], ax 		    ; Segment cap a la Taula Vector[01+02]            
            
;Bucle infinit (espera interrupcions)
    xor     bx, bx
    xor     cx, cx
    xor     dx, dx
    
    mov     [config_times+0], 06h   ; 6 segons per defecte semafor 1
    mov     [config_times+2], 06h   ; 6 segons per defecte semafor 2
    mov     [config_times+4], 06h   ; 6 segons per defecte semafor 3
    mov     [config_times+6], 06h   ; 6 segons per defecte semafor 4
    
    mov     ax, all_red
    out     4, ax
bucle:
    xor     ax,ax
    ;------------------
    mov     ax, [config]
    mov     [config2], ax			; assignem el valor de config a config 2
    xor     ax, ax
    cmp     [config], 01h           ; Depenent de la configuracio escollida
    je      conf1                   ; el bucle infinit executara unes accions
    cmp     [config], 02h           ; o unes altres. Al iniciar el programa la
    je      conf2                   ; configuracio es per defecte (2)
    cmp     [config], 03h
    je      conf3
    ;------------------ 
    
conf1:;-------------------------------------------------------------------------------------
    mov     dx, byte ptr [config_times+bx]   ; extraiem els segons del semafor
    mov     ax, green               ; semafor en verd
    shl     ax, cl
    push    dx
    mov     dx, red                 ; semafor +1 en vermell
    push    cx
    add     cl, 3                   ; ens movem 3 posicions
    cmp     cl, 12                  ; en el cas de sobrepassar 9+3 = 12
    jb      conf1ok
    sub     cl, 12                  ; restarem 12 i ens queda a la posicio 0
conf1ok:
    shl     dx, cl
    add     ax, dx                  ; sumem el valors
    pop     cx                      
    mov     dx, red                 ; semafor +1 en vermell
    push    cx
    add     cl, 6                   ; ens movem 6 posicions de la actual
    cmp     cl, 12                  ; en el cas de sobrepassar 6+6 = 12 o 9+6 = 15
    jb      conf1ok2
    sub     cl, 12                  ; restarem 12 i ens queda a la posicio 0 o 3
conf1ok2:
    shl     dx, cl
    add     ax, dx                  ; sumem el valors
    pop     cx
    mov     dx, red                 ; semafor +1 en vermell
    push    cx
    add     cl, 9                   ; ens movem 9 posicions de la actual
    cmp     cl, 12                  ; en el cas de sobrepassar 3+9 = 12 o 6+9 = 15 o 9+9 = 18
    jb      conf1ok3
    sub     cl, 12                  ; restarem 12 i ens queda a la posicio 0, 3 o 6
conf1ok3:
    shl     dx, cl
    add     ax, dx                  ; sumem el valors
    pop     cx
    pop     dx
    out     4, ax
    
    jmp     wait
conf2:;-------------------------------------------------------------------------------------
    mov     dx, byte ptr [config_times+bx]   ; extraiem els segons del semafor
    mov     ax, green
    shl     ax, cl
    push    dx
    mov     dx, green
    push    cx
    add     cl, 6
    shl     dx, cl
    add     ax, dx
    pop     cx
    mov     dx, red
    push    cx
    add     cl, 3
    shl     dx, cl
    add     ax, dx
    pop     cx
    mov     dx, red
    push    cx
    add     cl, 9
    cmp     cl, 12                  ; en aquest cas nomes pot fallar al sumar 9
    jb      conf2ok                 ; ja que la posicio actual nomes pot ser 0 o 3
    sub     cl, 12                  ; 3+9 = 12 - 12 = 0
conf2ok:
    shl     dx, cl
    add     ax, dx
    pop     cx
    pop     dx
    
    out     4, ax
                                    
    jmp     wait
conf3:;-------------------------------------------------------------------------------------
    mov     ax, all_red << 1        ; tots en intermitent
    out     4, ax
    
    mov 	dx, 0
	
	pusha
    mov     cx, 000Fh               ; 000F4240h = 1,000,000
    mov     dx, 4240h
    mov     ah, 86h                 ; esperem un segon amb llum encesa
    int     15h
    popa    
    
    jmp     wait
           
;-------------------------------------------------------------------------------------------    
wait:    
    cmp     dx, 00h                 ; crides on tenim els milisegons calculas en hexadecimal
    je      zeroseg
    cmp     dx, 01h
    je      unseg
    cmp     dx, 02h
    je      dosseg
    cmp     dx, 03h
    je      tresseg
    cmp     dx, 04h
    je      quatreseg
    cmp     dx, 05h
    je      cincseg
    cmp     dx, 06h
    je      sisseg
    cmp     dx, 07h
    je      setseg
    cmp     dx, 08h
    je      vuitseg
    cmp     dx, 09h
    je      nouseg
    cmp     dx, 0Ah
    je      deuseg
    cmp     dx, 0Bh
    je      onzeseg
    cmp     dx, 0Ch
    je      dotzeseg
    cmp     dx, 0Dh
    je      tretzeseg
    cmp     dx, 0Eh
    je      catorzeseg
    cmp     dx, 0Fh
    je      quinzeseg
postwait:
    ;------------------
    cmp     [config2], 01h          ; Depenent de la configuracio escollida
    je      conf11                  ; el bucle infinit executara unes accions
    cmp     [config2], 02h          ; o unes altres. Al iniciar el programa la
    je      conf22                  ; configuracio es per defecte (2)
    cmp     [config2], 03h			; En el cas de fer INT90, 91 o 92, primer acabara la execucio actual
    je      conf33
    ;------------------ 
conf11:;------------------------------------------------------------------------------------
    mov     ax, yellow_and_green    ; el mateix mecanisme que en el modul conf11, pero canviant a groc+verd
    shl     ax, cl
    push    dx
    mov     dx, red
    push    cx
    add     cl, 3
    cmp     cl, 12
    jb      conf11ok
    sub     cl, 12
conf11ok:
    shl     dx, cl
    add     ax, dx
    pop     cx
    mov     dx, red
    push    cx
    add     cl, 6
    cmp     cl, 12
    jb      conf11ok2
    sub     cl, 12
conf11ok2:
    shl     dx, cl
    add     ax, dx
    pop     cx
    mov     dx, red
    push    cx
    add     cl, 9
    cmp     cl, 12
    jb      conf11ok3
    sub     cl, 12
conf11ok3:
    shl     dx, cl
    add     ax, dx
    pop     cx
    pop     dx
    out     4, ax
    
    pusha
    mov     cx, 001Eh               ; 001E8480h = 2,000,000
    mov     dx, 8480h
    mov     ah, 86h
    int     15h
    popa
    
    mov     ax, all_red             ; tot a vermell
    out     4, ax
    
    cmp     bx, 6                   ; si arriba a la 4a posicio del array
    jne     no6
    xor     bx, bx
    xor     cx, cx                  ; tornem a la posicio 1
    jmp     fibucle
no6:
    add     cl, 3
    add     bx, 2                   ; continuem a la seguent posicio
    
    jmp     fibucle
conf22:;------------------------------------------------------------------------------------ 
    mov     ax, yellow_and_green    ; canvia de verd a groc
    shl     ax, cl 
    push    dx
    mov     dx, yellow_and_green    ; canvia de verd a groc
    push    cx
    add     cl, 6
    shl     dx, cl
    add     ax, dx
    pop     cx
    mov     dx, red                 
    push    cx
    add     cl, 3
    shl     dx, cl
    add     ax, dx
    pop     cx
    mov     dx, red                 
    push    cx
    add     cl, 9
    cmp     cl, 12
    jb      conf22ok
    sub     cl, 12
conf22ok:
    shl     dx, cl
    add     ax, dx
    pop     cx
    pop     dx
    out     4, ax
    
    pusha
    mov     cx, 001Eh               ; 001E8480h = 2,000,000
    mov     dx, 8480h
    mov     ah, 86h                 ; esperem dos segons de transcicio
    int     15h
    popa
    
    mov     ax, all_red             ; tot a vermell
    out     4, ax
     
    cmp     bx, 4                   ; si arriba a la 3 posicio del array
    jne     n6
    xor     bx, bx
    xor     cx, cx                  ; tornem a la posicio 1
    jmp     fibucle
n6:
    add     cl, 3
    add     bx, 4                   ; continuem a 3a seguent posicio
    
    jmp     fibucle
conf33:;------------------------------------------------------------------------------------
    mov     ax, null_color          ; canvia tots a null
    shl     ax, cl 
    out     4, ax
    
    pusha
    mov     cx, 000Fh               ; 000F4240h = 1,000,000
    mov     dx, 4240h
    mov     ah, 86h                 ; esperem 1 segons sense llum
    int     15h
    popa 
     
    jmp     fibucle
 
fibucle:;-----------------------------------------------------------------------------------
    pusha                           ; guardem registres anteriors
    xor     ax, ax                  ; posem a 0 el registre ax
    xor     bx, bx                  ; posem a 0 el registre bx
    mov     al, [config]            ; assignem estat 1
    mov     bl, [config2]           ; assignem estat 2
    cmp     al, bl                  ; comparem si es el mateix estat
    popa                            ; ax i bx tornen a tenir el valor anterior                           
    jne     diferent                ; mirem si son diferents                            
    je      mateixaINT              ; mirem si son iguals
diferent:                           ; si son diferents posem a 0 bx i cx
    xor     bx, bx                  
    xor     cx, cx
mateixaINT:                         ; si son iguals bx i cx tenen els seus valors anteriors
    jmp     bucle                   ; tornem al bucle
 
    int     20h                     ; aturar execucio

;----Definicio del Servei 90h:--------------------------------------------------------------
Config90: 
    pusha                           ; salvar tots els registres.
    cli                             ; enmascarar INT
    
    xor     ax, ax
    
    mov     [config], 01h                  
    
    mov     dx, 1001h
    in      al, dx
    mov     [config_times], al      ; guardar temps del primer semafor a la posicio 0 del array
                                
    mov     dx, 1002h
    in      al, dx
    mov     [config_times+2], al    ; guardar temps del segon semafor a la posicio 1 del array
      
    mov     dx, 1003h
    in      al, dx
    mov     [config_times+4], al    ; guardar temps del tercer semafor a la posicio 2 del array
    
    mov     dx, 1004h 
    in      al, dx
    mov     [config_times+6], al    ; guardar temps del quart semafor a la posicio 3 del array
    
    ;  
    sti                             ; Permetre INTs
    popa                            ; recuperar registres.
    iret                            ; retorn de interrupcio

;----Definicio del Servei 91h:--------------------------------------------------------------
defecte91: 
    pusha                           ; salvar tots els registres.
    cli                             ; enmascarar INT
    
    xor     ax, ax
    
    mov     [config], 02h                  
    
    mov     dx, 1001h
    in      al, dx
    mov     [config_times], al      ; guardar temps del primer semafor a la posicio 0 del array
                                      
    mov     dx, 1003h
    in      al, dx
    mov     [config_times+4], al    ; guardar temps del tercer semafor a la posicio 2 del array
     
    ;  
    sti                             ; Permetre INTs
    popa                            ; recuperar registres.
    iret                            ; retorn de interrupcio

;----Definicio del Servei 92h:--------------------------------------------------------------
Inter92:
    pusha                           ; salvar tots els registres.
    cli                             ; enmascarar INT

    mov     [config], 03h
     
    ;  
    sti                             ; Permetre INTs
    popa                            ; recuperar registres.
    iret                            ; retorn de interrupcio
;-------------------------------------------------------------------------------------------
quinzeseg:
    pusha
    mov     cx, 00E4h               ; 00E4E1C0h = 15,000,000
    mov     dx, 0E1C0h
    mov     ah, 86h                 ; esperem quinze seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
catorzeseg:
    pusha
    mov     cx, 00D5h               ; 00D59F80h = 14,000,000
    mov     dx, 9F80h
    mov     ah, 86h                 ; esperem catorze seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
tretzeseg:
    pusha
    mov     cx, 00C6h               ; 00C65D40h = 13,000,000
    mov     dx, 5D40h
    mov     ah, 86h                 ; esperem tretze seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
dotzeseg:
    pusha
    mov     cx, 00B7h               ; 00B71B00h = 12,000,000
    mov     dx, 1B00h
    mov     ah, 86h                 ; esperem dotze seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
onzeseg:
    pusha
    mov     cx, 00A7h               ; 00A7D8C0h = 11,000,000
    mov     dx, 0D8C0h
    mov     ah, 86h                 ; esperem onze seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
deuseg:
    pusha
    mov     cx, 0098h               ; 00989680h = 10,000,000
    mov     dx, 9680h
    mov     ah, 86h                 ; esperem deu seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
nouseg:
    pusha
    mov     cx, 0089h               ; 00895440h = 9,000,000
    mov     dx, 5440h
    mov     ah, 86h                 ; esperem nou seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
vuitseg:
    pusha
    mov     cx, 007Ah               ; 007A1200h = 8,000,000
    mov     dx, 1200h
    mov     ah, 86h                 ; esperem vuit seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
setseg:
    pusha
    mov     cx, 006Ah               ; 006ACFC0h = 7,000,000
    mov     dx, 0CFC0h
    mov     ah, 86h                 ; esperem set seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
sisseg:
    pusha
    mov     cx, 005Bh               ; 005B8D80h = 6,000,000
    mov     dx, 8D80h
    mov     ah, 86h                 ; esperem sis seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
cincseg:
    pusha
    mov     cx, 004Ch               ; 004C4B40h = 5,000,000
    mov     dx, 4B40h
    mov     ah, 86h                 ; esperem cinc seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
quatreseg:
    pusha
    mov     cx, 003Dh               ; 003D0900h = 4,000,000
    mov     dx, 0900h
    mov     ah, 86h                 ; esperem quatre seg
    int     15h                     
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
tresseg:
    pusha
    mov     cx, 002Dh               ; 002DC6C0h = 3,000,000
    mov     dx, 0C6C0h
    mov     ah, 86h                 ; esperem tres seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
dosseg:
    pusha
    mov     cx, 001Eh               ; 001E8480h = 2,000,000
    mov     dx, 8480h
    mov     ah, 86h                 ; esperem dos seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
unseg:
    pusha
    mov     cx, 000Fh               ; 000F4240h = 1,000,000
    mov     dx, 4240h
    mov     ah, 86h                 ; esperem un seg
    int     15h
    popa
    
    jmp postwait                    ; tornem a la execucio principal
    
zeroseg:
    pusha
    mov     cx, 0000h               ; 00000000h = 0
    mov     dx, 0000h
    mov     ah, 86h                 ; esperem zero seg
    int     15h
    popa
                                    
    jmp postwait                    ; tornem a la execucio principal
    
ends
end start

