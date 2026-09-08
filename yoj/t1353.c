#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAXL 10000
#define MAXN 20

typedef uint8_t u8;
typedef uint32_t u32;

u8 str[MAXL];
u32 str_tp = 0, h[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};
u32 W[MAXN][64];
u32 a, b, c, d, e, f, g, hh;
const u32 K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
    0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
    0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
    0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
    0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
    0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
    0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
    0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
    0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void message_padding() 
{
    size_t l = strlen((const char *)str) * 8;
    str[str_tp++] = 0x80;
    while ((str_tp * 8) % 512 != 448) 
        str[str_tp++] = 0x00;
    u8 *p = (u8 *)&l;
    for (int i = 0; i < 8; ++i)
        str[str_tp++] = p[7 - i];  // 大端序写入8字节
    str[str_tp] = '\0';
}

static inline u32 shr(u32 x, int n) { return (x >> n); }
static inline u32 rotr(u32 x, int n) { return (x >> n) | (x << (32 - n));}
static inline u32 sigma0(u32 x) { return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3); }
static inline u32 sigma1(u32 x) { return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10); }
static inline u32 Sigma0(u32 x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
static inline u32 Sigma1(u32 x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
static inline u32 ch(u32 x, u32 y, u32 z) { return (x & y) ^ ((~x) & z); }
static inline u32 maj(u32 x, u32 y, u32 z) { return (x & y) ^ (x & z) ^ (y & z); }

void block_and_sched() 
{
    for (int i = 0; i < (str_tp * 8) / 512; ++i) {
        for (int j = 0; j < 16; ++j) {
            // 手动转小端序存储,不能直接(u32 *)
            int idx = i * 64 + j * 4;
            W[i][j] = (str[idx] << 24) | (str[idx+1] << 16) | (str[idx+2] << 8) | str[idx+3];
        }
        for (int j = 16; j < 64; ++j) {
            W[i][j] = sigma1(W[i][j-2]) + W[i][j-7] + sigma0(W[i][j-15]) + W[i][j-16];
        }
    }
}

void main_compress() 
{
    u32 t1, t2;
    for (int i = 0; i < (str_tp * 8) / 512; ++i) {
        a = h[0]; b = h[1]; c = h[2]; d = h[3];
        e = h[4]; f = h[5]; g = h[6]; hh = h[7];
        for (int j = 0; j < 64; ++j) {
            t1 = hh + Sigma1(e) + ch(e, f, g) + K[j] + W[i][j];
            t2 = Sigma0(a) + maj(a, b, c);
            hh = g; g = f; f = e;
            e = d + t1; d = c;
            c = b; b = a; a = t1 + t2;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
    }
}

int main() 
{
    scanf("%s", (char *)str);
    str_tp = strlen((const char *)str);
    message_padding();
    //for (int i = 0; i < str_tp; ++i) 
        //printf("%hhx ", str[i]);
    //printf("\n%d", str_tp);
    block_and_sched();
    main_compress();
    for (int i = 0; i < 8; ++i) 
        printf("%08x", h[i]); // %08x,长度为8,不足以0填充
    return 0;
}