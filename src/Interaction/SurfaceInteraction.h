#pragma once
#include "Module/MouseInputModule.h"
#include "Module/TopologyModule.h"
#include "Topology/TriangleSet.h"

namespace dyno
{
	template<typename TDataType>
	class SurfaceInteraction : public MouseInputModule
	{
		DECLARE_TCLASS(SurfaceInteraction, TDataType)
	public:
		typedef typename TDataType::Real Real;
		typedef typename TDataType::Coord Coord;
		typedef typename TopologyModule::Edge Edge;
		typedef typename TopologyModule::Triangle Triangle;

		SurfaceInteraction();
		virtual ~SurfaceInteraction() {};

		void calcIntersectClick();
		void calcIntersectDrag();
		void calcSurfaceIntersectClick();
		void calcSurfaceIntersectDrag();

		void mergeIndex();

		void printInfoClick();
		void printInfoDragging();
		void printInfoDragRelease();

		DEF_INSTANCE_IN(TriangleSet<TDataType>, InitialTriangleSet, "");
		DEF_INSTANCE_OUT(TriangleSet<TDataType>, SelectedTriangleSet, "");
		DEF_INSTANCE_OUT(TriangleSet<TDataType>, OtherTriangleSet, "");
		DEF_ARRAY_OUT(int, TriangleIndex, DeviceType::GPU, "");

		DECLARE_ENUM(PickingTypeSelection,
		Click = 0,
			Drag = 1,
			Both = 2
			);

		DEF_ENUM(PickingTypeSelection, SurfacePickingType, PickingTypeSelection::Both, "");

		DECLARE_ENUM(MultiSelectionType,
		OR = 0,
			XOR = 1,
			C = 2
			);

		DEF_ENUM(MultiSelectionType, MultiSelectionType, MultiSelectionType::OR, "");

		//DEF_VAR(Real, InteractionRadius, 0.01, "The radius of interaction");

		DEF_VAR(Real, FloodAngle, 0.5f, "The angle limit of flood selection");

		DEF_VAR(bool, TogglePicker, true, "The toggle of surface picker");

		DEF_VAR(bool, ToggleMultiSelect, false, "The toggle of multiple selection");

		DEF_VAR(bool, ToggleFlood, false, "The toggle of flood selection");

		DEF_VAR(bool, ToggleVisibleFilter, false, "The toggle of visible filter");

		DEF_VAR(bool, ToggleQuad, false, "The toggle of quad selection");

	protected:
		void onEvent(PMouseEvent event) override;
	private:
		std::shared_ptr<Camera> camera;
		TRay3D<Real> ray1, ray2;
		Real x1, y1, x2, y2;
		bool isPressed;
		int tempNumT, tempNumS;

		DArray<int> triIntersectedIndex;

		DArray<int> tempTriIntersectedIndex;
	};

	IMPLEMENT_TCLASS(SurfaceInteraction, TDataType)
}
