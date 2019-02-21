
            Sharing Data Between C* and Python

Consider a data structure that is produced by a C program
and consumed by a python script, e.g.

<pre>
    uint16_t version;
    int32_t x1, y1;
    char description[16];
    int32_t x2, y2;
    uint32_t nattrs;
    uint32_t attributes[1];  /* actually longer */
</pre>

Assume that the data is 1) packed in binary form and 2) the
sizes of the arrays above may change over time....  It's 
possible to use python's struct module to unpack this data,
but when the sizes change, the python code would have to
change too.

Alternatively, consider augmenting the structure slightly:

<pre>
    char pythonUnpack[30];
    uint16_t version;
    int32_t x1, y1;
    char description[16];
    int32_t x2, y2;
    uint32_t nattrs;
    uint32_t attributes[1];  /* actually longer */
</pre>

This opens the door for the arrays to change size without the
python code needing to change :-)  In other words, if the
producing code includes the "unpacking instructions" up front,
it may be possible to avoid changing the "consumer" code.


*While the "producer" in this example is C code, the idea 
applies more generally.


