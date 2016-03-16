#include "stdio.h"
#include "stdlib.h"
#include "page2.h"

#define PTD(x) ((x >> 10) & 0x1F)
#define PTX(x) ((x >> 5) & 0x1F)
#define OFFSET(x) (x & 0x1F)
#define isValid(x) (x >> 7)

int PDBR;

void get_paddr(unsigned int vaddr) {
    unsigned char pde = memory[PDBR + PTD(vaddr)];
    printf("  --> pde index: 0x%x  pde contents:(valid %d, pfn 0x%x)\n", \
        PTD(vaddr), isValid(pde), (pde & 0x7F));
    if (!isValid(pde)) {
        printf("   --> Fault (page directory entry not valid)\n");
        return ;
    }
    unsigned char pte = memory[(((unsigned int)(pde & 0x7F)) << 5) + PTX(vaddr)];
    printf("   --> pte index:0x%x  pte contents:(valid %d, pfn 0x%x)\n", \
        PTX(vaddr), isValid(pte), (pte & 0x7F));
    unsigned int res = (((unsigned)(pte & 0x7F)) << 5) + OFFSET(vaddr);
    if (!isValid(pte)) {
        if ((pte & 0x7F) == 0x7F) {
            printf("   --> Fault (the page does not exist)\n");
            return ;
        } else {
            printf("     ---> the value of addr in disk sector 0x%x\n", (pte & 0x7F));
            printf("          and offset is 0x%x --> Value: 0x%x\n", OFFSET(vaddr), disk[res]);
            return ;
        }
    }
    printf("      --> Translates to Physical Address 0x%x --> Value: 0x%x\n", res, memory[res]);
    return ;
}

int main() {
    PDBR = 0xd80;
    printf("please input your virtual address:\n>");
    int input;
    scanf("%x", &input);
    printf("Virtual Address %x:\n", input);
    get_paddr(input & 0x7FFF);
}
