#include <iostream>
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include "process.h"
#pragma comment(lib, "Psapi.lib")

bool Process::Create(char* Process, char* Arguments, char* WorkingDirectory, bool ShowWindow) {
	// New process info
	PROCESS_INFORMATION PI;
	ZeroMemory(&PI, sizeof(PI));

	// New startup info
	STARTUPINFO SI;
	ZeroMemory(&SI, sizeof(SI));
	SI.cb = sizeof(SI);
	if(!ShowWindow) {
		SI.dwFlags = STARTF_USESHOWWINDOW;
		SI.wShowWindow = SW_HIDE;
	}

	// Create process
	char CMD[256];
	sprintf(CMD ,"%s %s", Process, Arguments);
	bool Success = CreateProcess(NULL, CMD, NULL, NULL, FALSE, 0, NULL, WorkingDirectory != "" ? WorkingDirectory : NULL, &SI, &PI);
	CloseHandle(PI.hProcess);
	CloseHandle(PI.hThread);

	return Success;
}

bool Process::IsRunning(char* Process) {
	return FindWindow(NULL, Process) != NULL;
}

bool Process::Stop(char* Process, int MaxKills) {
	std::string sProcess = Process;
	DWORD aProcesses[1024], cbNeeded, cProcesses;

	if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return false;

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	int Kills = 0;
	for(int i = 0; i < cProcesses; i++) {
		if(aProcesses[i] != 0) {
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,
				FALSE, aProcesses[i]);

			if(GetName(hProcess) == sProcess) {
				if(Kills >= MaxKills)
					break;
				TerminateProcess(hProcess, 0);
				Kills++;
			}
			CloseHandle(hProcess);
		}
	}

	return true;
}

std::string Process::GetName(HANDLE &hProcess) {
	char sProcessName[MAX_PATH] = "<unknown>";

	if(NULL != hProcess ){
		HMODULE hMod;
		DWORD cbNeeded;

		if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), 
			&cbNeeded)) {
			GetModuleBaseName(hProcess, hMod, sProcessName, 
				sizeof(sProcessName)/sizeof(TCHAR));
		}
	}
	return sProcessName;
}