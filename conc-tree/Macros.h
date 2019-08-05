#pragma once

#define DISALLOW_COPY(Typename) \
	Typename(const Typename& rhs) = delete; \
	Typename& operator=(const Typename& rhs) = delete; \

#define DISALLOW_MOVE(Typename) \
	Typename(Typename&& rhs) = delete; \
	Typename& operator=(Typename&& rhs) = delete; \

#define DISALLOW_COPY_AND_MOVE(Typename) \
	DISALLOW_COPY(Typename) \
	DISALLOW_MOVE(Typename) \
