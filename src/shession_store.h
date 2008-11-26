#ifndef SHESSION_STORE_H
#define SHESSION_STORE_H
/**
 * Copyright 2008 Matthew Graham
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>
#include <map>


/**
 * This is an object to aggregate info for a given shared session.
 */
class shession_c
{
public:
	/**
	 * Construct a shession object.
	 */
	shession_c( const std::string &shession_id
			, const std::string &user_id = std::string() );

	/**
	 * Set when this shession should expired.
	 */
	void expire_at( time_t expiration ) { m_expiration = expiration; }

	/**
	 * Get the shession_id for this shession.
	 */
	const std::string & shession_id() const { return m_shession_id; }
	/**
	 * Get the user_id for this shession.  May be empty.
	 */
	const std::string & user_id() const { return m_user_id; }
	/**
	 * Get the expiration time for this shession.
	 */
	time_t expiration() const { return m_expiration; }

	/**
	 * Check if this shession is expired.
	 */
	bool expired( time_t now ) const { return now >= m_expiration; }

private:
	std::string m_shession_id;
	std::string m_user_id;
	time_t m_expiration;
};


/**
 * Class for iterating through shessions
 */
class shession_iterator_c
{
public:
	friend class const_shession_iterator_c;

	shession_iterator_c(
			std::map< std::string, shession_c >::iterator it )
	: m_base( it )
	{}

	/**
	 * Prefix increment operator
	 */
	void operator ++ () { ++m_base; }
	/**
	 * Prefix decrement operator
	 */
	void operator -- () { --m_base; }
	/**
	 * Postfix increment operator
	 */
	void operator ++ ( int ) { m_base++; }
	/**
	 * Postfix decrement operator
	 */
	void operator -- ( int ) { m_base--; }

	shession_c & operator * () { return m_base->second; }
	shession_c * operator -> () { return &( m_base->second ); }
	const shession_c & operator * () const { return m_base->second; }
	const shession_c * operator -> () const { return &( m_base->second ); }

	bool operator == ( const shession_iterator_c &it ) const
	{
		return m_base == it.m_base;
	}
	bool operator != ( const shession_iterator_c &it ) const
	{
		return m_base != it.m_base;
	}

private:
	std::map< std::string, shession_c >::iterator m_base;
};

/**
 * Class for iterating through shessions
 */
class const_shession_iterator_c
{
public:
	/**
	 * Construct a const_shession_iterator for the internal iterator
	 * type in the shession_store.
	 */
	const_shession_iterator_c(
			std::map< std::string, shession_c >::const_iterator it )
	: m_base( it )
	{}
	/**
	 * Construct a const shession iterator from a non-const
	 * shession_iterator.
	 */
	const_shession_iterator_c( shession_iterator_c it )
	: m_base( it.m_base )
	{}

	/**
	 * Prefix increment operator
	 */
	void operator ++ () { ++m_base; }
	/**
	 * Prefix decrement operator
	 */
	void operator -- () { --m_base; }
	/**
	 * Postfix increment operator
	 */
	void operator ++ ( int ) { m_base++; }
	/**
	 * Postfix decrement operator
	 */
	void operator -- ( int ) { m_base--; }

	const shession_c & operator * () const { return m_base->second; }
	const shession_c * operator -> () const { return &( m_base->second ); }

	bool operator == ( const const_shession_iterator_c &it ) const
	{
		return m_base == it.m_base;
	}
	bool operator != ( const const_shession_iterator_c &it ) const
	{
		return m_base != it.m_base;
	}

private:
	std::map< std::string, shession_c >::const_iterator m_base;
};


/**
 * Abstract shession_store interface.
 */
class shession_store_i
{
public:
	/**
	 * Empty destructor to be overridden by implementing classes.
	 */
	virtual ~shession_store_i() {}

	/**
	 * Create a session for an optional user_id.
	 */
	virtual void create( const std::string &shession_id
			, const std::string &user_id ) = 0;
	/**
	 * Check if the given session_id is live.
	 * @return true if it is still alive.
	 */
	virtual bool live( const std::string &session_id ) const = 0;
	/**
	 * Renew the session if it exists.
	 * @return true if it is still alive.
	 */
	virtual bool renew( const std::string &session_id ) = 0;
	/**
	 * Kill the given session if it exists.
	 */
	virtual void kill( const std::string &ession_id ) = 0;

	/**
	 * Mirror a session from another server.
	 */
	virtual void mirror( const std::string &shession_id
			, const std::string &user_id ) = 0;

	/**
	 * Check if any sessions are expired and kill them.
	 * @return the number of sessions killed
	 */
	virtual int kill_expired() = 0;

	/**
	 * Check the total number of sessions in the store.
	 * This count may include session that have already
	 * expired but are still in the store.
	 */
	virtual int size() const = 0;


	/**
	 * Get the begin iterator.
	 */
	virtual shession_iterator_c begin() = 0;
	/**
	 * Get the end iterator.
	 */
	virtual shession_iterator_c end() = 0;

	/**
	 * Get the begin iterator.
	 */
	virtual const_shession_iterator_c begin() const = 0;
	/**
	 * Get the end iterator.
	 */
	virtual const_shession_iterator_c end() const = 0;
};


/**
 * Implementing class for the shession_store interface.
 * This might need to be renamed and put in a different file
 * at some point.  For now it will live here.
 */
class shession_store_c
: public shession_store_i
{
public:
	/**
	 * Timer class built to allow mocking for testing purposes.
	 */
	class timer_c
	{
	public:
		virtual ~timer_c() {}
		virtual time_t now() const { return time( NULL ); }
	};

public:
	/**
	 * Construct a session_store object.
	 */
	shession_store_c( int timeout_seconds );
	/**
	 * Destructor for the session_store object.
	 */
	~shession_store_c();
	/**
	 * Set the timer this store should use.
	 * This shouldn't need to be called outside of testing.
	 */
	void set_timer( timer_c & );

	/**
	 * Create a session for an optional user_id.
	 */
	virtual void create( const std::string &shession_id
			, const std::string &user_id );
	/**
	 * Check if the given session_id is live.
	 * @return true if it is still alive.
	 */
	virtual bool live( const std::string &session_id ) const;
	/**
	 * Renew the session if it exists.
	 * @return true if it is still alive.
	 */
	virtual bool renew( const std::string &session_id );
	/**
	 * Kill the given session if it exists.
	 */
	virtual void kill( const std::string &ession_id );

	/**
	 * Mirror a session from another server.
	 * This creates it if it doesn't exist and renews it if it does.
	 */
	virtual void mirror( const std::string &shession_id
			, const std::string &user_id );

	/**
	 * Check if any sessions are expired and kill them.
	 * @return the number of sessions killed
	 */
	virtual int kill_expired();

	/**
	 * Check the total number of sessions in the store.
	 */
	virtual int size() const;


	/**
	 * Get the begin iterator.
	 */
	virtual shession_iterator_c begin();
	/**
	 * Get the end iterator.
	 */
	virtual shession_iterator_c end();

	/**
	 * Get the begin const_iterator.
	 */
	virtual const_shession_iterator_c begin() const;
	/**
	 * Get the end const_iterator.
	 */
	virtual const_shession_iterator_c end() const;

private:
	timer_c m_default_timer;
	timer_c *m_timer;
	int m_timeout; // in seconds
	std::map< std::string, shession_c > m_store;
};


#endif

