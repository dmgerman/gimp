begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RULER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RULER_H__
define|#
directive|define
name|__GIMP_RULER_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_RULER
define|#
directive|define
name|GIMP_TYPE_RULER
value|(gimp_ruler_get_type ())
end_define

begin_define
DECL|macro|GIMP_RULER (obj)
define|#
directive|define
name|GIMP_RULER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RULER, GimpRuler))
end_define

begin_define
DECL|macro|GIMP_RULER_CLASS (klass)
define|#
directive|define
name|GIMP_RULER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RULER, GimpRulerClass))
end_define

begin_define
DECL|macro|GIMP_IS_RULER (obj)
define|#
directive|define
name|GIMP_IS_RULER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_RULER))
end_define

begin_define
DECL|macro|GIMP_IS_RULER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_RULER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_RULER))
end_define

begin_define
DECL|macro|GIMP_RULER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_RULER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_RULER, GimpRulerClass))
end_define

begin_typedef
DECL|typedef|GimpRulerClass
typedef|typedef
name|struct
name|_GimpRulerClass
name|GimpRulerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRulerMetric
typedef|typedef
name|struct
name|_GimpRulerMetric
name|GimpRulerMetric
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRuler
struct|struct
name|_GimpRuler
block|{
DECL|member|parent_instance
name|GtkWidget
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpRulerClass
struct|struct
name|_GimpRulerClass
block|{
DECL|member|parent_class
name|GtkWidgetClass
name|parent_class
decl_stmt|;
DECL|member|draw_ticks
name|void
function_decl|(
modifier|*
name|draw_ticks
function_decl|)
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
DECL|member|draw_pos
name|void
function_decl|(
modifier|*
name|draw_pos
function_decl|)
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
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

begin_struct
DECL|struct|_GimpRulerMetric
struct|struct
name|_GimpRulerMetric
block|{
DECL|member|metric_name
name|gchar
modifier|*
name|metric_name
decl_stmt|;
DECL|member|abbrev
name|gchar
modifier|*
name|abbrev
decl_stmt|;
comment|/* This should be points_per_unit. This is the size of the unit    * in 1/72nd's of an inch and has nothing to do with screen pixels */
DECL|member|pixels_per_unit
name|gdouble
name|pixels_per_unit
decl_stmt|;
DECL|member|ruler_scale
name|gdouble
name|ruler_scale
index|[
literal|10
index|]
decl_stmt|;
DECL|member|subdivide
name|gint
name|subdivide
index|[
literal|5
index|]
decl_stmt|;
comment|/* five possible modes of subdivision */
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_ruler_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_ruler_set_metric
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|,
name|GtkMetricType
name|metric
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ruler_set_range
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gdouble
name|position
parameter_list|,
name|gdouble
name|max_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ruler_draw_ticks
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ruler_draw_pos
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkMetricType
name|gimp_ruler_get_metric
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ruler_get_range
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|,
name|gdouble
modifier|*
name|lower
parameter_list|,
name|gdouble
modifier|*
name|upper
parameter_list|,
name|gdouble
modifier|*
name|position
parameter_list|,
name|gdouble
modifier|*
name|max_size
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GdkDrawable
modifier|*
name|_gimp_ruler_get_backing_store
argument_list|(
name|GimpRuler
operator|*
name|ruler
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GimpRulerMetric
modifier|*
name|_gimp_ruler_get_metric
argument_list|(
name|GimpRuler
operator|*
name|ruler
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RULER_H__ */
end_comment

end_unit

