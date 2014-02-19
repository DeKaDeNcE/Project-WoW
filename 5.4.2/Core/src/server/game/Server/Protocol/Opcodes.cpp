/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Opcodes.h"
#include "WorldSession.h"

OpcodeTable opcodeTable;

template<bool isInValidRange, bool isNonZero>
void OpcodeTable::ValidateAndSetOpcode(uint16 /*opcode*/, char const* /*name*/, SessionStatus /*status*/, PacketProcessing /*processing*/, pOpcodeHandler /*handler*/)
{
    // if for some reason we are here, that means NUM_OPCODE_HANDLERS == 0 (or your compiler is broken)
}

template<>
void OpcodeTable::ValidateAndSetOpcode<true, true>(uint16 opcode, char const* name, SessionStatus status, PacketProcessing processing, pOpcodeHandler handler)
{
    if (_internalTable[opcode] != NULL)
    {
        TC_LOG_ERROR("network", "Tried to override handler of %s with %s (opcode %u)", opcodeTable[opcode]->Name, name, opcode);
        return;
    }

    _internalTable[opcode] = new OpcodeHandler(name, status, processing, handler);
}

template<>
void OpcodeTable::ValidateAndSetOpcode<false, true>(uint16 opcode, char const* /*name*/, SessionStatus /*status*/, PacketProcessing /*processing*/, pOpcodeHandler /*handler*/)
{
    TC_LOG_ERROR("network", "Tried to set handler for an invalid opcode %d", opcode);
}

template<>
void OpcodeTable::ValidateAndSetOpcode<true, false>(uint16 /*opcode*/, char const* name, SessionStatus /*status*/, PacketProcessing /*processing*/, pOpcodeHandler /*handler*/)
{
    TC_LOG_ERROR("network", "Opcode %s got value 0", name);
}

