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
CC=avr-gcc
CCC=avr-g++
CXX=avr-g++
FC=gfortran
AS=avr-as

# Macros
CND_PLATFORM=Arduino-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1360930230/ConfigManager.o \
	${OBJECTDIR}/_ext/1360930230/ConfigurableStateUnit.o \
	${OBJECTDIR}/_ext/1360930230/ConfigurableTemperatureDefinitionSource.o \
	${OBJECTDIR}/_ext/1360930230/D18B20Thermometer.o \
	${OBJECTDIR}/_ext/1360930230/DailyRunStrategy.o \
	${OBJECTDIR}/_ext/1360930230/DailyTemperatureDefinitionSource.o \
	${OBJECTDIR}/_ext/1360930230/ElectricHeaterUnit.o \
	${OBJECTDIR}/_ext/1360930230/FileLogger.o \
	${OBJECTDIR}/_ext/1360930230/FloorHeatingUnit.o \
	${OBJECTDIR}/_ext/1360930230/LCDDisplay.o \
	${OBJECTDIR}/_ext/1360930230/LCDInfoMode.o \
	${OBJECTDIR}/_ext/1360930230/LCDSettingsMode.o \
	${OBJECTDIR}/_ext/1360930230/LCDSpecialCharacters.o \
	${OBJECTDIR}/_ext/1360930230/LM35Thermometer.o \
	${OBJECTDIR}/_ext/1360930230/MaxTemperatureConfigurator.o \
	${OBJECTDIR}/_ext/1360930230/MinTemperatureConfigurator.o \
	${OBJECTDIR}/_ext/1360930230/RelayUnit.o \
	${OBJECTDIR}/_ext/1360930230/RunnerUnit.o \
	${OBJECTDIR}/_ext/1360930230/SimpleTemperatureDefinitionSource.o \
	${OBJECTDIR}/_ext/1360930230/StartStopUnit.o \
	${OBJECTDIR}/_ext/1360930230/TankTemperatureLDCInfo.o \
	${OBJECTDIR}/_ext/1360930230/TemperatureController.o \
	${OBJECTDIR}/_ext/1360930230/TemperatureLogger.o \
	${OBJECTDIR}/_ext/1360930230/ThermometerExtension.o \
	${OBJECTDIR}/_ext/1360930230/ThermometerLCDInfo.o \
	${OBJECTDIR}/_ext/1360930230/Thermostat.o \
	${OBJECTDIR}/_ext/1360930230/ThreeWayValveController.o \
	${OBJECTDIR}/_ext/1360930230/TimeLCDInfo.o \
	${OBJECTDIR}/_ext/1360930230/UnitStateLogger.o \
	${OBJECTDIR}/_ext/1360930230/WaterTemperatureController.o \
	${OBJECTDIR}/_ext/1360930230/WebServer.o \
	${OBJECTDIR}/_ext/1360930230/WeeklyRunStrategy.o \
	${OBJECTDIR}/_ext/1360930230/WeeklyTemperatureDefinitionSource.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=${FLAGS_GCC}

# CC Compiler Flags
CCFLAGS=${FLAGS_GPP}
CXXFLAGS=${FLAGS_GPP}

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/app

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/app: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	avr-gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/app ${OBJECTFILES} ${LDLIBSOPTIONS} ${FLAGS_LINKER}

${OBJECTDIR}/_ext/1360930230/ConfigManager.o: ../lib/ConfigManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/ConfigManager.o ../lib/ConfigManager.cpp

${OBJECTDIR}/_ext/1360930230/ConfigurableStateUnit.o: ../lib/ConfigurableStateUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/ConfigurableStateUnit.o ../lib/ConfigurableStateUnit.cpp

${OBJECTDIR}/_ext/1360930230/ConfigurableTemperatureDefinitionSource.o: ../lib/ConfigurableTemperatureDefinitionSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/ConfigurableTemperatureDefinitionSource.o ../lib/ConfigurableTemperatureDefinitionSource.cpp

${OBJECTDIR}/_ext/1360930230/D18B20Thermometer.o: ../lib/D18B20Thermometer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/D18B20Thermometer.o ../lib/D18B20Thermometer.cpp

${OBJECTDIR}/_ext/1360930230/DailyRunStrategy.o: ../lib/DailyRunStrategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/DailyRunStrategy.o ../lib/DailyRunStrategy.cpp

${OBJECTDIR}/_ext/1360930230/DailyTemperatureDefinitionSource.o: ../lib/DailyTemperatureDefinitionSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/DailyTemperatureDefinitionSource.o ../lib/DailyTemperatureDefinitionSource.cpp

${OBJECTDIR}/_ext/1360930230/ElectricHeaterUnit.o: ../lib/ElectricHeaterUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/ElectricHeaterUnit.o ../lib/ElectricHeaterUnit.cpp

${OBJECTDIR}/_ext/1360930230/FileLogger.o: ../lib/FileLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/FileLogger.o ../lib/FileLogger.cpp

