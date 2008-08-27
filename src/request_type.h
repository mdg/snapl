#ifndef REQUEST_TYPE_H
#define REQUEST_TYPE_H
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


/**
 * An enumeration of the possible types of requests.
 */
enum request_type_e
{	RT_NULL
,	RT_CREATE_SESSION
,	RT_SESSION_STATUS
,	RT_KILL_SESSION
,	RT_STORE_TOKEN
,	RT_REQUEST_TOKEN
,	RT_CLOSE
};


#endif

