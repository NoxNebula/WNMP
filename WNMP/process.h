#include <Windows.h>
#include <string>
class Process {
private:
	Process(void) {};
	~Process(void) {};
public:
	static bool Create(char* Process, char* Arguments = "", char* WorkingDirectory = "", bool ShowWindow = true);
	static bool IsRunning(char* Process);
	static bool Stop(char* Process, int MaxKills = 1);
	static std::string GetName(HANDLE &hProcess);
};