begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-  * Gimp-Python - allows the writing of Gimp plugins in Python.  * Copyright (C) 1997-2002  James Henstridge<james@daa.com.au>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PYGIMP_H_
end_ifndef

begin_define
DECL|macro|_PYGIMP_H_
define|#
directive|define
name|_PYGIMP_H_
end_define

begin_include
include|#
directive|include
file|<Python.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_define
DECL|macro|_INSIDE_PYGIMP_
define|#
directive|define
name|_INSIDE_PYGIMP_
end_define

begin_include
include|#
directive|include
file|"pygimp-api.h"
end_include

begin_if
if|#
directive|if
name|PY_VERSION_HEX
operator|<
literal|0x02050000
operator|&&
operator|!
name|defined
argument_list|(
name|PY_SSIZE_T_MIN
argument_list|)
end_if

begin_typedef
DECL|typedef|Py_ssize_t
typedef|typedef
name|int
name|Py_ssize_t
typedef|;
end_typedef

begin_define
DECL|macro|PY_SSIZE_T_MAX
define|#
directive|define
name|PY_SSIZE_T_MAX
value|INT_MAX
end_define

begin_define
DECL|macro|PY_SSIZE_T_MIN
define|#
directive|define
name|PY_SSIZE_T_MIN
value|INT_MIN
end_define

begin_define
DECL|macro|PyInt_AsSsize_t (o)
define|#
directive|define
name|PyInt_AsSsize_t
parameter_list|(
name|o
parameter_list|)
value|PyInt_AsLong(o)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
name|G_BEGIN_DECLS
specifier|extern
name|PyObject
modifier|*
name|pygimp_error
decl_stmt|;
end_decl_stmt

begin_function_decl
name|PyObject
modifier|*
name|pygimp_param_to_tuple
parameter_list|(
name|int
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParam
modifier|*
name|pygimp_param_from_tuple
parameter_list|(
name|PyObject
modifier|*
name|args
parameter_list|,
specifier|const
name|GimpParamDef
modifier|*
name|ptype
parameter_list|,
name|int
name|nparams
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpPDB_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_pdb_check (v)
define|#
directive|define
name|pygimp_pdb_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpPDB_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_pdb_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpPDBFunction_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_pdb_function_check (v)
define|#
directive|define
name|pygimp_pdb_function_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpPDBFunction_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_pdb_function_new
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
specifier|const
name|char
modifier|*
name|blurb
parameter_list|,
specifier|const
name|char
modifier|*
name|help
parameter_list|,
specifier|const
name|char
modifier|*
name|author
parameter_list|,
specifier|const
name|char
modifier|*
name|copyright
parameter_list|,
specifier|const
name|char
modifier|*
name|date
parameter_list|,
name|GimpPDBProcType
name|proc_type
parameter_list|,
name|int
name|n_params
parameter_list|,
name|int
name|n_return_vals
parameter_list|,
name|GimpParamDef
modifier|*
name|params
parameter_list|,
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpImage_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_image_check (v)
define|#
directive|define
name|pygimp_image_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpImage_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_image_new
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpDisplay_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_display_check (v)
define|#
directive|define
name|pygimp_display_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpDisplay_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_display_new
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpItem_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_item_check (v)
define|#
directive|define
name|pygimp_item_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpItem_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_item_new
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpDrawable_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_drawable_check (v)
define|#
directive|define
name|pygimp_drawable_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpDrawable_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_drawable_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpLayer_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_layer_check (v)
define|#
directive|define
name|pygimp_layer_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpLayer_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_layer_new
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpChannel_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_channel_check (v)
define|#
directive|define
name|pygimp_channel_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpChannel_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_channel_new
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|struct|__anon2c3bc1910108
typedef|typedef
struct|struct
block|{
name|PyObject_HEAD
DECL|member|tile
name|GimpTile
modifier|*
name|tile
decl_stmt|;
DECL|member|drawable
name|PyGimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* we keep a reference to the drawable */
DECL|typedef|PyGimpTile
block|}
name|PyGimpTile
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpTile_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_tile_check (v)
define|#
directive|define
name|pygimp_tile_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpTile_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_tile_new
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|,
name|PyGimpDrawable
modifier|*
name|drw
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|struct|__anon2c3bc1910208
typedef|typedef
struct|struct
block|{
name|PyObject_HEAD
DECL|member|pr
name|GimpPixelRgn
name|pr
decl_stmt|;
DECL|member|drawable
name|PyGimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* keep the drawable around */
DECL|typedef|PyGimpPixelRgn
block|}
name|PyGimpPixelRgn
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpPixelRgn_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_pixel_rgn_check (v)
define|#
directive|define
name|pygimp_pixel_rgn_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpPixelRgn_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_pixel_rgn_new
parameter_list|(
name|PyGimpDrawable
modifier|*
name|drw
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|int
name|dirty
parameter_list|,
name|int
name|shadow
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|struct|__anon2c3bc1910308
typedef|typedef
struct|struct
block|{
name|PyObject_HEAD
DECL|member|para
name|GimpParasite
modifier|*
name|para
decl_stmt|;
DECL|typedef|PyGimpParasite
block|}
name|PyGimpParasite
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpParasite_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_parasite_check (v)
define|#
directive|define
name|pygimp_parasite_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpParasite_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_parasite_new
parameter_list|(
name|GimpParasite
modifier|*
name|para
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpVectors_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_vectors_check (v)
define|#
directive|define
name|pygimp_vectors_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpVectors_Type))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_vectors_new
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpVectorsStroke_Type
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpVectorsBezierStroke_Type
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon2c3bc1910408
typedef|typedef
struct|struct
block|{
name|PyObject_HEAD
DECL|member|pf
name|GimpPixelFetcher
modifier|*
name|pf
decl_stmt|;
DECL|member|drawable
name|PyGimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* keep the drawable around */
DECL|member|shadow
name|gboolean
name|shadow
decl_stmt|;
DECL|member|bg_color
name|GimpRGB
name|bg_color
decl_stmt|;
DECL|member|edge_mode
name|GimpPixelFetcherEdgeMode
name|edge_mode
decl_stmt|;
DECL|member|bpp
name|int
name|bpp
decl_stmt|;
DECL|typedef|PyGimpPixelFetcher
block|}
name|PyGimpPixelFetcher
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpPixelFetcher_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_pixel_fetcher_check (v)
define|#
directive|define
name|pygimp_pixel_fetcher_check
parameter_list|(
name|v
parameter_list|)
value|(PyObject_TypeCheck(v,&PyGimpPixelFetcher_Type))
end_define

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

end_unit

