#include "mm.h"

/* Could define them as macros... */

/* GDT */
void
gdt_entry_clear(gdt_entry_t *entry)
{
    entry->limit_low = 0;
    entry->base_low = 0;
    entry->base_middle = 0;
    entry->access = 0;
    entry->limit_high_flags = 0;
    entry->base_high = 0;
}

uint32_t
gdt_entry_get_limit(gdt_entry_t *entry)
{
    return ((entry->limit_high_flags & 0xf) << 16)
                | entry->limit_low;
}

void
gdt_entry_set_limit(gdt_entry_t *entry, uint32_t limit)
{
    entry->limit_low = (uint16_t)(limit & 0xffff);
    entry->limit_high_flags = (entry->limit_high_flags & 0xf)
                                | (uint8_t)((limit & 0xf0000) >> 16);
}


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
    entry->base_low = (uint16_t)(base & 0xffff);
    entry->base_middle = (uint8_t)((base & 0xff0000) >> 16);
    entry->base_high = (uint8_t)((base & 0xff000000) >> 24);
}

uint8_t
gdt_entry_get_bit_p(gdt_entry_t *entry)
{
    return (entry->access & 0x80) >> 7;
}

void
gdt_entry_set_bit_p(gdt_entry_t *entry, uint8_t bit_p)
{
    if(bit_p)
        entry->access |= 0x80;
    else
        entry->access &= 0x7f;
}


uint8_t
gdt_entry_get_bit_priv(gdt_entry_t *entry)
{
    return (entry->access & 0x40) >> 6;
}

void
gdt_entry_set_bit_priv(gdt_entry_t *entry, uint8_t bit_priv)
{
    if(bit_priv)
        entry->access |= 0x40;
    else
        entry->access &= 0xbf;
}


uint8_t
gdt_entry_get_bit_x(gdt_entry_t *entry)
{
    return (entry->access & 0x20) >> 5;
}

void
gdt_entry_set_bit_x(gdt_entry_t *entry, uint8_t bit_x)
{
    if(bit_x)
        entry->access |= 0x20;
    else
        entry->access &= 0xdf;
}


uint8_t
gdt_entry_get_bit_dc(gdt_entry_t *entry)
{
    return (entry->access & 0x10) >> 4;
}

void
gdt_entry_set_bit_dc(gdt_entry_t *entry, uint8_t bit_dc)
{
    if(bit_dc)
        entry->access |= 0x10;
    else
        entry->access &= 0xef;
}


uint8_t
gdt_entry_get_bit_rw(gdt_entry_t *entry)
{
    return (entry->access & 8) >> 3;
}

void
gdt_entry_set_bit_rw(gdt_entry_t *entry, uint8_t bit_rw)
{
    if(bit_rw)
        entry->access |= 8;
    else
        entry->access &= 0xf7;
}


uint8_t
gdt_entry_get_bit_a(gdt_entry_t *entry)
{
    return (entry->access & 4) >> 2;
}

void
gdt_entry_set_bit_a(gdt_entry_t *entry, uint8_t bit_a)
{
    if(bit_a)
        entry->access |= 4;
    else
        entry->access &= 0xfb;
}


uint8_t
gdt_entry_get_bit_g(gdt_entry_t *entry)
{
    return (entry->access & 2) >> 1;
}

void
gdt_entry_set_bit_g(gdt_entry_t *entry, uint8_t bit_g)
{
    if(bit_g)
        entry->access |= 2;
    else
        entry->access &= 0xfd;
}


uint8_t
gdt_entry_get_bit_s(gdt_entry_t *entry)
{
    return entry->access & 1;
}

void
gdt_entry_set_bit_s(gdt_entry_t *entry, uint8_t bit_s)
{
    if(bit_s)
        entry->access |= 1;
    else
        entry->access &= 0xfe;
}



/* Page tables */
void
ptab_entry_clear(ptab_entry_t *entry)
{
    *entry = 0;
}


uint8_t
ptab_entry_get_bit_p(ptab_entry_t *entry)
{
    return *entry & 1;
}

void
ptab_entry_set_bit_p(ptab_entry_t *entry, uint8_t bit_p)
{
    if(bit_p)
        *entry |= 1;
    else
        *entry &= 0xfe; 
}


uint8_t
ptab_entry_get_bit_rw(ptab_entry_t *entry)
{
    return (*entry & 2) >> 1;
}

void
ptab_entry_set_bit_rw(ptab_entry_t *entry, uint8_t bit_rw)
{
    if(bit_rw)
        *entry |= 2;
    else
        *entry &= 0xfd;
}


uint8_t
ptab_entry_get_bit_us(ptab_entry_t *entry)
{
    return (*entry & 4) >> 2;
}

void
ptab_entry_set_bit_us(ptab_entry_t *entry, uint8_t bit_us)
{
    if(bit_us)
        *entry |= 4;
    else
        *entry &= 0xfb;
}


uint8_t
ptab_entry_get_bit_d(ptab_entry_t *entry)
{
    return (*entry & 0x20) >> 5;
}

void
ptab_entry_set_bit_d(ptab_entry_t *entry, uint8_t bit_d)
{
    if(bit_d)
        *entry |= 0x20;
    else
        *entry &= 0xef;
}


uint8_t
ptab_entry_get_bit_a(ptab_entry_t *entry)
{
    return (*entry & 0x40) >> 6;
}

void
ptab_entry_set_bit_a(ptab_entry_t *entry, uint8_t bit_a)
{
    if(bit_a)
        *entry |= 0x40;
    else
        *entry &= 0xdf;
}


uint32_t
ptab_entry_get_pfa(ptab_entry_t *entry)
{
    return (*entry & 0xfffff000);
}

