extern "C" {

#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/rand.h>

}

int main(int argc, char *argv[])
{
    unsigned char buf[256] = { 0 };
    RAND_bytes(buf, 256);

    for (int i = 0; i < 256; ++i) {
        printf("%d\n", buf[i]);
    }
    return 0;
}
