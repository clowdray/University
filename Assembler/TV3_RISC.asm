	.data 	0x10000000
cadeEnt:  	.space 100
cadeSor:  	.space 100
saltLinia:	.asciiz "\n"
menuTitle:	.asciiz "--MENU--\n"
menu1: 		.asciiz "[1] Suma en CF \n"
menu2: 		.asciiz "[2] Crear e-mail \n"
menu3: 		.asciiz "[3] Conversio de binari a hexa \n"
menu4:		.asciiz "[4] Sortir \n"
opcio:		.asciiz "Entra opcio: "
errorr:		.asciiz "(Error, opcio valida 1..4) \n"
miss1:    	.asciiz "Introdueix nom i cognom: "
miss2:    	.asciiz "El mail es : "
miss3:    	.asciiz "Introdueix num 1 (float): "
miss4:    	.asciiz "Introdueix nom 2 (float): "
miss5:    	.asciiz "La seva suma es: "
miss6:		.asciiz "Introdueix el numero binari: "
domini:		.asciiz "@uda.ad"
num1:		.float 0.0
num2:		.float 0.0
solucio:	.space 100

    .text
    .globl main

############ Programa principal ################################	
main:
	
	la 	$a0, menuTitle			# Titol del menu
	jal escriuCad
	la 	$a0, menu1				# Menu 1 a Pantalla
	jal escriuCad
	la 	$a0, menu2				# Menu 2 a Pantalla
	jal escriuCad
	la 	$a0, menu3				# Menu 3 a Pantalla
	jal escriuCad
	la 	$a0, menu4				# Menu 4 a Pantalla
	jal escriuCad
	la 	$a0, opcio				# Missatge entrar opcio
	jal escriuCad
	la 	$a0, cadeEnt			# Espera entrada opcio
	jal llegirCad
	
	la 	$a0, saltLinia			# salt de linia
	jal escriuCad
	
	la 	$a0, cadeEnt			# recullo el numero introduit
	lb 	$v0, 0($a0)				# carrego el numero en un registre
	sub $v0, $v0, 48			# transformo el ascii a numeric restant 48
	
	beq $v0, 1, saltOP1
	beq $v0, 2, saltOP2
	beq $v0, 3, saltOP3
	beq $v0, 4, saltOP4
	j 	saltERR
saltOP1:	
	jal opcio1					# saltem a la opcio 1 guardant la adreça de retorn
	j fimain	
saltOP2:
    jal opcio2					# saltem a la opcio 2 guardant la adreça de retorn
	j fimain
saltOP3:
    jal opcio3					# saltem a la opcio 3 guardant la adreça de retorn
	j fimain	
saltOP4:
    jal opcio4					# saltem a la opcio 4 guardant la adreça de retorn
	j fimain
saltERR:
	la 	$a0, errorr				# missatge d errorr
	jal escriuCad

fimain:
	la 	$a0, saltLinia			# salt de linia
	jal escriuCad
	jal main

############## Opcions del Menu ################################		
	
opcio1:
	la	$s8, ($ra)				# push adreça retorn
	
	la 	$a0, miss3				# Missatge 3 a Pantalla
	jal escriuCad
	jal llegirFloat				# crida a la funcio de llegir un double, valor en f0
	mov.s $f6, $f0				# guardem el valor en un altre registre
	la 	$a0, miss4				# Missatge 4 a Pantalla
	jal escriuCad
	jal llegirFloat				# crida a la funcio de llegir un double, valor en f0
	la 	$a0, miss5
	jal escriuCad
	add.s $f12, $f0, $f6		# el resultat de num1, num2 es guarda en f12
	jal escriuFloat
	la 	$ra, ($s8)				# pop adreça retorn
	jr $ra
	
opcio2:
	la	$s8, ($ra)				# push adreça retorn
	
    la 	$a0, miss1				# Missatge 1 a Pantalla
	jal escriuCad
	la 	$a0, cadeEnt			# Espera entrada String
	jal llegirCad
	la 	$a0, cadeEnt			# Prepara Cadena a tractar i resultat
	la 	$a1, cadeSor
	jal email					# Tractament
	la 	$a0, miss2				# Missatge 2 a Pantalla
	jal escriuCad
	la 	$a0, cadeSor			# Enviar resultat a Pantalla
	jal escriuCad
	
	la 	$ra, ($s8)				# pop adreça retorn
	jr 	$ra

