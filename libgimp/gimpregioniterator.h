begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpregioniterator.h  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk  *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_REGION_ITERATOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_REGION_ITERATOR_H__
define|#
directive|define
name|__GIMP_REGION_ITERATOR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpRgnIterator
typedef|typedef
name|struct
name|_GimpRgnIterator
name|GimpRgnIterator
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRgnFunc1
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRgnFunc1
function_decl|)
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpRgnFunc2
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRgnFunc2
function_decl|)
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpRgnFuncDest
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRgnFuncDest
function_decl|)
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|GeglBufferIterator
argument_list|)
end_macro

begin_function_decl
name|GimpRgnIterator
modifier|*
name|gimp_rgn_iterator_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|unused
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|GeglBufferIterator
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_rgn_iterator_free
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|GeglBufferIterator
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_rgn_iterator_dest
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|,
name|GimpRgnFuncDest
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|GeglBufferIterator
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_rgn_iterate1
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|unused
parameter_list|,
name|GimpRgnFunc1
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|GeglBufferIterator
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_rgn_iterate2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|unused
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_REGION_ITERATOR_H__ */
end_comment

end_unit

