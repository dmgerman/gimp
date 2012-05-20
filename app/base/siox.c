begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * SIOX: Simple Interactive Object Extraction  *  * For algorithm documentation refer to:  * G. Friedland, K. Jantz, L. Knipping, R. Rojas:  * "Image Segmentation by Uniform Color Clustering  *  -- Approach and Benchmark Results",  * Technical Report B-05-07, Department of Computer Science,  * Freie Universitaet Berlin, June 2005.  * http://www.inf.fu-berlin.de/inst/pubs/tr-b-05-07.pdf  *  * See http://www.siox.org/ for more information.  *  * Algorithm idea by Gerald Friedland.  * This implementation is Copyright (C) 2005  * by Gerald Friedland<fland@inf.fu-berlin.de>  * and Kristian Jantz<jantz@inf.fu-berlin.de>  * and Tobias Lenz<tlenz@inf.fu-berlin.de>.  *  * Adapted for GIMP by Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
literal|0
end_if

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_comment
comment|/* eek, but this file will die anyway */
end_comment

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|<babl/babl.h>
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_include
include|#
directive|include
file|"tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"siox.h"
end_include

begin_comment
comment|/* Thresholds in the mask:  *   pixels< SIOX_LOW  are known background  *   pixels> SIOX_HIGH are known foreground  */
end_comment

begin_define
define|#
directive|define
name|SIOX_LOW
value|1
end_define

begin_define
define|#
directive|define
name|SIOX_HIGH
value|254
end_define

begin_comment
comment|/* When clustering:  *   use LAB for color images (3 dims),  *   use L only for grayscale images (1 dim)  */
end_comment

begin_define
define|#
directive|define
name|SIOX_COLOR_DIMS
value|3
end_define

begin_define
define|#
directive|define
name|SIOX_GRAY_DIMS
value|1
end_define

begin_comment
comment|/* For findmaxblob:  * Find all blobs with area not smaller than sizefactor of biggest blob  * CHECKME: Should the user decide this with a slider?  */
end_comment

begin_define
define|#
directive|define
name|MULTIBLOB_DEFAULT_SIZEFACTOR
value|4
end_define

begin_define
define|#
directive|define
name|MULTIBLOB_ONE_BLOB_ONLY
value|0
end_define

begin_comment
comment|/* #define SIOX_DEBUG  */
end_comment

begin_comment
unit|typedef struct {   gfloat l;   gfloat a;   gfloat b;   gint   cardinality; } lab;
comment|/* A struct that holds SIOX current state */
end_comment

begin_comment
unit|struct _SioxState {   TileManager  *pixels;   const guchar *colormap;   gint          bpp;   gint          offset_x;   gint          offset_y;   gint          x;   gint          y;   gint          width;   gint          height;   GHashTable   *cache;   lab          *bgsig;   lab          *fgsig;   gint          bgsiglen;   gint          fgsiglen;   gint          xsbpp; };
comment|/* A struct that holds the classification result */
end_comment

begin_comment
unit|typedef struct {   gfloat bgdist;   gfloat fgdist; } classresult;   static void siox_cache_entry_free (gpointer entry) {   g_slice_free (classresult, entry); }
comment|/* Progressbar update callback */
end_comment

begin_comment
unit|static inline void siox_progress_update (SioxProgressFunc  progress_callback,                       gpointer          progress_data,                       gdouble           value) {   if (progress_data)     progress_callback (progress_data, value); }
comment|/* Converts any pixel format to LAB */
end_comment

begin_comment
unit|static void calc_lab (const guchar *src,           gint          bpp,           const guchar *colormap,           lab          *pixel) {   float rgb[3];   float lab[3];    switch (bpp)     {     case 3:
comment|/* RGB  */
end_comment

begin_comment
unit|case 4:
comment|/* RGBA */
end_comment

begin_comment
unit|rgb[0] = src[RED]/255.0;       rgb[1] = src[GREEN]/255.0;       rgb[2] = src[BLUE]/255.0;       break;     case 2:     case 1:       if (colormap)
comment|/* INDEXED(A) */
end_comment

begin_comment
unit|{           gint i = *src * 3;            rgb[0] = colormap[i + RED] / 255.0;           rgb[1] = colormap[i + GREEN] / 255.0;           rgb[2] = colormap[i + BLUE] / 255.0;         }       else
comment|/* GRAY(A) */
end_comment

begin_comment
unit|{           rgb[0] = *src / 255.0;           rgb[1] = *src / 255.0;           rgb[2] = *src / 255.0;         }       break;      default:       g_return_if_reached ();     }   babl_process (babl_fish (babl_format ("R'G'B' float"),                            babl_format ("CIE Lab float")),                 rgb, lab, 1);    pixel->l = lab[0];   pixel->a = lab[1];   pixel->b = lab[2]; }
comment|/*  assumes that lab starts with an array of floats (l,a,b)  */
end_comment