opcio3:
	la	$s8, ($ra)				# push adreça retorn
	
	la 	$a0, miss6				# Missatge 3 a Pantalla
	jal escriuCad	
	la 	$a0, cadeEnt			# Espera entrada String
	jal llegirCad
	
	li $a3, -1
	la	$a2, solucio			# Apunta al string de sortida
llargada:
	lb  $a1, 0($a0)				# mirem si el caracter seguent es el final de la cadena
	addi $a0, $a0, 1
	beq $a1, $0, fi_llargada	# si es el ultim sortim del while
	addi $a3, $a3, 1
	j llargada
fi_llargada:    

sub $a0, $a0, 3

bwhile:
	xor $t1, $t1, $t1			# reiniciem registre $t1
	li $t3,1					# preparem per a que el bucle for vaig de 0<4
	li $t4,5
bfor:
	beq	$a3, $0, exitb
	lb  $t0, 0($a0)				# carreguem un byte
	sub $t0, $t0, 48			# transformem el char a digit
	beq $t0, 1, suma			# si es un 1 fem la suma
	j 	fisuma					# si es un 0 tornem al bucle for
suma:
	beq $t3, 4, L1				# si estem en el 4 bit
	beq $t3, 3, L2				# si estem en el 3 bit
	beq $t3, 2, L3				# si estem en el 2 bit
    j exitif					# si estem en el 1 bit
L1: addi $t0, $t0 , 7			# sumem 7 al 1, = 8
	j exitif
L2: addi $t0, $t0 , 3			# sumem 3 al 1, = 4
	j exitif
L3: addi $t0, $t0 , 1			# sumem 1 al 1, = 2
exitif:
	add $t1, $t1, $t0			# sumem el valor al resultat
fisuma:
	sub $a3, $a3, 1	
	add $t3, $t3,1				# decrementem el for
	sub $a0, $a0, 1				# apuntem al seguent caracter
	slt $8,$t3,$t4				# comparem si estem al final del for
	bne $8, 1, exitb
	j bfor
exitb:

# mirar quin es el valor del residu per trobar els ultims 4 digits en binari
	beq $t1, 0, s_zero			# transformem el numero a caracter numeric
	beq $t1, 1, s_un
	beq $t1, 2, s_dos
	beq $t1, 3, s_tres
	beq $t1, 4, s_quatre
	beq $t1, 5, s_cinc
	beq $t1, 6, s_sis
	beq $t1, 7, s_set
	beq $t1, 8, s_vuit
	beq $t1, 9, s_nou
	beq $t1, 10, s_deu
	beq $t1, 11, s_onze
	beq $t1, 12, s_dotze
	beq $t1, 13, s_tretze
	beq $t1, 14, s_catorze
	beq $t1, 15, s_quinze
# transformar els digits binaris a cacracters
s_zero:
	jal zero
	j 	fi_taula
s_un:
	jal un
	j 	fi_taula
s_dos:
	jal dos
	j 	fi_taula
s_tres:
	jal tres
	j 	fi_taula
s_quatre:
	jal quatre
	j 	fi_taula
s_cinc:
	jal cinc
	j 	fi_taula
s_sis:
	jal sis
	j 	fi_taula
s_set:
	jal set
	j 	fi_taula
s_vuit:
	jal vuit
	j 	fi_taula
s_nou:
	jal nou
	j 	fi_taula
s_deu:
	jal deu
	j 	fi_taula
s_onze:
	jal onze
	j 	fi_taula
s_dotze:
	jal dotze
	j 	fi_taula
s_tretze:
	jal tretze
	j 	fi_taula
s_catorze:
	jal catorze
	j 	fi_taula
s_quinze:
	jal quinze
	j 	fi_taula
fi_taula:	# fi transformacio binari a caracter

	sb  $t1, 0($a2)				# guardem el caracter en la resposta
	beq	$a3, $0, exitw			# si es el ultim sortim del while
	addi $a2, $a2, 1			# apuntem a la seguent posicio de la resposta
	
	j bwhile
exitw:

	la  $a2, solucio
contSolu:
	lb  $a1, 0($a2)				# mirem si el caracter seguent es el final de la cadena
	beq $a1, $0, fi_contSolu	# si es el ultim sortim del while
	addi $a2, $a2, 1
	addi $a3, $a3, 1
	j contSolu
fi_contSolu:

	sub $a3, $a3, 1
	la  $a2, solucio
	add $a2, $a2, $a3
	la 	$a0, cadeSor
	addi $a3, $a3, 1