/// Correspondence between opcodes and their names
void OpcodeTable::Initialize()
{
#define DEFINE_OPCODE_HANDLER(opcode, status, processing, handler)                                      \
    ValidateAndSetOpcode<(opcode < NUM_OPCODE_HANDLERS), (opcode != 0)>(opcode, #opcode, status, processing, handler);

    DEFINE_OPCODE_HANDLER(CMSG_ACCEPT_LEVEL_GRANT,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAcceptGrantLevel          );
    DEFINE_OPCODE_HANDLER(CMSG_ACCEPT_TRADE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAcceptTradeOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_ACTIVATETAXI,                            STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleActivateTaxiOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_ACTIVATETAXIEXPRESS,                     STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleActivateTaxiExpressOpcode );
    DEFINE_OPCODE_HANDLER(CMSG_ADDON_REGISTERED_PREFIXES,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddonRegisteredPrefixesOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_ADD_FRIEND,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddFriendOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_ADD_IGNORE,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddIgnoreOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_ADD_VOICE_IGNORE,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_ALTER_APPEARANCE,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAlterAppearance           );
    DEFINE_OPCODE_HANDLER(CMSG_AREATRIGGER,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAreaTriggerOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_AREA_SPIRIT_HEALER_QUERY,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAreaSpiritHealerQueryOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_AREA_SPIRIT_HEALER_QUEUE,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAreaSpiritHealerQueueOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_ACCEPT,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamAcceptOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_CREATE,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamCreateOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_DECLINE,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamDeclineOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_DISBAND,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamDisbandOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_INVITE,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamInviteOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_LEADER,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamLeaderOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_LEAVE,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamLeaveOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_QUERY,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamQueryOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_REMOVE,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamRemoveOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_ARENA_TEAM_ROSTER,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleArenaTeamRosterOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_ATTACKSTOP,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleAttackStopOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_ATTACKSWING,                             STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleAttackSwingOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_HELLO,                           STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionHelloOpcode        ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_LIST_BIDDER_ITEMS,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionListBidderItems    );
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_LIST_ITEMS,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionListItems          );
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_LIST_OWNER_ITEMS,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionListOwnerItems     );
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_LIST_PENDING_SALES,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionListPendingSales   );
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_PLACE_BID,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionPlaceBid           );
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_REMOVE_ITEM,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionRemoveItem         );
    DEFINE_OPCODE_HANDLER(CMSG_AUCTION_SELL_ITEM,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionSellItem           );
    DEFINE_OPCODE_HANDLER(CMSG_AUTH_SESSION,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::Handle_EarlyProccess            );
    DEFINE_OPCODE_HANDLER(CMSG_AUTOBANK_ITEM,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAutoBankItemOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_AUTOEQUIP_ITEM,                          STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleAutoEquipItemOpcode       ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_AUTOEQUIP_ITEM_SLOT,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAutoEquipItemSlotOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_AUTOSTORE_BAG_ITEM,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAutoStoreBagItemOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_AUTOSTORE_BANK_ITEM,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAutoStoreBankItemOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_AUTOSTORE_LOOT_ITEM,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAutostoreLootItemOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_AUTO_DECLINE_GUILD_INVITES,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAutoDeclineGuildInvites   );
    DEFINE_OPCODE_HANDLER(CMSG_BANKER_ACTIVATE,                         STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleBankerActivateOpcode      ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_LEAVE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleBattlefieldLeaveOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_LIST,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBattlefieldListOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_MGR_ENTRY_INVITE_RESPONSE,   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleBfEntryInviteResponse     );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_MGR_EXIT_REQUEST,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleBfExitRequest             );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_MGR_QUEUE_INVITE_RESPONSE,   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleBfQueueInviteResponse     );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_MGR_QUEUE_REQUEST,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_PORT,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBattleFieldPortOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_STATUS,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBattlefieldStatusOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEGROUND_PLAYER_POSITIONS,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleBattlegroundPlayerPositionsOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEMASTER_JOIN,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBattlemasterJoinOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEMASTER_JOIN_ARENA,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBattlemasterJoinArena     );
    DEFINE_OPCODE_HANDLER(CMSG_BATTLEMASTER_JOIN_RATED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_BEGIN_TRADE,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBeginTradeOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_BINDER_ACTIVATE,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBinderActivateOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_BUG,                                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBugOpcode                 );
    DEFINE_OPCODE_HANDLER(CMSG_BUSY_TRADE,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBusyTradeOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_BUYBACK_ITEM,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBuybackItem               );
    DEFINE_OPCODE_HANDLER(CMSG_BUY_BANK_SLOT,                           STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleBuyBankSlotOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_BUY_ITEM,                                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleBuyItemOpcode             );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_ADD_EVENT,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarAddEvent          );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_ARENA_TEAM,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarArenaTeam         );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_COMPLAIN,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarComplain          );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_COPY_EVENT,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarCopyEvent         );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_EVENT_INVITE,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarEventInvite       );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_EVENT_MODERATOR_STATUS,         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarEventModeratorStatus);
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_EVENT_REMOVE_INVITE,            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarEventRemoveInvite );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_EVENT_RSVP,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarEventRsvp         );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_EVENT_SIGNUP,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarEventSignup       );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_EVENT_STATUS,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarEventStatus       );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_GET_CALENDAR,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarGetCalendar       );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_GET_EVENT,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarGetEvent          );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_GET_NUM_PENDING,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarGetNumPending     );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_GUILD_FILTER,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarGuildFilter       );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_REMOVE_EVENT,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarRemoveEvent       );
    DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_UPDATE_EVENT,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarUpdateEvent       );
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_AURA,                             STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleCancelAuraOpcode          ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_AUTO_REPEAT_SPELL,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCancelAutoRepeatSpellOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_CAST,                             STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleCancelCastOpcode          ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_CHANNELLING,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCancelChanneling          );
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_MOUNT_AURA,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCancelMountAuraOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_QUEUED_SPELL,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_TEMP_ENCHANTMENT,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCancelTempEnchantmentOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_CANCEL_TRADE,                            STATUS_LOGGEDIN_OR_RECENTLY_LOGGOUT,    PROCESS_THREADUNSAFE,    &WorldSession::HandleCancelTradeOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_CAST_SPELL,                              STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleCastSpellOpcode           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_CHANGEPLAYER_DIFFICULTY,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE,      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChangeSeatsOnControlledVehicle);
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_ANNOUNCEMENTS,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelAnnouncements      );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_BAN,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelBan                );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_DISPLAY_LIST,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelDisplayListQuery   );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_INVITE,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelInvite             );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_KICK,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelKick               );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_LIST,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelList               );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_MODERATE,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_MODERATOR,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelModerator          );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_MUTE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelMute               );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_OWNER,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelOwner              );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_PASSWORD,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelPassword           );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_ROSTER_INFO,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_SET_OWNER,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelSetOwner           );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_SILENCE_ALL,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_SILENCE_VOICE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_UNBAN,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelUnban              );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_UNMODERATOR,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelUnmoderator        );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_UNMUTE,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelUnmute             );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_UNSILENCE_ALL,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_UNSILENCE_VOICE,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_VOICE_OFF,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelVoiceOnOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_CHANNEL_VOICE_ON,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChannelVoiceOnOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_CHAR_CREATE,                             STATUS_AUTHED,       PROCESS_THREADUNSAFE, &WorldSession::HandleCharCreateOpcode          ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_CHAR_CUSTOMIZE,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCharCustomize             );
    DEFINE_OPCODE_HANDLER(CMSG_CHAR_DELETE,                             STATUS_AUTHED,       PROCESS_THREADUNSAFE, &WorldSession::HandleCharDeleteOpcode          ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_CHAR_ENUM,                               STATUS_AUTHED,       PROCESS_THREADUNSAFE, &WorldSession::HandleCharEnumOpcode            ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_CHAR_FACTION_CHANGE,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCharFactionOrRaceChange   );
    DEFINE_OPCODE_HANDLER(CMSG_CHAR_RACE_CHANGE,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCharFactionOrRaceChange   );
    DEFINE_OPCODE_HANDLER(CMSG_CHAR_RENAME,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCharRenameOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_CHAT_FILTERED,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CHAT_IGNORED,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChatIgnoredOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_CLEAR_CHANNEL_WATCH,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CLEAR_RAID_MARKER,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CLEAR_TRADE_ITEM,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleClearTradeItemOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_ENABLE,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_ENTER_INSTANCE,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_EXIT_INSTANCE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_GET_MAP_INFO,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_GET_PARTY_INFO,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_GET_PLAYER_INFO,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_INSTANCE_COMMAND,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_SKIRMISH_QUEUE_COMMAND,      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMMENTATOR_START_WARGAME,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_COMPLAIN,                                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleComplainOpcode            );
    DEFINE_OPCODE_HANDLER(CMSG_COMPLETE_CINEMATIC,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCompleteCinematic         );
    DEFINE_OPCODE_HANDLER(CMSG_COMPLETE_MOVIE,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CONNECT_TO_FAILED,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_CONTACT_LIST,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleContactListOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_CORPSE_MAP_POSITION_QUERY,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCorpseMapPositionQuery    );
    DEFINE_OPCODE_HANDLER(CMSG_CREATURE_QUERY,                          STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleCreatureQueryOpcode       ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_DANCE_QUERY,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_DEL_FRIEND,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleDelFriendOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_DEL_IGNORE,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleDelIgnoreOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_DEL_VOICE_IGNORE,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_DESTROY_ITEM,                            STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleDestroyItemOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_DISMISS_CONTROLLED_VEHICLE,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleDismissControlledVehicle  );
    DEFINE_OPCODE_HANDLER(CMSG_DISMISS_CRITTER,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleDismissCritter            );
    DEFINE_OPCODE_HANDLER(CMSG_DUEL_ACCEPTED,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleDuelAcceptedOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_DUEL_CANCELLED,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleDuelCancelledOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_EJECT_PASSENGER,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_EMOTE,                                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleEmoteOpcode               );
    DEFINE_OPCODE_HANDLER(CMSG_ENABLETAXI,                              STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleTaxiQueryAvailableNodes   );
    DEFINE_OPCODE_HANDLER(CMSG_ENABLE_NAGLE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_EarlyProccess            );
    DEFINE_OPCODE_HANDLER(CMSG_EQUIPMENT_SET_DELETE,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleEquipmentSetDelete        );
    DEFINE_OPCODE_HANDLER(CMSG_EQUIPMENT_SET_SAVE,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleEquipmentSetSave          );
    DEFINE_OPCODE_HANDLER(CMSG_EQUIPMENT_SET_USE,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleEquipmentSetUse           );
    DEFINE_OPCODE_HANDLER(CMSG_FAR_SIGHT,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleFarSightOpcode            );
    DEFINE_OPCODE_HANDLER(CMSG_FORCE_MOVE_ROOT_ACK,                     STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveRootAck               );
    DEFINE_OPCODE_HANDLER(CMSG_FORCE_MOVE_UNROOT_ACK,                   STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveUnRootAck             );
    DEFINE_OPCODE_HANDLER(CMSG_GAMEOBJECT_QUERY,                        STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleGameObjectQueryOpcode     ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_GAMEOBJ_REPORT_USE,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGameobjectReportUse       );
    DEFINE_OPCODE_HANDLER(CMSG_GAMEOBJ_USE,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGameObjectUseOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_GET_MAIL_LIST,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGetMailList               );
    DEFINE_OPCODE_HANDLER(CMSG_GET_MIRRORIMAGE_DATA,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMirrorImageDataRequest    );
    DEFINE_OPCODE_HANDLER(CMSG_GMRESPONSE_RESOLVE,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGMResponseResolve         );
    DEFINE_OPCODE_HANDLER(CMSG_GMSURVEY_SUBMIT,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGMSurveySubmit            );
    DEFINE_OPCODE_HANDLER(CMSG_GMTICKET_CREATE,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGMTicketCreateOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_GMTICKET_DELETETICKET,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGMTicketDeleteOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_GMTICKET_GETTICKET,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGMTicketGetTicketOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_GMTICKET_SYSTEMSTATUS,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGMTicketSystemStatusOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_GMTICKET_UPDATETEXT,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGMTicketUpdateOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_GM_REPORT_LAG,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleReportLag                 );
    DEFINE_OPCODE_HANDLER(CMSG_GOSSIP_HELLO,                            STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleGossipHelloOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_GOSSIP_SELECT_OPTION,                    STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleGossipSelectOptionOpcode  ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_GRANT_LEVEL,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGrantLevel                );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_ASSISTANT_LEADER,                  STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupAssistantLeaderOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_CHANGE_SUB_GROUP,                  STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupChangeSubGroupOpcode );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_DISBAND,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupDisbandOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_INVITE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupInviteOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_INVITE_RESPONSE,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupInviteResponseOpcode );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_RAID_CONVERT,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupRaidConvertOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_REQUEST_JOIN_UPDATES,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_SET_LEADER,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupSetLeaderOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_SET_ROLES,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleGroupSetRolesOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_SWAP_SUB_GROUP,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupSwapSubGroupOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_GROUP_UNINVITE_GUID,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGroupUninviteGuidOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_ACCEPT,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildAcceptOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_ACHIEVEMENT_MEMBERS,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_ACHIEVEMENT_PROGRESS_QUERY,        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildAchievementProgressQuery);
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_ADD_RANK,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildAddRankOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_ASSIGN_MEMBER_RANK,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildAssignRankOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANKER_ACTIVATE,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankerActivate       );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_BUY_TAB,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankBuyTab           );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_DEPOSIT_MONEY,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankDepositMoney     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_LOG_QUERY,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankLogQuery         );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_MONEY_WITHDRAWN_QUERY,        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankMoneyWithdrawn   );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_QUERY_TAB,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankQueryTab         );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_QUERY_TEXT,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQueryGuildBankTabText     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_SWAP_ITEMS,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankSwapItems        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_UPDATE_TAB,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankUpdateTab        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_WITHDRAW_MONEY,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankWithdrawMoney    );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_CHANGE_NAME_REQUEST,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_DECLINE,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildDeclineOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_DEL_RANK,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildDelRankOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_DEMOTE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildDemoteOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_DISBAND,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildDisbandOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_EVENT_LOG_QUERY,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildEventLogQueryOpcode  );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_INFO_TEXT,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildChangeInfoTextOpcode );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_INVITE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildInviteOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_LEAVE,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildLeaveOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_MEMBER_SEND_SOR_REQUEST,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_MOTD,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildMOTDOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_NEWS_UPDATE_STICKY,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleGuildNewsUpdateStickyOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_PERMISSIONS,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildPermissions          );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_PROMOTE,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildPromoteOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_QUERY,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildQueryOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_QUERY_NEWS,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleGuildQueryNewsOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_QUERY_RANKS,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildQueryRanksOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_REMOVE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildRemoveOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_REPLACE_GUILD_MASTER,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_REQUEST_CHALLENGE_UPDATE,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_REQUEST_MAX_DAILY_XP,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildRequestMaxDailyXP    );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_REQUEST_PARTY_STATE,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildRequestPartyState    );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_ROSTER,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildRosterOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_SET_ACHIEVEMENT_TRACKING,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_SET_GUILD_MASTER,                  STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildSetGuildMaster       );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_SET_NOTE,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildSetNoteOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_SET_RANK_PERMISSIONS,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildSetRankPermissionsOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_GUILD_SWITCH_RANK,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
//	DEFINE_OPCODE_HANDLER(CMSG_GUILD_FINDER_LIST,			            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildSwitchRank		      );
//	DEFINE_OPCODE_HANDLER(CMSG_DELETE_GUILD_REQUEST,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderRequest        );
    DEFINE_OPCODE_HANDLER(CMSG_HEARTH_AND_RESURRECT,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleHearthAndResurrect        );
    DEFINE_OPCODE_HANDLER(CMSG_IGNORE_TRADE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleIgnoreTradeOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_INITIATE_TRADE,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleInitiateTradeOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_INSPECT,                                 STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleInspectOpcode             ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_INSPECT_HONOR_STATS,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleInspectHonorStatsOpcode   ); 
    DEFINE_OPCODE_HANDLER(CMSG_INSTANCE_LOCK_WARNING_RESPONSE,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_ITEM_REFUND,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleItemRefund                );
    DEFINE_OPCODE_HANDLER(CMSG_ITEM_REFUND_INFO,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleItemRefundInfoRequest     );
    DEFINE_OPCODE_HANDLER(CMSG_ITEM_TEXT_QUERY,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleItemTextQuery             );
    DEFINE_OPCODE_HANDLER(CMSG_JOIN_CHANNEL,                            STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleJoinChannel               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_KEEP_ALIVE,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::Handle_EarlyProccess            );
    DEFINE_OPCODE_HANDLER(CMSG_LEARN_PREVIEW_TALENTS,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLearnPreviewTalents       );
    DEFINE_OPCODE_HANDLER(CMSG_LEARN_PREVIEW_TALENTS_PET,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLearnPreviewTalentsPet    );
    DEFINE_OPCODE_HANDLER(CMSG_LEARN_TALENT,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLearnTalentOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_LEAVE_CHANNEL,                           STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleLeaveChannel              ); // 5.4.2 1768
    DEFINE_OPCODE_HANDLER(CMSG_LFG_GET_STATUS,                          STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleLfgGetStatus              );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_JOIN,                                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLfgJoinOpcode             );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_LEAVE,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLfgLeaveOpcode            );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_LFR_JOIN,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_LFR_LEAVE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_LOCK_INFO_REQUEST,                   STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleLfgGetLockInfoOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_PROPOSAL_RESULT,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLfgProposalResultOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_SET_BOOT_VOTE,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLfgSetBootVoteOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_SET_COMMENT,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_SET_ROLES,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLfgSetRolesOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_LFG_TELEPORT,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLfgTeleportOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_ADD_RECRUIT,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderAddRecruit     );
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_BROWSE,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderBrowse         );
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_DECLINE_RECRUIT,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderDeclineRecruit );
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_GET_APPLICATIONS,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderGetApplications);
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_GET_RECRUITS,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderGetRecruits    );
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_POST_REQUEST,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderPostRequest    );
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_REMOVE_RECRUIT,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderRemoveRecruit  );
    DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_SET_GUILD_POST,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildFinderSetGuildPost   );
    DEFINE_OPCODE_HANDLER(CMSG_LIST_INVENTORY,                          STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleListInventoryOpcode       ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_LOAD_SCREEN,                             STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleLoadScreenOpcode          ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_LOGOUT_CANCEL,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLogoutCancelOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_LOGOUT_REQUEST,                          STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleLogoutRequestOpcode       ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_LOG_DISCONNECT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_EarlyProccess            );
    DEFINE_OPCODE_HANDLER(CMSG_LOOT,                                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLootOpcode                );
    DEFINE_OPCODE_HANDLER(CMSG_LOOT_CURRENCY,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_LOOT_MASTER_GIVE,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLootMasterGiveOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_LOOT_METHOD,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLootMethodOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_LOOT_MONEY,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLootMoneyOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_LOOT_RELEASE,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLootReleaseOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_LOOT_ROLL,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleLootRoll                  );
    DEFINE_OPCODE_HANDLER(CMSG_MAIL_CREATE_TEXT_ITEM,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMailCreateTextItem        );
    DEFINE_OPCODE_HANDLER(CMSG_MAIL_DELETE,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMailDelete                );
    DEFINE_OPCODE_HANDLER(CMSG_MAIL_MARK_AS_READ,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMailMarkAsRead            );
    DEFINE_OPCODE_HANDLER(CMSG_MAIL_RETURN_TO_SENDER,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMailReturnToSender        );
    DEFINE_OPCODE_HANDLER(CMSG_MAIL_TAKE_ITEM,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMailTakeItem              );
    DEFINE_OPCODE_HANDLER(CMSG_MAIL_TAKE_MONEY,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMailTakeMoney             );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_ADDON_BATTLEGROUND,          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddonMessagechatOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_ADDON_GUILD,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddonMessagechatOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_ADDON_OFFICER,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddonMessagechatOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_ADDON_PARTY,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddonMessagechatOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_ADDON_RAID,                  STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddonMessagechatOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_ADDON_WHISPER,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleAddonMessagechatOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_AFK,                         STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_BATTLEGROUND,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_CHANNEL,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_DND,                         STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_EMOTE,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_GUILD,                       STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_OFFICER,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_PARTY,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_RAID,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_RAID_WARNING,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_SAY,                         STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_WHISPER,                     STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_MESSAGECHAT_YELL,                        STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_MINIGAME_MOVE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
	DEFINE_OPCODE_HANDLER(CMSG_MINIMAP_PING,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_MOUNTSPECIAL_ANIM,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMountSpecialAnimOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_CHNG_TRANSPORT,                     STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FALL_RESET,                         STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FEATHER_FALL_ACK,                   STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleFeatherFallAck            );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK, STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_FLIGHT_SPEED_CHANGE_ACK,      STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_PITCH_RATE_CHANGE_ACK,        STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_RUN_BACK_SPEED_CHANGE_ACK,    STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_RUN_SPEED_CHANGE_ACK,         STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_SWIM_BACK_SPEED_CHANGE_ACK,   STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_SWIM_SPEED_CHANGE_ACK,        STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_TURN_RATE_CHANGE_ACK,         STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_FORCE_WALK_SPEED_CHANGE_ACK,        STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleForceSpeedChangeAck       );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_GRAVITY_DISABLE_ACK,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_GRAVITY_ENABLE_ACK,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_HOVER_ACK,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMoveHoverAck              );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_KNOCK_BACK_ACK,                     STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveKnockBackAck          );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_NOT_ACTIVE_MOVER,                   STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveNotActiveMover        );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_SET_CAN_FLY,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_SET_CAN_FLY_ACK,                    STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveSetCanFlyAckOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY_ACK, STATUS_UNHANDLED,    PROCESS_INPLACE,    &WorldSession::Handle_NULL              );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_SET_COLLISION_HEIGHT_ACK,           STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleSetCollisionHeightAck     );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_SPLINE_DONE,                        STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveSplineDoneOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_TIME_SKIPPED,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleMoveTimeSkippedOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_MOVE_WATER_WALK_ACK,                     STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveWaterWalkAck          );
    DEFINE_OPCODE_HANDLER(CMSG_NAME_QUERY,                              STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleNameQueryOpcode           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_REALM_NAME_QUERY,                        STATUS_LOGGEDIN,     PROCESS_THREADSAFE, &WorldSession::HandleRealmNameQueryOpcode        ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_NEXT_CINEMATIC_CAMERA,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleNextCinematicCamera       );
    DEFINE_OPCODE_HANDLER(CMSG_NPC_TEXT_QUERY,                          STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleNpcTextQueryOpcode        ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_OBJECT_UPDATE_FAILED,                    STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleObjectUpdateFailedOpcode  ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_OBJECT_UPDATE_RESCUED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_OFFER_PETITION,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleOfferPetitionOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_OPENING_CINEMATIC,                       STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleOpeningCinematic          ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_OPEN_ITEM,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleOpenItemOpcode            );
    DEFINE_OPCODE_HANDLER(CMSG_OPT_OUT_OF_LOOT,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleOptOutOfLootOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_PAGE_TEXT_QUERY,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePageTextQueryOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_PARTY_SILENCE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_PARTY_UNSILENCE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_PETITION_BUY,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionBuyOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_PETITION_QUERY,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionQueryOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_PETITION_SHOWLIST,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionShowListOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_PETITION_SHOW_SIGNATURES,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionShowSignOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_PETITION_SIGN,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionSignOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_PET_ABANDON,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetAbandon                );
    DEFINE_OPCODE_HANDLER(CMSG_PET_ACTION,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetAction                 );
    DEFINE_OPCODE_HANDLER(CMSG_PET_CANCEL_AURA,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetCancelAuraOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_PET_CAST_SPELL,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetCastSpellOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_PET_LEARN_TALENT,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetLearnTalent            );
    DEFINE_OPCODE_HANDLER(CMSG_PET_NAME_QUERY,                          STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandlePetNameQuery              ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_PET_RENAME,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetRename                 );
    DEFINE_OPCODE_HANDLER(CMSG_PET_SET_ACTION,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetSetAction              );
    DEFINE_OPCODE_HANDLER(CMSG_PET_SPELL_AUTOCAST,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetSpellAutocastOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_PET_STOP_ATTACK,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetStopAttack             );
    DEFINE_OPCODE_HANDLER(CMSG_PING,                                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_EarlyProccess            );
    DEFINE_OPCODE_HANDLER(CMSG_PLAYED_TIME,                             STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandlePlayedTime                ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_PLAYER_LOGIN,                            STATUS_AUTHED,       PROCESS_THREADUNSAFE, &WorldSession::HandlePlayerLoginOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_PLAYER_VEHICLE_ENTER,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleEnterPlayerVehicle        );
    DEFINE_OPCODE_HANDLER(CMSG_PLAY_DANCE,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_PUSHQUESTTOPARTY,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePushQuestToParty          );
    DEFINE_OPCODE_HANDLER(CMSG_PVP_LOG_DATA,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandlePVPLogDataOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_BATTLEFIELD_STATE,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_GUILD_MEMBERS_FOR_RECIPE,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_GUILD_MEMBER_RECIPES,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_GUILD_RECIPES,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_GUILD_REWARDS,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleGuildRewardsQueryOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_GUILD_XP,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleGuildQueryXPOpcode        ); // STATUS_UNHANDLED
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_INSPECT_ACHIEVEMENTS,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQueryInspectAchievements  );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_QUESTS_COMPLETED,                  STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQueryQuestsCompleted      );
    DEFINE_OPCODE_HANDLER(CMSG_QUERY_TIME,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQueryTimeOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_ACCEPT_QUEST,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverAcceptQuestOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_CHOOSE_REWARD,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverChooseRewardOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_COMPLETE_QUEST,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverCompleteQuest   );
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_HELLO,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverHelloOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_QUERY_QUEST,                  STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverQueryQuestOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_REQUEST_REWARD,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverRequestRewardOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_STATUS_MULTIPLE_QUERY,        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverStatusMultipleQuery);
    DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_STATUS_QUERY,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleQuestgiverStatusQueryOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_QUESTLOG_REMOVE_QUEST,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestLogRemoveQuest       );
    DEFINE_OPCODE_HANDLER(CMSG_QUEST_CONFIRM_ACCEPT,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestConfirmAccept        );
    DEFINE_OPCODE_HANDLER(CMSG_QUEST_NPC_QUERY,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_QUEST_POI_QUERY,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestPOIQuery             );
    DEFINE_OPCODE_HANDLER(CMSG_QUEST_QUERY,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestQueryOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_RANDOMIZE_CHAR_NAME,                     STATUS_AUTHED,       PROCESS_THREADUNSAFE, &WorldSession::HandleRandomizeCharNameOpcode   ); // 5.4.2 17688