begin_define
define|#
directive|define
name|CURRENT_VALUE
parameter_list|(
name|points
parameter_list|,
name|i
parameter_list|,
name|dim
parameter_list|)
value|(((const gfloat *) (points + i))[dim])
end_define

begin_comment
comment|/* Stage one of modified KD-Tree algorithm (see literature above)*/
end_comment

begin_comment
unit|static void stageone (lab          *points,           gint          left,           gint          right,           const gint    depth,           gint         *clusters,           const gfloat *limits,           const gint    dims) {   const gint curdim = depth % dims;   gfloat     min, max;   gfloat     curval;   gint       i;    min = CURRENT_VALUE (points, left, curdim);   max = min;    for (i = left+1; i< right; i++)     {       curval = CURRENT_VALUE (points, i, curdim);        if (min> curval)         min = curval;       else if (max< curval)         max = curval;     }
comment|/* Split according to Rubner-Rule */
end_comment

begin_comment
unit|if (max - min> limits[curdim])     {       const gfloat pivot = (min + max) / 2.0;       gint         l     = left;       gint         r     = right - 1;       lab          tmp;        while (TRUE)         {           while (CURRENT_VALUE (points, l, curdim)<= pivot)             ++l;            while (CURRENT_VALUE (points, r, curdim)> pivot)             --r;            if (l> r)             break;            tmp = points[l];           points[l] = points[r];           points[r] = tmp;            ++l;           --r;         }
comment|/* create subtrees */
end_comment

begin_comment
unit|stageone (points, left, l, depth + 1, clusters, limits, dims);       stageone (points, l, right, depth + 1, clusters, limits, dims);     }   else     {
comment|/* create leave */
end_comment

begin_comment
unit|gfloat  l = 0;       gfloat  a = 0;       gfloat  b = 0;        points[*clusters].cardinality = right - left;        for (; left< right; ++left)         {           l += points[left].l;           a += points[left].a;           b += points[left].b;         }        points[*clusters].l = l / points[*clusters].cardinality;       points[*clusters].a = a / points[*clusters].cardinality;       points[*clusters].b = b / points[*clusters].cardinality;       ++(*clusters);     } }
comment|/* Stage two of modified KD-Tree algorithm (see literature above) */
end_comment

begin_comment
comment|/* This is very similar to stageone... but in future there may be more  * differences => not integrated into method stageone()  */
end_comment

begin_comment
unit|static void stagetwo (lab           *points,           gint           left,           gint           right,           const gint     depth,           gint          *clusters,           const gfloat  *limits,           const gfloat   threshold,           const gint     dims) {   const gint curdim = depth % dims;   gfloat     min, max;   gfloat     curval;   gint       i;    min = CURRENT_VALUE (points, left, curdim);   max = min;    for (i = left+1; i< right; i++)     {       curval = CURRENT_VALUE (points, i, curdim);        if (min> curval)         min = curval;       else if (max< curval)         max = curval;     }
comment|/* Split according to Rubner-Rule */
end_comment

begin_comment
unit|if (max - min> limits[curdim])     {       const gfloat pivot = (min + max) / 2.0;       gint         l     = left;       gint         r     = right - 1;       lab          tmp;        while (TRUE)         {           while (CURRENT_VALUE (points, l, curdim)<= pivot)             ++l;            while (CURRENT_VALUE (points, r, curdim)> pivot)             --r;            if (l> r)             break;            tmp = points[l];           points[l] = points[r];           points[r] = tmp;            ++l;           --r;         }
comment|/* create subtrees */
end_comment

begin_comment
unit|stagetwo (points, left, l, depth + 1, clusters, limits, threshold, dims);       stagetwo (points, l, right, depth + 1, clusters, limits, threshold, dims);     }   else
comment|/* create leave */
end_comment

begin_ifdef
unit|{       gint sum = 0;        for (i = left; i< right; i++)         sum += points[i].cardinality;        if (sum>= threshold)         {           const gint c = right - left;           gfloat     l = 0;           gfloat     a = 0;           gfloat     b = 0;            for (; left< right; ++left)             {               l += points[left].l;               a += points[left].a;               b += points[left].b;             }            points[*clusters].l = l / c;           points[*clusters].a = a / c;           points[*clusters].b = b / c;           ++(*clusters);
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: cluster=%f, %f, %f sum=%d\n",                      l, a, b, sum);
endif|#
directive|endif
end_endif

begin_comment
unit|}     } }
comment|/* squared euclidean distance */
end_comment

begin_comment
unit|static inline float euklid (const lab *p,         const lab *q) {   return (SQR (p->l - q->l) + SQR (p->a - q->a) + SQR (p->b - q->b)); }
comment|/* Returns squared clustersize */
end_comment

begin_comment
unit|static gfloat get_clustersize (const gfloat *limits) {   return (SQR (limits[0] - (-limits[0])) +           SQR (limits[1] - (-limits[1])) +           SQR (limits[2] - (-limits[2]))); }
comment|/* Creates a color signature for a given set of pixels */
end_comment

