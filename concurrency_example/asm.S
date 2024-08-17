
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
atomic_load_relaxed:
    // mov 
    ret


atomic_load_release:
    // mov
    ret

atomic_load_setcst:
    mov eax, 5
    ret

// Store
atomic_store_relaxed:
    // mov
    ret

atomic_store_release:
    // mov
    ret

atomic_store_setcst:
    // mov
    ret

// Exchange
atomic_echange_seqcst:
    ret