#ifndef VIDEO_H
#define VIDEO_H
#include <stdint.h>
#include <vector>
class video
{
public:
	video();
	void setline(int line,int16_t value);
	void draw();
private:
	std::vector<int16_t> lines;
};

#endif