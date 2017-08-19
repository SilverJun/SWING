#ifdef _WINDOWS

#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "../../lib/win/LLVMAArch64AsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMAArch64AsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMAArch64CodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMAArch64Desc.lib")
#pragma comment(lib, "../../lib/win/LLVMAArch64Disassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMAArch64Info.lib")
#pragma comment(lib, "../../lib/win/LLVMAArch64Utils.lib")
#pragma comment(lib, "../../lib/win/LLVMAMDGPUAsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMAMDGPUAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMAMDGPUCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMAMDGPUDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMAMDGPUDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMAMDGPUInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMAMDGPUUtils.lib")
#pragma comment(lib, "../../lib/win/LLVMAnalysis.lib")
#pragma comment(lib, "../../lib/win/LLVMAsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMBitReader.lib")
#pragma comment(lib, "../../lib/win/LLVMBitWriter.lib")
#pragma comment(lib, "../../lib/win/LLVMBPFAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMBPFCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMBPFDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMBPFDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMBPFInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMCore.lib")
#pragma comment(lib, "../../lib/win/LLVMCoroutines.lib")
#pragma comment(lib, "../../lib/win/LLVMCoverage.lib")
#pragma comment(lib, "../../lib/win/LLVMDebugInfoCodeView.lib")
#pragma comment(lib, "../../lib/win/LLVMDebugInfoDWARF.lib")
#pragma comment(lib, "../../lib/win/LLVMDebugInfoMSF.lib")
#pragma comment(lib, "../../lib/win/LLVMDebugInfoPDB.lib")
#pragma comment(lib, "../../lib/win/LLVMDemangle.lib")
#pragma comment(lib, "../../lib/win/LLVMExecutionEngine.lib")
#pragma comment(lib, "../../lib/win/LLVMGlobalISel.lib")
#pragma comment(lib, "../../lib/win/LLVMHexagonAsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMHexagonCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMHexagonDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMHexagonDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMHexagonInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMInstCombine.lib")
#pragma comment(lib, "../../lib/win/LLVMInstrumentation.lib")
#pragma comment(lib, "../../lib/win/LLVMInterpreter.lib")
#pragma comment(lib, "../../lib/win/LLVMipo.lib")
#pragma comment(lib, "../../lib/win/LLVMIRReader.lib")
#pragma comment(lib, "../../lib/win/LLVMLanaiAsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMLanaiCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMLanaiDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMLanaiDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMLanaiInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMLanaiInstPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMLibDriver.lib")
#pragma comment(lib, "../../lib/win/LLVMLineEditor.lib")
#pragma comment(lib, "../../lib/win/LLVMLinker.lib")
#pragma comment(lib, "../../lib/win/LLVMLTO.lib")
#pragma comment(lib, "../../lib/win/LLVMMC.lib")
#pragma comment(lib, "../../lib/win/LLVMMCDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMMCJIT.lib")
#pragma comment(lib, "../../lib/win/LLVMMCParser.lib")
#pragma comment(lib, "../../lib/win/LLVMMipsAsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMMipsAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMMipsCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMMipsDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMMipsDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMMipsInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMMIRParser.lib")
#pragma comment(lib, "../../lib/win/LLVMMSP430AsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMMSP430CodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMMSP430Desc.lib")
#pragma comment(lib, "../../lib/win/LLVMMSP430Info.lib")
#pragma comment(lib, "../../lib/win/LLVMNVPTXAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMNVPTXCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMNVPTXDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMNVPTXInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMObjCARCOpts.lib")
#pragma comment(lib, "../../lib/win/LLVMObject.lib")
#pragma comment(lib, "../../lib/win/LLVMObjectYAML.lib")
#pragma comment(lib, "../../lib/win/LLVMOption.lib")
#pragma comment(lib, "../../lib/win/LLVMOrcJIT.lib")
#pragma comment(lib, "../../lib/win/LLVMPasses.lib")
#pragma comment(lib, "../../lib/win/LLVMProfileData.lib")
#pragma comment(lib, "../../lib/win/LLVMRISCVCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMRISCVDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMRISCVInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMRuntimeDyld.lib")
#pragma comment(lib, "../../lib/win/LLVMScalarOpts.lib")
#pragma comment(lib, "../../lib/win/LLVMSelectionDAG.lib")
#pragma comment(lib, "../../lib/win/LLVMSparcAsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMSparcAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMSparcCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMSparcDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMSparcDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMSparcInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMSupport.lib")
#pragma comment(lib, "../../lib/win/LLVMSymbolize.lib")
#pragma comment(lib, "../../lib/win/LLVMSystemZAsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMSystemZAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMSystemZCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMSystemZDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMSystemZDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMSystemZInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMTableGen.lib")
#pragma comment(lib, "../../lib/win/LLVMTarget.lib")
#pragma comment(lib, "../../lib/win/LLVMTransformUtils.lib")
#pragma comment(lib, "../../lib/win/LLVMVectorize.lib")
#pragma comment(lib, "../../lib/win/LLVMX86AsmParser.lib")
#pragma comment(lib, "../../lib/win/LLVMX86AsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMX86CodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMX86Desc.lib")
#pragma comment(lib, "../../lib/win/LLVMX86Disassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMX86Info.lib")
#pragma comment(lib, "../../lib/win/LLVMX86Utils.lib")
#pragma comment(lib, "../../lib/win/LLVMXCoreAsmPrinter.lib")
#pragma comment(lib, "../../lib/win/LLVMXCoreCodeGen.lib")
#pragma comment(lib, "../../lib/win/LLVMXCoreDesc.lib")
#pragma comment(lib, "../../lib/win/LLVMXCoreDisassembler.lib")
#pragma comment(lib, "../../lib/win/LLVMXCoreInfo.lib")
#pragma comment(lib, "../../lib/win/LLVMXRay.lib")

#endif

#include <SwingCompiler.h>

int main(int argc, char* argv[])
{
	/*char* arg[] = {
		"C:/Users/SilverJun/Desktop/프로젝트/SWING/bin/Debug/swing.exe",
		"-compile",
		"-opt",
		"0",
		"-out",
		".obj",
		"C:/Users/SilverJun/SwingTestProject/Test.swingproj"
	};

	swing::SwingCLI cli(7, arg);
	cli.InitProgram();
	return cli.RunProgram();*/

	//*
	if (argc < 2)
		return -1;
	
	g_SwingCompiler->CompileSource(argv[1]);
	/*/
	//g_SwingCompiler->CompileSource("C:\\Users\\SilverJun\\Desktop\\SWING\\example\\MyProtocol\\main.swing");
	//g_SwingCompiler->CompileSource("C:\\Users\\SilverJun\\Desktop\\SWING\\example\\FunctionCall\\main.swing");
	g_SwingCompiler->CompileSource("C:\\Users\\SilverJun\\Desktop\\SWING\\example\\HelloSwing\\main.swing");
	//*/
	
	return 0;
}
