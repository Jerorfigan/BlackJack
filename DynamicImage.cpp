#include "stdafx.h"

#include "DynamicImage.h"
#include "ServiceProvider.h"
#include "GameError.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	DynamicImage::DynamicImage( DynamicImageDef def ) :
		m_transforms( def.m_transforms ), m_transformIndex( 0 ), m_isAnimating( true )
	{
		if( m_transforms.size() == 0 )
			throw GameError( "[DynamicImage::DynamicImage]: Attempt to create dynamic image with no transforms. " );

		/* Create sprite from dynamic image def */

		m_spriteCollectionID = ServProvider()->GetGraphicsProvider()->CreateSpriteCollection();

		GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo = InterpolateSpriteInfo();

		ServProvider()->GetGraphicsProvider()->AddSprite( m_spriteCollectionID, "sprite", spriteInfo );

		m_runTimer.Reset();
	}

	/***********/
	/* Methods */
	/***********/
	
	////////////
	// Update //
	////////////
	void 
	DynamicImage::Update()
	{
		if( m_isAnimating )
		{
			float elapsedTime = m_runTimer.GetElapsedTimeSec();
			if( elapsedTime > m_transforms[ m_transformIndex ].m_delay )
			{
				if( elapsedTime > m_transforms[ m_transformIndex ].m_delay + 
													 m_transforms[ m_transformIndex ].m_duration )
				{
					GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo = InterpolateSpriteInfo( 1.0f );

					ServProvider()->GetGraphicsProvider()->SetSprite( m_spriteCollectionID, "sprite", spriteInfo );

					// Once we've burned through all the transforms, we're done animating.
					if( ++m_transformIndex >= m_transforms.size() )
					{
						m_isAnimating = false;
						return;
					}

					m_runTimer.Reset();
				}
				else
				{
					float interpolation = ( elapsedTime - m_transforms[ m_transformIndex ].m_delay ) / m_transforms[ m_transformIndex ].m_duration;
					GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo = InterpolateSpriteInfo( interpolation );
					ServProvider()->GetGraphicsProvider()->SetSprite( m_spriteCollectionID, "sprite", spriteInfo );
				}
			}
		}
	}

	//////////
	// Draw //
	//////////
	void DynamicImage::Draw()
	{
		ServProvider()->GetGraphicsProvider()->DrawSpriteCollection( m_spriteCollectionID );
	}

	/////////////////
	// IsAnimating //
	/////////////////
	bool DynamicImage::IsAnimating()
	{
		return m_isAnimating;
	}

	DynamicImage::~DynamicImage()
	{
		ServProvider()->GetGraphicsProvider()->DestroySpriteCollection( m_spriteCollectionID );
	}

	/////////////////////////////
	// SpriteInfoFromTransfrom //
	/////////////////////////////
	GameUtilities::IGraphicsProvider::SpriteInfo    
	DynamicImage::InterpolateSpriteInfo( float interpolation )
	{
		GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo;

		spriteInfo.imageFile = m_transforms[ m_transformIndex ].m_imagePath;
		spriteInfo.subrect = m_transforms[ m_transformIndex ].m_subrect;
		spriteInfo.center = GameUtilities::Point2D( 
			( spriteInfo.subrect.right - spriteInfo.subrect.left ) / 2.0f,
			( spriteInfo.subrect.bottom - spriteInfo.subrect.top ) / 2.0f );
			
		//m_transforms[ m_transformIndex ].m_center;

		spriteInfo.position = m_transforms[ m_transformIndex ].m_startPosition + 
			( m_transforms[ m_transformIndex ].m_endPosition - m_transforms[ m_transformIndex ].m_startPosition ) * interpolation;

		spriteInfo.rotation = m_transforms[ m_transformIndex ].m_startRotation + 
			( m_transforms[ m_transformIndex ].m_endRotation - m_transforms[ m_transformIndex ].m_startRotation ) * interpolation;

		spriteInfo.scaleX = m_transforms[ m_transformIndex ].m_startScaleX + 
			( m_transforms[ m_transformIndex ].m_endScaleX - m_transforms[ m_transformIndex ].m_startScaleX ) * interpolation;

		spriteInfo.scaleY = m_transforms[ m_transformIndex ].m_startScaleY + 
			( m_transforms[ m_transformIndex ].m_endScaleY - m_transforms[ m_transformIndex ].m_startScaleY ) * interpolation;

		spriteInfo.alpha = m_transforms[ m_transformIndex ].m_startAlpha + 
			( m_transforms[ m_transformIndex ].m_endAlpha - m_transforms[ m_transformIndex ].m_startAlpha ) * interpolation;

		spriteInfo.zDepth = m_transforms[ m_transformIndex ].m_startZDepth + 
			( m_transforms[ m_transformIndex ].m_endZDepth - m_transforms[ m_transformIndex ].m_startZDepth ) * interpolation;

		return spriteInfo;
	}

}