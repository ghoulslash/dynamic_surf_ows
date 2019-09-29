#include "defines.h"
#include "../include/sprite.h"

extern u16 sSpritePriorities[];


void BuildSpritePriorities(void)
{
    u16 i;
    for (i = 0; i < MAX_SPRITES; ++i)
    {
        struct Sprite *sprite = &gSprites[i];
        u16 priority = sprite->subpriority | (sprite->oam.priority << 8);
        sSpritePriorities[i] = priority;
    }
}

/*
void SortSprites(void)
{
    u8 i;
    for (i = 1; i < MAX_SPRITES; i++)
    {
        u8 j = i;
        struct Sprite *sprite1 = &gSprites[sSpriteOrder[i - 1]];
        struct Sprite *sprite2 = &gSprites[sSpriteOrder[i]];
        u16 sprite1Priority = sSpritePriorities[sSpriteOrder[i - 1]];
        u16 sprite2Priority = sSpritePriorities[sSpriteOrder[i]];
        s16 sprite1Y = sprite1->oam.y;
        s16 sprite2Y = sprite2->oam.y;

        if (sprite1Y >= DISPLAY_HEIGHT)
            sprite1Y = sprite1Y - 256;

        if (sprite2Y >= DISPLAY_HEIGHT)
            sprite2Y = sprite2Y - 256;

        if (sprite1->oam.affineMode == ST_OAM_AFFINE_DOUBLE
         && sprite1->oam.size == 3)
        {
            u32 shape = sprite1->oam.shape;
            if (shape == ST_OAM_SQUARE || shape == 2)
            {
                if (sprite1Y > 128)
                    sprite1Y = sprite1Y - 256;
            }
        }

        if (sprite2->oam.affineMode == ST_OAM_AFFINE_DOUBLE
         && sprite2->oam.size == 3)
        {
            u32 shape = sprite2->oam.shape;
            if (shape == ST_OAM_SQUARE || shape == ST_OAM_V_RECTANGLE)
            {
                if (sprite2Y > 128)
                    sprite2Y = sprite2Y - 256;
            }
        }

        while (j > 0
            && ((sprite1Priority > sprite2Priority)
             || (sprite1Priority == sprite2Priority && sprite1Y < sprite2Y)))
        {
            u8 temp = sSpriteOrder[j];
            sSpriteOrder[j] = sSpriteOrder[j - 1];
            sSpriteOrder[j - 1] = temp;

            // UB: If j equals 1, then j-- makes j equal 0.
            // Then, sSpriteOrder[-1] gets accessed below.
            // Although this doesn't result in a bug in the ROM,
            // the behavior is undefined.
            j--;

            sprite1 = &gSprites[sSpriteOrder[j - 1]];
            sprite2 = &gSprites[sSpriteOrder[j]];
            sprite1Priority = sSpritePriorities[sSpriteOrder[j - 1]];
            sprite2Priority = sSpritePriorities[sSpriteOrder[j]];
            sprite1Y = sprite1->oam.y;
            sprite2Y = sprite2->oam.y;

            if (sprite1Y >= DISPLAY_HEIGHT)
                sprite1Y = sprite1Y - 256;

            if (sprite2Y >= DISPLAY_HEIGHT)
                sprite2Y = sprite2Y - 256;

            if (sprite1->oam.affineMode == ST_OAM_AFFINE_DOUBLE
             && sprite1->oam.size == 3)
            {
                u32 shape = sprite1->oam.shape;
                if (shape == ST_OAM_SQUARE || shape == ST_OAM_V_RECTANGLE)
                {
                    if (sprite1Y > 128)
                        sprite1Y = sprite1Y - 256;
                }
            }

            if (sprite2->oam.affineMode == ST_OAM_AFFINE_DOUBLE
             && sprite2->oam.size == 3)
            {
                u32 shape = sprite2->oam.shape;
                if (shape == ST_OAM_SQUARE || shape == ST_OAM_V_RECTANGLE)
                {
                    if (sprite2Y > 128)
                        sprite2Y = sprite2Y - 256;
                }
            }
        }
    }
}

*/
