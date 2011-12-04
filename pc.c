#include "mm.h"
#include "pc.h"

void
gdt_load(gdt_ptr_t *ptr)
{
}

void
ptab_load(ptab_entry_t *entry)
{
    pc.cpu.cr[3] = (uint32_t)entry & ~(MM_PAGE_SIZE - 1);
}