${OBJECTDIR}/_ext/1360930230/FloorHeatingUnit.o: ../lib/FloorHeatingUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/FloorHeatingUnit.o ../lib/FloorHeatingUnit.cpp

${OBJECTDIR}/_ext/1360930230/LCDDisplay.o: ../lib/LCDDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/LCDDisplay.o ../lib/LCDDisplay.cpp

${OBJECTDIR}/_ext/1360930230/LCDInfoMode.o: ../lib/LCDInfoMode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/LCDInfoMode.o ../lib/LCDInfoMode.cpp

${OBJECTDIR}/_ext/1360930230/LCDSettingsMode.o: ../lib/LCDSettingsMode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/LCDSettingsMode.o ../lib/LCDSettingsMode.cpp

${OBJECTDIR}/_ext/1360930230/LCDSpecialCharacters.o: ../lib/LCDSpecialCharacters.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/LCDSpecialCharacters.o ../lib/LCDSpecialCharacters.cpp

${OBJECTDIR}/_ext/1360930230/LM35Thermometer.o: ../lib/LM35Thermometer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/LM35Thermometer.o ../lib/LM35Thermometer.cpp

${OBJECTDIR}/_ext/1360930230/MaxTemperatureConfigurator.o: ../lib/MaxTemperatureConfigurator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/MaxTemperatureConfigurator.o ../lib/MaxTemperatureConfigurator.cpp

${OBJECTDIR}/_ext/1360930230/MinTemperatureConfigurator.o: ../lib/MinTemperatureConfigurator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/MinTemperatureConfigurator.o ../lib/MinTemperatureConfigurator.cpp

${OBJECTDIR}/_ext/1360930230/RelayUnit.o: ../lib/RelayUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/RelayUnit.o ../lib/RelayUnit.cpp

${OBJECTDIR}/_ext/1360930230/RunnerUnit.o: ../lib/RunnerUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/RunnerUnit.o ../lib/RunnerUnit.cpp

${OBJECTDIR}/_ext/1360930230/SimpleTemperatureDefinitionSource.o: ../lib/SimpleTemperatureDefinitionSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/SimpleTemperatureDefinitionSource.o ../lib/SimpleTemperatureDefinitionSource.cpp

${OBJECTDIR}/_ext/1360930230/StartStopUnit.o: ../lib/StartStopUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/StartStopUnit.o ../lib/StartStopUnit.cpp

${OBJECTDIR}/_ext/1360930230/TankTemperatureLDCInfo.o: ../lib/TankTemperatureLDCInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/TankTemperatureLDCInfo.o ../lib/TankTemperatureLDCInfo.cpp

${OBJECTDIR}/_ext/1360930230/TemperatureController.o: ../lib/TemperatureController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/TemperatureController.o ../lib/TemperatureController.cpp

${OBJECTDIR}/_ext/1360930230/TemperatureLogger.o: ../lib/TemperatureLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/TemperatureLogger.o ../lib/TemperatureLogger.cpp

${OBJECTDIR}/_ext/1360930230/ThermometerExtension.o: ../lib/ThermometerExtension.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/ThermometerExtension.o ../lib/ThermometerExtension.cpp

${OBJECTDIR}/_ext/1360930230/ThermometerLCDInfo.o: ../lib/ThermometerLCDInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/ThermometerLCDInfo.o ../lib/ThermometerLCDInfo.cpp

${OBJECTDIR}/_ext/1360930230/Thermostat.o: ../lib/Thermostat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/Thermostat.o ../lib/Thermostat.cpp

${OBJECTDIR}/_ext/1360930230/ThreeWayValveController.o: ../lib/ThreeWayValveController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/ThreeWayValveController.o ../lib/ThreeWayValveController.cpp

${OBJECTDIR}/_ext/1360930230/TimeLCDInfo.o: ../lib/TimeLCDInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/TimeLCDInfo.o ../lib/TimeLCDInfo.cpp

${OBJECTDIR}/_ext/1360930230/UnitStateLogger.o: ../lib/UnitStateLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/UnitStateLogger.o ../lib/UnitStateLogger.cpp

${OBJECTDIR}/_ext/1360930230/WaterTemperatureController.o: ../lib/WaterTemperatureController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/WaterTemperatureController.o ../lib/WaterTemperatureController.cpp

${OBJECTDIR}/_ext/1360930230/WebServer.o: ../lib/WebServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/WebServer.o ../lib/WebServer.cpp

${OBJECTDIR}/_ext/1360930230/WeeklyRunStrategy.o: ../lib/WeeklyRunStrategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/WeeklyRunStrategy.o ../lib/WeeklyRunStrategy.cpp

${OBJECTDIR}/_ext/1360930230/WeeklyTemperatureDefinitionSource.o: ../lib/WeeklyTemperatureDefinitionSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360930230
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360930230/WeeklyTemperatureDefinitionSource.o ../lib/WeeklyTemperatureDefinitionSource.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/app

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
