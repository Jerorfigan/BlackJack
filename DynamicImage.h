#pragma once

#include <vector>

#include "Globals.h"
#include "Transform.h"
#include "..\GameUtilities\HighResolutionTimer.h"
#include "..\GameUtilities\IGraphicsProvider.h"

namespace BlackJack
{

	class DynamicImage
	{
		/************/
		/* Typedefs */
		/************/
	private:
		typedef std::vector< Transform > TransformList;

		/********************/
		/* Internal Classes */
		/********************/
	public:
		struct DynamicImageDef
		{
			std::vector< Transform >    m_transforms;
		};

		/****************/
		/* Constructors */
		/****************/
	public:
		DynamicImage( DynamicImageDef def );

		/***********/
		/* Methods */
		/***********/
	public:
		void    Update();
		void    Draw();

		bool    IsAnimating();

		~DynamicImage();

	private:
		GameUtilities::IGraphicsProvider::SpriteInfo    InterpolateSpriteInfo( float interpolation = 0 );

		/********/
		/* Data */
		/********/
	private:
		TransformList          m_transforms;
		HighResolutionTimer    m_runTimer;
		uint                   m_transformIndex;
		GameUtilities::IGraphicsProvider::SpriteCollectionID    m_spriteCollectionID;
		bool				   m_isAnimating;
	};

}