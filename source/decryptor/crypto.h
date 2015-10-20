#pragma once

#include "common.h"

#define AES_BLOCK_SIZE 0x10

#define AES_CCM_DECRYPT_MODE (0 << 27)
#define AES_CCM_ENCRYPT_MODE (1 << 27)
#define AES_CTR_MODE         (2 << 27)
#define AES_CBC_DECRYPT_MODE (4 << 27)
#define AES_CBC_ENCRYPT_MODE (5 << 27)
#define AES_ECB_DECRYPT_MODE (6 << 27)
#define AES_ECB_ENCRYPT_MODE (7 << 27)

#define REG_AESCNT     ((volatile u32*)0x10009000)
#define REG_AESBLKCNT  ((volatile u32*)0x10009004)
#define REG_AESWRFIFO  ((volatile u32*)0x10009008)
#define REG_AESRDFIFO  ((volatile u32*)0x1000900C)
#define REG_AESKEYSEL  ((volatile u8 *)0x10009010)
#define REG_AESKEYCNT  ((volatile u8 *)0x10009011)
#define REG_AESCTR     ((volatile u32*)0x10009020)
#define REG_AESKEYFIFO ((volatile u32*)0x10009100)
#define REG_AESKEYXFIFO ((volatile u32*)0x10009104)
#define REG_AESKEYYFIFO ((volatile u32*)0x10009108)

#define AES_CNT_START         0x80000000
#define AES_CNT_INPUT_ORDER   0x02000000
#define AES_CNT_OUTPUT_ORDER  0x01000000
#define AES_CNT_INPUT_ENDIAN  0x00800000
#define AES_CNT_OUTPUT_ENDIAN 0x00400000
#define AES_CNT_FLUSH_READ    0x00000800
#define AES_CNT_FLUSH_WRITE   0x00000400

#define AES_CNT_CTRNAND_MODE (AES_CTR_MODE | AES_CNT_INPUT_ORDER | AES_CNT_OUTPUT_ORDER | AES_CNT_INPUT_ENDIAN | AES_CNT_OUTPUT_ENDIAN)
#define AES_CNT_TWLNAND_MODE AES_CTR_MODE
#define AES_CNT_TITLEKEY_MODE (AES_CBC_DECRYPT_MODE | AES_CNT_INPUT_ORDER | AES_CNT_OUTPUT_ORDER | AES_CNT_INPUT_ENDIAN | AES_CNT_OUTPUT_ENDIAN)


#define REG_SHACNT      ((volatile uint32_t*)0x1000A000)
#define REG_SHABLKCNT   ((volatile uint32_t*)0x1000A004)
#define REG_SHAHASH     ((volatile uint32_t*)0x1000A040)
#define REG_SHAINFIFO   ((volatile uint32_t*)0x1000A080)

#define SHA_CNT_STATE           0x00000003
#define SHA_CNT_OUTPUT_ENDIAN   0x00000008
#define SHA_CNT_MODE            0x00000030
#define SHA_CNT_ENABLE          0x00010000
#define SHA_CNT_ACTIVE          0x00020000

#define SHA_HASH_READY          0x00000000
#define SHA_NORMAL_ROUND        0x00000001
#define SHA_FINAL_ROUND         0x00000002

#define SHA256_MODE             0
#define SHA224_MODE             0x00000010
#define SHA1_MODE               0x00000020


void add_ctr(void* ctr, u32 carry);

void setup_aeskeyX(u8 keyslot, void* keyx);
void setup_aeskeyY(u8 keyslot, void* keyy);
void setup_aeskey(u8 keyslot, void* keyy);
void use_aeskey(u32 keyno);
void set_ctr(void* iv);
void aes_decrypt(void* inbuf, void* outbuf, void* iv, size_t size, u32 mode);
void aes_fifos(void* inbuf, void* outbuf, size_t blocks);
void set_aeswrfifo(u32 value);
u32 read_aesrdfifo(void);
u32 aes_getwritecount();
u32 aes_getreadcount();
u32 aescnt_checkwrite();
u32 aescnt_checkread();

void sha_init(u32 mode);
void sha_update(const void* src, u32 size);
void sha_get(void* res);
