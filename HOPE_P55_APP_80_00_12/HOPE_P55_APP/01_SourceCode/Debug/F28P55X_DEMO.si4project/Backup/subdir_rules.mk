################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F28P55X_DEMO.si4project/Backup/Main(900).obj: ../F28P55X_DEMO.si4project/Backup/Main(900).c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcrc -O2 --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/APP" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/CPU" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/CPU/DriveLib" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/CPU/DriveLib/inc" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/KERNEL" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/KERNEL/ports" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/KERNEL/SOURCE" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/TASK" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/TASK/Include" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/DRIVER" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/DRIVER/Sci" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/MODULE" --include_path="E:/DSP_CODE/TEST/F28P55X_DEMO/01_SourceCode/MODULE/Library" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="F28P55X_DEMO.si4project/Backup/Main(900).d_raw" --obj_directory="F28P55X_DEMO.si4project/Backup" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


