# Microsoft Developer Studio Project File - Name="SDL_image" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SDL_image - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "SDL_image.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "SDL_image.mak" CFG="SDL_image - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "SDL_image - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SDL_image - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SDL_image - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "graphics\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "LOAD_BMP" /D "LOAD_GIF" /D "LOAD_LBM" /D "LOAD_PCX" /D "LOAD_PNM" /D "LOAD_XPM" /D "LOAD_JPG" /D "LOAD_PNG" /D "LOAD_TGA" /D "PNG_USE_DLL" /D "ZLIB_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib SDL.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "SDL_image - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "graphics\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "LOAD_BMP" /D "LOAD_GIF" /D "LOAD_LBM" /D "LOAD_PCX" /D "LOAD_PNM" /D "LOAD_XPM" /D "LOAD_JPG" /D "LOAD_PNG" /D "LOAD_TGA" /D "LOAD_RAW" /D "LOAD_JP2" /D "PNG_USE_DLL" /D "ZLIB_DLL" /D "EXCLUDE_JPG_SUPPORT" /D "EXCLUDE_MIF_SUPPORT" /D "EXCLUDE_PNM_SUPPORT" /D "EXCLUDE_RAS_SUPPORT" /D "EXCLUDE_BMP_SUPPORT" /D "EXCLUDE_PGX_SUPPORT" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib SDL.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SDL_image - Win32 Release"
# Name "SDL_image - Win32 Debug"
# Begin Group "SDL_image Sources"

# PROP Default_Filter ""
# Begin Group "jas"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_debug.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_getopt.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_image.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_init.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_malloc.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_seq.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_stream.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_string.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_tvp.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\base\jas_version.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jp2\jp2_cod.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jp2\jp2_cod.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jp2\jp2_dec.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jp2\jp2_dec.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jp2\jp2_enc.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_bs.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_bs.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_cod.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_cs.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_cs.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_dec.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_dec.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_enc.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_enc.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_fix.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_flt.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_math.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_math.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mct.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mct.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mqcod.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mqcod.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mqdec.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mqdec.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mqenc.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_mqenc.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_qmfb.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_qmfb.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t1cod.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t1cod.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t1dec.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t1dec.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t1enc.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t1enc.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t2cod.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t2cod.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t2dec.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t2dec.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t2enc.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_t2enc.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_tagtree.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_tagtree.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_tsfb.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_tsfb.h"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_util.c"
# End Source File
# Begin Source File

SOURCE="..\..\jasper-1.500.3\src\libjasper\jpc\jpc_util.h"
# End Source File
# End Group
# Begin Source File

SOURCE=..\IMG.c
# End Source File
# Begin Source File

SOURCE=..\IMG_bmp.c
# End Source File
# Begin Source File

SOURCE=..\IMG_gif.c
# End Source File
# Begin Source File

SOURCE=..\IMG_jp2.c
# End Source File
# Begin Source File

SOURCE=..\IMG_jpg.c
# End Source File
# Begin Source File

SOURCE=..\IMG_lbm.c
# End Source File
# Begin Source File

SOURCE=..\IMG_pcx.c
# End Source File
# Begin Source File

SOURCE=..\IMG_png.c
# End Source File
# Begin Source File

SOURCE=..\IMG_pnm.c
# End Source File
# Begin Source File

SOURCE=..\IMG_ras.c
# End Source File
# Begin Source File

SOURCE=..\IMG_raw.c
# End Source File
# Begin Source File

SOURCE=..\IMG_tga.c
# End Source File
# Begin Source File

SOURCE=..\IMG_tif.c
# End Source File
# Begin Source File

SOURCE=..\IMG_xcf.c
# End Source File
# Begin Source File

SOURCE=..\IMG_xpm.c
# End Source File
# Begin Source File

SOURCE=..\IMG_xxx.c
# End Source File
# Begin Source File

SOURCE=Version.rc
# End Source File
# End Group
# Begin Group "SDL_image Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SDL_image.h
# End Source File
# End Group
# Begin Group "External Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\graphics\lib\jpeg.lib
# End Source File
# Begin Source File

SOURCE=.\graphics\lib\libpng1.lib
# End Source File
# Begin Source File

SOURCE=.\graphics\lib\zlib.lib
# End Source File
# End Group
# End Target
# End Project
