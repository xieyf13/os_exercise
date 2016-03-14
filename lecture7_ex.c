#include "stdio.h"
#include "stdlib.h"

typedef unsigned int uint;

int main() {
    uint vad = 0;
    uint pad = 0;
    scanf("%x %x", &vad, &pad);
    uint pde_idx = vad >> 22;
    uint pde_ctx = ((pde_idx - 0x300 + 1) << 12) | 0x3;
    uint pte_idx = ((vad >> 12) & 0x3FF);
    uint pte_ctx = (pad & ~0x3FF) | 0x3;
    printf("va 0x%08x, pa 0x%08x, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x\n", \
        vad, pad, pde_idx, pde_ctx, pte_idx, pte_ctx);
}
