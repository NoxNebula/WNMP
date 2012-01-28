#pragma once
class Application {
private:
	Application(void);
	~Application(void);
public:
	enum {
		INVALID = -1,
		START = 0,
		RESTART,
		STOP
	};

	static void PHP(int Mode);
	static void NGINX(int Mode);
	static void MySQL(int Mode);
};

