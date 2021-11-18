#pragma once

#include <unordered_map>

namespace SocketSpy
{

enum class MessageType
{
	// Account APIs
	GetProfileName,
	GetProfileProperty,
	FindProfilesByPlatformID,

	// Automatch APIs
	GetAutomatchMap,

	// Login APIs
	Logout,
	PlatformLogin,

	// Challenge APIs
	GetChallenges,
	GetChallengeProgress,
	UpdateProgressBatched,

	// Chat APIs
	GetChatChannels,
	GetOfflineMessages,
	DeleteOfflineMessages,

	// Item APIs
	GetInventoryByProfileIDs,
	GetPersonalizedSaleItems,
	GetScheduledSaleAndItems,
	GetItemPrices,
	SignItems,
	GetItemDefinitionsJson,
	GetItemBundleItemsJson,
	GetItemLoadouts,
	GetLevelRewardsTableJson,
	MoveCharges,
	OpenItemPack,
	DetachItems,
	MoveItem,

	// News APIs,
	GetNews,

	// Party APIs
	ChatMessage,
	PeerAdd,
	PeerUpdate,
	ReportMatch,

	// Relationship APIs
	SetPresenceProperty,
	SetPresence,
	GetPresenceData,
	GetRelationships,

	// Advertisement APIs
	FindAdvertisements,
	UpdatePlatformLobbyID,
	Update,
	Host,
	StartObserving,
	StopObserving,
	Join,
	Leave,
	UpdateState,
	GetAdvertisements,
	FindObservableAdvertisements,

	// Cloud APIs
	GetFileUrl,
	GetTempCredentials,

	// Automatch2 APIs,
	Polling,
	StopPolling,
	UpdateStatus,

	// Leaderboard APIs
	RecentMatchHistory,
	RecentMatchSinglePlayerHistory,
	GetStatGroupsByProfileIds,
	GetPartyStat,
	GetAvailableLeaderboards,

	// Achievement APIs
	GetAchievements,
	GetAvailableAchievements,
	SyncStats,

	// Community APIs
	GetAvailableCommunityEvents,

	Unknown
};

static std::unordered_map<std::string /*API Path*/, MessageType> m_apiTypeMappings = {

	// Account APIs
	{"/game/account/getProfileName", MessageType::GetProfileName},
	{"/game/account/getProfileProperty", MessageType::GetProfileProperty},
	{"/game/account/FindProfilesByPlatformID", MessageType::FindProfilesByPlatformID},

	// Automatch APIs
	{"/game/automatch/getAutomatchMap", MessageType::GetAutomatchMap},

	// Login APIs
	{"/game/login/logout", MessageType::Logout},
	{"/game/login/platformlogin", MessageType::PlatformLogin},

	// Challenge APIs
	{"/game/Challenge/getChallenges", MessageType::GetChallenges},
	{"/game/Challenge/getChallengeProgress", MessageType::GetChallengeProgress},
	{"/game/Challenge/updateProgressBatched", MessageType::UpdateProgressBatched},

	// Chat APIs
	{"/game/chat/getChatChannels", MessageType::GetChatChannels},
	{"/game/chat/getOfflineMessages", MessageType::GetOfflineMessages},
	{"/game/chat/deleteOfflineMessage", MessageType::DeleteOfflineMessages},

	// Item APIs
	{"/game/item/getInventoryByProfileIDs", MessageType::GetInventoryByProfileIDs},
	{"/game/item/getPersonalizedSaleItems", MessageType::GetPersonalizedSaleItems},
	{"/game/item/getScheduledSaleAndItems", MessageType::GetScheduledSaleAndItems},
	{"/game/item/getItemPrices", MessageType::GetItemPrices},
	{"/game/item/signItems", MessageType::SignItems},
	{"/game/item/getItemDefinitionsJson", MessageType::GetItemDefinitionsJson},
	{"/game/item/getItemBundleItemsJson", MessageType::GetItemBundleItemsJson},
	{"/game/item/getItemLoadouts", MessageType::GetItemLoadouts},
	{"/game/item/getLevelRewardsTableJson", MessageType::GetLevelRewardsTableJson},
	{"/game/item/moveCharges", MessageType::MoveCharges},
	{"/game/item/openItemPack", MessageType::OpenItemPack},
	{"/game/item/detachItems", MessageType::DetachItems},
	{"/game/item/moveItem", MessageType::MoveItem},

	// News APIs
	{"/game/news/getNews", MessageType::GetNews},

	// Party APIs
	{"/game/party/sendMatchChat", MessageType::ChatMessage},
	{"/game/party/peerAdd", MessageType::PeerAdd},
	{"/game/party/peerUpdate", MessageType::PeerUpdate},
	{"/game/party/reportMatch", MessageType::ReportMatch},

	// Relationship APIs
	{"/game/relationship/setPresenceProperty", MessageType::SetPresenceProperty},
	{"/game/relationship/setPresence", MessageType::SetPresence},
	{"/game/relationship/getPresenceData", MessageType::GetPresenceData},
	{"/game/relationship/getRelationships", MessageType::GetRelationships},

	// Advertisement APIs
	{"/game/advertisement/findAdvertisements", MessageType::FindAdvertisements},
	{"/game/advertisement/updatePlatformLobbyID", MessageType::UpdatePlatformLobbyID},
	{"/game/advertisement/update", MessageType::Update},
	{"/game/advertisement/host", MessageType::Host},
	{"/game/advertisement/startObserving", MessageType::StartObserving},
	{"/game/advertisement/stopObserving", MessageType::StopObserving},
	{"/game/advertisement/join", MessageType::Join},
	{"/game/advertisement/leave", MessageType::Leave},
	{"/game/advertisement/updateState", MessageType::UpdateState},
	{"/game/advertisement/getAdvertisements", MessageType::GetAdvertisements},
	{"/game/advertisement/findObservableAdvertisements", MessageType::FindObservableAdvertisements},

	// Cloud APIs
	{"/game/cloud/getFileURL", MessageType::GetFileUrl},
	{"/game/cloud/getTempCredentials", MessageType::GetTempCredentials},

	// Automatch2 APIs
	{"/game/automatch2/polling", MessageType::Polling},
	{"/game/advertisement/stoppolling", MessageType::StopPolling},
	{"/game/advertisement/updateStatus", MessageType::UpdateStatus},

	// Leaderboard APIs
	{"/game/Leaderboard/getRecentMatchHistory", MessageType::RecentMatchHistory},
	{"/game/Leaderboard/getRecentMatchSinglePlayerHistory", MessageType::RecentMatchSinglePlayerHistory},
	{"/game/Leaderboard/getStatGroupsByProfileIDs", MessageType::GetStatGroupsByProfileIds},
	{"/game/Leaderboard/getPartyStat", MessageType::GetPartyStat},
	{"/game/Leaderboard/getAvailableLeaderboards", MessageType::GetAvailableLeaderboards},

	// Achievement APIs
	{"/game/Achievement/getAchievements", MessageType::GetAchievements},
	{"/game/Achievement/getAvailableAchievements", MessageType::GetAvailableAchievements},
	{"/game/Achievement/syncStats", MessageType::GetAvailableAchievements},

	// Community APIs
	{"/game/CommunityEvent/getAvailableCommunityEvents", MessageType::GetAvailableCommunityEvents}
};

}