begin_ifdef
unit|static lab * create_signature (lab                *input,                   gint                length,                   gint               *returnlength,                   const gfloat       *limits,                   const gint          dims,                   SioxProgressFunc    progress_callback,                   gpointer            progress_data,                   gdouble             progress_value) {   gint size1 = 0;   gint size2 = 0;    if (length< 1)     {       *returnlength = 0;       return NULL;     }    stageone (input, 0, length, 0,&size1, limits, dims);
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: step #1 -> %d clusters\n", size1);
endif|#
directive|endif
end_endif

begin_ifdef
unit|siox_progress_update (progress_callback, progress_data, progress_value);    stagetwo (input, 0, size1, 0,&size2, limits, length * 0.001, dims);    *returnlength = size2;
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: step #2 -> %d clusters\n", *returnlength);
endif|#
directive|endif
end_endif

begin_comment
unit|return g_memdup (input, size2 * sizeof (lab)); }
comment|/* Smoothes mask by delegation to paint-funcs.c */
end_comment

begin_comment
unit|static void smooth_mask (TileManager *mask,              gint         x,              gint         y,              gint         width,              gint         height) {   PixelRegion region;    pixel_region_init (&region, mask, x, y, width, height, TRUE);    smooth_region (&region); }
comment|/* Erodes mask by delegation to paint-funcs.c */
end_comment

begin_comment
unit|static void erode_mask (TileManager *mask,             gint         x,             gint         y,             gint         width,             gint         height) {   PixelRegion region;    pixel_region_init (&region, mask, x, y, width, height, TRUE);    erode_region (&region); }
comment|/* Dilates mask by delegation to paint-funcs.c */
end_comment

begin_comment
unit|static void dilate_mask (TileManager *mask,              gint         x,              gint         y,              gint         width,              gint         height) {   PixelRegion region;    pixel_region_init (&region, mask, x, y, width, height, TRUE);    dilate_region (&region); }
comment|/* Mask settings for threshold_mask  * Do not change these defines! They contain some magic!  * Must all be non-zero and FINAL must be 0xFF!  */
end_comment

begin_define
define|#
directive|define
name|FIND_BLOB_SELECTED
value|0x1
end_define

begin_define
define|#
directive|define
name|FIND_BLOB_FORCEFG
value|0x3
end_define

begin_define
define|#
directive|define
name|FIND_BLOB_VISITED
value|0x7
end_define

begin_define
define|#
directive|define
name|FIND_BLOB_FINAL
value|0xFF
end_define

begin_comment
comment|/* Digitize mask */
end_comment

begin_comment
unit|static inline void threshold_mask (TileManager *mask,                 gint         x,                 gint         y,                 gint         width,                 gint         height) {   PixelRegion region;   gpointer    pr;   gint        row, col;    pixel_region_init (&region, mask, x, y, width, height, TRUE);    for (pr = pixel_regions_register (1,&region);        pr != NULL; pr = pixel_regions_process (pr))     {       guchar *data = region.data;        for (row = 0; row< region.h; row++)         {           guchar *d = data;
comment|/* everything that fits the mask is in the image */
end_comment

begin_comment
unit|for (col = 0; col< region.w; col++, d++)             {               if (*d> SIOX_HIGH)                 *d = FIND_BLOB_FORCEFG;               else if (*d>= 0x80)                 *d = FIND_BLOB_SELECTED;               else                 *d = 0;             }            data += region.rowstride;         }     } }
comment|/* a struct that contains information about a blob */
end_comment

begin_comment
unit|struct blob {   gint     seedx;   gint     seedy;   gint     size;   gboolean mustkeep; };
comment|/* This method checks out the neighbourhood of the pixel at position  * (x,y) in the TileManager mask, it adds the surrounding pixels to  * the queue to allow further processing it uses maskVal to determine  * if the surrounding pixels have already been visited x,y are passed  * from above.  */
end_comment

