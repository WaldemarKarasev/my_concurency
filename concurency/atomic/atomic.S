
// Load
.global atomic_load_relaxed
.global atomic_load_aquire
.global atomic_load_setcst

// Store
.global atomic_store_relaxed
.global atomic_store_aquire
.global atomic_store_setcst


// Exchange
.global atomic_echange_seqcst




// Load
atomic_load_relaxed:
    ; mov 
    rets

atomic_load_aquire:
    ; mov
    ret

atomic_load_setcst:
    ; mov
    mov %rax, [rcx]
    ret

// Store
atomic_store_relaxed:
    ; mov
    ret

atomic_store_aquire:
    ; mov
    ret

atomic_store_setcst:
    ; mov
    ret

// Exchange
atomic_echange_seqcst:
    ret