.data
array: .word 0, 5, 15, 3, 18, 7, 20, 2, 16, 1 
.text
.globl main
main:
addi $sp, $sp, -16	# open stack for 4 words

la $t0, array		# set array to &array
addi $a0, $t0, 0	# array[0]
addi $a1, $zero, 9	# N = 10

add $a2, $zero, $a1	# gap starts at N

######shellSort###############################
shellSort:	
beq $a2, $zero, exit
srl $a2, $a2, 1   	# gap / 2
jal insertShell

exit:
add $v0, $t0, $zero
li $v0, 10
syscall

######insertShell##############################
insertShell:
addi $v0, $zero, 0 	#reset $v register
add $s0, $zero, $a2   	# i = gap

outer:
beq $s0, $a1, shellSort 	# i < N
addi $s0, $s0, 1	# i ++ 

sub $s1, $s0, $a2 	# j = i-gap
inner:
add $t0, $a2, $s1	# j + gap
sll $v0, $t0, 2		# j + gap index	
sll $v1, $s1, 2		# j index

lw $t0, array($v0)	# value of j+gap
lw $t1, array($v1) 	# value of j

slt $t2, $t0, $t1  	# do the values need to be swapped?
slt $t0, $zero, $s1 	# is j positive?
and $t1, $t2, $t0       # 1 if AB = 1
beq $t1, $zero, outer	
sub $s1, $s1, $a2	# j - gap
lw $a0, 4($sp)		# array at 0
jal swap
j inner
######swap#####################################
swap: 
	lw $t0, array($v0)	
	lw $t1, array($v1)
	sw $t0, array($v1)	# store value of j at array j+gap
	sw $t1, array($v0)	# store j+gap in j
	jr $ra
