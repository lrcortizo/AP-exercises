#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin_4.x-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/cygdrive/C/opencv/build/x86/vc11/lib /cygdrive/C/opencv/build/x86/vc10/bin/opencv_core2410.dll /cygdrive/C/opencv/build/x86/vc10/bin/opencv_highgui2410.dll /cygdrive/C/opencv/build/x86/vc10/bin/opencv_imgproc2410.dll /cygdrive/C/opencv/build/x86/vc11/bin/opencv_core2410.dll /cygdrive/C/opencv/build/x86/vc11/bin/opencv_highgui2410.dll /cygdrive/C/opencv/build/x86/vc11/bin/opencv_imgproc2410.dll /cygdrive/C/opencv/build/x86/vc12/bin/opencv_core2410.dll /cygdrive/C/opencv/build/x86/vc12/bin/opencv_highgui2410.dll /cygdrive/C/opencv/build/x86/vc12/bin/opencv_imgproc2410.dll /cygdrive/C/opencv/build/x86/vc11/bin/opencv_highgui2410d.dll /cygdrive/C/opencv/build/x86/vc11/bin/opencv_core2410d.dll /cygdrive/C/opencv/build/x86/vc11/bin/opencv_imgproc2410d.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc10/bin/opencv_core2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc10/bin/opencv_highgui2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc10/bin/opencv_imgproc2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc11/bin/opencv_core2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc11/bin/opencv_highgui2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc11/bin/opencv_imgproc2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc12/bin/opencv_core2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc12/bin/opencv_highgui2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc12/bin/opencv_imgproc2410.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc11/bin/opencv_highgui2410d.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc11/bin/opencv_core2410d.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: /cygdrive/C/opencv/build/x86/vc11/bin/opencv_imgproc2410d.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/cygdrive/C/opencv/sources/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practicaparabola.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
