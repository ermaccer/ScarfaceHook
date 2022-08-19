#include "Base.h"

Vector BaseObject::GetLocation()
{
	return GetMatrix().GetPos();
}

Matrix BaseObject::GetMatrix()
{
	return *(Matrix*)((int)this + 52);
}
