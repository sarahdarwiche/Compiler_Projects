.data
printstr: .asciz "%d\n"
.text 
  .globl Main_main
Count_count:
  # Prologue
  push %ebp
  mov %esp, %ebp
  sub $4, %esp
  push %ebx
  push %edi
  push %esi
# For
# Assignment
  push $1
  pop -4(%ebp)
label0:
  push -4(%ebp)
  push $10
  # Less Than or Equal
pop %eax
pop %ebx
cmp %eax, %ebx
jle label2
  push $0
jmp label3
label2: push $1
label3:
pop %eax
mov $0, %ebx
cmp %eax, %ebx 
je label1
  push -4(%ebp)
# Print
push $printstr
call printf
# Assignment
  push -4(%ebp)
  push $1
  # Plus
  pop %edx
  pop %eax
  add %edx, %eax
  push %eax
  pop -4(%ebp)
jmp label0
label1:
  # Epilogue
  pop %eax
  pop %esi
  pop %edi
  pop %ebx
  mov %ebp, %esp
  pop %ebp
  ret
Main_main:
  # Prologue
  push %ebp
  mov %esp, %ebp
  sub $4, %esp
  push %ebx
  push %edi
  push %esi
# Assignment
  push $4
  call malloc
  add $4, %esp
  push %eax
  pop -4(%ebp)
  push %ecx
  push %edx
  push 8(%ebp)
  push 4(%ebp)
  add $4, %esp
  pop %edx
  pop %ecx
  push %eax
  push $0
  # Epilogue
  pop %eax
  pop %esi
  pop %edi
  pop %ebx
  mov %ebp, %esp
  pop %ebp
  ret
