begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_PIXMAP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_PIXMAP_H__
define|#
directive|define
name|__GIMP_BRUSH_PIXMAP_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_typedef
DECL|struct|_GimpBrushPixmap
typedef|typedef
struct|struct
name|_GimpBrushPixmap
block|{
DECL|member|gbrush
name|GimpBrush
name|gbrush
decl_stmt|;
DECL|member|pixmap_mask
name|TempBuf
modifier|*
name|pixmap_mask
decl_stmt|;
DECL|typedef|GimpBrushPixmap
block|}
name|GimpBrushPixmap
typedef|;
end_typedef

begin_typedef
DECL|struct|_GimpBrushPixmapClass
typedef|typedef
struct|struct
name|_GimpBrushPixmapClass
block|{
DECL|member|parent_class
name|GimpBrushClass
name|parent_class
decl_stmt|;
DECL|member|generate
name|void
function_decl|(
modifier|*
name|generate
function_decl|)
parameter_list|(
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|)
function_decl|;
DECL|typedef|GimpBrushPixmapClass
block|}
name|GimpBrushPixmapClass
typedef|;
end_typedef

begin_comment
comment|/* object stuff */
end_comment

begin_define
DECL|macro|GIMP_TYPE_BRUSH_PIXMAP
define|#
directive|define
name|GIMP_TYPE_BRUSH_PIXMAP
value|(gimp_brush_pixmap_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_PIXMAP (obj)
define|#
directive|define
name|GIMP_BRUSH_PIXMAP
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_PIXMAP, GimpBrushPixmap))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_PIXMAP (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_PIXMAP
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH_PIXMAP))
end_define

begin_function_decl
name|GtkType
name|gimp_brush_pixmap_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushPixmap
modifier|*
name|gimp_brush_pixmap_new
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushPixmap
modifier|*
name|gimp_brush_pixmap_load
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_brush_pixmap_get_pixmap
parameter_list|(
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPPIXMAPBRUSH_H__ */
end_comment

end_unit

