#pragma once

#include "common.h"

namespace discord
{
  class connection_state;

  /** Struct for holding API responses. Includes status code and JSON data. */
  struct api_response
  {
    rapidjson::Document data;
    uint16_t status_code;

    api_response()
    {
      status_code = 0;
    }

    api_response(const api_response& other)
    {
      data.CopyFrom(other.data, data.GetAllocator());
      status_code = other.status_code;
    }

    api_response& operator=(const api_response& other)
    {
      data.CopyFrom(other.data, data.GetAllocator());
      status_code = other.status_code;
      return *this;
    }
  };

  /** Responses that the Discord API can send. */
  enum response_code : uint32_t
  {
    UnknownAccount = 10001,
    UnknownApplication,
    UnknownChannel,
    UnknownGuild,
    UnknownIntegration,
    UnknownInvite,
    UnknownMember,
    UnknownMessage,
    UnknownOverwrite,
    UnknownProvider,
    UnknownRole,
    UnknownToken,
    UnknownUser,
    UnknownEmoji,
    UserOnlyEndpoint = 20001,
    BotOnlyEndpoint,
    MaxGuildsReached = 30001,
    MaxFriendsReached,
    MaxPinsReached,
    MaxGuildRolesReached = 30005,
    TooManyReactions = 30010,
    Unauthorized = 40001,
    MissingAccess = 50001,
    InvalidAccountType,
    CannotExecuteOnDM,
    EmbedDisabled,
    CannotEditAnotherUser,
    CannotSendEmptyMessage,
    CannotSendMessageToUser,
    CannotSendMessagesToVoiceChannel,
    ChannelVerificationTooHigh,
    OAuth2DoesNotHaveBot,
    OAuth2AppLimitReached,
    InvalidOAuth2State,
    MissingPermissions,
    InvalidAuthToken,
    NoteTooLong,
    TooFewOrTooManyMessagesToDelete,
    InvalidChannelForPin = 50019,
    TooOldToDelete = 50034,
    ReactionBlocked = 90001
  };

  enum api_key
  {
    Chan_CID,
    Chan_CID_Messages,
    Chan_CID_Messages_BulkDelete,
    Chan_CID_Messages_MID,
    Chan_CID_Messages_MID_Reactions,
    Chan_CID_Messages_MID_Reactions_Emoji,
    Chan_CID_Messages_MID_Reactions_Emoji_Me,
    Chan_CID_Messages_MID_Reactions_Emoji_UID,
    Chan_CID_Perms_OID,
    Chan_CID_Pins,
    Chan_CID_Pins_MID,
    Chan_CID_Recip_UID,
    Chan_CID_Typing,
    Gateway_Bot,
    Guild_GID,
    Guild_GID_Bans,
    Guild_GID_Bans_UID,
    Guild_GID_Chan,
    Guild_GID_Int,
    Guild_GID_Int_IID,
    Guild_GID_Int_IID_Sync,
    Guild_GID_Mem,
    Guild_GID_Mem_Me_Nick,
    Guild_GID_Mem_UID,
    Guild_GID_Mem_UID_Role_RID,
    Guild_GID_Prune,
    Guild_GID_Regions,
    Guild_GID_Roles,
    Guild_GID_Roles_RID,
  };

  namespace api
  {
    /** Get a secure websocket URL from Discord. *
      *
      * @return A WSS URL that can be used to connect to the Discord gateway.
      */
    std::string get_wss_url(connection_state& conn, int* shards = nullptr);
  }
}
