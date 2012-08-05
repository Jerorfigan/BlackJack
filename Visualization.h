#pragma once

#include <cstdlib>
#include <vector>

#include "DynamicImage.h"

namespace BlackJack
{

	class Visualization
	{
		/************/
		/* Typedefs */
		/************/
	private:
		typedef std::vector< DynamicImage* > DynamicImageList;

		/********************/
		/* Internal Classes */
		/********************/
	public:
		struct VisualizationDef
		{
			std::vector< DynamicImage::DynamicImageDef > m_dynamicImgDefs;
		};

		/****************/
		/* Constructors */
		/****************/
	public:
		Visualization( VisualizationDef visDef );

		/***********/
		/* Methods */
		/***********/
	public:
		void Update( float elapsedTime );
		void Draw();

		bool Complete();

		~Visualization();

		/********/
		/* Data */
		/********/
	private:
		DynamicImageList    m_dynamicImages;
	};

}