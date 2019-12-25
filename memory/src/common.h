#ifndef MEMORY_COMMON_H
#define MEMORY_COMMON_H

#define _ASAN_EXPORT extern "C" __attribute__((used)) \
	__attribute__((visibility("default"))) \
	__attribute__((no_sanitize_address))

int globalData();

#endif // MEMORY_COMMON_H
