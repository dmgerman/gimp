begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewcache.h"
end_include

begin_define
DECL|macro|MAX_CACHE_PREVIEWS
define|#
directive|define
name|MAX_CACHE_PREVIEWS
value|5
end_define

begin_undef
undef|#
directive|undef
name|PREVIEW_CACHE_DEBUG
end_undef

begin_typedef
DECL|struct|_PreviewCache
typedef|typedef
struct|struct
name|_PreviewCache
block|{
DECL|member|preview
name|TempBuf
modifier|*
name|preview
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|typedef|PreviewCache
block|}
name|PreviewCache
typedef|;
end_typedef

begin_typedef
DECL|struct|_PreviewNearest
typedef|typedef
struct|struct
name|_PreviewNearest
block|{
DECL|member|pc
name|PreviewCache
modifier|*
name|pc
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|typedef|PreviewNearest
block|}
name|PreviewNearest
typedef|;
end_typedef

begin_function
specifier|static
name|gint
DECL|function|preview_cache_compare (gconstpointer a,gconstpointer b)
name|preview_cache_compare
parameter_list|(
name|gconstpointer
name|a
parameter_list|,
name|gconstpointer
name|b
parameter_list|)
block|{
name|PreviewCache
modifier|*
name|pc1
init|=
operator|(
name|PreviewCache
operator|*
operator|)
name|a
decl_stmt|;
name|PreviewCache
modifier|*
name|pc2
init|=
operator|(
name|PreviewCache
operator|*
operator|)
name|b
decl_stmt|;
if|if
condition|(
name|pc1
operator|->
name|width
operator|>
name|pc2
operator|->
name|width
operator|&&
name|pc1
operator|->
name|height
operator|>
name|pc2
operator|->
name|height
condition|)
return|return
operator|-
literal|1
return|;
return|return
literal|1
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|preview_cache_find_exact (gpointer data,gpointer udata)
name|preview_cache_find_exact
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|udata
parameter_list|)
block|{
name|PreviewCache
modifier|*
name|pc
init|=
operator|(
name|PreviewCache
operator|*
operator|)
name|data
decl_stmt|;
name|PreviewNearest
modifier|*
name|pNearest
init|=
operator|(
name|PreviewNearest
operator|*
operator|)
name|udata
decl_stmt|;
comment|/*   g_print ("this value w,h [%d,%d]\n",pc->width,pc->height); */
comment|/*   if (pNearest->pc) */
comment|/*       g_print ("current nearest value w,h [%d,%d]\n",                  pNearest->pc->width,pNearest->pc->height); */
if|if
condition|(
name|pNearest
operator|->
name|pc
condition|)
return|return;
if|if
condition|(
name|pc
operator|->
name|width
operator|==
name|pNearest
operator|->
name|width
operator|&&
name|pc
operator|->
name|height
operator|==
name|pNearest
operator|->
name|height
condition|)
block|{
comment|/* Ok we could make the preview out of this one...        * If we already have it are these bigger dimensions?         */
name|pNearest
operator|->
name|pc
operator|=
name|pc
expr_stmt|;
return|return;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|preview_cache_find_biggest (gpointer data,gpointer udata)
name|preview_cache_find_biggest
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|udata
parameter_list|)
block|{
name|PreviewCache
modifier|*
name|pc
init|=
operator|(
name|PreviewCache
operator|*
operator|)
name|data
decl_stmt|;
name|PreviewNearest
modifier|*
name|pNearest
init|=
operator|(
name|PreviewNearest
operator|*
operator|)
name|udata
decl_stmt|;
comment|/*   g_print ("this value w,h [%d,%d]\n",pc->width,pc->height); */
comment|/*   if (pNearest->pc) */
comment|/*       g_print ("current nearest value w,h [%d,%d]\n",                  pNearest->pc->width,pNearest->pc->height); */
if|if
condition|(
name|pc
operator|->
name|width
operator|>=
name|pNearest
operator|->
name|width
operator|&&
name|pc
operator|->
name|height
operator|>=
name|pNearest
operator|->
name|height
condition|)
block|{
comment|/* Ok we could make the preview out of this one...        * If we already have it are these bigger dimensions?         */
if|if
condition|(
name|pNearest
operator|->
name|pc
condition|)
block|{
if|if
condition|(
name|pNearest
operator|->
name|pc
operator|->
name|width
operator|>
name|pc
operator|->
name|width
operator|&&
name|pNearest
operator|->
name|pc
operator|->
name|height
operator|>
name|pc
operator|->
name|height
condition|)
return|return;
block|}
name|pNearest
operator|->
name|pc
operator|=
name|pc
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|preview_cache_remove_smallest (GSList ** plist)
name|preview_cache_remove_smallest
parameter_list|(
name|GSList
modifier|*
modifier|*
name|plist
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|PreviewCache
modifier|*
name|smallest
init|=
name|NULL
decl_stmt|;
comment|/*   g_print ("Removing smallest\n"); */
for|for
control|(
name|list
operator|=
operator|*
name|plist
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
if|if
condition|(
operator|!
name|smallest
condition|)
block|{
name|smallest
operator|=
name|list
operator|->
name|data
expr_stmt|;
comment|/* 	  g_print ("init smallest  %d,%d\n", 	            smallest->width,smallest->height); */
block|}
else|else
block|{
name|PreviewCache
modifier|*
name|pcthis
init|=
name|list
operator|->
name|data
decl_stmt|;
comment|/* 	  g_print ("Checking %d,%d\n",pcthis->width,pcthis->height); */
if|if
condition|(
operator|(
name|smallest
operator|->
name|height
operator|*
name|smallest
operator|->
name|width
operator|)
operator|>=
operator|(
name|pcthis
operator|->
name|height
operator|*
name|pcthis
operator|->
name|width
operator|)
condition|)
block|{
name|smallest
operator|=
name|pcthis
expr_stmt|;
comment|/* 	      g_print ("smallest now  %d,%d\n",                       smallest->width,smallest->height); */
block|}
block|}
block|}
if|if
condition|(
operator|*
name|plist
operator|&&
name|smallest
condition|)
operator|*
name|plist
operator|=
name|g_slist_remove
argument_list|(
operator|*
name|plist
argument_list|,
name|smallest
argument_list|)
expr_stmt|;
comment|/*   g_print ("removed %d,%d\n",smallest->width,smallest->height); */
comment|/*   g_print ("removed smallest\n"); */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|preview_cache_invalidate (gpointer data,gpointer udata)
name|preview_cache_invalidate
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|udata
parameter_list|)
block|{
name|PreviewCache
modifier|*
name|pc
init|=
operator|(
name|PreviewCache
operator|*
operator|)
name|data
decl_stmt|;
name|temp_buf_free
argument_list|(
name|pc
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|preview_cache_print (GSList * plist)
name|preview_cache_print
parameter_list|(
name|GSList
modifier|*
name|plist
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|PREVIEW_CACHE_DEBUG
name|GSList
modifier|*
name|list
decl_stmt|;
name|PreviewCache
modifier|*
name|pc
decl_stmt|;
name|g_print
argument_list|(
literal|"preview cache dump:\n"
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|plist
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|pc
operator|=
operator|(
name|PreviewCache
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|g_print
argument_list|(
literal|"\tvalue w,h [%d,%d] => %p\n"
argument_list|,
name|pc
operator|->
name|width
argument_list|,
name|pc
operator|->
name|height
argument_list|,
name|pc
operator|->
name|preview
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* PREVIEW_CACHE_DEBUG */
block|}
end_function

begin_function
name|void
DECL|function|gimp_preview_cache_invalidate (GSList ** plist)
name|gimp_preview_cache_invalidate
parameter_list|(
name|GSList
modifier|*
modifier|*
name|plist
parameter_list|)
block|{
comment|/*   g_print ("gimp_preview_cache_invalidate\n"); */
name|preview_cache_print
argument_list|(
operator|*
name|plist
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
operator|*
name|plist
argument_list|,
name|preview_cache_invalidate
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|plist
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_preview_cache_add (GSList ** plist,TempBuf * buf)
name|gimp_preview_cache_add
parameter_list|(
name|GSList
modifier|*
modifier|*
name|plist
parameter_list|,
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
name|PreviewCache
modifier|*
name|pc
decl_stmt|;
comment|/*   g_print ("gimp_preview_cache_add %d %d\n",buf->width,buf->height); */
name|preview_cache_print
argument_list|(
operator|*
name|plist
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_slist_length
argument_list|(
operator|*
name|plist
argument_list|)
operator|>
name|MAX_CACHE_PREVIEWS
condition|)
block|{
comment|/* Remove the smallest */
name|preview_cache_remove_smallest
argument_list|(
name|plist
argument_list|)
expr_stmt|;
block|}
name|pc
operator|=
name|g_new0
argument_list|(
name|PreviewCache
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pc
operator|->
name|preview
operator|=
name|buf
expr_stmt|;
name|pc
operator|->
name|width
operator|=
name|buf
operator|->
name|width
expr_stmt|;
name|pc
operator|->
name|height
operator|=
name|buf
operator|->
name|height
expr_stmt|;
operator|*
name|plist
operator|=
name|g_slist_insert_sorted
argument_list|(
operator|*
name|plist
argument_list|,
name|pc
argument_list|,
name|preview_cache_compare
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_preview_cache_get (GSList ** plist,gint width,gint height)
name|gimp_preview_cache_get
parameter_list|(
name|GSList
modifier|*
modifier|*
name|plist
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|PreviewNearest
name|pn
decl_stmt|;
name|PreviewCache
modifier|*
name|pc
decl_stmt|;
comment|/*   g_print ("gimp_preview_cache_get %d %d\n",width,height); */
name|preview_cache_print
argument_list|(
operator|*
name|plist
argument_list|)
expr_stmt|;
name|pn
operator|.
name|pc
operator|=
name|NULL
expr_stmt|;
name|pn
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|pn
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|g_slist_foreach
argument_list|(
operator|*
name|plist
argument_list|,
name|preview_cache_find_exact
argument_list|,
operator|&
name|pn
argument_list|)
expr_stmt|;
if|if
condition|(
name|pn
operator|.
name|pc
operator|&&
name|pn
operator|.
name|pc
operator|->
name|preview
condition|)
block|{
comment|/*       g_print ("extact value w,h [%d,%d] => %p\n", 	           pn.pc->width,pn.pc->height,pn.pc->preview);  */
return|return
name|pn
operator|.
name|pc
operator|->
name|preview
return|;
block|}
name|g_slist_foreach
argument_list|(
operator|*
name|plist
argument_list|,
name|preview_cache_find_biggest
argument_list|,
operator|&
name|pn
argument_list|)
expr_stmt|;
if|if
condition|(
name|pn
operator|.
name|pc
condition|)
block|{
name|gint
name|pwidth
decl_stmt|;
name|gint
name|pheight
decl_stmt|;
name|gdouble
name|x_ratio
decl_stmt|;
name|gdouble
name|y_ratio
decl_stmt|;
name|guchar
modifier|*
name|src_data
decl_stmt|;
name|guchar
modifier|*
name|dest_data
decl_stmt|;
name|gint
name|loop1
decl_stmt|;
name|gint
name|loop2
decl_stmt|;
comment|/*       g_print ("nearest value w,h [%d,%d] => %p\n",                    pn.pc->width,pn.pc->height,pn.pc->preview); */
comment|/*       if(pn.pc->width == width&& */
comment|/* 	   pn.pc->height == height) */
comment|/* 	 return pn.pc->preview; */
if|if
condition|(
operator|!
name|pn
operator|.
name|pc
operator|->
name|preview
condition|)
block|{
name|g_error
argument_list|(
literal|"gimp_preview_cache_get:: Invalid cache item"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/* Make up new preview from the large one... */
name|pwidth
operator|=
name|pn
operator|.
name|pc
operator|->
name|preview
operator|->
name|width
expr_stmt|;
name|pheight
operator|=
name|pn
operator|.
name|pc
operator|->
name|preview
operator|->
name|height
expr_stmt|;
comment|/* Now get the real one and add to cache */
comment|/*       g_print ("Must create from large preview\n"); */
name|pc
operator|=
name|g_new0
argument_list|(
name|PreviewCache
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pc
operator|->
name|preview
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|pn
operator|.
name|pc
operator|->
name|preview
operator|->
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* preview from nearest bigger one */
if|if
condition|(
name|width
condition|)
name|x_ratio
operator|=
operator|(
name|gdouble
operator|)
name|pwidth
operator|/
operator|(
name|gdouble
operator|)
name|width
expr_stmt|;
else|else
name|x_ratio
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|height
condition|)
name|y_ratio
operator|=
operator|(
name|gdouble
operator|)
name|pheight
operator|/
operator|(
name|gdouble
operator|)
name|height
expr_stmt|;
else|else
name|y_ratio
operator|=
literal|0.0
expr_stmt|;
name|src_data
operator|=
name|temp_buf_data
argument_list|(
name|pn
operator|.
name|pc
operator|->
name|preview
argument_list|)
expr_stmt|;
name|dest_data
operator|=
name|temp_buf_data
argument_list|(
name|pc
operator|->
name|preview
argument_list|)
expr_stmt|;
comment|/*       g_print ("x_ratio , y_ratio [%f,%f]\n",x_ratio,y_ratio); */
for|for
control|(
name|loop1
operator|=
literal|0
init|;
name|loop1
operator|<
name|height
condition|;
name|loop1
operator|++
control|)
for|for
control|(
name|loop2
operator|=
literal|0
init|;
name|loop2
operator|<
name|width
condition|;
name|loop2
operator|++
control|)
block|{
name|gint
name|i
decl_stmt|;
name|guchar
modifier|*
name|src_pixel
decl_stmt|;
name|guchar
modifier|*
name|dest_pixel
decl_stmt|;
name|src_pixel
operator|=
name|src_data
operator|+
operator|(
call|(
name|gint
call|)
argument_list|(
name|loop2
operator|*
name|x_ratio
argument_list|)
operator|)
operator|*
name|pn
operator|.
name|pc
operator|->
name|preview
operator|->
name|bytes
operator|+
operator|(
call|(
name|gint
call|)
argument_list|(
name|loop1
operator|*
name|y_ratio
argument_list|)
operator|)
operator|*
name|pwidth
operator|*
name|pn
operator|.
name|pc
operator|->
name|preview
operator|->
name|bytes
expr_stmt|;
name|dest_pixel
operator|=
name|dest_data
operator|+
operator|(
name|loop2
operator|+
name|loop1
operator|*
name|width
operator|)
operator|*
name|pn
operator|.
name|pc
operator|->
name|preview
operator|->
name|bytes
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pn
operator|.
name|pc
operator|->
name|preview
operator|->
name|bytes
condition|;
name|i
operator|++
control|)
operator|*
name|dest_pixel
operator|++
operator|=
operator|*
name|src_pixel
operator|++
expr_stmt|;
block|}
name|pc
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|pc
operator|->
name|height
operator|=
name|height
expr_stmt|;
operator|*
name|plist
operator|=
name|g_slist_insert_sorted
argument_list|(
operator|*
name|plist
argument_list|,
name|pc
argument_list|,
name|preview_cache_compare
argument_list|)
expr_stmt|;
comment|/*       g_print ("New preview created [%d,%d] => %p\n", 	           pc->width,pc->height,pc->preview);  */
return|return
name|pc
operator|->
name|preview
return|;
block|}
comment|/*   g_print ("gimp_preview_cache_get returning NULL\n");  */
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gsize
DECL|function|gimp_preview_cache_get_memsize (GSList * cache)
name|gimp_preview_cache_get_memsize
parameter_list|(
name|GSList
modifier|*
name|cache
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cache
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|cache
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|PreviewCache
modifier|*
name|pc
decl_stmt|;
name|pc
operator|=
operator|(
name|PreviewCache
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|memsize
operator|+=
operator|(
sizeof|sizeof
argument_list|(
name|PreviewCache
argument_list|)
operator|+
name|temp_buf_get_memsize
argument_list|(
name|pc
operator|->
name|preview
argument_list|)
operator|)
expr_stmt|;
block|}
return|return
name|memsize
return|;
block|}
end_function

end_unit

