#pragma once

enum Number
{
	zero,
	first,
	second,
	third,
	fourth,
	fifth
};

class Load
{
public:
	Load();
	~Load();
	void Start();
	void Loading();
	void End();

private:
	Number number;
	int Graph;
};