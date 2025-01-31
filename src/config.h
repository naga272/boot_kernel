#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#ifndef OS_TOTAL_INTERRUPTS
    #define OS_TOTAL_INTERRUPTS 512  // l'os ha 512 interrupts totali
#endif

#define OS_HEAP_SIZE_BYTES  104857600 // 100 MB
#define OS_HEAP_BLOCK_SIZE  4096
#define OS_HEAP_ADDRESS     0x01000000



typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int i32;
typedef int64_t i64;

#endif
