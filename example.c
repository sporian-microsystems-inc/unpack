
/* Toy program to demonstrate the inclusion of a python "unpack" string
 * to somewhat decouple producers and consumers of binary data structures.
 *
 * Dumps binary data to standard out; redirect if need be.
 */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>


enum {
    nattrs = 10
};

#define UNPACK_STRING "!30sHii%dsiiI" 

typedef struct {
    char pythonUnpack[30];
    uint16_t version;
    int32_t x1, y1;
    char description[16];
    int32_t x2, y2; 
    uint32_t nattrs;
    uint32_t attributes[nattrs];
} data_t;


void main(int argc, char *argv)
{
    data_t d;
    unsigned i;
    
    bzero(&d, sizeof(d));
    snprintf(d.pythonUnpack, (unsigned) sizeof(d.pythonUnpack), UNPACK_STRING,
             (unsigned) sizeof(d.description));

    d.version = htons(1);
    d.x1 = htonl(-10);
    d.y1 = htonl(-10);
    strncpy(d.description, "start position", 15);
    d.x2 = htonl(5);
    d.y2 = htonl(2);
    d.nattrs = htonl(nattrs);
    for (i = 0; i < 10; i++)
        d.attributes[i] = htonl(i*10);

    write(1, &d, sizeof(d));
}

