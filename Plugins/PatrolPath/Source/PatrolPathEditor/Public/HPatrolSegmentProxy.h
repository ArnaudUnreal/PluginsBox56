// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once
#include "ComponentVisualizer.h"

struct PATROLPATHEDITOR_API HPatrolSegmentProxy : public HComponentVisProxy
{
	int32 SegmentStartIndex;
	
	DECLARE_HIT_PROXY();

	explicit HPatrolSegmentProxy(const UActorComponent* InComponent, int32 InSegmentStartIndex)
			 : HComponentVisProxy(InComponent, HPP_Wireframe)
			 , SegmentStartIndex(InSegmentStartIndex)
	{
	}
	
};
