
/* $Id: npc_data.hpp 512 2016-01-05 17:45:29Z sausage $
 * EOSERV is released under the zlib license.
 * See LICENSE.txt for more info.
 */

#ifndef FWD_NPC_DATA_HPP_INCLUDED
#define FWD_NPC_DATA_HPP_INCLUDED

class NPC_Data;

struct NPC_Drop;
struct NPC_Shop_Trade_Item;
struct NPC_Shop_Craft_Ingredient;
struct NPC_Shop_Craft_Item;
struct NPC_Citizenship;

enum InnUnsubscribeReply : unsigned char
{
	UNSUBSCRIBE_NOT_CITIZEN = 0,
	UNSUBSCRIBE_UNSUBSCRIBED = 1
};

enum SkillMasterReply : short
{
	SKILLMASTER_REMOVE_ITEMS = 1,
	SKILLMASTER_WRONG_CLASS = 2
};

#endif // FWD_NPC_HPP_INCLUDED
