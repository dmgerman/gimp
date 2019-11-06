begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2016, 2017 Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__METADATA_TAGS_H__
end_ifndef

begin_define
DECL|macro|__METADATA_TAGS_H__
define|#
directive|define
name|__METADATA_TAGS_H__
end_define

begin_include
include|#
directive|include
file|"metadata-misc.h"
end_include

begin_define
DECL|macro|TAG_TYPE_XMP
define|#
directive|define
name|TAG_TYPE_XMP
value|1
end_define

begin_define
DECL|macro|TAG_TYPE_EXIF
define|#
directive|define
name|TAG_TYPE_EXIF
value|2
end_define

begin_define
DECL|macro|TAG_TYPE_IPTC
define|#
directive|define
name|TAG_TYPE_IPTC
value|3
end_define

begin_enum
enum|enum
DECL|enum|__anon2b818eb60103
block|{
DECL|enumerator|GIMP_XMP_NONE
name|GIMP_XMP_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_XMP_TEXT
name|GIMP_XMP_TEXT
block|,
DECL|enumerator|GIMP_XMP_BAG
name|GIMP_XMP_BAG
block|,
DECL|enumerator|GIMP_XMP_SEQ
name|GIMP_XMP_SEQ
block|,
DECL|enumerator|GIMP_XMP_LANG
name|GIMP_XMP_LANG
block|,
DECL|enumerator|GIMP_XMP_ALT
name|GIMP_XMP_ALT
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60203
block|{
DECL|enumerator|COL_LICENSOR_NAME
name|COL_LICENSOR_NAME
init|=
literal|0
block|,
DECL|enumerator|COL_LICENSOR_ID
name|COL_LICENSOR_ID
block|,
DECL|enumerator|COL_LICENSOR_PHONE1
name|COL_LICENSOR_PHONE1
block|,
DECL|enumerator|COL_LICENSOR_PHONE_TYPE1
name|COL_LICENSOR_PHONE_TYPE1
block|,
DECL|enumerator|COL_LICENSOR_PHONE2
name|COL_LICENSOR_PHONE2
block|,
DECL|enumerator|COL_LICENSOR_PHONE_TYPE2
name|COL_LICENSOR_PHONE_TYPE2
block|,
DECL|enumerator|COL_LICENSOR_EMAIL
name|COL_LICENSOR_EMAIL
block|,
DECL|enumerator|COL_LICENSOR_WEB
name|COL_LICENSOR_WEB
block|,
DECL|enumerator|COL_LICENSOR_NUM_COLS
name|COL_LICENSOR_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60303
block|{
DECL|enumerator|COL_CR_OWNER_NAME
name|COL_CR_OWNER_NAME
init|=
literal|0
block|,
DECL|enumerator|COL_CR_OWNER_ID
name|COL_CR_OWNER_ID
block|,
DECL|enumerator|COL_CR_OWNER_NUM_COLS
name|COL_CR_OWNER_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60403
block|{
DECL|enumerator|COL_IMG_CR8_NAME
name|COL_IMG_CR8_NAME
init|=
literal|0
block|,
DECL|enumerator|COL_IMG_CR8_ID
name|COL_IMG_CR8_ID
block|,
DECL|enumerator|COL_IMG_CR8_NUM_COLS
name|COL_IMG_CR8_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60503
block|{
DECL|enumerator|COL_AOO_TITLE
name|COL_AOO_TITLE
init|=
literal|0
block|,
DECL|enumerator|COL_AOO_DATE_CREAT
name|COL_AOO_DATE_CREAT
block|,
DECL|enumerator|COL_AOO_CREATOR
name|COL_AOO_CREATOR
block|,
DECL|enumerator|COL_AOO_SOURCE
name|COL_AOO_SOURCE
block|,
DECL|enumerator|COL_AOO_SRC_INV_ID
name|COL_AOO_SRC_INV_ID
block|,
DECL|enumerator|COL_AOO_CR_NOT
name|COL_AOO_CR_NOT
block|,
DECL|enumerator|COL_AOO_NUM_COLS
name|COL_AOO_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60603
block|{
DECL|enumerator|COL_REGSITRY_ORG_ID
name|COL_REGSITRY_ORG_ID
init|=
literal|0
block|,
DECL|enumerator|COL_REGSITRY_ITEM_ID
name|COL_REGSITRY_ITEM_ID
block|,
DECL|enumerator|COL_REGSITRY_NUM_COLS
name|COL_REGSITRY_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60703
block|{
DECL|enumerator|COL_LOC_SHO_SUB_LOC
name|COL_LOC_SHO_SUB_LOC
init|=
literal|0
block|,
DECL|enumerator|COL_LOC_SHO_CITY
name|COL_LOC_SHO_CITY
block|,
DECL|enumerator|COL_LOC_SHO_STATE_PROV
name|COL_LOC_SHO_STATE_PROV
block|,
DECL|enumerator|COL_LOC_SHO_CNTRY
name|COL_LOC_SHO_CNTRY
block|,
DECL|enumerator|COL_LOC_SHO_CNTRY_ISO
name|COL_LOC_SHO_CNTRY_ISO
block|,
DECL|enumerator|COL_LOC_SHO_CNTRY_WRLD_REG
name|COL_LOC_SHO_CNTRY_WRLD_REG
block|,
DECL|enumerator|COL_LOC_SHO_NUM_COLS
name|COL_LOC_SHO_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60803
block|{
DECL|enumerator|COL_ORG_IMG_CODE
name|COL_ORG_IMG_CODE
init|=
literal|0
block|,
DECL|enumerator|ORG_IMG_CODE_REL_NUM_COLS
name|ORG_IMG_CODE_REL_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60903
block|{
DECL|enumerator|COL_ORG_IMG_NAME
name|COL_ORG_IMG_NAME
init|=
literal|0
block|,
DECL|enumerator|ORG_IMG_NAME_REL_NUM_COLS
name|ORG_IMG_NAME_REL_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60a03
block|{
DECL|enumerator|COL_MOD_REL_ID
name|COL_MOD_REL_ID
init|=
literal|0
block|,
DECL|enumerator|MOD_REL_NUM_COLS
name|MOD_REL_NUM_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b818eb60b03
block|{
DECL|enumerator|COL_PROP_REL_ID
name|COL_PROP_REL_ID
init|=
literal|0
block|,
DECL|enumerator|PROP_REL_NUM_COLS
name|PROP_REL_NUM_COLS
block|}
enum|;
end_enum

begin_decl_stmt
specifier|extern
specifier|const
name|metadata_tag
name|default_metadata_tags
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_default_metadata_tags
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|metadata_tag
name|equivalent_metadata_tags
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_equivalent_metadata_tags
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Digital Source Type Combobox Items  * http://cv.iptc.org/newscodes/digitalsourcetype/  */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|combobox_str_tag
name|digitalsourcetype
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_digitalsourcetype
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Model Release Status Combobox Items  * http://ns.useplus.org/LDF/ldf-XMPSpecification#ModelReleaseStatus  */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|combobox_str_tag
name|modelreleasestatus
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_modelreleasestatus
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Property Release Status Combobox Items  * http://ns.useplus.org/LDF/ldf-XMPSpecification#PropertyReleaseStatus  */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|combobox_str_tag
name|propertyreleasestatus
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_propertyreleasestatus
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Minor Model Age Disclosure Combobox Items  * http://ns.useplus.org/LDF/ldf-XMPSpecification#MinorModelAgeDisclosure  */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|combobox_str_tag
name|minormodelagedisclosure
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_minormodelagedisclosure
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Urgency */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|urgency
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_urgency
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Marked */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|combobox_int_tag
name|marked
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_marked
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Phone Types */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|combobox_str_tag
name|phone_types
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_phone_types
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* DICOM Patient Sex  * http://dicomlookup.com/lookup.asp?sw=Ttable&q=C.7-1  * http://www.sno.phy.queensu.ca/~phil/exiftool/TagNames/XMP.html#DICOM  * https://dicomiseasy.blogspot.ca/2011/11/introduction-to-dicom-chapter-iii-dicom.html  * http://dicom.nema.org/standard.html  */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|combobox_str_tag
name|dicom
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_dicom
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* GPS Altitude Ref */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|gpsaltref
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_gpsaltref
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* GPS Latitude Ref */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|gpslatref
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_gpslatref
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* GPS Longitude Ref */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|gpslngref
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_gpslngref
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* GPS Measurement System */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|gpsaltsys
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_gpsaltsys
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|TranslateHeaderTag
name|creatorContactInfoHeader
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|TranslateTag
name|creatorContactInfoTags
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|TranslateHeaderTag
name|locationCreationInfoHeader
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|TranslateTag
name|locationCreationInfoTags
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|TranslateHeaderTag
name|imageSupplierInfoHeader
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|TranslateTag
name|imageSupplierInfoTags
index|[]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Plus and IPTC extension tags */
end_comment

begin_define
DECL|macro|LICENSOR_HEADER
define|#
directive|define
name|LICENSOR_HEADER
value|"Xmp.plus.Licensor"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|licensor
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_licensor
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|USE_TAGS
end_ifdef

begin_define
DECL|macro|IMAGESUPPLIER_HEADER
define|#
directive|define
name|IMAGESUPPLIER_HEADER
value|"Xmp.plus.ImageSupplier"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|imagesupplier
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_imagesupplier
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|IMAGECREATOR_HEADER
define|#
directive|define
name|IMAGECREATOR_HEADER
value|"Xmp.plus.ImageCreator"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|imagecreator
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_imagecreator
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|COPYRIGHTOWNER_HEADER
define|#
directive|define
name|COPYRIGHTOWNER_HEADER
value|"Xmp.plus.CopyrightOwner"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|copyrightowner
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_copyrightowner
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|REGISTRYID_HEADER
define|#
directive|define
name|REGISTRYID_HEADER
value|"Xmp.iptcExt.RegistryId"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|registryid
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_registryid
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|ARTWORKOROBJECT_HEADER
define|#
directive|define
name|ARTWORKOROBJECT_HEADER
value|"Xmp.iptcExt.ArtworkOrObject"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|artworkorobject
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_artworkorobject
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|LOCATIONSHOWN_HEADER
define|#
directive|define
name|LOCATIONSHOWN_HEADER
value|"Xmp.iptcExt.LocationShown"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|locationshown
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_locationshown
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|USE_TAGS
end_ifdef

begin_define
DECL|macro|LOCATIONCREATED_HEADER
define|#
directive|define
name|LOCATIONCREATED_HEADER
value|"Xmp.iptcExt.LocationCreated"
end_define

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|locationcreated
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gint
name|n_locationcreated
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __METADATA_TAGS_H__ */
end_comment

end_unit

