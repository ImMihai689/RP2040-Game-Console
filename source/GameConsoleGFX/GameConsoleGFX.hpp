#ifndef GAME_CONSOLE_GFX

#define GAME_CONSOLE_GFX

#define WHITE 1
#define BLACK 0
#define INVERT 2

#define gfx_swap(a, b)                                                     \
  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))) ///< No-temp-var swap operation

#define gfx_abs(a) (((a) > 0) ? (a) : -(a))

/// Buffer size is 1024 bytes

class GameConsoleGFX
{
    public:
    
        unsigned char buffer[1024];

        GameConsoleGFX(void)
        {
            for(int i = 0; i < 1024; i++)
                buffer[i] = 0;
        }

        void clearDisplay()
        {
            for(int i = 0; i < 1024; i++)
                buffer[i] = 0;
        }

        void drawPixel(int x, int y, int color)
        {
            if(x < 0 || y < 0 || x > 127 || y > 63) return;
            switch(color)
            {
                case 2:
                    drawPixelFastInverted((unsigned char)(127 - x), (unsigned char)(63 - y));
                    break;
                case 1:
                    drawPixelFastWhite((unsigned char)(127 - x), (unsigned char)(63 - y));
                    break;
                case 0:
                    drawPixelFastBlack((unsigned char)(127 - x), (unsigned char)(63 - y));
                    break;
                default:
                    panic("Invalid color");
            }
        }

        void drawRect(int x, int y, int w, int h, int color)
        {
            int h_y = h + y;
            int w_x = w + x;
            for(int i = x; i <= w_x; i++)
            {
                drawPixel(i, y, color);
                drawPixel(i, h_y, color);
            }
            for(int i = y + 1; i < h_y; i++)
            {
                drawPixel(x, i, color);
                drawPixel(w_x, i, color);
            }
        }

        void drawRectFilled(int x, int y, int w, int h, int color)
        {
            int h_y = h + y;
            int w_x = w + x;
            for(int i = x; i <= w_x; i++)
                for(int j = y; j <= h_y; j++)
                    drawPixel(i, j, color);
        }

        void drawLineHorizontal(int x, int y, int length, int color)
        {
            int final_x = x + length;
            for(int i = x; i <= final_x; i++)
                drawPixel(i, y, color);
        }

        /// @brief Draw a shaded line using dither
        /// @param x 
        /// @param y 
        /// @param length 
        /// @param shade The shade level -- 0 -> black, 16 -> white -- MUST be [0, 16]
        void drawLineHorizontalShaded(int x, int y, int length, int shade)
        {
            int final_x = x + length;
            if(0 > shade || shade > 16)
            {
                panic("Provided a shade out of bounds (smaller than 0 or bigger than 16)");
                return;
            }

            int dither_nibble = (y & 0b000011) << 2;

            for(int i = x; i <= final_x; i++)
            {
                int dither_bit = (i & 0b0000011) + dither_nibble;
                int shaded_color = dither_shade_mask[shade] & (1 << dither_bit);
                if(shaded_color)
                    drawPixel(i, y, WHITE);
                else
                    drawPixel(i, y, BLACK);
            }
                
        }

        void drawLineVertical(int x, int y, int length, int color)
        {
            int final_y = y + length;
            for(int i = y; i <= final_y; i++)
                drawPixel(x, i, color);
        }

        void drawLine(int x0, int y0, int x1, int y1, int color)
        {
            bool steep = gfx_abs(y1 - y0) > gfx_abs(x1 - x0);
            if(steep)
            {
                gfx_swap(x0, y0);
                gfx_swap(x1, y1);
            }
            if (x0 > x1) 
            {
                gfx_swap(x0, x1);
                gfx_swap(y0, y1);
            }

            int dx, dy;
            dx = x1 - x0;
            dy = gfx_abs(y1 - y0);

            int err = dx / 2;
            int ystep;

            if (y0 < y1)
                ystep = 1;
            else
                ystep = -1;
            
            for (; x0 <= x1; x0++) 
            {
                if (steep)
                    drawPixel(y0, x0, color);
                else
                    drawPixel(x0, y0, color);
                
                err -= dy;
                if (err < 0) 
                {
                    y0 += ystep;
                    err += dx;
                }
            }
        }