//	DEFINE_OPCODE_HANDLER(CMSG_RANDOM_ROLL,								STATUS_UNHANDLED,    PROCESS_INPLACE,	   &WorldSession::HandleRandomRoll				  ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_READY_FOR_ACCOUNT_DATA_TIMES,            STATUS_AUTHED,       PROCESS_THREADUNSAFE, &WorldSession::HandleReadyForAccountDataTimes  ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_READ_ITEM,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleReadItem                  );
    DEFINE_OPCODE_HANDLER(CMSG_REALM_SPLIT,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRealmSplitOpcode          );
    DEFINE_OPCODE_HANDLER(CMSG_RECLAIM_CORPSE,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleReclaimCorpseOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_REDIRECTION_AUTH_PROOF,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_REFORGE_ITEM,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleReforgeItemOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_REORDER_CHARACTERS,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleReorderCharacters         );
    DEFINE_OPCODE_HANDLER(CMSG_REPAIR_ITEM,                             STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleRepairItemOpcode          ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_REPOP_REQUEST,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRepopRequestOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_REPORT_PVP_AFK,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleReportPvPAFK              );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_ACCOUNT_DATA,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRequestAccountData        );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_CATEGORY_COOLDOWNS,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleRequestCategoryCooldowns  );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_CEMETERY_LIST,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_HOTFIX,                          STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleRequestHotfix             ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_INSPECT_RATED_BG_STATS,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_PARTY_MEMBER_STATS,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRequestPartyMemberStatsOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_PET_INFO,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRequestPetInfoOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_PVP_OPTIONS_ENABLED,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleRequestPvpOptions         );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_PVP_REWARDS,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleRequestPvpReward          );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_RAID_INFO,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRequestRaidInfoOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_RATED_BG_INFO,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleRequestRatedBgInfo        );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_RATED_BG_STATS,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleRequestRatedBgStats       );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_RESEARCH_HISTORY,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_VEHICLE_EXIT,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRequestVehicleExit        );
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_VEHICLE_NEXT_SEAT,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChangeSeatsOnControlledVehicle);
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_VEHICLE_PREV_SEAT,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChangeSeatsOnControlledVehicle);
    DEFINE_OPCODE_HANDLER(CMSG_REQUEST_VEHICLE_SWITCH_SEAT,             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleChangeSeatsOnControlledVehicle);
    DEFINE_OPCODE_HANDLER(CMSG_RESET_FACTION_CHEAT,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_RESET_INSTANCES,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleResetInstancesOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_RESURRECT_RESPONSE,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleResurrectResponseOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_RETURN_TO_GRAVEYARD,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleReturnToGraveyard         );
    DEFINE_OPCODE_HANDLER(CMSG_ROLE_POLL_BEGIN,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SAVE_CUF_PROFILES,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleSaveCUFProfiles           );
    DEFINE_OPCODE_HANDLER(CMSG_SELF_RES,                                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSelfResOpcode             );
    DEFINE_OPCODE_HANDLER(CMSG_SELL_ITEM,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSellItemOpcode            );
    DEFINE_OPCODE_HANDLER(CMSG_SEND_MAIL,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSendMail                  );
    DEFINE_OPCODE_HANDLER(CMSG_SEND_SOR_REQUEST_VIA_ADDRESS,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SEND_SOR_REQUEST_VIA_BNET_ACCOUNT_ID,    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SETSHEATHED,                             STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleSetSheathedOpcode         ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_SET_ACTIONBAR_TOGGLES,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetActionBarToggles       );
    DEFINE_OPCODE_HANDLER(CMSG_SET_ACTION_BUTTON,                       STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleSetActionButtonOpcode     ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_SET_ACTIVE_MOVER,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetActiveMoverOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_SET_ACTIVE_VOICE_CHANNEL,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetActiveVoiceChannel     ); // STATUS_UNHANDLED
    DEFINE_OPCODE_HANDLER(CMSG_SET_ALLOW_LOW_LEVEL_RAID1,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_ALLOW_LOW_LEVEL_RAID2,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_CHANNEL_WATCH,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetChannelWatch           );
    DEFINE_OPCODE_HANDLER(CMSG_SET_CONTACT_NOTES,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetContactNotesOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_CURRENCY_FLAGS,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_EVERYONE_IS_ASSISTANT,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_FACTION_ATWAR,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetFactionAtWar           );
    DEFINE_OPCODE_HANDLER(CMSG_SET_FACTION_INACTIVE,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetFactionInactiveOpcode  );
    DEFINE_OPCODE_HANDLER(CMSG_SET_GUILD_BANK_TEXT,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetGuildBankTabText       );
    DEFINE_OPCODE_HANDLER(CMSG_SET_PET_SLOT,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_PLAYER_DECLINED_NAMES,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetPlayerDeclinedNames    );
    DEFINE_OPCODE_HANDLER(CMSG_SET_PREFERED_CEMETERY,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_PRIMARY_TALENT_TREE,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandeSetTalentSpecialization    );
    DEFINE_OPCODE_HANDLER(CMSG_SET_RELATIVE_POSITION,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_SAVED_INSTANCE_EXTEND,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetSavedInstanceExtend    );
    DEFINE_OPCODE_HANDLER(CMSG_SET_SELECTION,                           STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleSetSelectionOpcode        ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_SET_TAXI_BENCHMARK_MODE,                 STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetTaxiBenchmarkOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_SET_TITLE,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetTitleOpcode            );
    DEFINE_OPCODE_HANDLER(CMSG_SET_TRADE_CURRENCY,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_TRADE_GOLD,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetTradeGoldOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_SET_TRADE_ITEM,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetTradeItemOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_SET_VEHICLE_REC_ID_ACK,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SET_WATCHED_FACTION,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetWatchedFactionOpcode   );
    DEFINE_OPCODE_HANDLER(CMSG_SHOWING_CLOAK,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleShowingCloakOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_SHOWING_HELM,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleShowingHelmOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_SOCKET_GEMS,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSocketOpcode              );
    DEFINE_OPCODE_HANDLER(CMSG_SPELLCLICK,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSpellClick                );
    DEFINE_OPCODE_HANDLER(CMSG_SPIRIT_HEALER_ACTIVATE,                  STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSpiritHealerActivateOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_SPLIT_ITEM,                              STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleSplitItemOpcode           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_STANDSTATECHANGE,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleStandStateChangeOpcode    );
    DEFINE_OPCODE_HANDLER(CMSG_STOP_DANCE,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SUBMIT_BUG,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SUBMIT_COMPLAIN,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SUGGESTION_SUBMIT,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SUMMON_RESPONSE,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSummonResponseOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_SUSPEND_TOKEN,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_SWAP_INV_ITEM,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSwapInvItemOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_SWAP_ITEM,                               STATUS_LOGGEDIN,     PROCESS_THREADUNSAFE, &WorldSession::HandleSwapItem                  ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_SYNC_DANCE,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_TAXINODE_STATUS_QUERY,                   STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleTaxiNodeStatusQueryOpcode );
    DEFINE_OPCODE_HANDLER(CMSG_TAXIQUERYAVAILABLENODES,                 STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleTaxiQueryAvailableNodes   );
    DEFINE_OPCODE_HANDLER(CMSG_TELEPORT_TO_UNIT,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_TEXT_EMOTE,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTextEmoteOpcode           );
    DEFINE_OPCODE_HANDLER(CMSG_TIME_ADJUSTMENT_RESPONSE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_TIME_SYNC_RESP,                          STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleTimeSyncResp              ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_TIME_SYNC_RESP_FAILED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_TOGGLE_PVP,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTogglePvP                 );
    DEFINE_OPCODE_HANDLER(CMSG_TOTEM_DESTROYED,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTotemDestroyed            );
    DEFINE_OPCODE_HANDLER(CMSG_TRAINER_BUY_SPELL,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTrainerBuySpellOpcode     );
    DEFINE_OPCODE_HANDLER(CMSG_TRAINER_LIST,                            STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTrainerListOpcode         );
    DEFINE_OPCODE_HANDLER(CMSG_TRANSMOGRIFY_ITEMS,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTransmogrifyItems         );
    DEFINE_OPCODE_HANDLER(CMSG_TURN_IN_PETITION,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTurnInPetitionOpcode      );
    DEFINE_OPCODE_HANDLER(CMSG_TUTORIAL_CLEAR,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTutorialClear             );
    DEFINE_OPCODE_HANDLER(CMSG_TUTORIAL_FLAG,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTutorialFlag              );
    DEFINE_OPCODE_HANDLER(CMSG_TUTORIAL_RESET,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTutorialReset             );
    DEFINE_OPCODE_HANDLER(CMSG_UNACCEPT_TRADE,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleUnacceptTradeOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_UNLEARN_SKILL,                           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleUnlearnSkillOpcode        );
    DEFINE_OPCODE_HANDLER(CMSG_UNLEARN_SPECIALIZATION,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_UNREGISTER_ALL_ADDON_PREFIXES,           STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleUnregisterAddonPrefixesOpcode);
    DEFINE_OPCODE_HANDLER(CMSG_UPDATE_ACCOUNT_DATA,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleUpdateAccountData         );
    DEFINE_OPCODE_HANDLER(CMSG_UPDATE_MISSILE_TRAJECTORY,               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleUpdateMissileTrajectory   );
    DEFINE_OPCODE_HANDLER(CMSG_UPDATE_PROJECTILE_POSITION,              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleUpdateProjectilePosition  );
    DEFINE_OPCODE_HANDLER(CMSG_USED_FOLLOW,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_USE_ITEM,                                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleUseItemOpcode             );
    DEFINE_OPCODE_HANDLER(CMSG_VIOLENCE_LEVEL,                          STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleViolenceLevel             ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_VOICE_SESSION_ENABLE,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleVoiceSessionEnableOpcode  );
    DEFINE_OPCODE_HANDLER(CMSG_VOID_STORAGE_QUERY,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleVoidStorageQuery          );
    DEFINE_OPCODE_HANDLER(CMSG_VOID_STORAGE_TRANSFER,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleVoidStorageTransfer       );
    DEFINE_OPCODE_HANDLER(CMSG_VOID_STORAGE_UNLOCK,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleVoidStorageUnlock         );
    DEFINE_OPCODE_HANDLER(CMSG_VOID_SWAP_ITEM,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::HandleVoidSwapItem              );
    DEFINE_OPCODE_HANDLER(CMSG_WARDEN_DATA,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleWardenDataOpcode          ); // STATUS_UNHANDLED
    DEFINE_OPCODE_HANDLER(CMSG_WARGAME_ACCEPT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_WARGAME_START,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(CMSG_WHO,                                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleWhoOpcode                 );
    DEFINE_OPCODE_HANDLER(CMSG_WHOIS,                                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleWhoisOpcode               );
    DEFINE_OPCODE_HANDLER(CMSG_WORLD_STATE_UI_TIMER_UPDATE,             STATUS_LOGGEDIN,     PROCESS_INPLACE,      &WorldSession::HandleWorldStateUITimerUpdate   ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(CMSG_WORLD_TELEPORT,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleWorldTeleportOpcode       );
    DEFINE_OPCODE_HANDLER(CMSG_WRAP_ITEM,                               STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleWrapItemOpcode            );
    DEFINE_OPCODE_HANDLER(CMSG_ZONEUPDATE,                              STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleZoneUpdateOpcode          );
    DEFINE_OPCODE_HANDLER(MSG_CHANNEL_START,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(MSG_CHANNEL_UPDATE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(MSG_CORPSE_QUERY,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleCorpseQueryOpcode         );
    DEFINE_OPCODE_HANDLER(MSG_INSPECT_ARENA_TEAMS,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleInspectArenaTeamsOpcode   );
    DEFINE_OPCODE_HANDLER(MSG_LIST_STABLED_PETS,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleListStabledPetsOpcode     );
    DEFINE_OPCODE_HANDLER(MSG_MINIMAP_PING,                             STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleMinimapPingOpcode         );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_CHARM_TELEPORT_CHEAT,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_FALL_LAND,                           STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_HEARTBEAT,                           STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_JUMP,                                STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_FACING,                          STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_PITCH,                           STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_RUN_MODE,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_WALK_MODE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_ASCEND,                        STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_BACKWARD,                      STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_DESCEND,                       STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_FORWARD,                       STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_PITCH_DOWN,                    STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_PITCH_UP,                      STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_STRAFE_LEFT,                   STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_STRAFE_RIGHT,                  STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_SWIM,                          STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_TURN_LEFT,                     STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_START_TURN_RIGHT,                    STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_STOP,                                STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_STOP_ASCEND,                         STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_STOP_PITCH,                          STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_STOP_STRAFE,                         STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_STOP_SWIM,                           STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_STOP_TURN,                           STATUS_LOGGEDIN,     PROCESS_THREADSAFE,   &WorldSession::HandleMovementOpcodes           ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(MSG_MOVE_TELEPORT,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_TELEPORT_ACK,                        STATUS_UNHANDLED,    PROCESS_THREADSAFE,   &WorldSession::HandleMoveTeleportAck           );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_TELEPORT_CHEAT,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_TIME_SKIPPED,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_TOGGLE_COLLISION_CHEAT,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_MOVE_WORLDPORT_ACK,                       STATUS_TRANSFER,     PROCESS_THREADUNSAFE, &WorldSession::HandleMoveWorldportAckOpcode    );
    DEFINE_OPCODE_HANDLER(MSG_NOTIFY_PARTY_SQUELCH,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_PARTY_ASSIGNMENT,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePartyAssignmentOpcode     );
    DEFINE_OPCODE_HANDLER(MSG_PETITION_DECLINE,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionDeclineOpcode     );
    DEFINE_OPCODE_HANDLER(MSG_PETITION_RENAME,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionRenameOpcode      );
    DEFINE_OPCODE_HANDLER(MSG_QUERY_NEXT_MAIL_TIME,                     STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQueryNextMailTime         );
    DEFINE_OPCODE_HANDLER(MSG_QUEST_PUSH_RESULT,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleQuestPushResult           );
    DEFINE_OPCODE_HANDLER(MSG_RAID_READY_CHECK,                         STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRaidReadyCheckOpcode      );
    DEFINE_OPCODE_HANDLER(MSG_RAID_READY_CHECK_CONFIRM,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(MSG_RAID_READY_CHECK_FINISHED,                STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRaidReadyCheckFinishedOpcode);
    DEFINE_OPCODE_HANDLER(MSG_RAID_TARGET_UPDATE,                       STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRaidTargetUpdateOpcode    );
    DEFINE_OPCODE_HANDLER(MSG_RANDOM_ROLL,                              STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleRandomRollOpcode          );
    DEFINE_OPCODE_HANDLER(MSG_SAVE_GUILD_EMBLEM,                        STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSaveGuildEmblemOpcode     );
    DEFINE_OPCODE_HANDLER(MSG_SET_DUNGEON_DIFFICULTY,                   STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetDungeonDifficultyOpcode);
    DEFINE_OPCODE_HANDLER(MSG_SET_RAID_DIFFICULTY,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleSetRaidDifficultyOpcode   );
    DEFINE_OPCODE_HANDLER(MSG_TABARDVENDOR_ACTIVATE,                    STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTabardVendorActivateOpcode);
    DEFINE_OPCODE_HANDLER(MSG_TALENT_WIPE_CONFIRM,                      STATUS_UNHANDLED,    PROCESS_THREADUNSAFE, &WorldSession::HandleTalentWipeConfirmOpcode   );
    DEFINE_OPCODE_HANDLER(MSG_VERIFY_CONNECTIVITY,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_EarlyProccess            );
    DEFINE_OPCODE_HANDLER(SMSG_ACCOUNT_DATA_TIMES,                      STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_ACCOUNT_INFO_RESPONSE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ACCOUNT_RESTRICTED_WARNING,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ACHIEVEMENT_DELETED,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ACHIEVEMENT_EARNED,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ACTION_BUTTONS,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_ACTIVATETAXIREPLY,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ADDON_INFO,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ADD_RUNE_POWER,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AI_REACTION,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ALL_ACHIEVEMENT_DATA,                    STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_AREA_SPIRIT_HEALER_TIME,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AREA_TRIGGER_MESSAGE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AREA_TRIGGER_MOVEMENT_UPDATE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_ERROR,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_UNIT_DESTROYED,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_TEAM_CHANGE_FAILED_QUEUED,         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_TEAM_COMMAND_RESULT,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_TEAM_EVENT,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_TEAM_INVITE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_TEAM_QUERY_RESPONSE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_TEAM_ROSTER,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ARENA_TEAM_STATS,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ATTACKERSTATEUPDATE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ATTACKSTART,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ATTACKSTOP,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ATTACKSWING_BADFACING,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ATTACKSWING_CANT_ATTACK,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ATTACKSWING_DEADTARGET,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ATTACKSWING_NOTINRANGE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_BIDDER_LIST_RESULT,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_BIDDER_NOTIFICATION,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_COMMAND_RESULT,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_HELLO,                           STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_LIST_PENDING_SALES,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_LIST_RESULT,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_OWNER_LIST_RESULT,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_OWNER_NOTIFICATION,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AUCTION_REMOVED_NOTIFICATION,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AURA_POINTS_DEPLETED,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AURA_UPDATE,                             STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_AUTH_CHALLENGE,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_AUTH_RESPONSE,                           STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_AVAILABLE_VOICE_CHANNEL,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_AVERAGE_ITEM_LEVEL_INFORM,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BARBER_SHOP_RESULT,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_LIST,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_EJECTED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_EJECT_PENDING,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_ENTERED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_ENTRY_INVITE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_EXIT_REQUEST,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_QUEUE_INVITE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_QUEUE_REQUEST_RESPONSE,  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_MGR_STATE_CHANGE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_PLAYER_POSITIONS,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_PORT_DENIED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_RATED_INFO,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_STATUS,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_STATUS_QUEUED,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_STATUS_ACTIVE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_STATUS_NEEDCONFIRMATION,     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_STATUS_WAITFORGROUPS,        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEFIELD_STATUS_FAILED,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEGROUND_INFO_THROTTLED,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEGROUND_PLAYER_JOINED,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BATTLEGROUND_PLAYER_LEFT,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BINDER_CONFIRM,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BINDPOINTUPDATE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BREAK_TARGET,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BUY_FAILED,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_BUY_ITEM,                                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_ARENA_TEAM,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_CLEAR_PENDING_ACTION,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_COMMAND_RESULT,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_INVITE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_INVITE_ALERT,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_INVITE_NOTES,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_INVITE_NOTES_ALERT,       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_INVITE_REMOVED,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_INVITE_REMOVED_ALERT,     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_INVITE_STATUS_ALERT,      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_MODERATOR_STATUS_ALERT,   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_REMOVED_ALERT,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_STATUS,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_EVENT_UPDATED_ALERT,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_FILTER_GUILD,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_RAID_LOCKOUT_ADDED,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_RAID_LOCKOUT_REMOVED,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_RAID_LOCKOUT_UPDATED,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_SEND_CALENDAR,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_SEND_EVENT,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_SEND_NUM_PENDING,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CAMERA_SHAKE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CANCEL_AUTO_REPEAT,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CANCEL_COMBAT,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CAST_FAILED,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHANNEL_LIST,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHANNEL_MEMBER_COUNT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHANNEL_NOTIFY,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_CHARACTER_LOGIN_FAILED,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAR_CREATE,                             STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_CHAR_CUSTOMIZE,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAR_DELETE,                             STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_CHAR_ENUM,                               STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_CHAR_FACTION_CHANGE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAR_RENAME,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_IGNORED_ACCOUNT_MUTED,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_NOT_IN_PARTY,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_PLAYER_AMBIGUOUS,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_PLAYER_NOT_FOUND,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_RESTRICTED,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_SERVER_DISCONNECTED,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_SERVER_RECONNECTED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CHAT_WRONG_FACTION,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CLEAR_BOSS_EMOTES,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CLEAR_COOLDOWN,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CLEAR_COOLDOWNS,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CLEAR_FAR_SIGHT_IMMEDIATE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CLEAR_TARGET,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CLIENTCACHE_VERSION,                     STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_CLIENT_CONTROL_UPDATE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMBAT_EVENT_FAILED,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMMENTATOR_MAP_INFO,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMMENTATOR_PARTY_INFO,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMMENTATOR_PLAYER_INFO,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMMENTATOR_SKIRMISH_QUEUE_RESULT1,      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMMENTATOR_SKIRMISH_QUEUE_RESULT2,      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMMENTATOR_STATE_CHANGED,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMPLAIN_RESULT,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMPRESSED_MOVES,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMSAT_CONNECT_FAIL,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMSAT_DISCONNECT,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COMSAT_RECONNECT_TRY,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CONTACT_LIST,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CONVERT_RUNE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COOLDOWN_CHEAT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_COOLDOWN_EVENT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CORPSE_MAP_POSITION_QUERY_RESPONSE,      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CORPSE_NOT_IN_INSTANCE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CORPSE_RECLAIM_DELAY,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CREATURE_QUERY_RESPONSE,                 STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_CRITERIA_DELETED,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CRITERIA_UPDATE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CROSSED_INEBRIATION_THRESHOLD,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CURRENCY_LOOT_REMOVED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CURRENCY_LOOT_RESTORED,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_CUSTOM_LOAD_SCREEN,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DAMAGE_CALC_LOG,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DANCE_QUERY_RESPONSE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DB_REPLY,                                STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_DEATH_RELEASE_LOC,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DEBUG_RUNE_REGEN,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DEFENSE_MESSAGE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DESTROY_OBJECT,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_DESTRUCTIBLE_BUILDING_DAMAGE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DIFFERENT_INSTANCE_FROM_PARTY,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DISENCHANT_CREDIT,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DISMOUNT,                                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DISMOUNTRESULT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DISPEL_FAILED,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DISPLAY_GAME_ERROR,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DONT_AUTO_PUSH_SPELLS_TO_ACTION_BAR,     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DROP_NEW_CONNECTION,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DUEL_COMPLETE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DUEL_COUNTDOWN,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DUEL_INBOUNDS,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DUEL_OUTOFBOUNDS,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DUEL_REQUESTED,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DUEL_WINNER,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DUMP_RIDE_TICKETS_RESPONSE,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_DURABILITY_DAMAGE_DEATH,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ECHO_PARTY_SQUELCH,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_EMOTE,                                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ENABLE_BARBER_SHOP,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ENCHANTMENTLOG,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ENVIRONMENTALDAMAGELOG,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_EQUIPMENT_SET_LIST,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_EQUIPMENT_SET_SAVED,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_EQUIPMENT_SET_USE_RESULT,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_EXPECTED_SPAM_RECORDS,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_EXPLORATION_EXPERIENCE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FAILED_PLAYER_CONDITION,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FEATURE_SYSTEM_STATUS,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FEIGN_DEATH_RESISTED,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FISH_ESCAPED,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FISH_NOT_HOOKED,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FLIGHT_SPLINE_SYNC,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FLOOD_DETECTED,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FORCED_DEATH_UPDATE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FORCE_SEND_QUEUED_PACKETS,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FORCE_SET_VEHICLE_REC_ID,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FORGE_MASTER_SET,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_FRIEND_STATUS,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAMEOBJECT_CUSTOM_ANIM,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAMEOBJECT_DESPAWN_ANIM,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAMEOBJECT_PAGETEXT,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAMEOBJECT_QUERY_RESPONSE,               STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_GAMEOBJECT_RESET_STATE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAMESPEED_SET,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAMETIME_SET,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAMETIME_UPDATE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAME_EVENT_DEBUG_LOG,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GAME_OBJECT_ACTIVATE_ANIM_KIT,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMRESPONSE_DB_ERROR,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMRESPONSE_RECEIVED,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMRESPONSE_STATUS_UPDATE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMTICKET_CREATE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMTICKET_DELETETICKET,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMTICKET_GETTICKET,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMTICKET_SYSTEMSTATUS,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GMTICKET_UPDATETEXT,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GM_MESSAGECHAT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GM_PLAYER_INFO,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GM_TICKET_STATUS_UPDATE,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GODMODE,                                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GOSSIP_COMPLETE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GOSSIP_MESSAGE,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_GOSSIP_POI,                              STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_GROUPACTION_THROTTLED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_CANCEL,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_DECLINE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_DESTROYED,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_INVITE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_LIST,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_SET_LEADER,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_SET_ROLE,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GROUP_UNINVITE,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_ACHIEVEMENT_DATA,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_ACHIEVEMENT_DELETED,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_ACHIEVEMENT_EARNED,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_ACHIEVEMENT_MEMBERS,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_BANK_LIST,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_BANK_LOG_QUERY_RESULT,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_BANK_MONEY_WITHDRAWN,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_BANK_QUERY_TEXT_RESULT,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_CHALLENGE_COMPLETED,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_CHALLENGE_UPDATED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_CHANGE_NAME_RESULT,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_COMMAND_RESULT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_COMMAND_RESULT_2,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_CRITERIA_DATA,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_CRITERIA_DELETED,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_DECLINE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_EVENT,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_EVENT_LOG_QUERY_RESULT,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_FLAGGED_FOR_RENAME,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_INVITE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_INVITE_CANCEL,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_MAX_DAILY_XP,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_MEMBERS_FOR_RECIPE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_MEMBER_DAILY_RESET,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_MEMBER_RECIPES,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_MEMBER_UPDATE_NOTE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_MOVE_COMPLETE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_MOVE_STARTING,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_NEWS_DELETED,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_NEWS_UPDATE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_PARTY_STATE_RESPONSE,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_PERMISSIONS_QUERY_RESULTS,         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_QUERY_RESPONSE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_RANK,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_RANKS_UPDATE,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_RECIPES,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_RENAMED,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_REPUTATION_REACTION_CHANGED,       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_REPUTATION_WEEKLY_CAP,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_RESET,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_REWARDS_LIST,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_ROSTER,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_UPDATE_ROSTER,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_XP,                                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_GUILD_XP_GAIN,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_HEALTH_UPDATE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_HIGHEST_THREAT_UPDATE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_HOTFIX_INFO,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_HOTFIX_NOTIFY,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INITIALIZE_FACTIONS,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INITIAL_SPELLS,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_INIT_CURRENCY,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INIT_WORLD_STATES,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INSPECT_HONOR_STATS,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INSPECT_RATED_BG_STATS,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INSPECT_RESULTS_UPDATE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INSPECT_TALENT,                          STATUS_UNHANDLED,    PROCESS_THREADUNSAFE,    &WorldSession::Handle_ServerSide            );
    DEFINE_OPCODE_HANDLER(SMSG_INSTANCE_LOCK_WARNING_QUERY,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INSTANCE_RESET,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INSTANCE_RESET_FAILED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INSTANCE_SAVE_CREATED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INVALIDATE_DANCE,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INVALIDATE_PLAYER,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INVALID_PROMOTION_CODE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_INVENTORY_CHANGE_FAILURE,                STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_ADD_PASSIVE,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_COOLDOWN,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_ENCHANT_TIME_UPDATE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_EXPIRE_PURCHASE_REFUND,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_PUSH_RESULT,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_REFUND_INFO_RESPONSE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_REFUND_RESULT,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_REMOVE_PASSIVE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_SEND_PASSIVE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_TEXT_QUERY_RESPONSE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ITEM_TIME_UPDATE,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LEARNED_DANCE_MOVES,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LEARNED_SPELL,                           STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LEVELUP_INFO,                            STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LFG_BOOT_PROPOSAL_UPDATE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_DISABLED,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_JOIN_RESULT,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_OFFER_CONTINUE,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_PARTY_INFO,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_PLAYER_INFO,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_PLAYER_REWARD,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_PROPOSAL_UPDATE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_QUEUE_STATUS,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_ROLE_CHECK_UPDATE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_ROLE_CHOSEN,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_SLOT_INVALID,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_TELEPORT_DENIED,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_UPDATE_SEARCH,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_UPDATE_STATUS,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LFG_UPDATE_STATUS_NONE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_APPLICANT_LIST_UPDATED,         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_APPLICATIONS_LIST_CHANGED,      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_BROWSE_UPDATED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_COMMAND_RESULT,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_MEMBERSHIP_LIST_UPDATED,        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_POST_UPDATED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_RECRUIT_LIST_UPDATED,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LIST_INVENTORY,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LOAD_CUF_PROFILES,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOGIN_SETTIMESPEED,                      STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LOGIN_VERIFY_WORLD,                      STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LOGOUT_CANCEL_ACK,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOGOUT_COMPLETE,                         STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LOGOUT_RESPONSE,                         STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LOG_XPGAIN,                              STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_ALL_PASSED,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_CLEAR_MONEY,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_CONTENTS,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_ITEM_NOTIFY,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_LIST,                               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_MASTER_LIST,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_MONEY_NOTIFY,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_RELEASE_RESPONSE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_REMOVED,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_RESPONSE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_ROLL,                               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_ROLL_WON,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_SLOT_CHANGED,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_LOOT_START_ROLL,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MAIL_LIST_RESULT,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MAP_OBJ_EVENTS,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MEETINGSTONE_COMPLETE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MEETINGSTONE_IN_PROGRESS,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MESSAGECHAT,                             STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MESSAGE_BOX,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MINIGAME_SETUP,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MINIGAME_STATE,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
	DEFINE_OPCODE_HANDLER(SMSG_MINIMAP_PING,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MIRRORIMAGE_DATA,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MISSILE_CANCEL,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MODIFY_COOLDOWN,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MONEY_NOTIFY,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MONSTER_MOVE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MONSTER_MOVE_TRANSPORT,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOTD,                                    STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MOUNTRESULT,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOUNTSPECIAL_ANIM,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_COLLISION_DISABLE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_COLLISION_ENABLE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_FEATHER_FALL,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_GRAVITY_DISABLE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_GRAVITY_ENABLE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_KNOCK_BACK,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_LAND_WALK,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_NORMAL_FALL,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_ROOT,                               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_ACTIVE_MOVER,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_CAN_FLY,                        STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY, STATUS_UNHANDLED,    PROCESS_INPLACE,    &WorldSession::Handle_ServerSide            );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_COLLISION_HEIGHT,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_COMPOUND_STATE,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_FLIGHT_BACK_SPEED,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_FLIGHT_SPEED,                   STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_HOVER,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_PITCH_RATE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_RUN_BACK_SPEED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_RUN_SPEED,                      STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_SWIM_BACK_SPEED,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_SWIM_SPEED,                     STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_TURN_RATE,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_WALK_SPEED,                     STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UNROOT,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UNSET_CAN_FLY,                      STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UNSET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY, STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide        );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UNSET_HOVER,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_COLLISION_HEIGHT,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_FLIGHT_BACK_SPEED,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_FLIGHT_SPEED,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_KNOCK_BACK,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_PITCH_RATE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_RUN_BACK_SPEED,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_RUN_SPEED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_SWIM_BACK_SPEED,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_SWIM_SPEED,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_TELEPORT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_TURN_RATE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_UPDATE_WALK_SPEED,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MOVE_WATER_WALK,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_MULTIPLE_PACKETS,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_NAME_QUERY_RESPONSE,                     STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_REALM_NAME_QUERY_RESPONSE,               STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_NEW_TAXI_PATH,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_NEW_WORLD,                               STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_NEW_WORLD_ABORT,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_NOTIFICATION,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_NOTIFY_DANCE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_NOTIFY_DEST_LOC_SPELL_CAST,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_NPC_TEXT_UPDATE,                         STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_OFFER_PETITION_ERROR,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ON_CANCEL_EXPECTED_RIDE_VEHICLE_AURA,    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_OPEN_CONTAINER,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_OPEN_LFG_DUNGEON_FINDER,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_OVERRIDE_LIGHT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PAGE_TEXT_QUERY_RESPONSE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PARTYKILLLOG,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PARTY_COMMAND_RESULT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PARTY_MEMBER_STATS,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PARTY_MEMBER_STATS_FULL,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PAUSE_MIRROR_TIMER,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PERIODICAURALOG,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PETGODMODE,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PETITION_ALREADY_SIGNED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PETITION_QUERY_RESPONSE,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PETITION_SHOWLIST,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PETITION_SHOW_SIGNATURES,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PETITION_SIGN_RESULTS,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_ACTION_FEEDBACK,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_ACTION_SOUND,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_ADDED,                               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_BROKEN,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_CAST_FAILED,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_DISMISS_SOUND,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_GUIDS,                               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_LEARNED_SPELL,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_MODE,                                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_NAME_INVALID,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_NAME_QUERY_RESPONSE,                 STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_PET_REMOVED_SPELL,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_RENAMEABLE,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_SLOT_UPDATED,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_SPELLS,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_TAME_FAILURE,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PET_UPDATE_COMBO_POINTS,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAYED_TIME,                             STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_PLAYERBINDERROR,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAYERBOUND,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAYER_DIFFICULTY_CHANGE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAYER_MOVE,                             STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_PLAYER_SKINNED,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAYER_VEHICLE_DATA,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_DANCE,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_MUSIC,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_OBJECT_SOUND,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_ONE_SHOT_ANIM_KIT,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_SOUND,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_SPELL_VISUAL,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_SPELL_VISUAL_KIT,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PLAY_TIME_WARNING,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PONG,                                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_POWER_UPDATE,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PRE_RESURRECT,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PROCRESIST,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PROPOSE_LEVEL_GRANT,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PVP_CREDIT,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PVP_LOG_DATA,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_PVP_OPTIONS_ENABLED,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUERY_QUESTS_COMPLETED_RESPONSE,         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUERY_TIME_RESPONSE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_OFFER_REWARD,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_QUEST_COMPLETE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_QUEST_DETAILS,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_QUEST_FAILED,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_QUEST_INVALID,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_QUEST_LIST,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_REQUEST_ITEMS,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_STATUS,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTGIVER_STATUS_MULTIPLE,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTLOG_FULL,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTUPDATE_ADD_KILL,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTUPDATE_ADD_PVP_KILL,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTUPDATE_COMPLETE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTUPDATE_FAILED,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUESTUPDATE_FAILEDTIMER,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUEST_CONFIRM_ACCEPT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUEST_FORCE_REMOVE,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUEST_NPC_QUERY_RESPONSE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUEST_POI_QUERY_RESPONSE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_QUEST_QUERY_RESPONSE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RAID_GROUP_ONLY,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RAID_INSTANCE_INFO,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RAID_INSTANCE_MESSAGE,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RAID_MARKERS_CHANGED,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RAID_READY_CHECK_THROTTLED_ERROR,        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RAID_SUMMON_FAILED,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RANDOMIZE_CHAR_NAME,                     STATUS_NEVER,        PROCESS_THREADUNSAFE, &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
//	DEFINE_OPCODE_HANDLER(SMSG_RANDOM_ROLL,								STATUS_UNHANDLED,    PROCESS_INPLACE,	   &WorldSession::HandleRandomRoll				  ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_RATED_BG_RATING,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RATED_BG_STATS,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_READ_ITEM_FAILED,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_READ_ITEM_OK,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REALM_SPLIT,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REAL_GROUP_UPDATE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RECEIVED_MAIL,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REDIRECT_CLIENT,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REFER_A_FRIEND_EXPIRED,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REFER_A_FRIEND_FAILURE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REFORGE_RESULT,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REMOVED_SPELL,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REPORT_PVP_AFK_RESULT,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REQUEST_CEMETERY_LIST_RESPONSE,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_REQUEST_PVP_REWARDS_RESPONSE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RESEARCH_COMPLETE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RESEARCH_SETUP_HISTORY,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RESET_COMPRESSION_CONTEXT,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RESET_FAILED_NOTIFY,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RESPOND_INSPECT_ACHIEVEMENTS,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RESURRECT_REQUEST,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RESYNC_RUNES,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ROLE_POLL_BEGIN,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_RWHOIS,                                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SELL_ITEM,                               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SEND_MAIL_RESULT,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SEND_UNLEARN_SPELLS,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SERVERTIME,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SERVER_FIRST_ACHIEVEMENT,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SERVER_INFO_RESPONSE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SERVER_MESSAGE,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SERVER_PERF,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_DF_FAST_LAUNCH_RESULT,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_FACTION_ATWAR,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_FACTION_STANDING,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_FACTION_VISIBLE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_FLAT_SPELL_MODIFIER,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_FORCED_REACTIONS,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_PCT_SPELL_MODIFIER,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_PHASE_SHIFT,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_PLAYER_DECLINED_NAMES_RESULT,        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_PLAY_HOVER_ANIM,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_PROFICIENCY,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SET_PROJECTILE_POSITION,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SHOWTAXINODES,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SHOW_BANK,                               STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_SHOW_RATINGS,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SOCKET_GEMS_RESULT,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SOR_START_EXPERIENCE_INCOMPLETE,         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLBREAKLOG,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLDAMAGESHIELD,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLDISPELLOG,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLENERGIZELOG,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLHEALLOG,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLINSTAKILLLOG,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLINTERRUPTLOG,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLLOGEXECUTE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLLOGMISS,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLNONMELEEDAMAGELOG,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLORDAMAGE_IMMUNE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELLSTEALLOG,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_CATEGORY_COOLDOWN,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_COOLDOWN,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_DELAYED,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_FAILED_OTHER,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_FAILURE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_GO,                                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_START,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPELL_UPDATE_CHAIN_TARGETS,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPIRIT_HEALER_CONFIRM,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_COLLISION_DISABLE,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_COLLISION_ENABLE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_GRAVITY_DISABLE,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_GRAVITY_ENABLE,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_ROOT,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_ANIM,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_FEATHER_FALL,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_FLIGHT_BACK_SPEED,       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_FLIGHT_SPEED,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_FLYING,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_HOVER,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_LAND_WALK,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_NORMAL_FALL,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_PITCH_RATE,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_RUN_BACK_SPEED,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_RUN_MODE,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_RUN_SPEED,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_SWIM_BACK_SPEED,         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_SWIM_SPEED,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_TURN_RATE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_WALK_MODE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_WALK_SPEED,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_SET_WATER_WALK,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_START_SWIM,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_STOP_SWIM,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_UNROOT,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_UNSET_FLYING,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SPLINE_MOVE_UNSET_HOVER,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_STABLE_RESULT,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_STANDSTATE_UPDATE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_START_MIRROR_TIMER,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_START_TIMER,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_STOP_DANCE,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_STOP_MIRROR_TIMER,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_STREAMING_MOVIE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SUMMON_CANCEL,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SUMMON_REQUEST,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SUPERCEDED_SPELL,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SUPPRESS_NPC_GREETINGS,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SUSPEND_COMMS,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_SUSPEND_TOKEN_RESPONSE,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TALENTS_ERROR,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TALENTS_INFO,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TALENTS_INVOLUNTARILY_RESET,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TAXINODE_STATUS,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TEST_DROP_RATE_RESULT,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TEXT_EMOTE,                              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_THREAT_CLEAR,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_THREAT_REMOVE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_THREAT_UPDATE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TIME_ADJUSTMENT,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TIME_SYNC_REQ,                           STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_TITLE_EARNED,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TOGGLE_XP_GAIN,                          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TOTEM_CREATED,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRADE_STATUS,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRADE_STATUS_EXTENDED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRAINER_BUY_FAILED,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRAINER_BUY_SUCCEEDED,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRAINER_LIST,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRANSFER_ABORTED,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRANSFER_PENDING,                        STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TRIGGER_CINEMATIC,                       STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_TRIGGER_MOVIE,                           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TURN_IN_PETITION_RESULTS,                STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_TUTORIAL_FLAGS,                          STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_UNIT_HEALTH_FREQUENT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UNIT_SPELLCAST_START,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_ACCOUNT_DATA,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_ACCOUNT_DATA_COMPLETE,            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_COMBO_POINTS,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_CURRENCY,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_CURRENCY_WEEK_LIMIT,              STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_DUNGEON_ENCOUNTER_FOR_LOOT,       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_INSTANCE_ENCOUNTER_UNIT,          STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_INSTANCE_OWNERSHIP,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_LAST_INSTANCE,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_OBJECT,                           STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_SERVER_PLAYER_POSITION,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_UPDATE_WORLD_STATE,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_USERLIST_ADD,                            STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_USERLIST_REMOVE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_USERLIST_UPDATE,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOICESESSION_FULL,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOICE_CHAT_STATUS,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOICE_PARENTAL_CONTROLS,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOICE_SESSION_LEAVE,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOICE_SESSION_ROSTER_UPDATE,             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOICE_SET_TALKER_MUTED,                  STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOID_ITEM_SWAP_RESPONSE,                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOID_STORAGE_CONTENTS,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOID_STORAGE_FAILED,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOID_STORAGE_TRANSFER_CHANGES,           STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_VOID_TRANSFER_RESULT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WAIT_QUEUE_FINISH,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WAIT_QUEUE_UPDATE,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WARDEN_DATA,                             STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WARGAME_CHECK_ENTRY,                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WARGAME_REQUEST_SENT,                    STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WEATHER,                                 STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WEEKLY_LAST_RESET,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WEEKLY_RESET_CURRENCY,                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WEEKLY_SPELL_USAGE,                      STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WEEKLY_SPELL_USAGE_UPDATE,               STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WHO,                                     STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WHOIS,                                   STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_WORLD_SERVER_INFO,                       STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_WORLD_STATE_UI_TIMER_UPDATE,             STATUS_NEVER,        PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               ); // 5.4.2 17688
    DEFINE_OPCODE_HANDLER(SMSG_XP_GAIN_ABORTED,                         STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
    DEFINE_OPCODE_HANDLER(SMSG_ZONE_UNDER_ATTACK,                       STATUS_UNHANDLED,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );

    // These opcodes are not in WPP

  //DEFINE_OPCODE_HANDLER(CMSG_ACTIVE_PVP_CHEAT,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_ADD_PVP_MEDAL_CHEAT,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_ADVANCE_SPAWN_TIME,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_AFK_MONITOR_INFO_CLEAR,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_AFK_MONITOR_INFO_REQUEST,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_AUTH_SRP6_BEGIN,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_AUTH_SRP6_PROOF,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_AUTH_SRP6_RECODE,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_AUTOEQUIP_GROUND_ITEM,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_AUTOSTORE_GROUND_ITEM,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_JOIN,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_MANAGER_ADVANCE_STATE,       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_MANAGER_SET_NEXT_TRANSITION_TIME, STATUS_NEVER, PROCESS_INPLACE,     &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BATTLEFIELD_REQUEST_SCORE_DATA,          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     ); Need to send the response
  //DEFINE_OPCODE_HANDLER(CMSG_BATTLEMASTER_HELLO,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleBattlemasterHelloOpcode   );
  //DEFINE_OPCODE_HANDLER(CMSG_BEASTMASTER,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BOOTME,                                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BOT_DETECTED,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BOT_DETECTED2,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BUY_ITEM_IN_SLOT,                        STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleBuyItemInSlotOpcode       );
  //DEFINE_OPCODE_HANDLER(CMSG_BUY_LOTTERY_TICKET_OBSOLETE,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_BUY_STABLE_SLOT,                         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleBuyStableSlot             );
  //DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_CONTEXT_EVENT_SIGNUP,           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CALENDAR_EVENT_INVITE_NOTES,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CANCEL_GROWTH_AURA,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleCancelGrowthAuraOpcode    );
  //DEFINE_OPCODE_HANDLER(CMSG_CHANGE_GDF_ARENA_RATING,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHANGE_PERSONAL_ARENA_RATING,            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHARACTER_POINT_CHEAT,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHEAT_PLAYER_LOGIN,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHEAT_PLAYER_LOOKUP,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHEAT_SETMONEY,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHEAT_SET_ARENA_CURRENCY,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHEAT_SET_HONOR_CURRENCY,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CHECK_LOGIN_CRITERIA,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CLEAR_EXPLORATION,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CLEAR_HOLIDAY_BG_WIN_TIME,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CLEAR_QUEST,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CLEAR_RANDOM_BG_WIN_TIME,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CLEAR_SERVER_BUCK_DATA,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_COMPLETE_ACHIEVEMENT_CHEAT,              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CONTROLLER_EJECT_PASSENGER,              STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleEjectPassenger            );
  //DEFINE_OPCODE_HANDLER(CMSG_COOLDOWN_CHEAT,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CREATEGAMEOBJECT,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CREATEITEM,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_CREATEMONSTER,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DBLOOKUP,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEBUG_ACTIONS_START,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEBUG_ACTIONS_STOP,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEBUG_AISTATE,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEBUG_CHANGECELLZONE,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEBUG_LIST_TARGETS,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEBUG_PASSIVE_AURA,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEBUG_SERVER_GEO,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DECHARGE,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DECLINE_CHANNEL_INVITE,                  STATUS_LOGGEDIN,  PROCESS_INPLACE,      &WorldSession::HandleChannelDeclineInvite      );
  //DEFINE_OPCODE_HANDLER(CMSG_DELETE_DANCE,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DEL_PVP_MEDAL_CHEAT,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DESTROYMONSTER,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DESTROY_ITEMS,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DISABLE_PVP_CHEAT,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DROP_NEW_CONNECTION,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_DUMP_OBJECTS,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_ENABLE_DAMAGE_LOG,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_END_BATTLEFIELD_CHEAT,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_EXPIRE_RAID_INSTANCE,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FLAG_QUEST,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FLAG_QUEST_FINISH,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FLOOD_GRACE_CHEAT,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FORCEACTION,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FORCEACTIONONOTHER,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FORCEACTIONSHOW,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FORCE_ANIM,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_FORCE_SAY_CHEAT,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GAMESPEED_SET,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GAMETIME_SET,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GETDEATHBINDZONE,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GET_CHANNEL_MEMBER_COUNT,                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleGetChannelMemberCount     );
  //DEFINE_OPCODE_HANDLER(CMSG_GHOST,                                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GMRESPONSE_CREATE_TICKET,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_CHARACTER_RESTORE,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_CHARACTER_SAVE,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_CREATE_ITEM_TARGET,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_DESTROY_ONLINE_CORPSE,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_FREEZE,                               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_GRANT_ACHIEVEMENT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_INVIS,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_MOVECORPSE,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_NUKE,                                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_NUKE_ACCOUNT,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_NUKE_CHARACTER,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_REMOVE_ACHIEVEMENT,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_REQUEST_PLAYER_INFO,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_RESURRECT,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_REVEALTO,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_SET_CRITERIA_FOR_PLAYER,              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_SET_SECURITY_GROUP,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_SHOW_COMPLAINTS,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_SILENCE,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_SUMMONMOB,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_TEACH,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_UBERINVIS,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_UNSQUELCH,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_UNTEACH,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_UPDATE_TICKET_STATUS,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_VISION,                               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GM_WHISPER,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GODMODE,                                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GROUP_CANCEL,                            STATUS_LOGGEDIN,  PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GROUP_UNINVITE,                          STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleGroupUninviteOpcode       );
  //DEFINE_OPCODE_HANDLER(CMSG_GUILD_BANK_NOTE,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_GUILD_CREATE,                            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleGuildCreateOpcode         );
  //DEFINE_OPCODE_HANDLER(CMSG_GUILD_INFO,                              STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleGuildInfoOpcode           );
  //DEFINE_OPCODE_HANDLER(CMSG_IGNORE_DIMINISHING_RETURNS_CHEAT,        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_IGNORE_KNOCKBACK_CHEAT,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_IGNORE_REQUIREMENTS_CHEAT,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_INSTANCE_LOCK_RESPONSE,                  STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleInstanceLockResponse      );
  //DEFINE_OPCODE_HANDLER(CMSG_LEARN_DANCE_MOVE,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_LEARN_SPELL,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_LEVEL_CHEAT,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_LFG_SET_NEEDS,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_LF_GUILD_JOIN,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_LOAD_DANCES,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_LOTTERY_QUERY_OBSOLETE,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_LUA_USAGE,                               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MAELSTROM_GM_SENT_MAIL,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MAELSTROM_INVALIDATE_CACHE,              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MAELSTROM_RENAME_GUILD,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MAKEMONSTERATTACKGUID,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MEETINGSTONE_INFO,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_CHARACTER_CHEAT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_CHARM_PORT_CHEAT,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_CHARM_TELEPORT_CHEAT,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_ENABLE_SWIM_TO_FLY_TRANS_ACK,       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_SET_RELATIVE_POSITION,              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_SET_VEHICLE_REC_ID_ACK,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_START_SWIM_CHEAT,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_MOVE_STOP_SWIM_CHEAT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_NEW_SPELL_SLOT,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_NO_SPELL_VARIANCE,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PERFORM_ACTION_SET,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PETGODMODE,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PET_LEVEL_CHEAT,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PET_NAME_CACHE,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PET_UNLEARN,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PET_UNLEARN_TALENTS,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PLAYER_AI_CHEAT,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PLAYER_DIFFICULTY_CHANGE,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PLAYER_LOGOUT,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandlePlayerLogoutOpcode        );
  //DEFINE_OPCODE_HANDLER(CMSG_PROFILEDATA_REQUEST,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_PVP_QUEUE_STATS_REQUEST,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_QUERY_GUILD_MAX_XP,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_QUERY_OBJECT_POSITION,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_QUERY_OBJECT_ROTATION,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_QUERY_SERVER_BUCK_DATA,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_QUERY_VEHICLE_STATUS,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_CANCEL,                       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverCancel          );
  //DEFINE_OPCODE_HANDLER(CMSG_QUESTGIVER_QUEST_AUTOLAUNCH,             STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverQuestAutoLaunch );
  //DEFINE_OPCODE_HANDLER(CMSG_QUESTLOG_SWAP_QUEST,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleQuestLogSwapQuest         );
  //DEFINE_OPCODE_HANDLER(CMSG_RECHARGE,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_REDIRECTION_FAILED,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_REFER_A_FRIEND,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_REMOVE_GLYPH,                            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleRemoveGlyph               );
  //DEFINE_OPCODE_HANDLER(CMSG_REPLACE_ACCOUNT_DATA,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_RUN_SCRIPT,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SAVE_DANCE,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SAVE_PLAYER,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SEARCH_LFG_JOIN,                         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleLfrJoinOpcode           );
  //DEFINE_OPCODE_HANDLER(CMSG_SEARCH_LFG_LEAVE,                        STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleLfrLeaveOpcode            );
  //DEFINE_OPCODE_HANDLER(CMSG_SEND_COMBAT_TRIGGER,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SEND_EVENT,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SEND_GENERAL_TRIGGER,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SEND_LOCAL_EVENT,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SERVERINFO,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SERVERTIME,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SERVER_BROADCAST,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SERVER_COMMAND,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SERVER_INFO_QUERY,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SETDEATHBINDPOINT,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_ACTIVE_TALENT_GROUP_OBSOLETE,        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_ARENA_MEMBER_SEASON_GAMES,           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_ARENA_MEMBER_WEEKLY_GAMES,           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_ARENA_TEAM_RATING_BY_INDEX,          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_ARENA_TEAM_SEASON_GAMES,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_ARENA_TEAM_WEEKLY_GAMES,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_BREATH,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_CHARACTER_MODEL,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_CRITERIA_CHEAT,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_DURABILITY_CHEAT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_EXPLORATION,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_EXPLORATION_ALL,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_FACTION_CHEAT,                       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleSetFactionCheat           );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_GLYPH,                               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_GLYPH_SLOT,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_GRANTABLE_LEVELS,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_LFG_COMMENT,                         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleLfgSetCommentOpcode       );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_PAID_SERVICE_CHEAT,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_PVP_RANK_CHEAT,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_PVP_TITLE,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_RUNE_COOLDOWN,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_RUNE_COUNT,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_SKILL_CHEAT,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_STAT_CHEAT,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_TITLE_SUFFIX,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SET_WORLDSTATE,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SKILL_BUY_RANK,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SKILL_BUY_STEP,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_STABLE_PET,                              STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleStablePet                 );
  //DEFINE_OPCODE_HANDLER(CMSG_STABLE_REVIVE_PET,                       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleStableRevivePet           );
  //DEFINE_OPCODE_HANDLER(CMSG_STABLE_SWAP_PET,                         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleStableSwapPet             );
  //DEFINE_OPCODE_HANDLER(CMSG_START_BATTLEFIELD_CHEAT,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_START_QUEST,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_STORE_LOOT_IN_SLOT,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_SUSPEND_COMMS_ACK,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TARGET_CAST,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TARGET_SCRIPT_CAST,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TAXICLEARALLNODES,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TAXICLEARNODE,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TAXIENABLEALLNODES,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TAXIENABLENODE,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TAXISHOWNODES,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TEST_DROP_RATE,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TOGGLE_XP_GAIN,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_TRIGGER_CINEMATIC_CHEAT,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNCLAIM_LICENSE,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNDRESSPLAYER,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNITANIMTIER_CHEAT,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNLEARN_DANCE_MOVE,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNLEARN_SPELL,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNLEARN_TALENTS,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNSTABLE_PET,                            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleUnstablePet               );
  //DEFINE_OPCODE_HANDLER(CMSG_UNUSED5,                                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_UNUSED6,                                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_USE_SKILL_CHEAT,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_VOICE_SET_TALKER_MUTED_REQUEST,          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_WEATHER_SPEED_CHEAT,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_XP_CHEAT,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(CMSG_ZONE_MAP,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_DELAY_GHOST_TELEPORT,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_DEV_SHOWLABEL,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_ACCOUNT_ONLINE,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_BIND_OTHER,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_CHANGE_ARENA_RATING,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_DESTROY_CORPSE,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_GEARRATING,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_RESETINSTANCELIMIT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_SHOWLABEL,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_GM_SUMMON,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_ALL_SPEED_CHEAT,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_FLIGHT_BACK_SPEED_CHEAT,         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_FLIGHT_SPEED_CHEAT,              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_PITCH_RATE_CHEAT,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_RAW_POSITION_ACK,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_RUN_BACK_SPEED_CHEAT,            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_RUN_SPEED_CHEAT,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_SWIM_BACK_SPEED_CHEAT,           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_SWIM_SPEED_CHEAT,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_TURN_RATE_CHEAT,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_SET_WALK_SPEED_CHEAT,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_START_SWIM_CHEAT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_STOP_SWIM_CHEAT,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_TOGGLE_FALL_LOGGING,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_MOVE_TOGGLE_LOGGING,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_NULL_ACTION,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(MSG_PVP_LOG_DATA,                             STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandlePVPLogDataOpcode          );
  //DEFINE_OPCODE_HANDLER(MSG_VIEW_PHASE_SHIFT,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_NULL                     );
  //DEFINE_OPCODE_HANDLER(SMSG_AFK_MONITOR_INFO_RESPONSE,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_AURACASTLOG,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_BINDZONEREPLY,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_BUY_BANK_SLOT_RESULT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_ACTION_PENDING,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CALENDAR_UPDATE_INVITE_LIST,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CHANGEPLAYER_DIFFICULTY_RESULT,          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CHARACTER_PROFILE,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CHARACTER_PROFILE_REALM_CONNECTED,       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY_RESPONSE,    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY_RESPONSE_WRITE_FILE, STATUS_NEVER, PROCESS_INPLACE, &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CHEAT_PLAYER_LOOKUP,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CHECK_FOR_BOTS,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CLEAR_EXTRA_AURA_INFO_OBSOLETE,          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_COMBAT_LOG_MULTIPLE,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_COMMENTATOR_GET_PLAYER_INFO,             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_COMPLETION_NPC_RESPONCE,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_CORPSE_IS_NOT_IN_INSTANCE,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DAMAGE_DONE_OBSOLETE,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DBLOOKUP,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DEBUGAURAPROC,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DEBUG_AISTATE,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DEBUG_LIST_TARGETS,                      STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DEBUG_SERVER_GEO,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DUMP_OBJECTS_DATA,                       STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_DYNAMIC_DROP_ROLL_RESULT,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_FORCEACTIONSHOW,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_FORCE_ANIM,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_FORCE_DISPLAY_UPDATE,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GAMETIMEBIAS_SET,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GHOSTEE_GONE,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GMRESPONSE_CREATE_TICKET,                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GOGOGO_OBSOLETE,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GUILD_CANCEL,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GUILD_INFO,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GUILD_KNOWN_RECIPES,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GUILD_SET_NOTE,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_GUILD_TRADESKILL_UPDATE,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  DEFINE_OPCODE_HANDLER(SMSG_GUILD_XP_UPDATE,	                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  DEFINE_OPCODE_HANDLER(SMSG_GUILD_FINDER_LIST,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_IGNORE_DIMINISHING_RETURNS_CHEAT,        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_IGNORE_REQUIREMENTS_CHEAT,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_INIT_EXTRA_AURA_INFO_OBSOLETE,           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_INSPECT,                                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_JOINED_BATTLEGROUND_QUEUE,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_KICK_REASON,                             STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_LFG_OPEN_FROM_GOSSIP,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_LFG_UPDATE_LIST,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_LF_GUILD_SEARCH_RESULT,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_LOTTERY_QUERY_RESULT_OBSOLETE,           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_LOTTERY_RESULT_OBSOLETE,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MEETINGSTONE_MEMBER_ADDED,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MEETINGSTONE_SETQUEUE,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MINIGAME_MOVE_FAILED,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MOVE_CHARACTER_CHEAT,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_VEHICLE_REC_ID,                 STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MOVE_SET_WALK_IN_AIR,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MOVE_SKIP_TIME,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_MOVE_UNSET_WALK_IN_AIR,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_NPC_WONT_TALK,                           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_PET_UNLEARN_CONFIRM,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_PLAYER_UNK_DEAD_ALIVE,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_PROFILEDATA_RESPONSE,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_PUREMOUNT_CANCELLED_OBSOLETE,            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_PVP_QUEUE_STATS,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_QUERY_OBJECT_POSITION,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_QUERY_OBJECT_ROTATION,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_RAID_READY_CHECK_ERROR,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_REMOVED_FROM_PVP_QUEUE,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_RESET_RANGED_COMBAT_TIMER,               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_RESISTLOG,                               STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_RESUME_CAST_BAR,                         STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_RESURRECT_FAILED,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SCRIPT_MESSAGE,                          STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SEND_ALL_COMBAT_LOG,                     STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SERVERINFO,                              STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SERVER_BUCK_DATA,                        STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SERVER_BUCK_DATA_START,                  STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SET_EXTRA_AURA_INFO_NEED_UPDATE_OBSOLETE, STATUS_NEVER,    PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SET_EXTRA_AURA_INFO_OBSOLETE,            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SHOW_MAILBOX,                            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SPELL_CHANCE_PROC_LOG,                   STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_SPELL_CHANCE_RESIST_PUSHBACK,            STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_VOICE_SESSION_ADJUST_PRIORITY,           STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_VOICE_SESSION_ENABLE,                    STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );
  //DEFINE_OPCODE_HANDLER(SMSG_ZONE_MAP,                                STATUS_NEVER,     PROCESS_INPLACE,      &WorldSession::Handle_ServerSide               );

#undef DEFINE_OPCODE_HANDLER
};
