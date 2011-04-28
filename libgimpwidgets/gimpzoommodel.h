begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpzoommodel.h  * Copyright (C) 2005  David Odin<dindinx@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ZOOM_MODEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ZOOM_MODEL_H__
define|#
directive|define
name|__GIMP_ZOOM_MODEL_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_ZOOM_MODEL
define|#
directive|define
name|GIMP_TYPE_ZOOM_MODEL
value|(gimp_zoom_model_get_type ())
end_define

begin_define
DECL|macro|GIMP_ZOOM_MODEL (obj)
define|#
directive|define
name|GIMP_ZOOM_MODEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ZOOM_MODEL, GimpZoomModel))
end_define

begin_define
DECL|macro|GIMP_ZOOM_MODEL_CLASS (klass)
define|#
directive|define
name|GIMP_ZOOM_MODEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ZOOM_MODEL, GimpZoomModelClass))
end_define

begin_define
DECL|macro|GIMP_IS_ZOOM_MODEL (obj)
define|#
directive|define
name|GIMP_IS_ZOOM_MODEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ZOOM_MODEL))
end_define

begin_define
DECL|macro|GIMP_IS_ZOOM_MODEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ZOOM_MODEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ZOOM_MODEL))
end_define

begin_define
DECL|macro|GIMP_ZOOM_MODEL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ZOOM_MODEL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ZOOM_MODEL, GimpZoomModel))
end_define

begin_typedef
DECL|typedef|GimpZoomModelClass
typedef|typedef
name|struct
name|_GimpZoomModelClass
name|GimpZoomModelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpZoomModel
struct|struct
name|_GimpZoomModel
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpZoomModelClass
struct|struct
name|_GimpZoomModelClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
DECL|member|zoomed
name|void
function_decl|(
modifier|*
name|zoomed
function_decl|)
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|gdouble
name|old_factor
parameter_list|,
name|gdouble
name|new_factor
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_zoom_model_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpZoomModel
modifier|*
name|gimp_zoom_model_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_zoom_model_set_range
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|gdouble
name|min
parameter_list|,
name|gdouble
name|max
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_zoom_model_zoom
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|GimpZoomType
name|zoom_type
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_zoom_model_get_factor
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_zoom_model_get_fraction
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|gint
modifier|*
name|numerator
parameter_list|,
name|gint
modifier|*
name|denominator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_zoom_button_new
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|GimpZoomType
name|zoom_type
parameter_list|,
name|GtkIconSize
name|icon_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_zoom_model_zoom_step
parameter_list|(
name|GimpZoomType
name|zoom_type
parameter_list|,
name|gdouble
name|scale
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
comment|/* __GIMP_ZOOM_MODEL_H__ */
end_comment

end_unit

