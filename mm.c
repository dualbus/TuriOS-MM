#include "mm.h"

/* Could define them as macros... */

/* GDT Stuff */
uint32_t
gdt_entry_get_base(gdt_entry_t *entry)
{
    return (entry->base_high << 24)
                | (entry->base_middle << 16)
                | entry->base_low;
}

void
gdt_entry_set_base(gdt_entry_t *entry, uint32_t base)
{
    entry->base_low |= (uint16_t)(base & 0xffff);
    entry->base_middle |= (uint8_t)(base & 0xff0000) >> 16;
    entry->base_high |= (uint8_t)(base & 0xff000000) >> 24;
}



/* Page Table Stuff */
void
ptab_entry_clear(ptab_entry_t *entry)
{
    *entry = 0;
}


uint8_t
ptab_entry_get_pbit(ptab_entry_t *entry)
{
    return (*entry & 1) >> 0;
}

void
ptab_entry_set_pbit(ptab_entry_t *entry, uint8_t pbit)
{
    pbit &= 1;
    *entry |= pbit << 0;
}


uint8_t
ptab_entry_get_rwbit(ptab_entry_t *entry)
{
    return (*entry & 2) >> 1;
}

void
ptab_entry_set_rwbit(ptab_entry_t *entry, uint8_t rwbit)
{
    rwbit &= 1;
    *entry |= rwbit << 1;
}


uint8_t
ptab_entry_get_usbit(ptab_entry_t *entry)
{
    return (*entry & 4) >> 2;
}

void
ptab_entry_set_usbit(ptab_entry_t *entry, uint8_t usbit)
{
    usbit &= 1;
    *entry |= usbit << 2;
}


uint8_t
ptab_entry_get_dbit(ptab_entry_t *entry)
{
    return (*entry & 0x20) >> 5;
}

void
ptab_entry_set_dbit(ptab_entry_t *entry, uint8_t dbit)
{
    dbit &= 1;
    *entry |= dbit << 5;
}


uint8_t
ptab_entry_get_abit(ptab_entry_t *entry)
{
    return (*entry & 0x40) >> 6;
}

void
ptab_entry_set_abit(ptab_entry_t *entry, uint8_t abit)
{
    abit &= 1;
    *entry |= abit << 6;
}


uint32_t
ptab_entry_get_pfaddr(ptab_entry_t *entry)
{
    return (*entry & 0xfffff000) >> 12;
}

void
ptab_entry_set_pfaddr(ptab_entry_t *entry, uint32_t pfaddr)
{
    pfaddr &= 0x100000; /* 20-bit */
    *entry |= pfaddr << 12;
}
