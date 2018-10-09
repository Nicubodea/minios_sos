#include "screen.h"

static PSCREEN gVideo = (PSCREEN)(0x000B8000);

void HelloBoot(QWORD x)
{
    int i, len;
	char boot[] = "Hello Boot! Greetings from C...";

	len = 0;
	while (boot[len] != 0)
	{
		len++;
	}

	for (i = 0; (i < len) && (i < MAX_OFFSET); i++)
	{
		gVideo[i].color = 10;
		gVideo[i].c = boot[i];
	}


    while (x != 0)
    {
        gVideo[i].color = 10;
        gVideo[i].c = x % 10 + '0';
        x = x / 10;
        i++;
    }
}