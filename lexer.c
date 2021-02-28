#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// Don't set this value over 16 or
// the avl tree will cut off bytes
#define MAX_WORD_SIZE 16

#define MIN_WORD_SIZE 6

#define BUF_SIZE 8192

/*
 * This lexer categorizes three types of bytes: special, space, and printable.
 * The switch statement below maps all bytes to a category, which you can
 * redefine.
 *
 * This lexer accepts words that are consecutive printable bytes ending with
 * a byte in the space category. A word needs to have more lowercase letters
 * than uppercase.
*/

int main(int argc, char* argv[])
{
    uint8_t buffer[BUF_SIZE];
    uint64_t size;
    uint64_t word_leng = 0;
    uint64_t upper_count = 0;
    uint64_t lower_count = 0;

    while ((size = read(0, buffer+word_leng, BUF_SIZE-word_leng)) > 0) {
        uint64_t buf_index = word_leng;
        for (uint64_t i = 0; i < size; i++) {
            switch (buffer[i]) {
                case 0x9:  goto space;      // \t
                case 0xa:  goto space;      // \n
                case 0x20: goto space;      // Space
                case 0x21: goto printable;  // !
                case 0x22: goto space;      // "
                case 0x23: goto printable;  // #
                case 0x24: goto printable;  // $
                case 0x25: goto printable;  // %
                case 0x26: goto printable;  // &
                case 0x27: goto space;      // '
                case 0x28: goto printable;  // (
                case 0x29: goto printable;  // )
                case 0x2a: goto printable;  // *
                case 0x2b: goto printable;  // +
                case 0x2c: goto printable;  // ,
                case 0x2d: goto printable;  // -
                case 0x2e: goto printable;  // .
                case 0x2f: goto space;      // /
                case 0x30: goto printable;  // 0
                case 0x31: goto printable;  // 1
                case 0x32: goto printable;  // 2
                case 0x33: goto printable;  // 3
                case 0x34: goto printable;  // 4
                case 0x35: goto printable;  // 5
                case 0x36: goto printable;  // 6
                case 0x37: goto printable;  // 7
                case 0x38: goto printable;  // 8
                case 0x39: goto printable;  // 9
                case 0x3a: goto printable;  // :
                case 0x3b: goto printable;  // ;
                case 0x3c: goto printable;  // <
                case 0x3d: goto printable;  // =
                case 0x3e: goto printable;  // >
                case 0x3f: goto printable;  // ?
                case 0x40: goto printable;  // @
                case 0x41: goto printable;  // A
                case 0x42: goto printable;  // B
                case 0x43: goto printable;  // C
                case 0x44: goto printable;  // D
                case 0x45: goto printable;  // E
                case 0x46: goto printable;  // F
                case 0x47: goto printable;  // G
                case 0x48: goto printable;  // H
                case 0x49: goto printable;  // I
                case 0x4a: goto printable;  // J
                case 0x4b: goto printable;  // K
                case 0x4c: goto printable;  // L
                case 0x4d: goto printable;  // M
                case 0x4e: goto printable;  // N
                case 0x4f: goto printable;  // O
                case 0x50: goto printable;  // P
                case 0x51: goto printable;  // Q
                case 0x52: goto printable;  // R
                case 0x53: goto printable;  // S
                case 0x54: goto printable;  // T
                case 0x55: goto printable;  // U
                case 0x56: goto printable;  // V
                case 0x57: goto printable;  // W
                case 0x58: goto printable;  // X
                case 0x59: goto printable;  // Y
                case 0x5a: goto printable;  // Z
                case 0x5b: goto printable;  // [
                case 0x5c: goto printable;  // '\'
                case 0x5d: goto printable;  // ]
                case 0x5e: goto printable;  // ^
                case 0x5f: goto printable;  // _
                case 0x60: goto printable;  // `
                case 0x61: goto printable;  // a
                case 0x62: goto printable;  // b
                case 0x63: goto printable;  // c
                case 0x64: goto printable;  // d
                case 0x65: goto printable;  // e
                case 0x66: goto printable;  // f
                case 0x67: goto printable;  // g
                case 0x68: goto printable;  // h
                case 0x69: goto printable;  // i
                case 0x6a: goto printable;  // j
                case 0x6b: goto printable;  // k
                case 0x6c: goto printable;  // l
                case 0x6d: goto printable;  // m
                case 0x6e: goto printable;  // n
                case 0x6f: goto printable;  // o
                case 0x70: goto printable;  // p
                case 0x71: goto printable;  // q
                case 0x72: goto printable;  // r
                case 0x73: goto printable;  // s
                case 0x74: goto printable;  // t
                case 0x75: goto printable;  // u
                case 0x76: goto printable;  // v
                case 0x77: goto printable;  // w
                case 0x78: goto printable;  // x
                case 0x79: goto printable;  // y
                case 0x7a: goto printable;  // z
                case 0x7b: goto printable;  // {
                case 0x7c: goto printable;  // |
                case 0x7d: goto printable;  // }
                case 0x7e: goto printable;  // ~
                default:   goto special;
            }

space:      {
                if (
                    word_leng >= MIN_WORD_SIZE &&
                    word_leng <= MAX_WORD_SIZE &&
                    upper_count < lower_count
                   )
                    buffer[buf_index++] = '\n';
                else
special:            buf_index -= word_leng;
                word_leng = 0;
                upper_count = 0;
                lower_count = 0;
                continue;
            }

printable:  {
                if (isupper(buffer[i]))
                    upper_count++;
                else if (islower(buffer[i]))
                    lower_count++;
                buffer[buf_index++] = buffer[i];
                word_leng++;
            }
        }

        if (word_leng > MAX_WORD_SIZE) {
            buf_index -= word_leng;
            word_leng = 0;
            upper_count = BUF_SIZE + 1;
            lower_count = 0;
        }

        uint64_t cutoff = buf_index - word_leng;
        uint64_t wrote = write(1, buffer, cutoff);

        if (wrote == -1)
            fprintf(stderr, "error write\n"), exit(1);
        
        memmove(buffer, buffer + cutoff, word_leng);
    }

    if (size == -1)
        fprintf(stderr, "read error\n"), exit(1);
}
