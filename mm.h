#ifndef MM_H
#define MM_H

/* Valid on GCC-x86 */
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;

/* MM Constants */
enum mm_k {
    MM_PAGE_SIZE    =   4096,
    MM_BITMAP_SIZE  =   MM_PAGE_SIZE,
    MM_MAX_PROC     =   8,
    MM_BIT_ERROR    =   2,       /* hehe */
    MM_SYS_ERROR    =   0,
    MM_SYS_SUCCESS  =   1
};

/* GDT */
typedef struct gdt_ptr {
    uint16_t    limit;
    uint32_t    base;
}           gdt_ptr_t;

typedef struct gdt_entry {
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_middle;
    uint8_t     access;
    uint8_t     limit_high_flags;
    uint8_t     base_high;
}           gdt_entry_t;

void        gdt_load(gdt_ptr_t *); /* defined in pc.c */
void        gdt_add(void);

void        gdt_entry_clear(gdt_entry_t *);
uint32_t    gdt_entry_get_limit(gdt_entry_t *);
void        gdt_entry_set_limit(gdt_entry_t *, uint32_t);
uint32_t    gdt_entry_get_base(gdt_entry_t *);
void        gdt_entry_set_base(gdt_entry_t *, uint32_t);
uint8_t     gdt_entry_get_bit_p(gdt_entry_t *);
void        gdt_entry_set_bit_p(gdt_entry_t *, uint8_t);
uint8_t     gdt_entry_get_priv(gdt_entry_t *);
void        gdt_entry_set_priv(gdt_entry_t *, uint8_t);
uint8_t     gdt_entry_get_bit_x(gdt_entry_t *);
void        gdt_entry_set_bit_x(gdt_entry_t *, uint8_t);
uint8_t     gdt_entry_get_bit_dc(gdt_entry_t *);
void        gdt_entry_set_bit_dc(gdt_entry_t *, uint8_t);
uint8_t     gdt_entry_get_bit_rw(gdt_entry_t *);
void        gdt_entry_set_bit_rw(gdt_entry_t *, uint8_t);
uint8_t     gdt_entry_get_bit_a(gdt_entry_t *);
void        gdt_entry_set_bit_a(gdt_entry_t *, uint8_t);
uint8_t     gdt_entry_get_bit_g(gdt_entry_t *);
void        gdt_entry_set_bit_g(gdt_entry_t *, uint8_t);
uint8_t     gdt_entry_get_bit_s(gdt_entry_t *);
void        gdt_entry_set_bit_s(gdt_entry_t *, uint8_t);

/* Page Table Entry */
typedef uint32_t ptab_entry_t;

void        ptab_load(ptab_entry_t *); /* defined in pc.c */

void        ptab_entry_clear(ptab_entry_t *);
uint32_t    ptab_entry_get_pfa(ptab_entry_t *);
void        ptab_entry_set_pfa(ptab_entry_t *, uint32_t);
uint8_t     ptab_entry_get_bit_a(ptab_entry_t *);
void        ptab_entry_set_bit_a(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_bit_d(ptab_entry_t *);
void        ptab_entry_set_bit_d(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_bit_us(ptab_entry_t *);
void        ptab_entry_set_bit_us(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_bit_rw(ptab_entry_t *);
void        ptab_entry_set_bit_rw(ptab_entry_t *, uint8_t);
uint8_t     ptab_entry_get_bit_p(ptab_entry_t *);
void        ptab_entry_set_bit_p(ptab_entry_t *, uint8_t);

/* Free page frames */
typedef struct bitmap {
    char byte[MM_PAGE_SIZE];
}           bitmap_t;

void        bitmap_clear(bitmap_t *);
uint8_t     bitmap_get_bit(bitmap_t *, int, int);
void        bitmap_set_bit(bitmap_t *, int, int, uint8_t);
char        bitmap_request_pfa(bitmap_t *, uint32_t *);

char        vm_page_is_assigned(uint16_t, uint16_t);
void        vm_page_assign(uint16_t, uint16_t, uint32_t);
void        vm_page_unassign(uint16_t, uint16_t);

/* Syscalls */
int         vm_request(uint32_t, int);
int         vm_return(uint32_t);

/* MM */
typedef struct mm {
    gdt_ptr_t       *gdt;
    ptab_entry_t    *pdir;         /* pdir[MM_MAX_PROC] */
    bitmap_t        *pfbm;         /* Page frame bitmap */
}           mm_t;

mm_t mm;    /* =) */

#endif
