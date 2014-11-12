#ifndef LED_PATTERNS
#define LED_PATTERNS

#define BUILD_SHAPE(X,Y,N,NAME) \
{	\
	char xvec[N] = {X}; \
	char yvec[N] = {Y}; \
	NAME.buildShape(xvec,yvec,N); \
}

#endif
