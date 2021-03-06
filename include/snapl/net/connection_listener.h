#ifndef SNAPL_CONNECTION_LISTENER_H
#define SNAPL_CONNECTION_LISTENER_H
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

namespace snapl {

class connection_i;


/**
 * An abstract class that looks for and handles connections.
 */
class connection_listener_i
{
public:
	/**
	 * Virtual destructor.
	 */
	virtual ~connection_listener_i() {}

	/**
	 * Set this listener to listen on a given port.
	 */
	virtual bool listen( short port ) = 0;

	/**
	 * Get an open connection from the listener that is ready
	 * to be read.  Callers should expect that this may block
	 * while waiting for a connection to become ready.
	 * @return an instance of a connection_i.
	 */
	virtual connection_i * connection() = 0;

	/**
	 * Replace an open connection to be listened to again now that it's
	 * no longer in use.
	 */
	virtual void replace( connection_i * ) = 0;
};


} // namespace

#endif

