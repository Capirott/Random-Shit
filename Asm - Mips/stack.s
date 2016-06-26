.data
infix: 		.space 101	#Array of Char[101]
rpnExpression:	.space 101	#Array of Char[101]
line:		.asciiz "\n"	
.text
.globl main

main:
	jal readString
	move $s3, $sp	#Initial Address Stack

	la $s0, infix
	la $s1, rpnExpression
	lb $t0, ($s0)
while:	beq $t0, '\n', end
	move $a0, $t0
	jal isLetter
	beq $v0, 1, addLetterOutPut
	beq $t0, '(', push
	beq $t0, ')', closeParentheses
	jal condition	
while3:	beq $v0, 0, endWhile3
	lw $t4, ($sp)
	sb $t4, ($s1)
	addi $s1, 1	
	addu $sp, 4	
	jal condition
	j while3
endWhile3:
	beq $sp, $s3, push	#Stack empty
	jal precedenceValue
	move $t4, $v0
	lw $a0, ($sp)
	jal precedenceValue
	bne $t4, $v0, push	
swap:	
	lw $t1, ($sp)
	sb $t1, ($s1)
	addi $s1, 1
	addu $sp, 4
push:
	subu $sp, 4
	sw $t0, ($sp)
	j endWhile
closeParentheses:
	lw $t1, ($sp)
while2:	beq $t1, '(', endWhile2
	sb $t1, ($s1)
	addi $s1, 1	
	addu $sp, 4
	lw $t1, ($sp)
	j while2	
endWhile2:
	addu $sp, 4
	j endWhile
addLetterOutPut:
	sb $t0, ($s1)
	addi $s1, 1
endWhile:
	addi $s0, 1
	lb $t0, ($s0)
	j while

end:
	sb $0, ($s1)
	li $v0, 4
	la $a0, rpnExpression
	syscall
	li $v0, 10
	syscall

.end main


readString:
	li $v0, 8
	la $a0, infix
	li $a1, 100
	syscall
	jr $ra
.end readString

isLetter:
	blt $a0, 'A', isNotLetter
	bgt $a0, 'Z', isNotLetter

	li $v0, 1
	jr $ra

isNotLetter:
	li $v0, 0
	jr $ra
.end isLetter

precedenceValue:
	beq $a0, '+', value1
	beq $a0, '-', value1
	beq $a0, '*', value2
	beq $a0, '/', value2

	li $v0, -1	#Error Value Return
	jr $ra
value1:
	li $v0, 1
	jr $ra
value2:
	li $v0, 2
	jr $ra

.end precedenceValue

condition:
	move $t9, $ra
	beq $sp, $s3, false
	jal precedenceValue
	move $t7, $v0
	move $a1, $a0
	lw $a0, ($sp)
	jal precedenceValue
	move $a0, $a1
	blt $t7, $v0, true
false:
	move $v0, $0
	jr $t9
true:
	li $v0, 1
	jr $t9
.end condition
