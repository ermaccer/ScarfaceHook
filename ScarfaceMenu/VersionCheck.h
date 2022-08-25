#pragma once


#define TARGET_EXE "Scarface.exe"
#define TARGET_VERSION "1.0.0.2"

bool IsExecutableSpecifiedVersion(const char* exeName = TARGET_EXE, const char* version = TARGET_VERSION);