
// Load
.global atomic_load_relaxed
.global atomic_load_release
.global atomic_load_setcst

// Store
.global atomic_store_relaxed
.global atomic_store_release
.global atomic_store_setcst


// Exchange
.global atomic_echange_seqcst


// Load
// args: rdi = &cell (cell address)
// return: rax = *(&cell) (value inside the cell)
atomic_load_relaxed: 
    mov rax, [rdi]
    ret


atomic_load_release:
    mov rax, [rdi]
    ret

atomic_load_setcst:
    mov rax, [rdi]
    ret

// Store
// args: rdi = &cell, rsi = value (for storing into the cell)
// return: void
atomic_store_relaxed:
    xchg [rdi], rsi
    ret

atomic_store_release:
    xchg [rdi], rsi
    ret

atomic_store_setcst:
    xchg [rdi], rsi
    ret

// Exchange
// args: rdi = &cell, rsi = new_value
atomic_echange_seqcst:
    mov rax, rsi    // moving to rax value from cell for return value
    xchg [rdi], rax // exchanging: storing new_value in cell
    ret