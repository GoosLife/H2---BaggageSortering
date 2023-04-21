#pragma once
template <class T> class Spawner
{
public:
	T* Spawn() { return new T(); }
};