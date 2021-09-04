.data

.text
fib:
	addi $sp, $sp, -12	# 3 words stored on the stack (12 bytes) 
	sw $ra, 8($sp)		# register saved to 2nd word 
	sw $a0, 4($sp)		# N stored as as first word in the stack
	addi $a0, $zero, 20
	
	bne $a0, $zero, elif 	# if (n==0)
	addi $v0, $zero, 0 	# return 0
	j exit
elif:
	addi $t0, $zero, 1	# $t0 = 1
	bne  $a0, $t0, else 	# if (n==1)
	addi $v0, $zero, 1	# return 1
	j exit
else: 
	addi $a0, $a0, -1	# set a0 = a0-1 (n-1)
	jal fib 		# calls Fib recursively
r1:	sw $v0, 0($sp)		# save the response of fib to the stack.
	lw $a0, 4($sp)		# restore a0 'N' from the stack.
	addi $a0, $a0, -2	# set a0 = a0 - 2 (n-2) 
	jal fib			# calls Fib recursively with n-2 now in a0
r2: 	lw $t0, 0($sp) 		# Restore from stack.
	add $v0, $v0, $t0	# add recursive results.
	
	
exit:
	lw $ra, 8($sp)		# restore the return address
	lw $a0, 4($sp)		# restire the return address
	addi $sp, $sp, 12 	# completely restore the stack pointer
	jr $ra			# jump back
	
	