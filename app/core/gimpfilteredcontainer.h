begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpfilteredcontainer.h  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILTERED_CONTAINER_H__
end_ifndef

begin_define
define|#
directive|define
name|__GIMP_FILTERED_CONTAINER_H__
end_define

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_define
define|#
directive|define
name|GIMP_TYPE_FILTERED_CONTAINER
value|(gimp_filtered_container_get_type ())
end_define

begin_define
define|#
directive|define
name|GIMP_FILTERED_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILTERED_CONTAINER, GimpFilteredContainer))
end_define

begin_define
define|#
directive|define
name|GIMP_FILTERED_CONTAINER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILTERED_CONTAINER, GimpFilteredContainerClass))
end_define

begin_define
define|#
directive|define
name|GIMP_IS_FILTERED_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILTERED_CONTAINER))
end_define

begin_define
define|#
directive|define
name|GIMP_IS_FILTERED_CONTAINER_CLASS
parameter_list|(
name|class
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((class), GIMP_TYPE_FILTERED_CONTAINER))
end_define

begin_define
define|#
directive|define
name|GIMP_FILTERED_CONTAINER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILTERED_CONTAINER, GimpFilteredContainerClass))
end_define

begin_endif
unit|typedef struct _GimpFilteredContainerClass GimpFilteredContainerClass;  struct _GimpFilteredContainer {   GimpList       parent_instance;    GimpContainer *src_container;   GList         *filter;   GHashTable    *tag_ref_counts;   gint           tag_count; };  struct _GimpFilteredContainerClass {   GimpContainerClass  parent_class;    void (* tag_count_changed) (GimpFilteredContainer *container,                               gint                   count); };   GType           gimp_filtered_container_get_type      (void) G_GNUC_CONST;  GimpContainer * gimp_filtered_container_new           (GimpContainer         *src_container,                                                        GCompareFunc           sort_func);  void            gimp_filtered_container_set_filter    (GimpFilteredContainer *filtered_container,                                                        GList                 *tags); const GList   * gimp_filtered_container_get_filter    (GimpFilteredContainer *filtered_container);  gint            gimp_filtered_container_get_tag_count (GimpFilteredContainer *container);
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILTERED_CONTAINER_H__ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

