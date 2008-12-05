#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H
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


class inbox_i
{
public:
	virtual ~inbox_i() {}

	virtual void queue( connection_i &, message_i * ) = 0;
	virtual void queue( connection_i &, const message_i & ) = 0;
};

class outbox_i
{
public:
	virtual ~outbox_i() {}

	virtual void receive( connection_i & );
};


#endif