begin_comment
unit|static void depth_first_search (TileManager *mask,                     gint         x,                     gint         y,                     gint         xwidth,                     gint         yheight,                     struct blob *b,                     guchar       mark) {   GSList *stack = NULL;   gint    xx    = b->seedx;   gint    yy    = b->seedy;   gint    oldx  = -1;    while (TRUE)     {       guchar val;        if (oldx == xx)         {           if (stack == NULL)             break;            xx    = GPOINTER_TO_INT (stack->data);           stack = g_slist_delete_link (stack, stack);            yy    = GPOINTER_TO_INT (stack->data);           stack = g_slist_delete_link (stack, stack);         }        oldx = xx;        tile_manager_read_pixel_data_1 (mask, xx, yy,&val);        if (val&& (val != mark))         {           if (mark == FIND_BLOB_VISITED)             {               ++(b->size);               if (val == FIND_BLOB_FORCEFG)                 b->mustkeep = TRUE;             }            tile_manager_write_pixel_data_1 (mask, xx, yy,&mark);            if (yy> y)             stack = g_slist_prepend (g_slist_prepend                                      (stack, GINT_TO_POINTER (yy - 1)),                                      GINT_TO_POINTER (xx));            if (yy + 1< yheight)             stack = g_slist_prepend (g_slist_prepend                                      (stack, GINT_TO_POINTER (yy + 1)),                                      GINT_TO_POINTER (xx));            if (xx + 1< xwidth)             {               if (xx> x)                 stack = g_slist_prepend (g_slist_prepend (stack,                                                           GINT_TO_POINTER (yy)),                                          GINT_TO_POINTER (xx - 1));               ++xx;             }           else if (xx> x)             {               --xx;             }         }     } }
comment|/*  * This method finds the biggest connected components in mask, it  * clears everything in mask except the biggest components' Pixels that  * should be considererd set in incoming mask, must fulfill (pixel&  * 0x1) the method uses no further memory, except a queue, it finds  * the biggest components by a 2 phase algorithm 1. in the first phase  * the coordinates of an element of the biggest components are  * identified, during this phase all pixels are visited. In the  * second phase first visitation flags are reset, and afterwards  * connected components starting at the found coordinates are  * determined. These are the biggest components, the result is written  * into mask, all pixels that belong to the biggest components are set  * to 255, any other to 0.  */
end_comment

begin_comment
unit|static void find_max_blob (TileManager *mask,                gint         x,                gint         y,                gint         width,                gint         height,                const gint   size_factor) {   GSList     *list = NULL;   GSList     *iter;   PixelRegion region;   gpointer    pr;   gint        row, col;   gint        maxsize = 0;   guchar      val;    threshold_mask (mask, x, y, width, height);    pixel_region_init (&region, mask, x, y, width, height, TRUE);    for (pr = pixel_regions_register (1,&region);        pr != NULL;        pr = pixel_regions_process (pr))     {       gint    pos_y = region.y;       guchar *data  = region.data;        for (row = 0; row< region.h; row++, pos_y++)         {           guchar *d = data;            for (col = 0; col< region.w; col++, d++)             {               val = *d;                if (val&& (val != FIND_BLOB_VISITED))                 {                   struct blob *b = g_slice_new (struct blob);                    b->seedx    = region.x + col;                   b->seedy    = pos_y;                   b->size     = 0;                   b->mustkeep = FALSE;                    depth_first_search (mask,                                       x, y, x + width, y + height,                                       b, FIND_BLOB_VISITED);                    list = g_slist_prepend (list, b);                    if (b->size> maxsize)                     maxsize = b->size;                 }             }            data += region.rowstride;         }     }    for (iter = list; iter; iter = iter->next)     {       struct blob *b = iter->data;        depth_first_search (mask, x, y, x + width, y + height, b,                           (b->mustkeep || (b->size * size_factor>= maxsize)) ?                           FIND_BLOB_FINAL : 0);        g_slice_free (struct blob, b);     }    g_slist_free (list); }
comment|/* Creates a key for the hashtable from a given pixel color value */
end_comment

begin_comment
unit|static inline gint create_key (const guchar *src,             gint          bpp,             const guchar *colormap) {   switch (bpp)     {     case 3:
comment|/* RGB  */
end_comment

begin_comment
unit|case 4:
comment|/* RGBA */
end_comment

begin_comment
unit|return (src[RED]<< 16 | src[GREEN]<< 8 | src[BLUE]);     case 2:     case 1:       if (colormap)
comment|/* INDEXED(A) */
end_comment

begin_comment
unit|{           gint i = *src * 3;            return (colormap[i + RED]<< 16 |                   colormap[i + GREEN]<< 8  |                   colormap[i + BLUE]);         }       else
comment|/* GRAY(A) */
end_comment

begin_comment
unit|{           return *src;         }     default:       return 0;     } }
comment|/* Clear hashtable entries that get invalid due to refinement */
end_comment

begin_comment
unit|static gboolean siox_cache_remove_bg (gpointer key,                       gpointer value,                       gpointer user_data) {   classresult *cr = value;    return (cr->bgdist< cr->fgdist); }  static gboolean siox_cache_remove_fg (gpointer key,                       gpointer value,                       gpointer user_data) {   classresult *cr = value;    return (cr->bgdist>= cr->fgdist); }
comment|/**  * siox_init:  * @pixels:   the tiles to extract the foreground from  * @colormap: colormap in case @pixels are indexed, %NULL otherwise  * @offset_x: horizontal offset of @pixels with respect to the @mask  * @offset_y: vertical offset of @pixels with respect to the @mask  * @x:        horizontal offset into the mask  * @y:        vertical offset into the mask  * @width:    width of working area on mask  * @height:   height of working area on mask  *  * Initializes the SIOX segmentator.  * Creates and returns a SioxState struct that has to be passed to all  * function calls of this module as it maintaines the state.  * '* Returns: a new siox state structure.  */
end_comment

