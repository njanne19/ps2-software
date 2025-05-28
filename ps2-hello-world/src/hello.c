// src/hello.c

#include <tamtypes.h> 
#include <kernel.h> 
#include <sifrpc.h> 
#include <stdio.h> 

int main(int argc, char* argv[]) {

    // Initialize the SIF RPC system so that printf can send output. 
    SifInitRpc(0); 

    // Print to the PS2 Link console or 
    printf("Hello, PS2 World!\n"); 

    // Return to the loader (e.g. PS2 Link or browser) 
    return 0; 
}
