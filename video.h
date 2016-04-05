#ifndef VIDEO_H
#define VIDEO_H
#include <stdint.h>
class video
{
public:
	video();
	void setline(int line,int16_t value);
	void draw();
private:
	int16_t lines[16];
	bool redrawNeeded;
};

#endif