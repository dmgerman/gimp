begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 1997-2002  James Henstridge<james@daa.com.au>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
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

begin_if
if|#
directive|if
name|PY_VERSION_HEX
operator|<
literal|0x020300F0
end_if

begin_define
DECL|macro|PyBool_FromLong (v)
define|#
directive|define
name|PyBool_FromLong
parameter_list|(
name|v
parameter_list|)
value|PyInt_FromLong((v) ? 1L : 0L);
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

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

begin_typedef
DECL|struct|__anon2961ab920108
typedef|typedef
struct|struct
block|{
name|PyObject_HEAD
DECL|member|ID
name|gint32
name|ID
decl_stmt|;
DECL|typedef|PyGimpImage
block|}
name|PyGimpImage
typedef|;
end_typedef

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

begin_typedef
DECL|struct|__anon2961ab920208
typedef|typedef
struct|struct
block|{
name|PyObject_HEAD
DECL|member|ID
name|gint32
name|ID
decl_stmt|;
DECL|typedef|PyGimpDisplay
block|}
name|PyGimpDisplay
typedef|;
end_typedef

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

begin_typedef
DECL|struct|__anon2961ab920308
typedef|typedef
struct|struct
block|{
name|PyObject_HEAD
DECL|member|ID
name|gint32
name|ID
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|typedef|PyGimpDrawable
DECL|typedef|PyGimpLayer
DECL|typedef|PyGimpChannel
block|}
name|PyGimpDrawable
operator|,
name|PyGimpLayer
operator|,
name|PyGimpChannel
typedef|;
end_typedef

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
DECL|struct|__anon2961ab920408
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
DECL|struct|__anon2961ab920508
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
DECL|struct|__anon2961ab920608
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
value|(PyObject_TypeCheck(v,&Paratype))
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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

end_unit

