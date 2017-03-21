#pragma once

#include <unordered_map>

#include "api.h"
#include "channel.h"
#include "common.h"
#include "gateway.h"
#include "user.h"

//  Convoluted forward declaration
namespace web
{
  namespace http
  {
    namespace client
    {
      class http_client;
    }
  }
}

namespace discord
{
  enum event_type
  {
    Ready,
    MessageCreated,
    MessageDeleted,
    MessageEdited,
    MessagesBulkDeleted,
    EmojiCreated,
    EmojiDeleted,
    EmojiEdited,
    Presence,
    Typing
  };

  class connection_state
  {
    std::string m_token;
    int m_shards;

    std::mutex m_global_mutex;
    std::unordered_map<size_t, std::unique_ptr<std::mutex>> m_api_mutex;
    web::http::client::http_client* m_client;

    std::vector<std::unique_ptr<gateway>> m_gateways;
    std::unique_ptr<user> m_profile;
    std::unordered_map<uint64_t, guild> m_guilds;
    std::unordered_map<uint64_t, channel> m_private_channels;

    /** Allows getting a guild id from a channel id */
    std::unordered_map<uint64_t, uint64_t> m_channel_guilds;

    std::function<void(event_type, rapidjson::Value& data)> m_event_handler;

    /** Raises an event to the registered event handler if applicable.
     *
     * @param type The type of event being raised.
     * @param data The data the event contains.
     */
    void raise_event(event_type type, rapidjson::Value& data) const;

    /** Called whenever a dispatch event is sent from the gateway.
    *
    * @param event_name The name of the event that was sent.
    * @param data The data that the event contains.
    */
    void on_dispatch(std::string event_name, rapidjson::Value& data);
  public:
    connection_state();

    /** Create a connection with a set number of shards.
     *
     * @param token The token for the bot that is connecting.
     * @param shards The amount of shards to use for this connection.
     */
    connection_state(std::string token, int shards = 1);

    ~connection_state();

    /** Starts the connection by connecting to as many gateways as requested. */
    void connect();

    /** Make a request to the Discord API. Returns a task that must be synced to get a value.
     *
     * @param endpoint The endpoint to query.
     * @param major The major parameter of the API call.
     * @param type The method to use when connecting to the API.
     * @param data The JSON payload to attach.
     */
    pplx::task<api_response> connection_state::request(api_key key, snowflake major, method type, std::string endpoint, const std::string&& data = "");

    /** Registers an event handler that will be called on certain gateway events.
     *
     * @param callback A callback that accepts an event type and a JSON representation of the data.
     */
    void on_event(std::function<void(event_type, rapidjson::Value& data)> callback);


    /** Get the current token.
     *
     * @return The token used for this connection.
     */
    const std::string& token() const;

    /** Get the bot's user profile.
     *
     * @return The bot's user profile.
     */
    const user& profile() const;

    /** Get a list of guilds that this bot is currently in.
     *
     * @return A list of guilds this bot is in.
     */
    std::vector<guild> guilds() const;

    /** Find a guild by its id.
    *
    * @param id The guild's id.
    * @return The guild that was found or an empty guild if not found.
    */
    guild find_guild(snowflake id) const;

    /** Find a channel by its id.
    *
    * @param id The channel's id.
    * @return The channel that was found or an empty channel if not found.
    */
    channel find_channel(snowflake id) const;

    guild find_guild_from_channel(snowflake id) const;

    /** Adds an entry to the cache that links a channel id to a guild id.
     *
     * @param guild_id The guild id that owns the channel.
     * @param channel_id The channel id that is owned by the guild.
     */
    void cache_channel_id(snowflake guild_id, snowflake channel_id);
  };
}
