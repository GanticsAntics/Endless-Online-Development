
/* $Id: party.hpp 396 2014-02-04 13:25:25Z sausage $
 * EOSERV is released under the zlib license.
 * See LICENSE.txt for more info.
 */

#ifndef FWD_PARTY_HPP_INCLUDED
#define FWD_PARTY_HPP_INCLUDED

class Party;

enum PartyRequestType : unsigned char
{
	PARTY_REQUEST_JOIN = 0,
	PARTY_REQUEST_INVITE = 1,
};

#endif // FWD_PARTY_HPP_INCLUDED
