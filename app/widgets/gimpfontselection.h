begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpfontselection.h  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FONT_SELECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FONT_SELECTION_H__
define|#
directive|define
name|__GIMP_FONT_SELECTION_H__
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
DECL|macro|GIMP_TYPE_FONT_SELECTION
define|#
directive|define
name|GIMP_TYPE_FONT_SELECTION
value|(gimp_font_selection_get_type ())
DECL|macro|GIMP_FONT_SELECTION (obj)
define|#
directive|define
name|GIMP_FONT_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FONT_SELECTION, GimpFontSelection))
DECL|macro|GIMP_FONT_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_FONT_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FONT_SELECTION, GimpFontSelectionClass))
DECL|macro|GIMP_IS_FONT_SELECTION (obj)
define|#
directive|define
name|GIMP_IS_FONT_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_FONT_SELECTION))
DECL|macro|GIMP_IS_FONT_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FONT_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FONT_SELECTION))
DECL|typedef|GimpFontSelectionClass
typedef|typedef
name|struct
name|_GimpFontSelectionClass
name|GimpFontSelectionClass
typedef|;
DECL|struct|_GimpFontSelection
struct|struct
name|_GimpFontSelection
block|{
DECL|member|parent_instance
name|GtkHBox
name|parent_instance
decl_stmt|;
DECL|member|context
name|PangoContext
modifier|*
name|context
decl_stmt|;
DECL|member|font_desc
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
DECL|member|entry
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpFontSelectionClass
struct|struct
name|_GimpFontSelectionClass
block|{
DECL|member|parent_class
name|GtkHBoxClass
name|parent_class
decl_stmt|;
DECL|member|font_changed
name|void
function_decl|(
modifier|*
name|font_changed
function_decl|)
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
parameter_list|)
function_decl|;
block|}
struct|;
name|GType
name|gimp_font_selection_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_font_selection_new
parameter_list|(
name|PangoContext
modifier|*
name|context
parameter_list|)
function_decl|;
name|gboolean
name|gimp_font_selection_set_fontname
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|)
function_decl|;
specifier|const
name|gchar
modifier|*
name|gimp_font_selection_get_fontname
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
parameter_list|)
function_decl|;
name|void
name|gimp_font_selection_set_font_desc
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
parameter_list|,
specifier|const
name|PangoFontDescription
modifier|*
name|font_desc
parameter_list|)
function_decl|;
name|PangoFontDescription
modifier|*
name|gimp_font_selection_get_font_desc
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
parameter_list|)
function_decl|;
name|void
name|gimp_font_selection_font_changed
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
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
comment|/* __GIMP_FONT_SELECTION_H__ */
end_comment

end_unit

