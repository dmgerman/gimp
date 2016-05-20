begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-darktable.c -- raw file format plug-in that uses darktable  * Copyright (C) 2016 Tobias Ellinghaus<me@houz.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* These are the raw formats that file-darktable will register */
end_comment

begin_typedef
DECL|typedef|FileFormat
typedef|typedef
name|struct
name|_FileFormat
name|FileFormat
typedef|;
end_typedef

begin_struct
DECL|struct|_FileFormat
struct|struct
name|_FileFormat
block|{
DECL|member|file_type
specifier|const
name|gchar
modifier|*
name|file_type
decl_stmt|;
DECL|member|mime_type
specifier|const
name|gchar
modifier|*
name|mime_type
decl_stmt|;
DECL|member|extensions
specifier|const
name|gchar
modifier|*
name|extensions
decl_stmt|;
DECL|member|magic
specifier|const
name|gchar
modifier|*
name|magic
decl_stmt|;
DECL|member|load_proc
specifier|const
name|gchar
modifier|*
name|load_proc
decl_stmt|;
DECL|member|load_blurb
specifier|const
name|gchar
modifier|*
name|load_blurb
decl_stmt|;
DECL|member|load_help
specifier|const
name|gchar
modifier|*
name|load_help
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* some magic numbers taken from  * http://www.garykessler.net/library/file_sigs.html  *  * see also  * http://fileformats.archiveteam.org/wiki/Cameras_and_Digital_Image_Sensors  */
end_comment

begin_decl_stmt
DECL|variable|file_formats
specifier|static
specifier|const
name|FileFormat
name|file_formats
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"Raw Canon"
argument_list|)
block|,
literal|"image/x-canon-cr2,image/x-canon-crw,image/tiff"
block|,
comment|// FIXME: only one mime type
literal|"cr2,crw,tif,tiff"
block|,
literal|"0,string,II*\\0\\020\\0\\0\\0CR,"
comment|// cr2
literal|"0,string,II\\024\\0\\0\\0HEAPCCDR,"
comment|// crw
literal|"0,string,MM\\0*\\0\\0\\0\\020\\0272\\0260,"
comment|// tiff
literal|"0,string,MM\\0*\\0\\0\\021\\064\\0\\04,"
comment|// tiff
literal|"0,string,II*\\0\\0\\03\\0\\0\\0377\\01"
block|,
comment|// tiff
literal|"file-darktable-canon-load"
block|,
literal|"Load files in the Canon raw formats via darktable"
block|,
literal|"This plug-in loads files in Canon's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Nikon"
argument_list|)
block|,
literal|"image/x-nikon-nef,image/x-nikon-nrw"
block|,
comment|// FIXME: only one mime type
literal|"nef,nrw"
block|,
name|NULL
block|,
literal|"file-darktable-nikon-load"
block|,
literal|"Load files in the Nikon raw formats via darktable"
block|,
literal|"This plug-in loads files in Nikon's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Hasselblad"
argument_list|)
block|,
literal|"image/x-hasselblad-3fr,image/x-hasselblad-fff"
block|,
comment|// FIXME: only one mime type
literal|"3fr,fff"
block|,
name|NULL
block|,
literal|"file-darktable-hasselblad-load"
block|,
literal|"Load files in the Hasselblad raw formats via darktable"
block|,
literal|"This plug-in loads files in Hasselblad's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Sony"
argument_list|)
block|,
literal|"image/x-sony-arw,image/x-sony-srf,image/x-sony-sr2"
block|,
comment|// FIXME: only one mime type
literal|"arw,srf,sr2"
block|,
name|NULL
block|,
literal|"file-darktable-sony-load"
block|,
literal|"Load files in the Sony raw formats via darktable"
block|,
literal|"This plug-in loads files in Sony's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Casio BAY"
argument_list|)
block|,
literal|"image/x-casio-bay"
block|,
literal|"bay"
block|,
name|NULL
block|,
literal|"file-darktable-bay-load"
block|,
literal|"Load files in the BAY raw format via darktable"
block|,
literal|"This plug-in loads files in Casio's raw BAY format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Phantom Software CINE"
argument_list|)
block|,
literal|""
block|,
comment|// FIXME: find a mime type
literal|"cine,cin"
block|,
name|NULL
block|,
literal|"file-darktable-cine-load"
block|,
literal|"Load files in the CINE raw format via darktable"
block|,
literal|"This plug-in loads files in Phantom Software's raw CINE format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Sinar"
argument_list|)
block|,
literal|""
block|,
comment|// FIXME: find a mime type
literal|"cs1,ia,sti"
block|,
name|NULL
block|,
literal|"file-darktable-sinar-load"
block|,
literal|"Load files in the Sinar raw formats via darktable"
block|,
literal|"This plug-in loads files in Sinar's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Kodak"
argument_list|)
block|,
literal|"image/x-kodak-dc2,image/x-kodak-dcr,image/x-kodak-kdc,image/x-kodak-k25,image/x-kodak-kc2,image/tiff"
block|,
comment|// FIXME: only one mime type
literal|"dc2,dcr,kdc,k25,kc2,tif,tiff"
block|,
literal|"0,string,MM\\0*\\0\\0\\021\\0166\\0\\04,"
comment|// tiff
literal|"0,string,II*\\0\\0\\03\\0\\0\\0174\\01"
block|,
comment|// tiff
literal|"file-darktable-kodak-load"
block|,
literal|"Load files in the Kodak raw formats via darktable"
block|,
literal|"This plug-in loads files in Kodak's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Adobe DNG Digital Negative"
argument_list|)
block|,
literal|"image/x-adobe-dng"
block|,
literal|"dng"
block|,
name|NULL
block|,
literal|"file-darktable-dng-load"
block|,
literal|"Load files in the DNG raw format via darktable"
block|,
literal|"This plug-in loads files in the Adobe Digital Negative DNG format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Epson ERF"
argument_list|)
block|,
literal|"image/x-epson-erf"
block|,
literal|"erf"
block|,
name|NULL
block|,
literal|"file-darktable-erf-load"
block|,
literal|"Load files in the ERF raw format via darktable"
block|,
literal|"This plug-in loads files in Epson's raw ERF format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Phase One"
argument_list|)
block|,
literal|"image/x-phaseone-cap,image/x-phaseone-iiq"
block|,
comment|// FIXME: only one mime type
literal|"cap,iiq"
block|,
name|NULL
block|,
literal|"file-darktable-phaseone-load"
block|,
literal|"Load files in the Phase One raw formats via darktable"
block|,
literal|"This plug-in loads files in Phase One's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Minolta"
argument_list|)
block|,
literal|"image/x-minolta-mdc,image/x-minolta-mrw"
block|,
comment|// FIXME: only one mime type
literal|"mdc,mrw"
block|,
name|NULL
block|,
literal|"file-darktable-minolta-load"
block|,
literal|"Load files in the Minolta raw formats via darktable"
block|,
literal|"This plug-in loads files in Minolta's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Mamiya MEF"
argument_list|)
block|,
literal|"image/x-mamiya-mef"
block|,
literal|"mef"
block|,
name|NULL
block|,
literal|"file-darktable-mef-load"
block|,
literal|"Load files in the MEF raw format via darktable"
block|,
literal|"This plug-in loads files in Mamiya's raw MEF format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Leaf MOS"
argument_list|)
block|,
literal|"image/x-leaf-mos"
block|,
literal|"mos"
block|,
name|NULL
block|,
literal|"file-darktable-mos-load"
block|,
literal|"Load files in the MOS raw format via darktable"
block|,
literal|"This plug-in loads files in Leaf's raw MOS format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Olympus ORF"
argument_list|)
block|,
literal|"image/x-olympus-orf"
block|,
literal|"orf"
block|,
literal|"0,string,IIRO,0,string,MMOR,0,string,IIRS"
block|,
literal|"file-darktable-orf-load"
block|,
literal|"Load files in the ORF raw format via darktable"
block|,
literal|"This plug-in loads files in Olympus' raw ORF format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Pentax PEF"
argument_list|)
block|,
literal|"image/x-pentax-pef,image/x-pentax-raw"
block|,
comment|// FIXME: only one mime type
literal|"pef,raw"
block|,
name|NULL
block|,
literal|"file-darktable-pef-load"
block|,
literal|"Load files in the PEF raw format via darktable"
block|,
literal|"This plug-in loads files in Pentax' raw PEF format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Logitech PXN"
argument_list|)
block|,
literal|"image/x-pxn"
block|,
comment|// FIXME: is that the correct mime type?
literal|"pxn"
block|,
name|NULL
block|,
literal|"file-darktable-pxn-load"
block|,
literal|"Load files in the PXN raw format via darktable"
block|,
literal|"This plug-in loads files in Logitech's raw PXN format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Apple QuickTake QTK"
argument_list|)
block|,
literal|""
block|,
comment|// FIXME: find a mime type
literal|"qtk"
block|,
name|NULL
block|,
literal|"file-darktable-qtk-load"
block|,
literal|"Load files in the QTK raw format via darktable"
block|,
literal|"This plug-in loads files in Apple's QuickTake QTK raw format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Fujifilm RAF"
argument_list|)
block|,
literal|"image/x-fuji-raf"
block|,
literal|"raf"
block|,
literal|"0,string,FUJIFILMCCD-RAW"
block|,
literal|"file-darktable-raf-load"
block|,
literal|"Load files in the RAF raw format via darktable"
block|,
literal|"This plug-in loads files in Fujifilm's raw RAF format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Panasonic"
argument_list|)
block|,
literal|"image/x-panasonic-raw,image/x-panasonic-rw2"
block|,
comment|// FIXME: only one mime type
literal|"raw,rw2"
block|,
literal|"0,string,IIU\\0"
block|,
literal|"file-darktable-panasonic-load"
block|,
literal|"Load files in the Panasonic raw formats via darktable"
block|,
literal|"This plug-in loads files in Panasonic's raw formats by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Digital Foto Maker RDC"
argument_list|)
block|,
literal|""
block|,
comment|// FIXME: find a mime type
literal|"rdc"
block|,
name|NULL
block|,
literal|"file-darktable-rdc-load"
block|,
literal|"Load files in the RDC raw format via darktable"
block|,
literal|"This plug-in loads files in Digital Foto Maker's raw RDC format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Leica RWL"
argument_list|)
block|,
literal|"image/x-leica-rwl"
block|,
literal|"rwl"
block|,
name|NULL
block|,
literal|"file-darktable-rwl-load"
block|,
literal|"Load files in the RWL raw format via darktable"
block|,
literal|"This plug-in loads files in Leica's raw RWL format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Samsung SRW"
argument_list|)
block|,
literal|"image/x-samsung-srw"
block|,
literal|"srw"
block|,
name|NULL
block|,
literal|"file-darktable-srw-load"
block|,
literal|"Load files in the SRW raw format via darktable"
block|,
literal|"This plug-in loads files in Samsung's raw SRW format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Sigma X3F"
argument_list|)
block|,
literal|"image/x-sigma-x3f"
block|,
literal|"x3f"
block|,
literal|"0,string,FOVb"
block|,
literal|"file-darktable-x3f-load"
block|,
literal|"Load files in the X3F raw format via darktable"
block|,
literal|"This plug-in loads files in Sigma's raw X3F format by calling darktable."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Raw Arriflex ARI"
argument_list|)
block|,
literal|""
block|,
literal|"ari"
block|,
name|NULL
block|,
literal|"file-darktable-ari-load"
block|,
literal|"Load files in the ARI raw format via darktable"
block|,
literal|"This plug-in loads files in Arriflex' raw ARI format by calling darktable."
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

