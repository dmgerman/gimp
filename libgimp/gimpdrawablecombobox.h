begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawablecombobox.h  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_COMBO_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_COMBO_BOX_H__
define|#
directive|define
name|__GIMP_DRAWABLE_COMBO_BOX_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE_COMBO_BOX
define|#
directive|define
name|GIMP_TYPE_DRAWABLE_COMBO_BOX
value|(gimp_drawable_combo_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_DRAWABLE_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DRAWABLE_COMBO_BOX, GimpDrawableComboBox))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_IS_DRAWABLE_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DRAWABLE_COMBO_BOX)
end_define

begin_define
DECL|macro|GIMP_TYPE_CHANNEL_COMBO_BOX
define|#
directive|define
name|GIMP_TYPE_CHANNEL_COMBO_BOX
value|(gimp_channel_combo_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_CHANNEL_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_CHANNEL_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CHANNEL_COMBO_BOX, GimpChannelComboBox))
end_define

begin_define
DECL|macro|GIMP_IS_CHANNEL_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_IS_CHANNEL_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CHANNEL_COMBO_BOX)
end_define

begin_define
DECL|macro|GIMP_TYPE_LAYER_COMBO_BOX
define|#
directive|define
name|GIMP_TYPE_LAYER_COMBO_BOX
value|(gimp_layer_combo_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_LAYER_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LAYER_COMBO_BOX, GimpLayerComboBox))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_IS_LAYER_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LAYER_COMBO_BOX)
end_define

begin_typedef
DECL|typedef|GimpDrawableConstraintFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpDrawableConstraintFunc
function_decl|)
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_drawable_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GType
name|gimp_channel_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GType
name|gimp_layer_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_drawable_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_channel_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_layer_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
name|constraint
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
comment|/* __GIMP_DRAWABLE_COMBO_BOX_H__ */
end_comment

end_unit

