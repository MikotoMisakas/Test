/* Data structure for MD5 (Message-Digest) computation */
#include<windows.h>
#include <stdio.h>

typedef struct {
	ULONG i[2];                          /* number of _bits_ handled mod 2^64 */
	ULONG buf[4];                                           /* scratch buffer */
	unsigned char in[64];                                     /* input buffer */
	unsigned char digest[16];            /* actual digest after MD5Final call */
} MD5_CTX;
struct SENDSTC
{
	int type;
	char md5[33];
	char filePath[MAX_PATH];
};

#define MD5DIGESTLEN 16
#define CLOUDEKILL 1
#define MD5INFO 2
#define PROTO_LIST(list)    list



//* MTS: Each of these assumes MD5_CTX is locked against simultaneous use.

typedef void(WINAPI* PMD5Init)PROTO_LIST((MD5_CTX *));
typedef void(WINAPI* PMD5Update)PROTO_LIST((MD5_CTX *, const unsigned char *, unsigned int));
typedef void(WINAPI* PMD5Final)PROTO_LIST((MD5_CTX *));

PMD5Init MD5Init = NULL;
PMD5Update MD5Update = NULL;
PMD5Final MD5Final = NULL;

const char *Hex2ASC(const BYTE *Hex, int Len)
{
	static char  ASC[4096 * 2];
	int    i;

	for (i = 0; i < Len; i++)
	{
		ASC[i * 2] = "0123456789ABCDEF"[Hex[i] >> 4];
		ASC[i * 2 + 1] = "0123456789ABCDEF"[Hex[i] & 0x0F];
	}
	ASC[i * 2] = '\0';

	return ASC;
}

