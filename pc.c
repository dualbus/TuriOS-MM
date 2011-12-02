#include "mm.h"
#include "pc.h"

void
gdt_load(gdt_entry_t *entry)
{
}

void
ptab_load(ptab_entry_t *entry)
{
    pc.cpu.cr[3] = ptab_entry_get_pfaddr(entry);
}
