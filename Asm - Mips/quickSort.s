.data
array:	.space 40
line:				.asciiz "\n"
.text
.globl main
main:	
	li $t0, 0
	la $s0, array
	li.s $f2, 0.0
read:
	li $v0, 6
	syscall	
	s.s $f0, ($s0)
	add $s0, $s0, 4	
	add $t0, $t0, 1
	blt $t0, 10, read	
	la $a0, array
	jal average
	mov.s $f12, $f0
	li $v0, 4
	la $a0, line
	syscall		
	li $v0, 4
	la $a0, line
	syscall	
	li $v0, 2
	syscall		
	li $v0, 4
	la $a0, line
	syscall	
	li $v0, 4
	la $a0, line
	syscall	
	la $a0, array
	li $a1, 0
	li $a2, 9
	jal quickSort
	la $s0, array
	li $t0, 0
printArray:
	li $v0, 2
	l.s $f12, ($s0) 
	syscall
	li $v0, 4
	la $a0, line
	syscall
	add $s0, $s0, 4	
	add $t0, $t0, 1
	blt $t0, 10, printArray	
	li $v0, 10
	syscall
.end main

.globl average
.ent average
average:
	move $s1, $a0
	li.s $f0, 0.0
	li $t0, 0
averageLoop:
	l.s $f1, ($s1)
	add.s $f0, $f0, $f1
	add $s1, $s1, 4	
	add $t0, $t0, 1
	blt $t0, 10, averageLoop		
	li.s $f1, 10.0
	div.s $f0, $f0, $f1
	jr $ra	
.end average

.globl quickSort
.ent quickSort
quickSort:
	sub $sp, $sp, 20
	sw $ra, 0($sp)		#save return value	
	move $s0, $a0		#*v
	move $s1, $a1		#i = left
	move $s2, $a2		#j = right
	move $s3, $a1		#left
	move $s4, $a2		#rigtht
	add $t0, $s3, $s4	#left + right
	div $t0, $t0, 2
	mul $t0, $t0, 4
	add $t0, $t0, $s0
	l.s $f20, ($t0)		#pivot = v[(left + right) / 2]
whileQuickSort:
	bgt $s1, $s2, label
	mul $t0, $s1, 4
	add $t0, $t0, $s0
	l.s $f22, ($t0)
	c.lt.s $f22, $f20
whileQuickSort2:		#pivot > v[i]
	bc1f label2
	add $s1, $s1, 1 	#i++	
	add $t0, $t0, 4
	l.s $f22, ($t0)
	c.lt.s $f22, $f20
	j whileQuickSort2
label2:
	mul $t0, $s2, 4
	add $t0, $t0, $s0
	l.s $f22, ($t0)
	c.lt.s $f20, $f22	#pivot < v[j]
whileQuickSort3:
	bc1f label3
	sub $s2, $s2, 1 	#j--
	sub $t0, $t0, 4
	l.s $f22, ($t0)
	c.lt.s $f20, $f22	#pivot < v[j]
	j whileQuickSort3
label3:
	bgt $s1, $s2, label4
	mul $t0, $s1, 4
	mul $t1, $s2, 4
	add $t0, $t0, $s0
	add $t1, $t1, $s0
	l.s $f0, ($t0)		#v[i]
	l.s $f2, ($t1)		#v[j]
	s.s $f0, ($t1)
	s.s $f2, ($t0)	
	add $s1, $s1, 1
	sub $s2, $s2, 1
label4:
	j whileQuickSort
label:	
	sw $s1, 4($sp)		#save i
	sw $s2, 8($sp)		#save j
	sw $s3, 12($sp)		#save left
	sw $s4, 16($sp)		#save right
	
	blt $s3, $s2,  callLeft
label5:
	lw $s1, 4($sp)		#load i
	lw $s2, 8($sp)		#load j
	lw $s3, 12($sp)		#load left
	lw $s4, 16($sp)		#load right
	bgt $s4, $s1, callRight
	lw $ra, ($sp)		#load $ra
	add $sp, $sp, 20	
	jr $ra
 callLeft:
	move $a0, $s0
	move $a1, $s3
	move $a2, $s2
	jal quickSort
	j label5
callRight:
	move $a0, $s0
	move $a1, $s1
	move $a2, $s4
	jal quickSort
	lw $ra, ($sp)	#load $ra	
	add $sp, $sp, 20	
	jr $ra
.end quickSort