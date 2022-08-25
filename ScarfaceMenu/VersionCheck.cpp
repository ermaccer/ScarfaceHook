#include "VersionCheck.h"
#include <Windows.h>
#include <memory>

bool IsExecutableSpecifiedVersion(const char* exeName, const char* version)
{
	DWORD handle = 0, size = 0;
	UINT valSize = 0;
	std::unique_ptr<char[]> dataBuff;
	LPBYTE lpBuffer = NULL;

	size = GetFileVersionInfoSize(exeName, &handle);

	if (size > 0)
	{
		dataBuff = std::make_unique<char[]>(size);

		if (GetFileVersionInfoA(exeName,handle,size,dataBuff.get()))
		{
			if (VerQueryValue(dataBuff.get(), "\\", (LPVOID*)&lpBuffer, &valSize))
			{
				VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
				if (verInfo)
				{
					if (verInfo->dwSignature == 0xFEEF04BD)
					{
						char buff[128] = {};
						sprintf(buff,"%d.%d.%d.%d", (verInfo->dwFileVersionMS >> 16) & 0xffff, (verInfo->dwFileVersionMS >> 0) & 0xffff,
							(verInfo->dwFileVersionLS >> 16) & 0xffff,
							(verInfo->dwFileVersionLS >> 0) & 0xffff
						);
						if (strcmp(version, buff) == 0)
							return true;
						else
							return false;
					}
				}
			}
		}
	}

	return false;
}