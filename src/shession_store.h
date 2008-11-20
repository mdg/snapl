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
 * This is an object to aggregate info for a given shession.
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
	bool expired( time_t now = 0 ) const;

private:
	std::string m_shession_id;
	std::string m_user_id;
	time_t m_expiration;
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
	virtual void create_session( const std::string &shession_id
			, const std::string &user_id ) = 0;
	/**
	 * Check if the given session_id is live.
	 * @return true if it is still alive.
	 */
	virtual bool live_session( const std::string &session_id ) const = 0;
	/**
	 * Renew the session if it exists.
	 * @return true if it is still alive.
	 */
	virtual bool renew_session( const std::string &session_id ) = 0;
	/**
	 * Kill the given session if it exists.
	 */
	virtual void kill_session( const std::string &ession_id ) = 0;

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
		virtual time_t operator () () const { return time( NULL ); }
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
	virtual void create_session( const std::string &shession_id
			, const std::string &user_id );
	/**
	 * Check if the given session_id is live.
	 * @return true if it is still alive.
	 */
	virtual bool live_session( const std::string &session_id ) const;
	/**
	 * Renew the session if it exists.
	 * @return true if it is still alive.
	 */
	virtual bool renew_session( const std::string &session_id );
	/**
	 * Kill the given session if it exists.
	 */
	virtual void kill_session( const std::string &ession_id );

	/**
	 * Check if any sessions are expired and kill them.
	 * @return the number of sessions killed
	 */
	virtual int kill_expired();

	/**
	 * Check the total number of sessions in the store.
	 */
	virtual int size() const;

private:
	timer_c m_default_timer;
	timer_c *m_timer;
	int m_timeout; // in seconds
	std::map< std::string, time_t > m_store;
};


#endif

