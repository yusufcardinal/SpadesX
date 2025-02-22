//Copyright CircumScriptor and DarkNeutrino 2021
#include "Compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static z_stream* GlobalCompressor = NULL;

int InitCompressor(int level)
{
    if (GlobalCompressor != NULL) {
        fprintf(stderr, "WARNING: compressor is already initialized\n");
        return 1;
    } else {
        GlobalCompressor = (z_stream*) malloc(sizeof(z_stream));
    }

    GlobalCompressor->zalloc = Z_NULL;
    GlobalCompressor->zfree  = Z_NULL;
    GlobalCompressor->opaque = Z_NULL;

    if (deflateInit(GlobalCompressor, level) < 0) {
        fprintf(stderr, "ERROR: failed to initialize compressor\n");
        return 1;
    }
    return 0;
}

int CloseCompressor()
{
    if (GlobalCompressor == NULL) {
        fprintf(stderr, "WARNING: compressor is not initialized\n");
        return 1;
    }

    if (deflateEnd(GlobalCompressor) != 0) {
        fprintf(stderr, "ERROR: failed to close compressor\n");
        return 1;
    }

    free(GlobalCompressor);
    GlobalCompressor = NULL;
    return 0;
}

Queue* CompressData(uint8* data, uint32 length, uint32 chunkSize)
{
    InitCompressor(5);
    if (GlobalCompressor == NULL) {
        fprintf(stderr, "WARNING: compressor is not initialized\n");
        return NULL;
    }

    Queue* first = NULL;
    Queue* node  = NULL;

    GlobalCompressor->next_in  = (uint8*) data;
    GlobalCompressor->avail_in = length;

    do {
        if (first == NULL) {
            first = Push(NULL, chunkSize);
            node  = first;
        } else {
            node = Push(node, chunkSize);
        }

        GlobalCompressor->avail_out = chunkSize;
        GlobalCompressor->next_out  = node->block;
        if (deflate(GlobalCompressor, Z_FINISH) < 0) {
            printf("ERROR: failed to compress data\n");
            return NULL;
        }
        node->length = chunkSize - GlobalCompressor->avail_out;
    } while (GlobalCompressor->avail_out == 0);
    CloseCompressor();

    return first;
}