girarSolu:
	beq $a3, $0, fi_girarSolu	# si es el ultim sortim del while
 	lb  $a1, 0($a2)				# mirem si el caracter seguent es el final de la cadena
	sb  $a1, 0($a0)
	sub $a2, $a2, 1
	addi $a0, $a0, 1
	sub $a3, $a3, 1
	j girarSolu
fi_girarSolu:
	la $a0, cadeSor
	jal escriuCad
	
	la 	$ra, ($s8)				# pop adreça retorn
	jr 	$ra
opcio4:
	jal sortir

############# Rutines Escriu, Llegir, Sortir ###################	
escriuCad:	
	li $v0, 4					# $v0 num de funció (4-->imprimir)
    syscall						# Crida a sistema
    jr 	$ra
	
llegirCad:	
	addi $a1, $0, 100			# $a1 llargada max
    li $v0, 8					# $v0 num de funció (8-->llegir String)
    syscall
    jr 	$ra
	
llegirFloat:
    li $v0, 6					# $v0 num de funció (6-->llegir float)
    syscall
    jr 	$ra

escriuFloat:
    li $v0, 2					# $v0 num de funció (2-->imprimir float)
    syscall
    jr 	$ra

llegirChar:
	li 	$v0, 5
	syscall
	jr 	$ra

sortir:
	addi $v0, $0, 10			# $v0 num de funció (10-->exit)
    syscall						# Crida a sistema
	
############## Rutina Tractament Email #########################
email:	
	
	addi $t3, $0, 96			# codi ASCII abans de 'a'
    addi $t4, $0, 123			# codi ASCII després de 'z'
	addi $t6, $0, 32			# codi ASCII "space"
	addi $t7, $0, 46			# codi ASCII '.'
	

# $t5 : Conté el caràcter a tractar
# $a0 : Apuntador a cadena entrada
# $a1 : Apuntador a cadena sortida
 	lb 	$t5, 0($a0)				# Llegir un char
	blt $t5, $t3, nomMayus		# és inferior a 'a' --> deixa'l estar
	j 	gnom
nomMayus:
	addi $t5, $t5, 32			# Era una minúscula, doncs transforma a majus
gnom:
	sb 	$t5, 0($a1)	
nom:
	addi $a0, $a0, 1			# Tractar el següent de la taula
	lb 	$t5, 0($a0)				# Llegir un char    
	beq $t5, $t6, punt			# si es igual a espai salta a cognom
	j 	nom
punt:
	addi $a1, $a1, 1			# Punter sortida seguent posició
	sb 	$t7, 0($a1)
cognom:
	addi $a0, $a0, 1			# Tractar el següent de la taula
	lb 	$t5, 0($a0)				# Llegir un char
	beq $t5, $0, fi
	addi $a1, $a1, 1			# Punter sortida seguent posició
	blt $t5, $t3, cognomMayus	# és inferior a 'a' --> deixa'l estar
	sb 	$t5, 0($a1)	
    j 	cognom
cognomMayus:
	addi $t5, $t5, 32			# Era una minúscula, doncs transforma a majus
	sb 	$t5, 0($a1)	
	j 	cognom
fi:
	la 	$a3, domini
	lb 	$t5, 0($a3)				# Llegir un char
addDomini:
	beq $t5, $0, fiDom
	sb 	$t5, 0($a1)
	addi $a1, $a1,1				# Punter sortida seguent posició
	addi $a3, $a3,1				# Tractar el següent de la taula
	lb 	$t5, 0($a3)				# Llegir un char
	j 	addDomini
fiDom:	
	jr 	$ra

zero:
	li  $t1, '0'
	jr 	$ra
un:
	li  $t1, '1'
	jr 	$ra
dos:
	li  $t1, '2'
	jr 	$ra
tres:
	li  $t1, '3'
	jr 	$ra
quatre:
	li  $t1, '4'
	jr 	$ra
cinc:
	li  $t1, '5'
	jr 	$ra
sis:
	li  $t1, '6'
	jr 	$ra
set:
	li  $t1, '7'
	jr 	$ra
vuit:
	li  $t1, '8'
	jr 	$ra
nou:
	li  $t1, '9'
	jr 	$ra
deu:
	li  $t1, 'A'
	jr 	$ra
onze:
	li  $t1, 'B'
	jr 	$ra
dotze:
	li  $t1, 'C'
	jr 	$ra
tretze:
	li  $t1, 'D'
	jr 	$ra
catorze:
	li  $t1, 'E'
	jr 	$ra
quinze:
	li  $t1, 'F'
	jr 	$ra