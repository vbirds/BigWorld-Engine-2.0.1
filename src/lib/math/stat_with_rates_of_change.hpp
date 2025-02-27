/******************************************************************************
BigWorld Technology 
Copyright BigWorld Pty, Ltd.
All Rights Reserved. Commercial in confidence.

WARNING: This computer program is protected by copyright law and international
treaties. Unauthorized use, reproduction or distribution of this program, or
any portion of this program, may result in the imposition of civil and
criminal penalties as provided by law.
******************************************************************************/

#ifndef STAT_WITH_RATES_OF_CHANGE_HPP
#define STAT_WITH_RATES_OF_CHANGE_HPP

#include "pch.hpp"
#include "ema.hpp"
#include "stat_with_rates_of_change.hpp"
#include "cstdmf/debug.hpp"
#include "cstdmf/intrusive_object.hpp"
#include <math.h>


/**
 *	This class is used to keep a statistic. The rate of change of this statistic
 *	is monitored.
 */
template < class TYPE >
class StatWithRatesOfChange
{
public:
	StatWithRatesOfChange();

	void monitorRateOfChange( float numSamples );

	void tick( double deltaTime );

	void operator++()		{ this->add( 1 ); }
	void operator++( int )	{ this->add( 1 ); }

	void operator--()		{ this->add( -1 ); }
	void operator--( int )	{ this->add( -1 ); }

	void operator+=( TYPE value )	{ this->add( value ); }
	void operator-=( TYPE value )	{ this->subtract( value ); }

	TYPE total() const;
	void setTotal( TYPE total );

	double getRateOfChange( int index = 0 ) const;

	// Workaround for Watchers
	template <int INDEX>
	double getRateOfChangeT() const { return this->getRateOfChange( INDEX ); }

	double getRateOfChange0() const { return this->getRateOfChange( 0 ); }
	double getRateOfChange1() const { return this->getRateOfChange( 1 ); }
	double getRateOfChange2() const { return this->getRateOfChange( 2 ); }
	double getRateOfChange3() const { return this->getRateOfChange( 3 ); }
	double getRateOfChange4() const { return this->getRateOfChange( 4 ); }

private:
	void add( TYPE value );
	void subtract( TYPE value );

	TYPE total_;
	TYPE prevTotal_;

	typedef std::vector< EMA > Averages;
	Averages averages_;
};


/**
 *	This class adds IntrusiveObject functionality to StatWithRatesOfChange.
 */
template < class TYPE >
class IntrusiveStatWithRatesOfChange :
	public StatWithRatesOfChange< TYPE >,
	public IntrusiveObject< IntrusiveStatWithRatesOfChange< TYPE > >
{
public:
	typedef typename IntrusiveObject<
		IntrusiveStatWithRatesOfChange< TYPE > >::Container Container;

	IntrusiveStatWithRatesOfChange( Container *& pContainer );

	TYPE total() const	{ return StatWithRatesOfChange< TYPE >::total(); }
};

#include "stat_with_rates_of_change.ipp"

#endif // STAT_WITH_RATES_OF_CHANGE_HPP
