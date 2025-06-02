#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <stdio.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <math.h>

int main(int argc, char *argv[]) {
    // 1) IOP RPC
    SifInitRpc(0);

    // 2) DMA for GIF
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF,
                D_CTRL_STS_UNSPEC, D_CTRL_STD_OFF,
                D_CTRL_RCYC_8, DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    // 3) gsKit global context
    GSGLOBAL *gs = gsKit_init_global();
    gs->Mode      = GS_MODE_NTSC;
    gs->Interlace = GS_NONINTERLACED;
    gs->Width     = 640;
    gs->Height    = 448;
    gsKit_init_screen(gs);

    // 4) Colors
    const u64 White = GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0,0);
    const u64 Blue  = GS_SETREG_RGBAQ(0x00,0x00,0x20,0,0);

    float angle = 0.0f;
    while (1) {
        // A) Clear to dark blue
        gsKit_clear(gs, Blue);

        // B) Compute triangle verts
        const float cx = gs->Width  * 0.5f;
        const float cy = gs->Height * 0.5f;
        const float r  = 100.0f;
        float x0 = cx + r * cosf(angle + 0.0f);
        float y0 = cy + r * sinf(angle + 0.0f);
        float x1 = cx + r * cosf(angle + 2.0944f);
        float y1 = cy + r * sinf(angle + 2.0944f);
        float x2 = cx + r * cosf(angle + 4.1888f);
        float y2 = cy + r * sinf(angle + 4.1888f);

        // C) Draw white triangle
        gsKit_prim_triangle(gs, x0,y0, x1,y1, x2,y2, 1, White);

        // D) Flush & swap
        gsKit_queue_exec(gs);
        gsKit_sync_flip(gs);

        // E) Rotate
        angle += 0.02f;
    }
    return 0;
}