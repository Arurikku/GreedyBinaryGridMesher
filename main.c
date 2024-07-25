#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include <time.h>

#define SIZE 32

struct GreedyQuad{
    uint8_t yPos;
    uint8_t xPos;
    uint8_t width;
    uint8_t height;
};
typedef struct GreedyQuad GreedyQuad;

static inline uint8_t trailing_zeros(uint32_t x) {
    return __builtin_ctzl(x);
}

static inline uint8_t trailing_ones(uint32_t x) {
    return __builtin_ctzl(~x);
}

int greedy_mesh_binary(uint32_t* cols, GreedyQuad* greedyOut){
    int ctr = 0;
    for(uint8_t i = 0; i < SIZE; i++){
        uint32_t y = 0;
        while(y < SIZE){
            uint8_t nZeros = trailing_zeros(cols[i] >> y);
            y += nZeros;
            if(y >= SIZE)
                continue;
            uint8_t height = trailing_ones(cols[i] >> y);
            uint32_t heightMask = ((1 << height) - 1) << y;
            uint8_t width = 1;
            while(i + width < SIZE){
                uint32_t toCheck = cols[i + width] & heightMask;
                if(toCheck != heightMask)
                    break;
                cols[i + width] = cols[i + width] & ~heightMask;
                width++;
            }
            greedyOut[ctr++] = (GreedyQuad){y, i, width, height};
            y += height;
        }
    }
    return ctr;

}

uint32_t random_32bit(){
    uint16_t varA = (uint16_t)rand();
    uint16_t varB = (uint16_t)rand();
    uint16_t varC = (uint16_t)rand();
    return (uint32_t)((varA << 17) + (varB << 2) + (varC >> 13));
}

uint32_t* generate_random_plane_32() {
    uint32_t* randomArray = (uint32_t*)malloc(32 * sizeof(uint32_t));
    if (randomArray == NULL) {
        printf("Malloc failed??\n");
        return NULL;
    }
    for (int i = 0; i < 32; i++) {
        randomArray[i] = random_32bit();
    }
    return randomArray;
}


int main(){
    srand(time(NULL));
    uint32_t* plane = generate_random_plane_32();
    GreedyQuad* outputQuads = malloc(sizeof(GreedyQuad)*32*32);
    int nQuads = greedy_mesh_binary(plane, outputQuads);
    printf("%d quads were found\n", nQuads);
    for(int i = 0; i < nQuads; i++)
        printf("(%d) x=%d y=%d w=%d h=%d\n", i, outputQuads[i].xPos, outputQuads[i].yPos, outputQuads[i].width, outputQuads[i].height);
    free(plane);
    free(outputQuads);
    return 0;
}
