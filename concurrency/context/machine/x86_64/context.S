

.global SetupMachineContext
.global SwitchMachineContext

// https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86/

// SetupMachineContext(stack, trampoline, arg)

SetupMachineContext:
    // Arguments
    // 1) rdi  bottom of the stack
    // 2) rsi - trampoline 
    // 3) rdx - arg

    // Switch to stack
    mov r11, rsp  // tmp := rsp
    mov rsp, rdi  // rsp := rdi

    // Just to be safe
    sub rsp, 64

    // trampoline stack must be 16-bytes aligned
    and rsp, -16
    add rsp, 8

    // 7-th argument for trampoline
    mov [rsp + 8], rdx

    // Prepare for context Switch

    // 1) Return address for SwitchMachinecontext
    push rsi

    // 2) Calle-saved registers
    push 0 // r15
    push 0 // r14
    push 0 // r13
    push 0 // r12
    push 0 // rbx
    push 0 // rbp

    // Return value for SetupMachinecontext
    mov rax, rsp //atomic_load_relaxed

    // Restore callstack
    mov rsp, r11 // rsp := tmp

    ret


// SwitchMachineContext(from_rsp, to_rsp)
SwitchMachineContext:
    // SwitchMachinecontext frame created on top og the current stack
    // 1. Save current execution context to 'from'

    // 1.1 Save callee-saved registers on top of the current stack

    // https://stackoverflow.com/questions/18024672/what-registers-are-preserved-through-a-linux-x86-64-function-call
    // https://uclibc.org/docs/psABI-x86_64.pdf

    push r15
    push r14
    push r13
    push r12

    push rbx
    push rbp

    // Switch stacks

    // 1.2 Save current stack pointer to 'from' MachineContext
    mov [rdi], rsp # from_rsp := rsp

    // 2. Activate 'to' machine context

    // 2.1 Set stack pointer to target stack
    mov rsp, [rsi] # rsp := to_rsp

    // 2.2 Restore and pop registers saved on target stack

    pop rbp
    pop rbx

    pop r12
    pop r13
    pop r14
    pop r15

    // Pop current SwitchMachineContext frame from target stack

    ret

