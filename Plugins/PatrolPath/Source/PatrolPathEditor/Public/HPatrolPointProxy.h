#pragma once
#include "ComponentVisualizer.h"

struct PATROLPATHEDITOR_API HPatrolPointProxy : public HComponentVisProxy
{
	int32 PointIndex;
	
	DECLARE_HIT_PROXY();

	explicit HPatrolPointProxy(const UActorComponent* InComponent, int32 InPointIndex)
			 : HComponentVisProxy(InComponent, HPP_Wireframe)
			 , PointIndex(InPointIndex)
	{
		HComponentVisProxy(InComponent, HPP_Wireframe);
		PointIndex = InPointIndex;
	}
	
};
