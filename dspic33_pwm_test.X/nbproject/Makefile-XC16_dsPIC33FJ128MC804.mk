#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-XC16_dsPIC33FJ128MC804.mk)" "nbproject/Makefile-local-XC16_dsPIC33FJ128MC804.mk"
include nbproject/Makefile-local-XC16_dsPIC33FJ128MC804.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=XC16_dsPIC33FJ128MC804
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=configuration_bits.c interrupts.c main.c system.c traps.c user.c pwm.c uart.c cli.c motor_driver.c axis.c encoder.c ring_buffer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/user.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/cli.o ${OBJECTDIR}/motor_driver.o ${OBJECTDIR}/axis.o ${OBJECTDIR}/encoder.o ${OBJECTDIR}/ring_buffer.o
POSSIBLE_DEPFILES=${OBJECTDIR}/configuration_bits.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/traps.o.d ${OBJECTDIR}/user.o.d ${OBJECTDIR}/pwm.o.d ${OBJECTDIR}/uart.o.d ${OBJECTDIR}/cli.o.d ${OBJECTDIR}/motor_driver.o.d ${OBJECTDIR}/axis.o.d ${OBJECTDIR}/encoder.o.d ${OBJECTDIR}/ring_buffer.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/user.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/cli.o ${OBJECTDIR}/motor_driver.o ${OBJECTDIR}/axis.o ${OBJECTDIR}/encoder.o ${OBJECTDIR}/ring_buffer.o

# Source Files
SOURCEFILES=configuration_bits.c interrupts.c main.c system.c traps.c user.c pwm.c uart.c cli.c motor_driver.c axis.c encoder.c ring_buffer.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-XC16_dsPIC33FJ128MC804.mk dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/traps.o.d 
	@${RM} ${OBJECTDIR}/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pwm.o: pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uart.o: uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart.c  -o ${OBJECTDIR}/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/cli.o: cli.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cli.o.d 
	@${RM} ${OBJECTDIR}/cli.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cli.c  -o ${OBJECTDIR}/cli.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/cli.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/cli.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_driver.o: motor_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor_driver.o.d 
	@${RM} ${OBJECTDIR}/motor_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_driver.c  -o ${OBJECTDIR}/motor_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/axis.o: axis.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/axis.o.d 
	@${RM} ${OBJECTDIR}/axis.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  axis.c  -o ${OBJECTDIR}/axis.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/axis.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/axis.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/encoder.o: encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder.o.d 
	@${RM} ${OBJECTDIR}/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  encoder.c  -o ${OBJECTDIR}/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/encoder.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ring_buffer.o: ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ring_buffer.c  -o ${OBJECTDIR}/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ring_buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/ring_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/traps.o.d 
	@${RM} ${OBJECTDIR}/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pwm.o: pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pwm.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/uart.o: uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart.c  -o ${OBJECTDIR}/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uart.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/cli.o: cli.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cli.o.d 
	@${RM} ${OBJECTDIR}/cli.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cli.c  -o ${OBJECTDIR}/cli.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/cli.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/cli.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_driver.o: motor_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor_driver.o.d 
	@${RM} ${OBJECTDIR}/motor_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_driver.c  -o ${OBJECTDIR}/motor_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_driver.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/axis.o: axis.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/axis.o.d 
	@${RM} ${OBJECTDIR}/axis.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  axis.c  -o ${OBJECTDIR}/axis.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/axis.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/axis.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/encoder.o: encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder.o.d 
	@${RM} ${OBJECTDIR}/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  encoder.c  -o ${OBJECTDIR}/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/encoder.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ring_buffer.o: ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ring_buffer.c  -o ${OBJECTDIR}/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ring_buffer.o.d"        -g -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/ring_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libq-dsp-coff.a ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libq-dsp-elf.a ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libdsp-coff.a ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libdsp-elf.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libq-dsp-coff.a" "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libq-dsp-elf.a" "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libdsp-coff.a" "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libdsp-elf.a"  -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h"  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../../../../../../Program Files (x86)/Microchip/xc16/v1.36/lib",--force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libq-dsp-coff.a ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libq-dsp-elf.a ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libdsp-coff.a ../../../../../../Program\ Files\ (x86)/Microchip/xc16/v1.36/lib/libdsp-elf.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libq-dsp-coff.a" "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libq-dsp-elf.a" "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libdsp-coff.a" "..\..\..\..\..\..\Program Files (x86)\Microchip\xc16\v1.36\lib\libdsp-elf.a"  -mcpu=$(MP_PROCESSOR_OPTION)        -omf=coff -DXPRJ_XC16_dsPIC33FJ128MC804=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"h" -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../../../../../../Program Files (x86)/Microchip/xc16/v1.36/lib",--force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_pwm_test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/XC16_dsPIC33FJ128MC804
	${RM} -r dist/XC16_dsPIC33FJ128MC804

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
