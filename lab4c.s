	.text
main:
    li $5, 100              # Loop count
    la $1, floats           # Address of float_values

	l.d $f0, 0($1)          # kx
	l.d $f1, 4($1)          # X2
	l.d $f2, 8($1)          # X1
	l.d $f3, 12($1)         # ky
	l.d $f4, 16($1)         # Y2
	l.d $f5, 20($1)         # Y1

	li $f6, 0               # X0
	li $f7, 0               # Y0

loop:
	fmul $f6, $f0, $f2      # X0 = kx * X1
	fsub $f6, $f6, $f1      # X0 = X0 - X2

	fmul $f7, $f3, $f5      # Y0 = ky * Y1
	fsub $f7, $f7, $f4      # Y0 = Y0 - Y2

    add $f1, $f2, $zero     # X2 = X1
    add $f2, $f6, $zero     # X1 = X0

    add $f4, $f5, $zero     # Y2 = Y1
    add $f5, $f7, $zero     # Y1 = Y0

	beq $5, $0, end         # $5 == 0 ? goto end
    subi $5, $5, 1          # $5--;
    b loop                  # goto loop

end:
	li $2, 2                # load print_float procedure

    add $f12, $f6, $zero    # print X0
	syscall

    add $f12, $f7, $zero    # print Y0
	syscall

	li $2, 10               # exit
	syscall

	.data
floats: .float 1.65, -0.57, 0.0, 0.80, -0.92, 0.0