begin_ifdef
unit|SioxState * siox_init (TileManager  *pixels,            const guchar *colormap,            gint          offset_x,            gint          offset_y,            gint          x,            gint          y,            gint          width,            gint          height) {   SioxState *state;    g_return_val_if_fail (pixels != NULL, NULL);   g_return_val_if_fail (x>= 0, NULL);   g_return_val_if_fail (y>= 0, NULL);    state = g_slice_new (SioxState);    state->pixels   = pixels;   state->colormap = colormap;   state->offset_x = offset_x;   state->offset_y = offset_y;   state->x        = x;   state->y        = y;   state->width    = width;   state->height   = height;   state->bgsig    = NULL;   state->fgsig    = NULL;   state->bgsiglen = 0;   state->fgsiglen = 0;   state->bpp      = tile_manager_bpp (pixels);    state->cache = g_hash_table_new_full (g_direct_hash,                                         NULL, NULL,                                         (GDestroyNotify) siox_cache_entry_free);
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: siox_init (bpp=%d, "               "x=%d, y=%d, width=%d, height=%d, offset_x=%d, offset_y=%d)\n",               state->bpp, x, y, width, height, offset_x, offset_y);
endif|#
directive|endif
end_endif

begin_comment
unit|return state; }
comment|/**  * siox_foreground_extract:  * @state:       current state struct as constructed by siox_init  * @refinement:  #SioxRefinementType  * @mask:        a mask indicating sure foreground (255), sure background (0)  *               and undecided regions ([1..254]).  * @x1:          region of interest  * @y1:          region of interest  * @x2:          region of interest  * @y2:          region of interest  * @sensitivity: a double array with three entries specifing the accuracy,  *               a good value is: { 0.64, 1.28, 2.56 }  * @smoothness:  boundary smoothness (a good value is 3)  * @multiblob:   allow multiple blobs (true) or only one (false)  * @progress_callback: a progress callback  * @progress_data: data passed to @progress_callback  *  * Writes the resulting segmentation into @mask. The region of  * interest as specified using @x1, @y1, @x2 and @y2 defines the  * bounding box of the background and undecided areas. No changes to  * the mask are done outside this rectangle.  */
end_comment