        void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color)
        {
            drawLine(x0, y0, x1, y1, color);
            drawLine(x1, y1, x2, y2, color);
            drawLine(x0, y0, x2, y2, color);
        }

        void drawTriangleFilled(int x0, int y0, int x1, int y1, int x2, int y2, int color)
        {
            int a, b, y, last;

            // Sort coordinates by Y order (y2 >= y1 >= y0)
            if (y0 > y1) {
                gfx_swap(y0, y1);
                gfx_swap(x0, x1);
            }
            if (y1 > y2) {
                gfx_swap(y2, y1);
                gfx_swap(x2, x1);
            }
            if (y0 > y1) {
                gfx_swap(y0, y1);
                gfx_swap(x0, x1);
            }

            if (y0 == y2) 
            { // Handle awkward all-on-same-line case as its own thing
                a = b = x0;
                if (x1 < a)
                    a = x1;
                else if (x1 > b)
                    b = x1;
                if (x2 < a)
                    a = x2;
                else if (x2 > b)
                    b = x2;
                drawLineHorizontal(a, y0, b - a + 1, color);
                return;
            }

            int dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
                    dx12 = x2 - x1, dy12 = y2 - y1;
            int sa = 0, sb = 0;

            // For upper part of triangle, find scanline crossings for segments
            // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
            // is included here (and second loop will be skipped, avoiding a /0
            // error there), otherwise scanline y1 is skipped here and handled
            // in the second loop...which also avoids a /0 error here if y0=y1
            // (flat-topped triangle).
            if (y1 == y2)
                last = y1; // Include y1 scanline
            else
                last = y1 - 1; // Skip it

            for (y = y0; y <= last; y++) {
                a = x0 + sa / dy01;
                b = x0 + sb / dy02;
                sa += dx01;
                sb += dx02;
                /* longhand:
                a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
                b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
                */
                if (a > b)
                    gfx_swap(a, b);
                drawLineHorizontal(a, y, b - a + 1, color);
            }

            // For lower part of triangle, find scanline crossings for segments
            // 0-2 and 1-2.  This loop is skipped if y1=y2.
            sa = (int)dx12 * (y - y1);
            sb = (int)dx02 * (y - y0);
            for (; y <= y2; y++) {
                a = x1 + sa / dy12;
                b = x0 + sb / dy02;
                sa += dx12;
                sb += dx02;
                /* longhand:
                a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
                b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
                */
                if (a > b)
                    gfx_swap(a, b);
                drawLineHorizontal(a, y, b - a + 1, color);
            }
        }

        void drawTriangleShaded(int x0, int y0, int x1, int y1, int x2, int y2, int shade)
        {
            int a, b, y, last;

            // Sort coordinates by Y order (y2 >= y1 >= y0)
            if (y0 > y1) {
                gfx_swap(y0, y1);
                gfx_swap(x0, x1);
            }
            if (y1 > y2) {
                gfx_swap(y2, y1);
                gfx_swap(x2, x1);
            }
            if (y0 > y1) {
                gfx_swap(y0, y1);
                gfx_swap(x0, x1);
            }

            if (y0 == y2) 
            { // Handle awkward all-on-same-line case as its own thing
                a = b = x0;
                if (x1 < a)
                    a = x1;
                else if (x1 > b)
                    b = x1;
                if (x2 < a)
                    a = x2;
                else if (x2 > b)
                    b = x2;
                drawLineHorizontalShaded(a, y0, b - a + 1, shade);
                return;
            }

            int dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
                    dx12 = x2 - x1, dy12 = y2 - y1;
            int sa = 0, sb = 0;

            // For upper part of triangle, find scanline crossings for segments
            // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
            // is included here (and second loop will be skipped, avoiding a /0
            // error there), otherwise scanline y1 is skipped here and handled
            // in the second loop...which also avoids a /0 error here if y0=y1
            // (flat-topped triangle).
            if (y1 == y2)
                last = y1; // Include y1 scanline
            else
                last = y1 - 1; // Skip it

            for (y = y0; y <= last; y++) {
                a = x0 + sa / dy01;
                b = x0 + sb / dy02;
                sa += dx01;
                sb += dx02;
                /* longhand:
                a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
                b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
                */
                if (a > b)
                    gfx_swap(a, b);
                drawLineHorizontalShaded(a, y, b - a + 1, shade);
            }

            // For lower part of triangle, find scanline crossings for segments
            // 0-2 and 1-2.  This loop is skipped if y1=y2.
            sa = (int)dx12 * (y - y1);
            sb = (int)dx02 * (y - y0);
            for (; y <= y2; y++) {
                a = x1 + sa / dy12;
                b = x0 + sb / dy02;
                sa += dx12;
                sb += dx02;
                /* longhand:
                a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
                b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
                */
                if (a > b)
                    gfx_swap(a, b);
                drawLineHorizontalShaded(a, y, b - a + 1, shade);
            }
        }

    private:
        inline void drawPixelFastWhite(unsigned char x, unsigned char y)
        {
            unsigned char page = y >> 3;
            buffer[(page << 7) + x] |= (unsigned char)(1 << (y & 7));
        }

        inline void drawPixelFastBlack(unsigned char x, unsigned char y)
        {
            unsigned char page = y >> 3;
            buffer[(page << 7) + x] &= (unsigned char)(((unsigned char)0xFF) << (y & 7));
        }

        inline void drawPixelFastInverted(unsigned char x, unsigned char y)
        {
            unsigned char page = y >> 3;
            buffer[(page << 7) + x] ^= (unsigned char)(1 << (y & 7));
        }

        const unsigned short dither_shade_mask[17] = {
            0b0000000000000000,
            0b1000000000000000,
            0b1000000000100000,
            0b1000000010100000,
            0b1010000010100000,
            0b1010010010100000,
            0b1010010010100001,
            0b1010010010100101,
            0b1010010110100101,
            0b1010011110100101,
            0b1010011110101101,
            0b1010011110101111,
            0b1010111110101111,
            0b1110111110101111,
            0b1110111110111111,
            0b1110111111111111,
            0b1111111111111111,
        };
};

#endif