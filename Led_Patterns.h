#ifndef LED_PATTERNS
#define LED_PATTERNS

#define BUILD_SHAPE(PREFIX,NAME) \
{	\
	char xvec[PREFIX ## _PATTERN_SIZE] = {PREFIX ## _PATTERN_X}; \
	char yvec[PREFIX ## _PATTERN_SIZE] = {PREFIX ## _PATTERN_Y}; \
	NAME.buildShape(xvec,yvec,PREFIX ## _PATTERN_SIZE); \
}

#endif
