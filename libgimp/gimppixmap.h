begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppixmap.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PIXMAP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PIXMAP_H__
define|#
directive|define
name|__GIMP_PIXMAP_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

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
DECL|macro|GIMP_TYPE_PIXMAP
define|#
directive|define
name|GIMP_TYPE_PIXMAP
value|(gimp_pixmap_get_type ())
DECL|macro|GIMP_PIXMAP (obj)
define|#
directive|define
name|GIMP_PIXMAP
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_PIXMAP, GimpPixmap))
DECL|macro|GIMP_PIXMAP_CLASS (klass)
define|#
directive|define
name|GIMP_PIXMAP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PIXMAP, GimpPixmapClass))
DECL|macro|GIMP_IS_PIXMAP (obj)
define|#
directive|define
name|GIMP_IS_PIXMAP
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_PIXMAP))
DECL|macro|GIMP_IS_PIXMAP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PIXMAP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PIXMAP))
DECL|typedef|GimpPixmap
typedef|typedef
name|struct
name|_GimpPixmap
name|GimpPixmap
typedef|;
DECL|typedef|GimpPixmapClass
typedef|typedef
name|struct
name|_GimpPixmapClass
name|GimpPixmapClass
typedef|;
DECL|struct|_GimpPixmapClass
struct|struct
name|_GimpPixmapClass
block|{
DECL|member|parent_class
name|GtkPixmapClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|GtkType
name|gimp_pixmap_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_pixmap_new
parameter_list|(
name|gchar
modifier|*
modifier|*
name|xpm_data
parameter_list|)
function_decl|;
name|void
name|gimp_pixmap_set
parameter_list|(
name|GimpPixmap
modifier|*
name|pixmap
parameter_list|,
name|gchar
modifier|*
modifier|*
name|xpm_data
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
comment|/* __GIMP_PIXMAP_H__ */
end_comment

end_unit

