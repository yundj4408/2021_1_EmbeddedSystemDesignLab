
main:     file format elf64-x86-64


Disassembly of section .init:

00000000000004f0 <_init>:
 4f0:	48 83 ec 08          	sub    $0x8,%rsp
 4f4:	48 8b 05 ed 0a 20 00 	mov    0x200aed(%rip),%rax        # 200fe8 <__gmon_start__>
 4fb:	48 85 c0             	test   %rax,%rax
 4fe:	74 02                	je     502 <_init+0x12>
 500:	ff d0                	callq  *%rax
 502:	48 83 c4 08          	add    $0x8,%rsp
 506:	c3                   	retq   

Disassembly of section .plt:

0000000000000510 <.plt>:
 510:	ff 35 aa 0a 20 00    	pushq  0x200aaa(%rip)        # 200fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
 516:	ff 25 ac 0a 20 00    	jmpq   *0x200aac(%rip)        # 200fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
 51c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000000520 <printf@plt>:
 520:	ff 25 aa 0a 20 00    	jmpq   *0x200aaa(%rip)        # 200fd0 <printf@GLIBC_2.2.5>
 526:	68 00 00 00 00       	pushq  $0x0
 52b:	e9 e0 ff ff ff       	jmpq   510 <.plt>

Disassembly of section .plt.got:

0000000000000530 <__cxa_finalize@plt>:
 530:	ff 25 c2 0a 20 00    	jmpq   *0x200ac2(%rip)        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 536:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000000540 <_start>:
 540:	31 ed                	xor    %ebp,%ebp
 542:	49 89 d1             	mov    %rdx,%r9
 545:	5e                   	pop    %rsi
 546:	48 89 e2             	mov    %rsp,%rdx
 549:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
 54d:	50                   	push   %rax
 54e:	54                   	push   %rsp
 54f:	4c 8d 05 ba 01 00 00 	lea    0x1ba(%rip),%r8        # 710 <__libc_csu_fini>
 556:	48 8d 0d 43 01 00 00 	lea    0x143(%rip),%rcx        # 6a0 <__libc_csu_init>
 55d:	48 8d 3d e6 00 00 00 	lea    0xe6(%rip),%rdi        # 64a <main>
 564:	ff 15 76 0a 20 00    	callq  *0x200a76(%rip)        # 200fe0 <__libc_start_main@GLIBC_2.2.5>
 56a:	f4                   	hlt    
 56b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000000570 <deregister_tm_clones>:
 570:	48 8d 3d 99 0a 20 00 	lea    0x200a99(%rip),%rdi        # 201010 <__TMC_END__>
 577:	55                   	push   %rbp
 578:	48 8d 05 91 0a 20 00 	lea    0x200a91(%rip),%rax        # 201010 <__TMC_END__>
 57f:	48 39 f8             	cmp    %rdi,%rax
 582:	48 89 e5             	mov    %rsp,%rbp
 585:	74 19                	je     5a0 <deregister_tm_clones+0x30>
 587:	48 8b 05 4a 0a 20 00 	mov    0x200a4a(%rip),%rax        # 200fd8 <_ITM_deregisterTMCloneTable>
 58e:	48 85 c0             	test   %rax,%rax
 591:	74 0d                	je     5a0 <deregister_tm_clones+0x30>
 593:	5d                   	pop    %rbp
 594:	ff e0                	jmpq   *%rax
 596:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 59d:	00 00 00 
 5a0:	5d                   	pop    %rbp
 5a1:	c3                   	retq   
 5a2:	0f 1f 40 00          	nopl   0x0(%rax)
 5a6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 5ad:	00 00 00 

00000000000005b0 <register_tm_clones>:
 5b0:	48 8d 3d 59 0a 20 00 	lea    0x200a59(%rip),%rdi        # 201010 <__TMC_END__>
 5b7:	48 8d 35 52 0a 20 00 	lea    0x200a52(%rip),%rsi        # 201010 <__TMC_END__>
 5be:	55                   	push   %rbp
 5bf:	48 29 fe             	sub    %rdi,%rsi
 5c2:	48 89 e5             	mov    %rsp,%rbp
 5c5:	48 c1 fe 03          	sar    $0x3,%rsi
 5c9:	48 89 f0             	mov    %rsi,%rax
 5cc:	48 c1 e8 3f          	shr    $0x3f,%rax
 5d0:	48 01 c6             	add    %rax,%rsi
 5d3:	48 d1 fe             	sar    %rsi
 5d6:	74 18                	je     5f0 <register_tm_clones+0x40>
 5d8:	48 8b 05 11 0a 20 00 	mov    0x200a11(%rip),%rax        # 200ff0 <_ITM_registerTMCloneTable>
 5df:	48 85 c0             	test   %rax,%rax
 5e2:	74 0c                	je     5f0 <register_tm_clones+0x40>
 5e4:	5d                   	pop    %rbp
 5e5:	ff e0                	jmpq   *%rax
 5e7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 5ee:	00 00 
 5f0:	5d                   	pop    %rbp
 5f1:	c3                   	retq   
 5f2:	0f 1f 40 00          	nopl   0x0(%rax)
 5f6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 5fd:	00 00 00 