begin_ifdef
unit|void siox_foreground_extract (SioxState          *state,                          SioxRefinementType  refinement,                          TileManager        *mask,                          gint                x1,                          gint                y1,                          gint                x2,                          gint                y2,                          gint                smoothness,                          const gdouble       sensitivity[3],                          gboolean            multiblob,                          SioxProgressFunc    progress_callback,                          gpointer            progress_data) {   PixelRegion  srcPR;   PixelRegion  mapPR;   gpointer     pr;   gint         row, col;   gint         x, y;   gint         width, height;   gfloat       clustersize;   lab         *surebg      = NULL;   lab         *surefg      = NULL;   gint         surebgcount = 0;   gint         surefgcount = 0;   gint         n;   gint         pixels, total;   gfloat       limits[3];    g_return_if_fail (state != NULL);   g_return_if_fail (mask != NULL&& tile_manager_bpp (mask) == 1);   g_return_if_fail (x1>= 0);   g_return_if_fail (x2> x1&& x2<= tile_manager_width (mask));   g_return_if_fail (y1>= 0);   g_return_if_fail (y2> y1&& y2<= tile_manager_height (mask));   g_return_if_fail (smoothness>= 0);   g_return_if_fail (progress_data == NULL || progress_callback != NULL);    x      = state->x;   y      = state->y;   width  = state->width;   height = state->height;    g_return_if_fail (x + width<= tile_manager_width (mask));   g_return_if_fail (y + height<= tile_manager_height (mask));    limits[0] = sensitivity[0];   limits[1] = sensitivity[1];   limits[2] = sensitivity[2];
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: limits %f %f %f\n", limits[0], limits[1], limits[2]);
endif|#
directive|endif
end_endif

begin_comment
unit|clustersize = get_clustersize (limits);    siox_progress_update (progress_callback, progress_data, 0.0);    if (refinement& SIOX_REFINEMENT_CHANGE_SENSITIVITY)     {
comment|/* trigger complete recalculation */
end_comment

begin_comment
unit|refinement = (SIOX_REFINEMENT_ADD_BACKGROUND |                     SIOX_REFINEMENT_ADD_FOREGROUND);     }    if (refinement& SIOX_REFINEMENT_ADD_FOREGROUND)     g_hash_table_foreach_remove (state->cache, siox_cache_remove_bg, NULL);    if (refinement& SIOX_REFINEMENT_ADD_BACKGROUND)     g_hash_table_foreach_remove (state->cache, siox_cache_remove_fg, NULL);    if (! state->bgsig)     refinement |= SIOX_REFINEMENT_ADD_BACKGROUND;    if (! state->fgsig)     refinement |= SIOX_REFINEMENT_ADD_FOREGROUND;    if (refinement& (SIOX_REFINEMENT_ADD_FOREGROUND |                     SIOX_REFINEMENT_ADD_BACKGROUND))     {
comment|/* count given foreground and background pixels */
end_comment

begin_ifdef
unit|pixel_region_init (&mapPR, mask, x, y, width, height, FALSE);       total = width * height;        for (pr = pixel_regions_register (1,&mapPR), pixels = 0, n = 0;            pr != NULL;            pr = pixel_regions_process (pr),n++)         {           const guchar *map = mapPR.data;            for (row = 0; row< mapPR.h; row++)             {               const guchar *m = map;                for (col = 0; col< mapPR.w; col++, m++)                 {                   if (*m< SIOX_LOW)                     {                       surebgcount++;                     }                   else if (*m> SIOX_HIGH)                     {                       surefgcount++;                     }                 }                map += mapPR.rowstride;             }              pixels += mapPR.w * mapPR.h;              if (n % 16 == 0)               siox_progress_update (progress_callback, progress_data,                                     0.1 * ((gdouble) pixels / (gdouble) total));         }
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: usermask #surebg=%d #surefg=%d\n",                   surebgcount, surefgcount);
endif|#
directive|endif
end_endif

begin_comment
unit|if (refinement& SIOX_REFINEMENT_ADD_FOREGROUND)         surefg = g_new (lab, surefgcount);        if (refinement& SIOX_REFINEMENT_ADD_BACKGROUND)         surebg = g_new (lab, surebgcount);
comment|/* create inputs for color signatures */
end_comment

begin_comment
unit|pixel_region_init (&srcPR, state->pixels,                          x - state->offset_x, y - state->offset_y,                          width, height, FALSE);       pixel_region_init (&mapPR, mask,                          x, y, width, height, FALSE);        pr = pixel_regions_register (2,&srcPR,&mapPR);        if (! (refinement& SIOX_REFINEMENT_ADD_FOREGROUND))         {           gint i = 0;            for (pixels = 0, n = 0;                pr != NULL;                pr = pixel_regions_process (pr), n++)             {               const guchar *src = srcPR.data;               const guchar *map = mapPR.data;                for (row = 0; row< srcPR.h; row++)                 {                   const guchar *s = src;                   const guchar *m = map;                    for (col = 0; col< srcPR.w; col++, m++, s += state->bpp)                     {                       if (*m< SIOX_LOW)                         {                           calc_lab (s, state->bpp, state->colormap, surebg + i);                           i++;                         }                     }                    src += srcPR.rowstride;                   map += mapPR.rowstride;                 }                pixels += mapPR.w * mapPR.h;                if (n % 16 == 0)                 siox_progress_update (progress_callback, progress_data,                                       0.1 + 0.1 * ((gdouble) pixels /                                                    (gdouble) total));             }         }       else if (! (refinement& SIOX_REFINEMENT_ADD_BACKGROUND))         {           gint i = 0;            for (pixels = 0, n = 0;                pr != NULL;                pr = pixel_regions_process (pr), n++)             {               const guchar *src = srcPR.data;               const guchar *map = mapPR.data;                for (row = 0; row< srcPR.h; row++)                 {                   const guchar *s = src;                   const guchar *m = map;                    for (col = 0; col< srcPR.w; col++, m++, s += state->bpp)                     {                       if (*m> SIOX_HIGH)                         {                           calc_lab (s, state->bpp, state->colormap, surefg + i);                           i++;                         }                     }                    src += srcPR.rowstride;                   map += mapPR.rowstride;                 }                pixels += mapPR.w * mapPR.h;                if (n % 16 == 0)                 siox_progress_update (progress_callback, progress_data,                                       0.1 + 0.1 * ((gdouble) pixels /                                                    (gdouble) total));             }         }       else
comment|/* both changed */
end_comment

begin_comment
unit|{           gint i = 0;           gint j = 0;            for (pixels = 0, n = 0;                pr != NULL;                pr = pixel_regions_process (pr), n++)             {               const guchar *src = srcPR.data;               const guchar *map = mapPR.data;                for (row = 0; row< srcPR.h; row++)                 {                   const guchar *s = src;                   const guchar *m = map;                    for (col = 0; col< srcPR.w; col++, m++, s += state->bpp)                     {                       if (*m< SIOX_LOW)                         {                           calc_lab (s, state->bpp, state->colormap, surebg + i);                           i++;                         }                       else if (*m> SIOX_HIGH)                         {                           calc_lab (s, state->bpp, state->colormap, surefg + j);                           j++;                         }                     }                    src += srcPR.rowstride;                   map += mapPR.rowstride;                 }                pixels += mapPR.w * mapPR.h;                if (n % 16 == 0)                 siox_progress_update (progress_callback, progress_data,                                       0.1 + 0.1 * ((gdouble) pixels /                                                    (gdouble) total));             }         }        if (refinement& SIOX_REFINEMENT_ADD_BACKGROUND)         {           g_free (state->bgsig);
comment|/* Create color signature for the background */
end_comment

begin_comment
unit|state->bgsig = create_signature (surebg, surebgcount,&state->bgsiglen, limits,                                            state->bpp == 1 ?                                            SIOX_GRAY_DIMS : SIOX_COLOR_DIMS,                                            progress_callback,                                            progress_data,                                            0.3);           g_free (surebg);            if (state->bgsiglen< 1)             {               g_free (surefg);               return;             }         }        siox_progress_update (progress_callback, progress_data, 0.4);        if (refinement& SIOX_REFINEMENT_ADD_FOREGROUND)         {           g_free (state->fgsig);
comment|/* Create color signature for the foreground */
end_comment

begin_comment
unit|state->fgsig = create_signature (surefg, surefgcount,&state->fgsiglen, limits,                                            state->bpp == 1 ?                                            SIOX_GRAY_DIMS : SIOX_COLOR_DIMS,                                            progress_callback,                                            progress_data,                                            0.45);           g_free (surefg);         }   }    siox_progress_update (progress_callback, progress_data, 0.5);
comment|/* Reduce the working area to the region of interest */
end_comment

begin_comment
unit|gimp_rectangle_intersect (x1, y1, x2 - x1, y2 - y1,                             x, y, width, height,&x,&y,&width,&height);
comment|/* Classify - the cached way....Better: Tree traversation? */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|gint hits = 0;   gint miss = 0;
endif|#
directive|endif
end_endif

begin_ifdef
unit|pixel_region_init (&srcPR, state->pixels,                      x - state->offset_x, y - state->offset_y, width, height,                      FALSE);   pixel_region_init (&mapPR, mask, x, y, width, height, TRUE);    total = width * height;    for (pr = pixel_regions_register (2,&srcPR,&mapPR), n = 0, pixels = 0;        pr != NULL;        pr = pixel_regions_process (pr), n++)     {       const guchar *src = srcPR.data;       guchar       *map = mapPR.data;        for (row = 0; row< srcPR.h; row++)         {           const guchar *s = src;           guchar       *m = map;            for (col = 0; col< srcPR.w; col++, m++, s += state->bpp)             {               lab          labpixel;               gfloat       minbg, minfg, d;               classresult *cr;               gint         key;               gint         i;                if (*m< SIOX_LOW || *m> SIOX_HIGH)                 continue;                key = create_key (s, state->bpp, state->colormap);                cr = g_hash_table_lookup (state->cache, GINT_TO_POINTER (key));                if (cr)                 {                   *m = (cr->bgdist>= cr->fgdist) ? 254 : 0;
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|++hits;
endif|#
directive|endif
end_endif

begin_ifdef
unit|continue;                 }
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|++miss;
endif|#
directive|endif
end_endif

begin_comment
unit|cr = g_slice_new0 (classresult);               calc_lab (s, state->bpp, state->colormap,&labpixel);                minbg = euklid (&labpixel, state->bgsig + 0);                for (i = 1; i< state->bgsiglen; i++)                 {                   d = euklid (&labpixel, state->bgsig + i);                    if (d< minbg)                     minbg = d;                 }                cr->bgdist = minbg;                if (state->fgsiglen == 0)                 {                   if (minbg< clustersize)                     minfg = minbg + clustersize;                   else                     minfg = 0.00001;
comment|/* This is a guess -                                         now we actually require a foreground                                         signature, !=0 to avoid div by zero                                       */
end_comment

begin_ifdef
unit|}               else                 {                   minfg = euklid (&labpixel, state->fgsig + 0);                    for (i = 1; i< state->fgsiglen; i++)                     {                       d = euklid (&labpixel, state->fgsig + i);                        if (d< minfg)                         {                           minfg = d;                         }                     }                 }                cr->fgdist = minfg;                g_hash_table_insert (state->cache, GINT_TO_POINTER (key), cr);                *m = minbg>= minfg ? 254 : 0;            }            src += srcPR.rowstride;           map += mapPR.rowstride;         }        pixels += mapPR.w * mapPR.h;        if (n % 8 == 0)         siox_progress_update (progress_callback, progress_data,                               0.5 + 0.3 * ((gdouble) pixels / (gdouble) total));     }
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: Hashtable size %d, misses=%d, hits=%d, ratio=%f\n",               g_hash_table_size (state->cache),               miss,               hits,               ((gfloat) hits) / miss);
endif|#
directive|endif
end_endif

begin_comment
comment|/* smooth a bit for error killing */
end_comment

begin_comment
unit|smooth_mask (mask, x, y, width, height);
comment|/* erode, to make sure only "strongly connected components"    * keep being connected    */
end_comment

begin_comment
unit|erode_mask (mask, x, y, width, height);
comment|/* search the biggest connected component */
end_comment

begin_comment
unit|find_max_blob (mask, x, y, width, height,                  multiblob ?                  MULTIBLOB_DEFAULT_SIZEFACTOR : MULTIBLOB_ONE_BLOB_ONLY);    siox_progress_update (progress_callback, progress_data, 0.9);
comment|/* smooth again - as user specified */
end_comment

begin_comment
unit|for (n = 0; n< smoothness; n++)     smooth_mask (mask, x, y, width, height);
comment|/* search the biggest connected component again to kill jitter */
end_comment

begin_comment
unit|find_max_blob (mask, x, y, width, height,                  multiblob ?                  MULTIBLOB_DEFAULT_SIZEFACTOR : MULTIBLOB_ONE_BLOB_ONLY);
comment|/* dilate, to fill up boundary pixels killed by erode */
end_comment

begin_comment
unit|dilate_mask (mask, x, y, width, height);    siox_progress_update (progress_callback, progress_data, 1.0); }
comment|/**  * siox_drb:  * @state:        current state struct as constructed by siox_init  * @mask:  * @x:  * @y:  * @brush_radius: the radius of the brush  * @brush_mode:   at this time either SIOX_DRB_ADD or SIOX_DRB_SUBTRACT  * @threshold:    a threshold to be defined by the user.  *                Range for SIOX_DRB_ADD: ]0..1] default: 1.0,  *                range for for SIOX_DRB_SUBTRACT: [0..1[, default: 0.0  *  * drb - detail refinement brush, a brush mask for subpixel classification.  *  * FIXME: Now it is assumed that the brush is a square. Should be able  * to be whatever GIMP offers.  * TODO: This is still an experimental method. There are more tests  * needed to evaluate performance of this!  */
end_comment

