begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpguides_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GUIDES_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GUIDES_PDB_H__
define|#
directive|define
name|__GIMP_GUIDES_PDB_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
name|gint32
name|gimp_image_add_hguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|yposition
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_add_vguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|xposition
parameter_list|)
function_decl|;
name|void
name|gimp_image_delete_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_find_next_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
function_decl|;
name|GOrientation
name|gimp_image_get_guide_orientation
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_get_guide_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GUIDES_PDB_H__ */
end_comment

end_unit

