
main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  13:	00 00 
  15:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  19:	31 c0                	xor    %eax,%eax
  1b:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 22 <main+0x22>
  22:	b8 00 00 00 00       	mov    $0x0,%eax
  27:	e8 00 00 00 00       	callq  2c <main+0x2c>
  2c:	48 8d 45 f4          	lea    -0xc(%rbp),%rax
  30:	48 89 c6             	mov    %rax,%rsi
  33:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 3a <main+0x3a>
  3a:	b8 00 00 00 00       	mov    $0x0,%eax
  3f:	e8 00 00 00 00       	callq  44 <main+0x44>
  44:	8b 45 f4             	mov    -0xc(%rbp),%eax
  47:	83 e0 01             	and    $0x1,%eax
  4a:	85 c0                	test   %eax,%eax
  4c:	75 13                	jne    61 <main+0x61>
  4e:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 55 <main+0x55>
  55:	e8 00 00 00 00       	callq  5a <main+0x5a>
  5a:	b8 00 00 00 00       	mov    $0x0,%eax
  5f:	eb 11                	jmp    72 <main+0x72>
  61:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 68 <main+0x68>
  68:	e8 00 00 00 00       	callq  6d <main+0x6d>
  6d:	b8 01 00 00 00       	mov    $0x1,%eax
  72:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  76:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
  7d:	00 00 
  7f:	74 05                	je     86 <main+0x86>
  81:	e8 00 00 00 00       	callq  86 <main+0x86>
  86:	c9                   	leaveq 
  87:	c3                   	retq   

Disassembly of section .rodata:

0000000000000000 <.rodata>:
   0:	d0 92 d0 b2 d0 b5    	rclb   -0x4a2f4d30(%rdx)
   6:	d0 b4 d0 b8 d1 82 d0 	shlb   -0x2f7d2e48(%rax,%rdx,8)
   d:	b5 20                	mov    $0x20,%ch
   f:	d1 87 d0 b8 d1 81    	roll   -0x7e2e4730(%rdi)
  15:	d0 bb d0 be 3a 20    	sarb   0x203abed0(%rbx)
  1b:	00 25 64 00 d0 a7    	add    %ah,-0x582fff9c(%rip)        # ffffffffa7d00085 <main+0xffffffffa7d00085>
  21:	d0 b8 d1 81 d0 bb    	sarb   -0x442f7e2f(%rax)
  27:	d0 be 20 d1 87 d1    	sarb   -0x2e782ee0(%rsi)
  2d:	91                   	xchg   %eax,%ecx
  2e:	d1 82 d0 bd d0 be    	roll   -0x412f4230(%rdx)
  34:	d0 b5 2e 00 d0 a7    	shlb   -0x582fffd2(%rbp)
  3a:	d0 b8 d1 81 d0 bb    	sarb   -0x442f7e2f(%rax)
  40:	d0 be 20 d0 bd d0    	sarb   -0x2f422fe0(%rsi)
  46:	b5 d1                	mov    $0xd1,%ch
  48:	87 d1                	xchg   %edx,%ecx
  4a:	91                   	xchg   %eax,%ecx
  4b:	d1 82 d0 bd d0 be    	roll   -0x412f4230(%rdx)
  51:	d0                   	.byte 0xd0
  52:	b5 2e                	mov    $0x2e,%ch
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%rdi)
   3:	43 3a 20             	rex.XB cmp (%r8),%spl
   6:	28 55 62             	sub    %dl,0x62(%rbp)
   9:	75 6e                	jne    79 <main+0x79>
   b:	74 75                	je     82 <main+0x82>
   d:	20 39                	and    %bh,(%rcx)
   f:	2e 34 2e             	cs xor $0x2e,%al
  12:	30 2d 31 75 62 75    	xor    %ch,0x75627531(%rip)        # 75627549 <main+0x75627549>
  18:	6e                   	outsb  %ds:(%rsi),(%dx)
  19:	74 75                	je     90 <main+0x90>
  1b:	31 7e 32             	xor    %edi,0x32(%rsi)
  1e:	30 2e                	xor    %ch,(%rsi)
  20:	30 34 29             	xor    %dh,(%rcx,%rbp,1)
  23:	20 39                	and    %bh,(%rcx)
  25:	2e 34 2e             	cs xor $0x2e,%al
  28:	30 00                	xor    %al,(%rax)

Disassembly of section .note.gnu.property:

0000000000000000 <.note.gnu.property>:
   0:	04 00                	add    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	10 00                	adc    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	05 00 00 00 47       	add    $0x47000000,%eax
   d:	4e 55                	rex.WRX push %rbp
   f:	00 02                	add    %al,(%rdx)
  11:	00 00                	add    %al,(%rax)
  13:	c0 04 00 00          	rolb   $0x0,(%rax,%rax,1)
  17:	00 03                	add    %al,(%rbx)
  19:	00 00                	add    %al,(%rax)
  1b:	00 00                	add    %al,(%rax)
  1d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .eh_frame:

0000000000000000 <.eh_frame>:
   0:	14 00                	adc    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	00 00                	add    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	01 7a 52             	add    %edi,0x52(%rdx)
   b:	00 01                	add    %al,(%rcx)
   d:	78 10                	js     1f <.eh_frame+0x1f>
   f:	01 1b                	add    %ebx,(%rbx)
  11:	0c 07                	or     $0x7,%al
  13:	08 90 01 00 00 1c    	or     %dl,0x1c000001(%rax)
  19:	00 00                	add    %al,(%rax)
  1b:	00 1c 00             	add    %bl,(%rax,%rax,1)
  1e:	00 00                	add    %al,(%rax)
  20:	00 00                	add    %al,(%rax)
  22:	00 00                	add    %al,(%rax)
  24:	88 00                	mov    %al,(%rax)
  26:	00 00                	add    %al,(%rax)
  28:	00 45 0e             	add    %al,0xe(%rbp)
  2b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  31:	02 7f 0c             	add    0xc(%rdi),%bh
  34:	07                   	(bad)  
  35:	08 00                	or     %al,(%rax)
	...