0000000000000600 <__do_global_dtors_aux>:
 600:	80 3d 09 0a 20 00 00 	cmpb   $0x0,0x200a09(%rip)        # 201010 <__TMC_END__>
 607:	75 2f                	jne    638 <__do_global_dtors_aux+0x38>
 609:	48 83 3d e7 09 20 00 	cmpq   $0x0,0x2009e7(%rip)        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 610:	00 
 611:	55                   	push   %rbp
 612:	48 89 e5             	mov    %rsp,%rbp
 615:	74 0c                	je     623 <__do_global_dtors_aux+0x23>
 617:	48 8b 3d ea 09 20 00 	mov    0x2009ea(%rip),%rdi        # 201008 <__dso_handle>
 61e:	e8 0d ff ff ff       	callq  530 <__cxa_finalize@plt>
 623:	e8 48 ff ff ff       	callq  570 <deregister_tm_clones>
 628:	c6 05 e1 09 20 00 01 	movb   $0x1,0x2009e1(%rip)        # 201010 <__TMC_END__>
 62f:	5d                   	pop    %rbp
 630:	c3                   	retq   
 631:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 638:	f3 c3                	repz retq 
 63a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000000640 <frame_dummy>:
 640:	55                   	push   %rbp
 641:	48 89 e5             	mov    %rsp,%rbp
 644:	5d                   	pop    %rbp
 645:	e9 66 ff ff ff       	jmpq   5b0 <register_tm_clones>

000000000000064a <main>:
 64a:	55                   	push   %rbp
 64b:	48 89 e5             	mov    %rsp,%rbp
 64e:	48 83 ec 10          	sub    $0x10,%rsp
 652:	bf 02 00 00 00       	mov    $0x2,%edi
 657:	e8 20 00 00 00       	callq  67c <foo>
 65c:	89 45 fc             	mov    %eax,-0x4(%rbp)
 65f:	8b 45 fc             	mov    -0x4(%rbp),%eax
 662:	89 c6                	mov    %eax,%esi
 664:	48 8d 3d b9 00 00 00 	lea    0xb9(%rip),%rdi        # 724 <_IO_stdin_used+0x4>
 66b:	b8 00 00 00 00       	mov    $0x0,%eax
 670:	e8 ab fe ff ff       	callq  520 <printf@plt>
 675:	b8 00 00 00 00       	mov    $0x0,%eax
 67a:	c9                   	leaveq 
 67b:	c3                   	retq   

000000000000067c <foo>:
 67c:	55                   	push   %rbp
 67d:	48 89 e5             	mov    %rsp,%rbp
 680:	89 7d ec             	mov    %edi,-0x14(%rbp)
 683:	8b 45 ec             	mov    -0x14(%rbp),%eax
 686:	89 45 f8             	mov    %eax,-0x8(%rbp)
 689:	8b 45 f8             	mov    -0x8(%rbp),%eax
 68c:	83 c0 02             	add    $0x2,%eax
 68f:	89 45 fc             	mov    %eax,-0x4(%rbp)
 692:	8b 45 fc             	mov    -0x4(%rbp),%eax
 695:	5d                   	pop    %rbp
 696:	c3                   	retq   
 697:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 69e:	00 00 

00000000000006a0 <__libc_csu_init>:
 6a0:	41 57                	push   %r15
 6a2:	41 56                	push   %r14
 6a4:	49 89 d7             	mov    %rdx,%r15
 6a7:	41 55                	push   %r13
 6a9:	41 54                	push   %r12
 6ab:	4c 8d 25 06 07 20 00 	lea    0x200706(%rip),%r12        # 200db8 <__frame_dummy_init_array_entry>
 6b2:	55                   	push   %rbp
 6b3:	48 8d 2d 06 07 20 00 	lea    0x200706(%rip),%rbp        # 200dc0 <__init_array_end>
 6ba:	53                   	push   %rbx
 6bb:	41 89 fd             	mov    %edi,%r13d
 6be:	49 89 f6             	mov    %rsi,%r14
 6c1:	4c 29 e5             	sub    %r12,%rbp
 6c4:	48 83 ec 08          	sub    $0x8,%rsp
 6c8:	48 c1 fd 03          	sar    $0x3,%rbp
 6cc:	e8 1f fe ff ff       	callq  4f0 <_init>
 6d1:	48 85 ed             	test   %rbp,%rbp
 6d4:	74 20                	je     6f6 <__libc_csu_init+0x56>
 6d6:	31 db                	xor    %ebx,%ebx
 6d8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 6df:	00 
 6e0:	4c 89 fa             	mov    %r15,%rdx
 6e3:	4c 89 f6             	mov    %r14,%rsi
 6e6:	44 89 ef             	mov    %r13d,%edi
 6e9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
 6ed:	48 83 c3 01          	add    $0x1,%rbx
 6f1:	48 39 dd             	cmp    %rbx,%rbp
 6f4:	75 ea                	jne    6e0 <__libc_csu_init+0x40>
 6f6:	48 83 c4 08          	add    $0x8,%rsp
 6fa:	5b                   	pop    %rbx
 6fb:	5d                   	pop    %rbp
 6fc:	41 5c                	pop    %r12
 6fe:	41 5d                	pop    %r13
 700:	41 5e                	pop    %r14
 702:	41 5f                	pop    %r15
 704:	c3                   	retq   
 705:	90                   	nop
 706:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 70d:	00 00 00 

0000000000000710 <__libc_csu_fini>:
 710:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000000714 <_fini>:
 714:	48 83 ec 08          	sub    $0x8,%rsp
 718:	48 83 c4 08          	add    $0x8,%rsp
 71c:	c3                   	retq   
