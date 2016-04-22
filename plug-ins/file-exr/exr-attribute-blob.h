begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*     This file is part of GIMP,     copyright (c) 2012 johannes hanika      GIMP is free software: you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation, either version 3 of the License, or     (at your option) any later version.      GIMP is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with GIMP.  If not, see<http://www.gnu.org/licenses/>. */
end_comment

begin_pragma
pragma|#
directive|pragma
name|once
end_pragma

begin_include
include|#
directive|include
file|<ciso646>
end_include

begin_include
include|#
directive|include
file|<inttypes.h>
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|_LIBCPP_VERSION
argument_list|)
end_if

begin_include
include|#
directive|include
file|<memory>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<tr1/memory>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<OpenEXR/ImfFrameBuffer.h>
end_include

begin_include
include|#
directive|include
file|<OpenEXR/ImfTestFile.h>
end_include

begin_include
include|#
directive|include
file|<OpenEXR/ImfInputFile.h>
end_include

begin_include
include|#
directive|include
file|<OpenEXR/ImfTiledInputFile.h>
end_include

begin_include
include|#
directive|include
file|<OpenEXR/ImfChannelList.h>
end_include

begin_include
include|#
directive|include
file|<OpenEXR/ImfStandardAttributes.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|OPENEXR_IMF_INTERNAL_NAMESPACE
end_ifdef

begin_define
DECL|macro|IMF_NS
define|#
directive|define
name|IMF_NS
value|OPENEXR_IMF_INTERNAL_NAMESPACE
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|IMF_NS
define|#
directive|define
name|IMF_NS
value|Imf
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|// this stores our exif data as a blob.
end_comment

begin_expr_stmt
DECL|struct|array_deleter
name|template
operator|<
name|typename
name|T
operator|>
expr|struct
name|array_deleter
block|{
DECL|function|operator ()
name|void
name|operator
argument_list|()
operator|(
name|T
specifier|const
operator|*
name|p
operator|)
block|{
name|delete
index|[]
name|p
block|;   }
block|}
expr_stmt|;
end_expr_stmt

begin_decl_stmt
name|namespace
name|IMF_NS
block|{
name|class
name|Blob
block|{
name|public
label|:
DECL|function|Blob ()
name|Blob
argument_list|()
operator|:
name|size
argument_list|(
literal|0
argument_list|)
operator|,
name|data
argument_list|(
argument|(uint8_t *)NULL
argument_list|)
block|{   }
DECL|function|Blob (uint32_t _size,uint8_t * _data)
name|Blob
argument_list|(
argument|uint32_t _size
argument_list|,
argument|uint8_t *_data
argument_list|)
operator|:
name|size
argument_list|(
argument|_size
argument_list|)
block|{
name|uint8_t
operator|*
name|tmp_ptr
operator|=
name|new
name|uint8_t
index|[
name|_size
index|]
block|;
name|memcpy
argument_list|(
name|tmp_ptr
argument_list|,
name|_data
argument_list|,
name|_size
argument_list|)
block|;
name|data
operator|.
name|reset
argument_list|(
name|tmp_ptr
argument_list|,
name|array_deleter
operator|<
name|uint8_t
operator|>
operator|(
operator|)
argument_list|)
block|;   }
DECL|variable|size
name|uint32_t
name|size
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|_LIBCPP_VERSION
argument_list|)
DECL|variable|data
name|std
operator|::
name|shared_ptr
operator|<
name|uint8_t
operator|>
name|data
expr_stmt|;
else|#
directive|else
DECL|variable|data
name|std
operator|::
name|tr1
operator|::
name|shared_ptr
operator|<
name|uint8_t
operator|>
name|data
expr_stmt|;
endif|#
directive|endif
block|}
empty_stmt|;
DECL|typedef|BlobAttribute
typedef|typedef
name|IMF_NS
operator|::
name|TypedAttribute
operator|<
name|IMF_NS
operator|::
name|Blob
operator|>
name|BlobAttribute
expr_stmt|;
DECL|function|staticTypeName ()
name|template
operator|<
operator|>
specifier|const
name|char
operator|*
name|BlobAttribute
operator|::
name|staticTypeName
argument_list|()
block|{
return|return
literal|"blob"
return|;
block|}
DECL|function|writeValueTo (OStream & os,int version)
name|template
operator|<
operator|>
name|void
name|BlobAttribute
operator|::
name|writeValueTo
argument_list|(
argument|OStream&os
argument_list|,
argument|int version
argument_list|)
specifier|const
block|{
name|Xdr
operator|::
name|write
operator|<
name|StreamIO
operator|>
operator|(
name|os
operator|,
name|_value
operator|.
name|size
operator|)
block|;
name|Xdr
operator|::
name|write
operator|<
name|StreamIO
operator|>
operator|(
name|os
operator|,
operator|(
name|char
operator|*
operator|)
operator|(
name|_value
operator|.
name|data
operator|.
name|get
argument_list|()
operator|)
operator|,
name|_value
operator|.
name|size
operator|)
block|; }
DECL|function|readValueFrom (IStream & is,int size,int version)
name|template
operator|<
operator|>
name|void
name|BlobAttribute
operator|::
name|readValueFrom
argument_list|(
argument|IStream&is
argument_list|,
argument|int size
argument_list|,
argument|int version
argument_list|)
block|{
name|Xdr
operator|::
name|read
operator|<
name|StreamIO
operator|>
operator|(
name|is
operator|,
name|_value
operator|.
name|size
operator|)
block|;
name|_value
operator|.
name|data
operator|.
name|reset
argument_list|(
argument|new uint8_t[_value.size]
argument_list|,
argument|array_deleter<uint8_t>()
argument_list|)
block|;
name|Xdr
operator|::
name|read
operator|<
name|StreamIO
operator|>
operator|(
name|is
operator|,
operator|(
name|char
operator|*
operator|)
operator|(
name|_value
operator|.
name|data
operator|.
name|get
argument_list|()
operator|)
operator|,
name|_value
operator|.
name|size
operator|)
block|; }
block|}
end_decl_stmt

end_unit

