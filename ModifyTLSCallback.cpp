#include <Windows.h>
#include <stdio.h>
#include <ImageHlp.h>
#pragma comment(lib, "ImageHlp")

bool ModifyTLSCallbacks(UINT64 newCallbackAddress) //you can edit this routine to work with multiple tls callbacks, this is just a proof of concept
{
	unsigned long cDirSize = 0;
	IMAGE_TLS_DIRECTORY* tlsDirectory;

	tlsDirectory = (IMAGE_TLS_DIRECTORY*)ImageDirectoryEntryToData(GetModuleHandle(NULL), TRUE, IMAGE_DIRECTORY_ENTRY_TLS, &cDirSize);

	DWORD dOldProt = 0;

	if (!VirtualProtect((LPVOID)tlsDirectory->AddressOfCallBacks, sizeof(UINT64), PAGE_EXECUTE_READWRITE, &dOldProt))
		return false;

	memcpy((void*)tlsDirectory->AddressOfCallBacks, &newCallbackAddress, sizeof(UINT64)); //this writes over the pointer to the callback, not the callback itself
	tlsDirectory->AddressOfCallBacks = newCallbackAddress;

	return true;
}

int main(void)
{
	if (ModifyTLSCallbacks((UINT64)GetModuleHandle(NULL))) //this will block x64dbg, CE debugger, etc.
	{
		printf("Modified tls callback successfully!\n");
	}

	return 0;
}
