#ifndef __AES_H__
#define __AES_H__

typedef uint32_t aeskey_t[4];
typedef uint32_t keyexp_t[44];

// 置換表
extern uint8_t sbox[255];
// ラウンド定数
extern uint8_t rcon[255];

// Perform the AES key core operation on a word.(word:AESの暗号化単位　1ワード= 4byte = 32bit)
// (Assumes the standard byte order.)
// key coreはkey expansionに対応？？？たぶん，与えられた仮の鍵からラウンドキーを作成して戻している
static inline uint32_t key_core(uint32_t k, int i) {
    uint32_t t = 0;
    for (int j=0; j<4; j++)
        t = set_byte(t, (j-1)%4, sbox[get_byte(k,j)]);
    return set_byte(t, 0, get_byte(t,0) ^ rcon[i]);
}

// Run each byte of a word through the sbox separately for word 4 of 256-bit AES.
static inline uint32_t sbox_bytes(uint32_t k) {
    uint32_t r = 0;
    for (int j=0; j<4; j++)
        r = set_byte(r,j,sbox[get_byte(k,j)]);
    return r;
}

#endif//__AES_H__
