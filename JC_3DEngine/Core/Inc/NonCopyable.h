#pragma once


// Description: Helper macros for copy/assign deletion.

#define NONCOPYABLE(Type)\
Type(const Type &) = delete;\
Type& operator=(const Type&) = delete;

#define NOCOPY(Type)\
Type(const Type&) = delete;

#define NOASSIGN(Type)\
Type& operator=(const Type&) = delete;




