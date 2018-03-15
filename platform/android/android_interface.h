#pragma once

class AndroidInterface 
{
	bool exit = false;
	int width = 800;
	int height = 600;
	
public:
	AndroidInterface(){}
	virtual ~AndroidInterface(){}

	virtual void Update() {};
	
	virtual bool IsExit(){return false;}
	
	virtual unsigned short Width(unsigned short _width = 0) { return width = (_width == 0) ? width : _width; }
	virtual unsigned short Height(unsigned short _height = 0) { return height = (_height == 0) ? height : _height; }

};


