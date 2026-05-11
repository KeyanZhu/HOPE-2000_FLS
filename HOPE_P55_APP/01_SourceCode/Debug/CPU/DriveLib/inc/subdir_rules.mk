################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CPU/DriveLib/inc/%.obj: ../CPU/DriveLib/inc/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --vcu_support=vcrc --include_path="F:/DSP_CODE_M/28P55X_CODE/F28P55X_DEMO/01_SourceCode" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="F:/DSP_CODE_M/28P55X_CODE/F28P55X_DEMO/01_SourceCode/APP" --include_path="F:/DSP_CODE_M/28P55X_CODE/F28P55X_DEMO/01_SourceCode/CPU" --include_path="F:/DSP_CODE_M/28P55X_CODE/F28P55X_DEMO/01_SourceCode/CPU/DriveLib" --include_path="F:/DSP_CODE_M/28P55X_CODE/F28P55X_DEMO/01_SourceCode/CPU/DriveLib/inc" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="CPU/DriveLib/inc/$(basename $(<F)).d_raw" --obj_directory="CPU/DriveLib/inc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