begin_comment
unit|void siox_drb (SioxState   *state,           TileManager *mask,           gint         x,           gint         y,           gint         brush_radius,           gint         brush_mode,           gfloat       threshold) {   PixelRegion  srcPR;   PixelRegion  mapPR;   gpointer     pr;   gint         row, col;    g_return_if_fail (state != NULL);   g_return_if_fail (mask != NULL&& tile_manager_bpp (mask) == 1);    pixel_region_init (&srcPR, state->pixels,                      x - brush_radius, y - brush_radius, brush_radius * 2,                      brush_radius * 2, FALSE);   pixel_region_init (&mapPR, mask, x - brush_radius, y - brush_radius,                      brush_radius * 2, brush_radius * 2, TRUE);    for (pr = pixel_regions_register (2,&srcPR,&mapPR);        pr != NULL;        pr = pixel_regions_process (pr))     {       const guchar *src = srcPR.data;       guchar       *map = mapPR.data;        for (row = 0; row< srcPR.h; row++)         {           const guchar *s = src;           guchar       *m = map;            for (col = 0; col< srcPR.w; col++, m++, s += state->bpp)             {               gint         key;               classresult *cr;               gfloat       mindistbg;               gfloat       mindistfg;               gfloat       alpha;                key = create_key (s, state->bpp, state->colormap);               cr  = g_hash_table_lookup (state->cache, GINT_TO_POINTER (key));                if (! cr)                 continue;
comment|/* Unknown color -                              can only be sure background or sure forground */
end_comment

begin_comment
unit|mindistbg = (gfloat) sqrt (cr->bgdist);               mindistfg = (gfloat) sqrt (cr->fgdist);                if (brush_mode == SIOX_DRB_ADD)                 {                   if (*m> SIOX_HIGH)                     continue;                    if (mindistfg == 0.0)                     {                       alpha = 1.0;
comment|/* avoid div by zero */
end_comment

begin_comment
unit|}                   else                     {                       gdouble d = mindistbg / mindistfg;                        alpha = MIN (d, 1.0);                     }                 }               else
comment|/*if (brush_mode == SIOX_DRB_SUBTRACT)*/
end_comment

begin_comment
unit|{                   if (*m< SIOX_HIGH)                     continue;                    if (mindistbg == 0.0)                     {                       alpha = 0.0;
comment|/* avoid div by zero */
end_comment

begin_comment
unit|}                   else                     {                       gdouble d = mindistfg / mindistbg;                        alpha = 1.0 - MIN (d, 1.0);                     }                 }                if (alpha< threshold)                 {
comment|/* background with a certain confidence                    * to be decided by user.                    */
end_comment

begin_comment
unit|*m = 0;                 }               else                 {                   *m = (gint) (255.999 * alpha);                 }             }            src += srcPR.rowstride;           map += mapPR.rowstride;         }     } }
comment|/**  * siox_done:  * @state: The state of this tool.  *  * Frees the memory assciated with the state.  */
end_comment

begin_ifdef
unit|void siox_done (SioxState *state) {   g_return_if_fail (state != NULL);    g_free (state->fgsig);   g_free (state->bgsig);   g_hash_table_destroy (state->cache);    g_slice_free (SioxState, state);
ifdef|#
directive|ifdef
name|SIOX_DEBUG
end_ifdef

begin_endif
unit|g_printerr ("siox.c: siox_done()\n");
endif|#
directive|endif
end_endif

begin_endif
unit|}
endif|#
directive|endif
end_endif

end_unit

