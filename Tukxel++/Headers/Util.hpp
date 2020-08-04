#pragma once
#ifndef UTILH
#define UTILH

template<typename T> T* addressOfTemporary(T&& v) { return &v; }

#endif