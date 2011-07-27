begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppageselector.h  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_PAGE_SELECTOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAGE_SELECTOR_H__
define|#
directive|define
name|__GIMP_PAGE_SELECTOR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PAGE_SELECTOR
define|#
directive|define
name|GIMP_TYPE_PAGE_SELECTOR
value|(gimp_page_selector_get_type ())
end_define

begin_define
DECL|macro|GIMP_PAGE_SELECTOR (obj)
define|#
directive|define
name|GIMP_PAGE_SELECTOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PAGE_SELECTOR, GimpPageSelector))
end_define

begin_define
DECL|macro|GIMP_PAGE_SELECTOR_CLASS (klass)
define|#
directive|define
name|GIMP_PAGE_SELECTOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PAGE_SELECTOR, GimpPageSelectorClass))
end_define

begin_define
DECL|macro|GIMP_IS_PAGE_SELECTOR (obj)
define|#
directive|define
name|GIMP_IS_PAGE_SELECTOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PAGE_SELECTOR))
end_define

begin_define
DECL|macro|GIMP_IS_PAGE_SELECTOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PAGE_SELECTOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PAGE_SELECTOR))
end_define

begin_define
DECL|macro|GIMP_PAGE_SELECTOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PAGE_SELECTOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PAGE_SELECTOR, GimpPageSelectorClass))
end_define

begin_typedef
DECL|typedef|GimpPageSelectorClass
typedef|typedef
name|struct
name|_GimpPageSelectorClass
name|GimpPageSelectorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPageSelector
struct|struct
name|_GimpPageSelector
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPageSelectorClass
struct|struct
name|_GimpPageSelectorClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|selection_changed
name|void
function_decl|(
modifier|*
name|selection_changed
function_decl|)
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
DECL|member|activate
name|void
function_decl|(
modifier|*
name|activate
function_decl|)
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
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
name|gimp_page_selector_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_page_selector_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_set_n_pages
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|n_pages
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_page_selector_get_n_pages
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_set_target
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|GimpPageSelectorTarget
name|target
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPageSelectorTarget
name|gimp_page_selector_get_target
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_set_page_thumbnail
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|page_no
parameter_list|,
name|GdkPixbuf
modifier|*
name|thumbnail
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_page_selector_get_page_thumbnail
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|page_no
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_set_page_label
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|page_no
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_page_selector_get_page_label
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|page_no
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_select_all
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_unselect_all
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_select_page
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|page_no
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_unselect_page
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|page_no
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_page_selector_page_is_selected
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
name|page_no
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
modifier|*
name|gimp_page_selector_get_selected_pages
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
name|gint
modifier|*
name|n_selected_pages
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_page_selector_select_range
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|gchar
modifier|*
name|range
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_page_selector_get_selected_range
parameter_list|(
name|GimpPageSelector
modifier|*
name|selector
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
comment|/* __GIMP_PAGE_SELECTOR_H__ */
end_comment

end_unit