void
ptab_entry_set_pfa(ptab_entry_t *entry, uint32_t pfa)
{
    pfa &= 0xfffff000; /* 20-bit */
    *entry = (*entry & 0xfff) | pfa;
}

uint16_t
vaddr_get_pdir(uint32_t vaddr)
{
   return (vaddr & 0xffc00000) >> 22;
}

uint32_t
vaddr_set_pdir(uint32_t vaddr, uint16_t pdir)
{
    return (vaddr & 0x3fffff) | ((pdir & 0x3ff) << 22);
}

uint16_t
vaddr_get_ptab(uint32_t vaddr)
{
   return (vaddr & 0x3ff000) >> 12;
}

uint32_t
vaddr_set_ptab(uint32_t vaddr, uint16_t ptab)
{
    return (vaddr & 0xffc00fff) | ((ptab & 0x3ff) << 12);
}



/* Bitmap */
void
bitmap_clear(bitmap_t *bitmap)
{
    int i;
    for(i = 0; i < MM_BITMAP_SIZE; i++)
        bitmap->byte[i] = 0;
}

uint8_t
bitmap_get_bit(bitmap_t *bitmap, int byte, int bit)
{
    if(MM_BITMAP_SIZE > byte) {
        return (bitmap->byte[byte] >> bit) & 1;
    }
    return MM_BIT_ERROR;
}

void
bitmap_set_bit(bitmap_t *bitmap, int byte, int bit, uint8_t value)
{
    if(MM_BITMAP_SIZE > byte) {
        bitmap->byte[byte] = (value & 1) << bit;
    }
}

char
bitmap_request_pfa(bitmap_t *bitmap, uint32_t *pfa)
{
    int byte, bit;
    for(byte = 0; byte < MM_BITMAP_SIZE; byte++) {
        for(bit = 0; bit < 8; bit++) {
            if(!bitmap_get_bit(bitmap, byte, bit)) {
                bitmap_set_bit(bitmap, byte, bit, 1);
                *pfa = (8 * byte + bit) * MM_PAGE_SIZE;
                return 1;
            }
        }
    }
    return 0;
}

void
bitmap_return_pfa(bitmap_t *bitmap, uint32_t pfa)
{
    int pfa_i, byte, bit;
    pfa_i = pfa / MM_PAGE_SIZE;
    byte = pfa_i / 8;
    bit = pfa_i % 8;
    bitmap_set_bit(bitmap, byte, bit, 0);
}



char
vm_page_is_assigned(uint16_t pdiri, uint16_t ptabi)
{
    ptab_entry_t *ptab;
    ptab = (ptab_entry_t *)ptab_entry_get_pfa(&mm.pdir[pdiri]);
    return ptab_entry_get_bit_p(&ptab[ptabi]);
}

void
vm_page_assign(uint16_t pdiri, uint16_t ptabi, uint32_t pfa)
{
    ptab_entry_t *ptab;
    ptab = (ptab_entry_t *)ptab_entry_get_pfa(&mm.pdir[pdiri]);
    ptab_entry_set_pfa(&ptab[ptabi], pfa);
    ptab_entry_set_bit_us(&ptab[ptabi], 1);
    ptab_entry_set_bit_rw(&ptab[ptabi], 1);
    ptab_entry_set_bit_p(&ptab[ptabi], 1);
}

void
vm_page_unassign(uint16_t pdiri, uint16_t ptabi)
{
    ptab_entry_t *ptab;
    ptab = (ptab_entry_t *)ptab_entry_get_pfa(&mm.pdir[pdiri]);
    ptab_entry_clear(&ptab[ptabi]);
}

uint32_t
vm_page_get_pfa(uint16_t pdiri, uint16_t ptabi)
{
    ptab_entry_t *ptab;
    ptab = (ptab_entry_t *)ptab_entry_get_pfa(&mm.pdir[pdiri]);
    return ptab_entry_get_pfa(&ptab[ptabi]);
}



/* Syscalls */
int
vm_request(uint32_t vaddr, int length)
{
    char success;
    int i;
    uint16_t pdiri, ptabi;
    uint32_t vaddri, pfa;
    for(i = 0; i < length; i++) {
        vaddri = vaddr + i * MM_PAGE_SIZE;
        pdiri = vaddr_get_pdir(vaddri); 
        ptabi = vaddr_get_ptab(vaddri); 
        success = 0;
        if(!vm_page_is_assigned(pdiri, ptabi)) {
            if(bitmap_request_pfa(mm.pfbm, &pfa)) {
                vm_page_assign(pdiri, ptabi, pfa);
                success = 1;
            }
        }

        /* roll-back */
        if(!success) {
            for(i--; 0 <= i; i--) {
                vaddri = vaddr + i * MM_PAGE_SIZE;
                pdiri = vaddr_get_pdir(vaddri); 
                ptabi = vaddr_get_ptab(vaddri); 
                pfa = vm_page_get_pfa(pdiri, ptabi);
                bitmap_return_pfa(mm.pfbm, pfa);
                vm_page_unassign(pdiri, ptabi);
            }
            return MM_SYS_ERROR;
        }
    }
    return (i == length) ? MM_SYS_SUCCESS : MM_SYS_ERROR;
}

int
vm_return(uint32_t vaddr)
{
    uint16_t pdiri, ptabi;
    uint32_t pfa;
    pdiri = vaddr_get_pdir(vaddr); 
    ptabi = vaddr_get_ptab(vaddr); 
    if(vm_page_is_assigned(pdiri, ptabi)) {
        pfa = vm_page_get_pfa(pdiri, ptabi);
        bitmap_return_pfa(mm.pfbm, pfa);
        vm_page_unassign(pdiri, ptabi);
        return MM_SYS_SUCCESS;
    }
    return MM_SYS_ERROR;
}
