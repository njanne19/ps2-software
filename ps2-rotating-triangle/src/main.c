#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <stdio.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <libpad.h>
#include <math.h>

int main(int argc, char *argv[])
{
    SifInitRpc(0);

    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    // Note: the actual gsKit type is GSGLOBAL, not GS_GLOBAL
    GSGLOBAL *gs = gsKit_init_global();
    gs->Mode      = GS_MODE_NTSC;
    gs->Interlace = GS_NONINTERLACED;
    gs->Width     = 640;
    gs->Height    = 448;
    gsKit_init_screen(gs);

    // Choose a solid‐white color (RGBAQ: R,G,B,Alpha,Q)
    u64 White = GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x00, 0x00);

    float angle = 0.0f;

    while (1) {
        // 1) Clear the color buffer to dark blue
        gsKit_clear(gs, GS_SETREG_RGBAQ(0x00, 0x00, 0x20, 0x00, 0x00));

        // 2) Compute three points around a circle centered at (320,224)
        float x0 = 320 + 100 * cosf(angle + 0.0f);
        float y0 = 224 + 100 * sinf(angle + 0.0f);
        float x1 = 320 + 100 * cosf(angle + 2.0944f); // +120°
        float y1 = 224 + 100 * sinf(angle + 2.0944f);
        float x2 = 320 + 100 * cosf(angle + 4.1888f); // +240°
        float y2 = 224 + 100 * sinf(angle + 4.1888f);

        // 3) Draw the triangle (context 1)
        gsKit_prim_triangle(
          gs,
          x0, y0,
          x1, y1,
          x2, y2,
          1,      // drawing context
          White  // color
        );

        // 4) Flush and swap buffers
        gsKit_queue_exec(gs);
        gsKit_sync_flip(gs);

        // 5) Advance rotation
        angle += 0.02f;
    }

    return 0;
}