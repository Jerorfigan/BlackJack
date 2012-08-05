#pragma once

#include <string>
#include <Windows.h>

#include "..\GameUtilities\Point2D.h"

namespace BlackJack
{
	using namespace GameUtilities;

	struct Transform
	{
		std::string    m_imagePath;
		RECT           m_subrect;
		float          m_delay; // in seconds
		float		   m_duration; // in seconds
		Point2D        m_startPosition;
		Point2D        m_endPosition;
		float          m_startRotation; // in degrees, positive for CW
		float          m_endRotation;
		float          m_startScale; // 0-1(shrink), >1(grow)
		float          m_endScale;
		float          m_startAlpha; // 0(trans)-1(opaque)
		float          m_endAlpha;
		float          m_startZDepth; // 0(foreground)-1(background)
		float          m_endZDepth;
	};

}