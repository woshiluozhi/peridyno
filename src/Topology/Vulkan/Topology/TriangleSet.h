#pragma once
#include "EdgeSet.h"

namespace dyno
{
	class TriangleSet : public EdgeSet
	{
	public:
		TriangleSet();
		~TriangleSet() override;

		void updateTopology() override;

		VkDeviceArray<uint32_t> mIndex;
	public:
		VkDeviceArray<dyno::TopologyModule::Triangle> mTriangleIndex;
	};
}

