#ifndef MM_H
#define MM_H
#define PAGE_SIZE           4096

/* Valid on GCC-x86 */
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;

/* GDT Entry */
typedef struct gdt_entry {
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_middle;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
}           gdt_entry_t;

void        gdt_load(gdt_entry_t *); /* defined in pc.c */

uint32_t    gdt_entry_get_base(gdt_entry_t *entry);
void        gdt_entry_set_base(gdt_entry_t *, uint32_t);

/* Page Table Entry */
typedef uint32_t ptab_entry_t;

void        ptab_load(ptab_entry_t *); /* defined in pc.c */

void        ptab_entry_clear(ptab_entry_t *);
uint8_t     ptab_entry_get_pbit(ptab_entry_t *);
void        ptab_entry_set_pbit(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_rwbit(ptab_entry_t *);
void        ptab_entry_set_rwbit(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_usbit(ptab_entry_t *);
void        ptab_entry_set_usbit(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_dbit(ptab_entry_t *);
void        ptab_entry_set_dbit(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_abit(ptab_entry_t *);
void        ptab_entry_set_abit(ptab_entry_t *, uint8_t);
uint32_t    ptab_entry_get_pfaddr(ptab_entry_t *);
void        ptab_entry_set_pfaddr(ptab_entry_t *, uint32_t);
#endif
