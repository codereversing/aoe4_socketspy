#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "HttpRequest.h"
#include "Parameters.h"

#include <fstream>
#include <istream>
#include <string>
#include <string_view>

using namespace SocketSpy;

std::vector<char> ToVector(std::string_view stringData)
{
	return std::vector<char> { stringData.data(), stringData.data() + stringData.length() };
}

HttpRequest MakeRequestFromFile(std::string_view fileName)
{
	std::ifstream inputFile(fileName.data(), std::istream::binary);
	REQUIRE(inputFile.is_open());

	auto content{ std::vector<char>((std::istreambuf_iterator<char>(inputFile)),
							  std::istreambuf_iterator<char>()) };
	return HttpRequest::FromRaw(content.data(), content.size());
}

void CompareConnectionInfo(PostConnectionInfoView& connectionInfoView, int callNumber,
	std::string_view connectId, int lastCallTime, std::string_view sessionId)
{
	REQUIRE(connectionInfoView.PostCallNumberViewValue().Value() == callNumber);
	REQUIRE(connectionInfoView.PostConnectIdViewValue().Value() == ToVector(connectId));
	REQUIRE(connectionInfoView.PostLastCallTimeViewValue().Value() == lastCallTime);
	REQUIRE(connectionInfoView.PostSessionIdViewValue().Value() == ToVector(sessionId));
}

void CompareConnectionInfo(GetConnectionInfoView& connectionInfoView, int callNumber,
	std::string_view connectId, int lastCallTime, std::string_view sessionId)
{
	REQUIRE(connectionInfoView.GetCallNumberViewValue().Value() == callNumber);
	REQUIRE(connectionInfoView.GetConnectIdViewValue().Value() == ToVector(connectId));
	REQUIRE(connectionInfoView.GetLastCallTimeViewValue().Value() == lastCallTime);
	REQUIRE(connectionInfoView.GetSessionIdViewValue().Value() == ToVector(sessionId));
}

void CompareModuleInfo(PostModInfoView& modInfoView, int checksum, std::string_view dllFile,
	std::string_view modName, std::string_view modVersion)
{
	REQUIRE(modInfoView.PostModDllChecksumViewValue().Value() == checksum);
	REQUIRE(modInfoView.PostModDllFileViewValue().Value() == ToVector(dllFile));
	REQUIRE(modInfoView.PostModNameViewValue().Value() == ToVector(modName));
	REQUIRE(modInfoView.PostModVersionViewValue().Value() == ToVector(modVersion));
}

void CompareModuleInfo(PostModInfo2View& modInfoView, int crcValue, std::string_view dllFile,
	std::string_view modName, std::string_view modVersion)
{
	REQUIRE(modInfoView.PostModDllFile2ViewValue().Value() == ToVector(dllFile));
	REQUIRE(modInfoView.PostModDllCRCViewValue().Value() == crcValue);
	REQUIRE(modInfoView.PostModName2ViewValue().Value() == ToVector(modName));
	REQUIRE(modInfoView.PostModVersion2ViewValue().Value() == ToVector(modVersion));
}

void CompareModuleInfo(GetModInfoView& modInfoView, int checksum, std::string_view dllFile,
	std::string_view modName, std::string_view modVersion)
{
	REQUIRE(modInfoView.GetModDllChecksumViewValue().Value() == checksum);
	REQUIRE(modInfoView.GetModDllFileViewValue().Value() == ToVector(dllFile));
	REQUIRE(modInfoView.GetModNameViewValue().Value() == ToVector(modName));
	REQUIRE(modInfoView.GetModVersionViewValue().Value() == ToVector(modVersion));
}

void CompareObserverInfo(PostObserverInfoView& observerInfoView, int isObservable, int observerDelay,
	std::string_view observerPassword)
{
	REQUIRE(observerInfoView.PostIsObservableViewValue().Value() == isObservable);
	REQUIRE(observerInfoView.PostObserverDelayViewValue().Value() == observerDelay);
	REQUIRE(observerInfoView.PostObserverPasswordViewValue().Value() == ToVector(observerPassword));
}

void ComparePasswordInfo(PostPasswordInfoView& passwordInfoView, int passworded, std::string_view password)
{
	REQUIRE(passwordInfoView.PostPasswordedViewValue().Value() == passworded);
	REQUIRE(passwordInfoView.PostPasswordViewValue().Value() == ToVector(password));
}

void CompareRaceInfoView(PostRaceInfoView& raceInfoView, std::string_view raceInfoKey,
	std::string_view raceInfoProfileId, std::string_view raceInfoRaceId)
{
	REQUIRE(raceInfoView.PostRaceInfoKeyViewValue().Value() == ToVector(raceInfoKey));
	REQUIRE(raceInfoView.PostRaceInfoProfileIdViewValue().Value() == ToVector(raceInfoProfileId));
	REQUIRE(raceInfoView.PostRaceInfoRaceIdViewValue().Value() == ToVector(raceInfoRaceId));
}

void CompareRelayInfo(PostRelayInfoView& relayInfoView, std::string_view relayPingTimes,
	std::string_view relayRegion, std::string_view relayRegions)
{
	REQUIRE(relayInfoView.PostRelayPingTimesViewValue().Value() == ToVector(relayPingTimes));
	REQUIRE(relayInfoView.PostRelayRegionViewValue().Value() == ToVector(relayRegion));
	REQUIRE(relayInfoView.PostRelayRegionsViewValue().Value() == ToVector(relayRegions));
}

TEST_CASE("View Find Advertisements") {

	auto httpRequest{ MakeRequestFromFile("requests/findAdvertisements.log") };
	auto findAdvertisements{ GetFindAdvertisementsView(httpRequest) };

	CompareConnectionInfo(findAdvertisements.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	CompareModuleInfo(findAdvertisements.GetModInfoViewValue(), 0, "INVALID", "INVALID", "INVALID");
	REQUIRE(findAdvertisements.GetAppBinaryChecksumViewValue().Value() == 8888);
	REQUIRE(findAdvertisements.GetDataChecksumViewValue().Value() == -888);
	REQUIRE(findAdvertisements.GetMatchTypeIdViewValue().Value() == 0);
	REQUIRE(findAdvertisements.GetProfileIds2ViewValue().Value() == ToVector("%5B1%2C1%5D"));
	REQUIRE(findAdvertisements.GetRaceIdsViewValue().Value() == ToVector("%5B1%2C2%2C3%5D"));
	REQUIRE(findAdvertisements.GetStatGroupIdsViewValue().Value() == ToVector("%5B4%2C5%2C6%5D"));
	REQUIRE(findAdvertisements.GetVersionFlagsViewValue().Value() == 0);
}

TEST_CASE("View Find Observable Advertisements") {

	auto httpRequest{ MakeRequestFromFile("requests/findObservableAdvertisements.log") };
	auto findObservableAdvertisements{ GetFindObservableAdvertisementsView(httpRequest) };

	CompareConnectionInfo(findObservableAdvertisements.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	CompareModuleInfo(findObservableAdvertisements.GetModInfoViewValue(), 0, "INVALID", "INVALID", "INVALID");
	REQUIRE(findObservableAdvertisements.GetAppBinaryChecksumViewValue().Value() == 8888);
	REQUIRE(findObservableAdvertisements.GetDataChecksumViewValue().Value() == -888);
	REQUIRE(findObservableAdvertisements.GetCountViewValue().Value() == 20);
	REQUIRE(findObservableAdvertisements.GetObserverGroupIdViewValue().Value() == 0);
	REQUIRE(findObservableAdvertisements.GetSortOrderViewValue().Value() == 0);
	REQUIRE(findObservableAdvertisements.GetStartViewValue().Value() == 0);
	REQUIRE(findObservableAdvertisements.GetVersionFlagsViewValue().Value() == 0);
}

TEST_CASE("View Find Profiles By Platform ID") {

	auto httpRequest{ MakeRequestFromFile("requests/FindProfilesByPlatformID.log") };
	auto findProfilesByPlatformId{ PostFindProfilesByPlatformIdView(httpRequest) };

	CompareConnectionInfo(findProfilesByPlatformId.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(findProfilesByPlatformId.PostPlatformIdsViewValue().Value() == ToVector("%5B9%2C8%2C7%5D"));
}

TEST_CASE("View Get Achievements") {

	auto httpRequest{ MakeRequestFromFile("requests/getAchievements.log") };
	auto getAchievements{ GetAchievementsView(httpRequest) };

	CompareConnectionInfo(getAchievements.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getAchievements.GetProfileIdsViewValue().Value() == ToVector("%5B1%2C1%5D"));
}

TEST_CASE("View Get Advertisements") {

	auto httpRequest{ MakeRequestFromFile("requests/getAdvertisements.log") };
	auto getAdvertisements{ GetAdvertisementsView(httpRequest) };

	CompareConnectionInfo(getAdvertisements.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getAdvertisements.GetMatchIdsViewValue().Value() == ToVector("%5B5%5D"));
}

TEST_CASE("View Get Automatch Map") {

	auto httpRequest{ MakeRequestFromFile("requests/getAutomatchMap.log") };
	auto getAutomatchMap{ GetAutomatchMapView(httpRequest) };

	CompareConnectionInfo(getAutomatchMap.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Get Available Achievements") {

	auto httpRequest{ MakeRequestFromFile("requests/getAvailableAchievements.log") };
	auto getAvailableAchievements{ GetAvailableAchievementsView(httpRequest) };

	CompareConnectionInfo(getAvailableAchievements.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getAvailableAchievements.GetSignatureViewValue().Value() == ToVector("sss"));
}

TEST_CASE("View Get Available Community Events") {

	auto httpRequest{ MakeRequestFromFile("requests/getAvailableCommunityEvents.log") };
	auto getAvailableCommunityEvents{ GetAvailableCommunityEventsView(httpRequest) };

	CompareConnectionInfo(getAvailableCommunityEvents.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Get Available Leaderboards") {

	auto httpRequest{ MakeRequestFromFile("requests/getAvailableLeaderboards.log") };
	auto getAvailableLeaderboards{ GetAvailableLeaderboardsView(httpRequest) };

	CompareConnectionInfo(getAvailableLeaderboards.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Get Party Stat") {

	auto httpRequest{ MakeRequestFromFile("requests/getPartyStat.log") };
	auto getPartyStat{ GetPartyStatView(httpRequest) };

	CompareConnectionInfo(getPartyStat.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getPartyStat.GetStatsIdsViewValue().Value() == ToVector("%5B1%2C2%5D"));
}

TEST_CASE("View Get Challenge Progress") {

	auto httpRequest{ MakeRequestFromFile("requests/getChallengeProgress.log") };
	auto getChallengeProgress{ GetChallengeProgressView(httpRequest) };

	CompareConnectionInfo(getChallengeProgress.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Get Challenges") {

	auto httpRequest{ MakeRequestFromFile("requests/getChallenges.log") };
	auto getChallenges{ GetChallengesView(httpRequest) };

	CompareConnectionInfo(getChallenges.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getChallenges.GetSignatureViewValue().Value() == ToVector("sss"));
}

TEST_CASE("View Get Chat Channels") {

	auto httpRequest{ MakeRequestFromFile("requests/getChatChannels.log") };
	auto getChatChannels{ GetChatChannelsView(httpRequest) };

	CompareConnectionInfo(getChatChannels.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Get File URL") {

	auto httpRequest{ MakeRequestFromFile("requests/getFileURL.log") };
	auto getFileUrl{ GetFileUrlView(httpRequest) };

	CompareConnectionInfo(getFileUrl.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getFileUrl.GetNamesViewValue().Value() == ToVector("%5B%22Attrib.sga%22%2C%22EngineData.sga%22%5D"));
}

TEST_CASE("View Get Temp Credentials") {

	auto httpRequest{ MakeRequestFromFile("requests/getTempCredentials.log") };
	auto getTempCredentials{ GetTempCredentialsView(httpRequest) };

	CompareConnectionInfo(getTempCredentials.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getTempCredentials.GetKeyViewValue().Value() == ToVector("file.gz"));
}

TEST_CASE("View Get Invetory By Profile Ids") {

	auto httpRequest{ MakeRequestFromFile("requests/getInventoryByProfileIDs.log") };
	auto getInventoryByProfileIds{ GetInventoryByProfileIdsView(httpRequest) };

	CompareConnectionInfo(getInventoryByProfileIds.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getInventoryByProfileIds.GetProfileIdsViewValue().Value() == ToVector("%5B1%2C1%5D"));
}

TEST_CASE("View Get Bundle Items Json") {

	auto httpRequest{ MakeRequestFromFile("requests/getItemBundleItemsJson.log") };
	auto getBundleItemsJson{ GetItemBundlesJsonView(httpRequest) };

	CompareConnectionInfo(getBundleItemsJson.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getBundleItemsJson.GetSignatureViewValue().Value() == ToVector("sss"));
}

TEST_CASE("View Get Item Definitions Json") {

	auto httpRequest{ MakeRequestFromFile("requests/getItemDefinitionsJson.log") };
	auto getItemDefinitionsJson{ GetItemDefinitionsJsonView(httpRequest) };

	CompareConnectionInfo(getItemDefinitionsJson.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getItemDefinitionsJson.GetSignatureViewValue().Value() == ToVector("sss"));
}

TEST_CASE("View Get Item Loadouts") {

	auto httpRequest{ MakeRequestFromFile("requests/getItemLoadouts.log") };
	auto getItemLoadouts{ GetItemLoadoutsView(httpRequest) };

	CompareConnectionInfo(getItemLoadouts.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Detach Items") {

	auto httpRequest{ MakeRequestFromFile("requests/detachItems.log") };
	auto detachItems{ PostDetachItemsView(httpRequest) };

	CompareConnectionInfo(detachItems.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(detachItems.PostItemIdsViewValue().Value() == ToVector("%5B2%5D"));
	REQUIRE(detachItems.PostItemChargesViewValue().Value() == ToVector("%5B1%5D"));
	REQUIRE(detachItems.PostItemLocationsViewValue().Value() == ToVector("%5B0%5D"));
}

TEST_CASE("View Get Item Prices") {

	auto httpRequest{ MakeRequestFromFile("requests/getItemPrices.log") };
	auto getItemPrices{ GetItemPricesView(httpRequest) };

	CompareConnectionInfo(getItemPrices.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getItemPrices.GetAccountTypeViewValue().Value() == 3);
	REQUIRE(getItemPrices.GetCountryViewValue().Value() == ToVector("us"));
	REQUIRE(getItemPrices.GetCurrencyViewValue().Value() == ToVector("usd"));
	REQUIRE(getItemPrices.GetSaleVersionViewValue().Value() == -1);
}

TEST_CASE("View Move Charges") {

	auto httpRequest{ MakeRequestFromFile("requests/moveCharges.log") };
	auto moveCharges{ PostMoveChargesView(httpRequest) };

	CompareConnectionInfo(moveCharges.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(moveCharges.PostChargesViewValue().Value() == ToVector("%5B123%5D"));
	REQUIRE(moveCharges.PostDeletesViewValue().Value() == ToVector("%5B1%5D"));
	REQUIRE(moveCharges.PostFromItemIdsViewValue().Value() == ToVector("%5B321%5D"));
	REQUIRE(moveCharges.PostToItemIdsViewValue().Value() == ToVector("%5B456%5D"));
}

TEST_CASE("View Move Item") {

	auto httpRequest{ MakeRequestFromFile("requests/moveItem.log") };
	auto moveItem{ PostMoveItemView(httpRequest) };

	CompareConnectionInfo(moveItem.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(moveItem.PostItemIdsViewValue().Value() == ToVector("%5B1%2C2%5D"));
	REQUIRE(moveItem.PostItemLocationIdsViewValue().Value() == ToVector("%5B0%2C2%5D"));
	REQUIRE(moveItem.PostPosIdsViewValue().Value() == ToVector("%5B-1%2C-1%5D"));
	REQUIRE(moveItem.PostSlotIdsViewValue().Value() == ToVector("%5B-1%2C-1%5D"));
}

TEST_CASE("View Open Item Pack") {

	auto httpRequest{ MakeRequestFromFile("requests/openItemPack.log") };
	auto openItemPack{ PostOpenItemPackView(httpRequest) };

	CompareConnectionInfo(openItemPack.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(openItemPack.PostChoicesViewValue().Value() == ToVector("%5B%5D"));
	REQUIRE(openItemPack.PostItemInstanceIdViewValue().Value() == 5678);
	REQUIRE(openItemPack.PostItemLocationIdViewValue().Value() == 0);
}

TEST_CASE("View Level Rewards Table Json") {

	auto httpRequest{ MakeRequestFromFile("requests/getLevelRewardsTableJson.log") };
	auto getLevelRewardsTableJson{ GetLevelRewardsTableJsonView(httpRequest) };

	CompareConnectionInfo(getLevelRewardsTableJson.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(getLevelRewardsTableJson.GetSignatureViewValue().Value() == ToVector("sss"));
}

TEST_CASE("View News") {

	auto httpRequest{ MakeRequestFromFile("requests/getNews.log") };
	auto getNews{ GetNewsView(httpRequest) };

	CompareConnectionInfo(getNews.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Offline Messages") {

	auto httpRequest{ MakeRequestFromFile("requests/getOfflineMessages.log") };
	auto offlineMessages{ GetOfflineMessagesView(httpRequest) };

	CompareConnectionInfo(offlineMessages.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Delete Offline Message") {

	auto httpRequest{ MakeRequestFromFile("requests/deleteOfflineMessage.log") };
	auto deleteOfflineMessage{ PostDeleteOfflineMessages(httpRequest) };

	CompareConnectionInfo(deleteOfflineMessage.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(deleteOfflineMessage.PostMessageIdViewValue().Value() == 333);
}

TEST_CASE("View Personalized Sale Items") {

	auto httpRequest{ MakeRequestFromFile("requests/getPersonalizedSaleItems.log") };
	auto personalizedSaleItems{ GetPersonalizedSaleItemsView(httpRequest) };

	CompareConnectionInfo(personalizedSaleItems.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Presence Data") {

	auto httpRequest{ MakeRequestFromFile("requests/getPresenceData.log") };
	auto presenceData{ GetPresenceDataView(httpRequest) };

	CompareConnectionInfo(presenceData.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Profile Name") {

	auto httpRequest{ MakeRequestFromFile("requests/getProfileName.log") };
	auto profileName{ GetProfileNameView(httpRequest) };

	CompareConnectionInfo(profileName.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(profileName.GetProfileIds2ViewValue().Value() == ToVector("%5B1%2C1%5D"));
}

TEST_CASE("View Set Avatar Metadata") {

	auto httpRequest{ MakeRequestFromFile("requests/setAvatarMetadata.log") };
	auto avatarMetadata{ PostSetAvatarMetadata(httpRequest) };

	CompareConnectionInfo(avatarMetadata.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(avatarMetadata.PostMetadataViewValue().Value() == ToVector("%7B%22sharedHistory%22%3A0%7D"));
}

TEST_CASE("View Profile Property") {

	auto httpRequest{ MakeRequestFromFile("requests/getProfileProperty.log") };
	auto profileProperty{ GetProfilePropertyView(httpRequest) };

	CompareConnectionInfo(profileProperty.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(profileProperty.GetProfileIdViewValue().Value() == 99);
	REQUIRE(profileProperty.GetPropertyIdViewValue().Value() == ToVector("appearOffline"));
}

TEST_CASE("View Recent Match History") {

	auto httpRequest{ MakeRequestFromFile("requests/getRecentMatchHistory.log") };
	auto recentMatchHistory{ GetRecentMatchHistoryView(httpRequest) };

	CompareConnectionInfo(recentMatchHistory.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(recentMatchHistory.GetProfileIds2ViewValue().Value() == ToVector("%5B1%2C1%5D"));
}

TEST_CASE("View Recent Match History Single Player") {

	auto httpRequest{ MakeRequestFromFile("requests/getRecentMatchSinglePlayerHistory.log") };
	auto recentMatchHistorySinglePlayer{ GetRecentMatchHistorySinglePlayerView(httpRequest) };

	CompareConnectionInfo(recentMatchHistorySinglePlayer.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(recentMatchHistorySinglePlayer.GetProfileIds2ViewValue().Value() == ToVector("%5B-1%5D"));
}

TEST_CASE("View Relationships") {

	auto httpRequest{ MakeRequestFromFile("requests/getRelationships.log") };
	auto relationships{ GetRelationshipsView(httpRequest) };

	CompareConnectionInfo(relationships.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
}

TEST_CASE("View Scheduled Sale And Items") {

	auto httpRequest{ MakeRequestFromFile("requests/getScheduledSaleAndItems.log") };
	auto scheduledSaleAndItems{ GetScheduledSaleAndItemsView(httpRequest) };

	CompareConnectionInfo(scheduledSaleAndItems.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(scheduledSaleAndItems.GetSaleTypeViewValue().Value() == 1);
}

TEST_CASE("View Stat Groups By Profile Ids") {

	auto httpRequest{ MakeRequestFromFile("requests/getStatGroupsByProfileIDs.log") };
	auto statGroupsByProfileIds{ GetStatGroupsByProfileIdsView(httpRequest) };

	CompareConnectionInfo(statGroupsByProfileIds.GetConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(statGroupsByProfileIds.GetProfileIds3ViewValue().Value() == ToVector("%5B1%2C1%5D"));
}

TEST_CASE("View Host") {

	auto httpRequest{ MakeRequestFromFile("requests/host.log") };
	auto host{ PostHostView(httpRequest) };

	CompareConnectionInfo(host.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	CompareObserverInfo(host.PostObserverInfoViewValue(), 1, 180, "");
	CompareModuleInfo(host.PostModInfoViewValue(), 0, "INVALID", "INVALID", "INVALID");
	ComparePasswordInfo(host.PostPasswordInfoViewValue(), 0, "");
	REQUIRE(host.PostAdvertisementIdViewValue().Value() == -1);
	REQUIRE(host.PostAppBinaryChecksumViewValue().Value() == 4141);
	REQUIRE(host.PostAutomatchPollIdViewValue().Value() == -1);
	REQUIRE(host.PostDatachecksumViewValue().Value() == -777);
	REQUIRE(host.PostDescriptionViewValue().Value() == ToVector("SESSION_MATCH_KEY"));
	REQUIRE(host.PostHostIdViewValue().Value() == 1);
	REQUIRE(host.PostMapNameViewValue().Value() == ToVector("no_map"));
	REQUIRE(host.PostMatchTypeViewValue().Value() == 19);
	REQUIRE(host.PostMaxPlayersViewValue().Value() == 8);
	REQUIRE(host.PostOptionsViewValue().Value() == ToVector("opts"));
	REQUIRE(host.PostPartyViewValue().Value() == -1);
	REQUIRE(host.PostRaceViewValue().Value() == 123);
	REQUIRE(host.PostRelayRegionViewValue().Value() == ToVector("eastus"));
	REQUIRE(host.PostServiceTypeViewValue().Value() == 0);
	REQUIRE(host.PostSlotInfoViewValue().Value() == ToVector("slot"));
	REQUIRE(host.PostStateViewValue().Value() == -1);
	REQUIRE(host.PostStatGroupViewValue().Value() == -1);
	REQUIRE(host.PostTeamViewValue().Value() == -1);
	REQUIRE(host.PostVersionFlagsViewValue().Value() == 0);
	REQUIRE(host.PostVisibleViewValue().Value() == 0);
}

TEST_CASE("View Join") {

	auto httpRequest{ MakeRequestFromFile("requests/join.log") };
	auto join{ PostJoinView(httpRequest) };

	CompareConnectionInfo(join.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	CompareModuleInfo(join.PostModInfoViewValue(), 0, "INVALID", "INVALID", "INVALID");
	REQUIRE(join.PostAdvertisementIdViewValue().Value() == 1);
	REQUIRE(join.PostAppBinaryChecksumViewValue().Value() == 4141);
	REQUIRE(join.PostDatachecksumViewValue().Value() == -777);
	REQUIRE(join.PostPartyViewValue().Value() == 66);
	REQUIRE(join.PostRaceViewValue().Value() == 123);
	REQUIRE(join.PostStatGroupViewValue().Value() == -1);
	REQUIRE(join.PostTeamViewValue().Value() == -1);
	REQUIRE(join.PostVersionFlagsViewValue().Value() == 0);
}

TEST_CASE("View Leave") {

	auto httpRequest{ MakeRequestFromFile("requests/leave.log") };
	auto leave{ PostLeaveView(httpRequest) };

	CompareConnectionInfo(leave.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(leave.PostAdvertisementIdViewValue().Value() == 1);
}

TEST_CASE("View Peer Add") {

	auto httpRequest{ MakeRequestFromFile("requests/peerAdd.log") };
	auto peerAdd{ PostPeerAddView(httpRequest) };

	CompareConnectionInfo(peerAdd.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(peerAdd.PostMatchIdViewValue().Value() == 555);
	REQUIRE(peerAdd.PostProfileIds2ViewValue().Value() == ToVector("%5B1%2C1%5D"));
	REQUIRE(peerAdd.PostRaceIdsViewValue().Value() == ToVector("%5B1%2C2%2C3%5D"));
	REQUIRE(peerAdd.PostStatGroupIdsViewValue().Value() == ToVector("%5B4%2C5%2C6%5D"));
	REQUIRE(peerAdd.PostTeamIdsViewValue().Value() == ToVector("%5B0%5D"));
}

TEST_CASE("View Peer Update") {

	auto httpRequest{ MakeRequestFromFile("requests/peerUpdate.log") };
	auto peerUpdate{ PostPeerUpdateView(httpRequest) };

	CompareConnectionInfo(peerUpdate.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(peerUpdate.PostMatchIdViewValue().Value() == 555);
	REQUIRE(peerUpdate.PostIsNonParticipantsViewValue().Value() == ToVector("%5B0%2C0%5D"));
	REQUIRE(peerUpdate.PostIsNonParticipantsViewValue().Value() == ToVector("%5B0%2C0%5D"));
	REQUIRE(peerUpdate.PostProfileIds2ViewValue().Value() == ToVector("%5B1%2C1%5D"));
	REQUIRE(peerUpdate.PostRaceIdsViewValue().Value() == ToVector("%5B1%2C2%2C3%5D"));
	REQUIRE(peerUpdate.PostTeamIdsViewValue().Value() == ToVector("%5B0%2C1%5D"));
}

TEST_CASE("View Platform Login") {

	auto httpRequest{ MakeRequestFromFile("requests/platformlogin.log") };
	auto platformLogin{ PostPlatformLoginView(httpRequest) };

	REQUIRE(platformLogin.PostAccountTypeViewValue().Value() == ToVector("STEAM"));
	REQUIRE(platformLogin.PostActiveMatchIdViewValue().Value() == -1);
	REQUIRE(platformLogin.PostAliasViewValue().Value() == ToVector("name"));
	REQUIRE(platformLogin.PostAppIdViewValue().Value() == 8888);
	REQUIRE(platformLogin.PostAuthViewValue().Value() == ToVector("authzzz"));
	REQUIRE(platformLogin.PostCallNumberViewValue().Value() == 123);
	REQUIRE(platformLogin.PostClientLibVersionViewValue().Value() == 5);
	REQUIRE(platformLogin.PostConnectIdViewValue().Value() == ToVector(""));
	REQUIRE(platformLogin.PostCountryViewValue().Value() == ToVector("US"));
	REQUIRE(platformLogin.PostInstallationTypeViewValue().Value() == ToVector("windows"));
	REQUIRE(platformLogin.PostLanguageViewValue().Value() == ToVector("en"));
	REQUIRE(platformLogin.PostLastCallTimeViewValue().Value() == 111);
	REQUIRE(platformLogin.PostMacAddressViewValue().Value() == ToVector("mac"));
	REQUIRE(platformLogin.PostMajorVersionViewValue().Value() == ToVector("0.0.0"));
	REQUIRE(platformLogin.PostMinorVersionViewValue().Value() == 7777);
	REQUIRE(platformLogin.PostPlatformUserIdViewValue().Value() == ToVector("666"));
	REQUIRE(platformLogin.PostStartGameTokenViewValue().Value() == ToVector(""));
	REQUIRE(platformLogin.PostSyncHashViewValue().Value() == ToVector("%5B0%2C0%5D"));
	REQUIRE(platformLogin.PostTimeoutOverrideViewValue().Value() == 0);
	REQUIRE(platformLogin.PostTitleViewValue().Value() == ToVector("age4"));
}

TEST_CASE("View Start Polling") {

	auto httpRequest{ MakeRequestFromFile("requests/polling.log") };
	auto polling{ PostStartPollingView(httpRequest) };

	CompareConnectionInfo(polling.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	CompareModuleInfo(polling.PostModInfo2ViewValue(), 0, "INVALID", "INVALID", "INVALID");
	CompareRaceInfoView(polling.PostRaceInfoViewValue(), "%5B0%2C1%2C2%2C3%5D", "%5B1%2C1%2C1%2C1%5D",
		"%5B8%2C8%2C8%2C8%5D");
	CompareRelayInfo(polling.PostRelayInfoViewValue(), "%5B1%2C1%2C2%2C2%2C3%2C3%2C4%2C4%2C5%5D",
		"eastus", "%5B%22westeurope%22%2C%22ukwest%22%2C%22australiasoutheast%22%2C%22westindia%22%2C%22"
		"eastus%22%2C%22southeastasia%22%2C%22brazilsouth%22%2C%22westus2%22%2C%22koreacentral%22%5D");
	REQUIRE(polling.PostAppBinCRCViewValue().Value() == 9876);
	REQUIRE(polling.PostDataCRCViewValue().Value() == 6789);
	REQUIRE(polling.PostFactionIdsViewValue().Value() == ToVector("%5B0%2C0%2C0%2C0%5D"));
	REQUIRE(polling.PostMatchTypesViewValue().Value() == ToVector("%5B20%2C21%2C22%2C23%5D"));
	REQUIRE(polling.PostOptionsViewValue().Value() == ToVector("%5B%22%22%2C%22%22%2C%22%22%2C%22%22%5D"));
	REQUIRE(polling.PostPartySessionIdViewValue().Value() == 444);
	REQUIRE(polling.PostVersionFlagsViewValue().Value() == 0);
}

TEST_CASE("View Report Match") {

	auto httpRequest{ MakeRequestFromFile("requests/reportMatch.log") };
	auto reportMatch{ PostReportMatchView(httpRequest) };

	CompareConnectionInfo(reportMatch.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(reportMatch.PostChecksumsViewValue().Value() == ToVector("%5B0%2C0%5D"));
	REQUIRE(reportMatch.PostCountersZipViewValue().Value() == ToVector("zip"));
	REQUIRE(reportMatch.PostItemUpdatesViewValue().Value() == ToVector("upd"));
	REQUIRE(reportMatch.PostMatchIdViewValue().Value() == 555);
	REQUIRE(reportMatch.PostProfileIds2ViewValue().Value() == ToVector("%5B1%2C1%5D"));
	REQUIRE(reportMatch.PostRaceIdsViewValue().Value() == ToVector("%5B1%2C2%2C3%5D"));
	REQUIRE(reportMatch.PostResultsViewValue().Value() == ToVector("%5B0%2C1%5D"));
	REQUIRE(reportMatch.PostSimPlayerIdsViewValue().Value() == ToVector("%5B1%2C7%5D"));
	REQUIRE(reportMatch.PostTeamIdsViewValue().Value() == ToVector("%5B0%2C1%5D"));
	REQUIRE(reportMatch.PostXpGainedViewValue().Value() == ToVector("%5B2%2C20%5D"));
}

TEST_CASE("View Match Chat Message") {

	auto httpRequest{ MakeRequestFromFile("requests/sendMatchChat.log") };
	auto matchChat{ PostMatchChatMessageView(httpRequest) };

	CompareConnectionInfo(matchChat.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(matchChat.PostBroadcastViewValue().Value() == 1);
	REQUIRE(matchChat.PostFromProfileIdViewValue().Value() == 111);
	REQUIRE(matchChat.PostMatchIdViewValue().Value() == 555);
	REQUIRE(matchChat.PostMessageViewValue().Value() == ToVector("dummymsg"));
	REQUIRE(matchChat.PostMessageTypeIdViewValue().Value() == 2);
	REQUIRE(matchChat.PostToProfileIdViewValue().Value() == 222);
}

TEST_CASE("View Set Presence") {

	auto httpRequest{ MakeRequestFromFile("requests/setPresence.log") };
	auto setPresence{ PostSetPresenceView(httpRequest) };

	CompareConnectionInfo(setPresence.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(setPresence.PostPresenceIdViewValue().Value() == 3);
}

TEST_CASE("View Set Presence Property") {

	auto httpRequest{ MakeRequestFromFile("requests/setPresenceProperty.log") };
	auto setPresence{ PostSetPresencePropertyView(httpRequest) };

	CompareConnectionInfo(setPresence.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(setPresence.PostPresencePropertyDefIdViewValue().Value() == -1);
	REQUIRE(setPresence.PostValueViewValue().Value() == ToVector(""));
}

TEST_CASE("View Sign Items") {

	auto httpRequest{ MakeRequestFromFile("requests/signItems.log") };
	auto signItems{ PostSignItemsView(httpRequest) };

	CompareConnectionInfo(signItems.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(signItems.PostCRCViewValue().Value() == 888);
}

TEST_CASE("View Start Observing") {

	auto httpRequest{ MakeRequestFromFile("requests/startObserving.log") };
	auto startObserving{ PostStartObservingView(httpRequest) };

	CompareConnectionInfo(startObserving.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	CompareModuleInfo(startObserving.PostModInfoViewValue(), 0, "INVALID", "INVALID", "INVALID");
	REQUIRE(startObserving.PostAdvertisementIdViewValue().Value() == 1);
	REQUIRE(startObserving.PostAppBinaryChecksumViewValue().Value() == 8888);
	REQUIRE(startObserving.PostDatachecksumViewValue().Value() == -888);
	REQUIRE(startObserving.PostPasswordViewValue().Value() == ToVector(""));
	REQUIRE(startObserving.PostVersionFlagsViewValue().Value() == 0);
	REQUIRE(startObserving.PostWithPartySessionIdViewValue().Value() == 333);
}

TEST_CASE("View Stop Observing") {

	auto httpRequest{ MakeRequestFromFile("requests/stopObserving.log") };
	auto stopObserving{ PostStopObservingView(httpRequest) };

	CompareConnectionInfo(stopObserving.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(stopObserving.PostAdvertisementIdViewValue().Value() == 1);
}

TEST_CASE("View Stop Polling") {

	auto httpRequest{ MakeRequestFromFile("requests/stopPolling.log") };
	auto stopPolling{ PostStopPollingView(httpRequest) };

	CompareConnectionInfo(stopPolling.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(stopPolling.PostOwnerProfileIdViewValue().Value() == 444);
	REQUIRE(stopPolling.PostCommitViewValue().Value() == 0);
}

TEST_CASE("View Sync Stats") {

	auto httpRequest{ MakeRequestFromFile("requests/syncStats.log") };
	auto syncStats{ PostSyncStatsView(httpRequest) };

	CompareConnectionInfo(syncStats.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(syncStats.PostAuthViewValue().Value() == ToVector(""));
	REQUIRE(syncStats.PostAccountTypeViewValue().Value() == ToVector("STEAM"));
}

TEST_CASE("View Update") {

	auto httpRequest{ MakeRequestFromFile("requests/update.log") };
	auto update{ PostUpdateView(httpRequest) };

	CompareConnectionInfo(update.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	CompareObserverInfo(update.PostObserverInfoViewValue(), 1, 180, "");
	CompareModuleInfo(update.PostModInfoViewValue(), 0, "INVALID", "INVALID", "INVALID");
	ComparePasswordInfo(update.PostPasswordInfoViewValue(), 0, "");
	REQUIRE(update.PostAdvertisementIdViewValue().Value() == 1);
	REQUIRE(update.PostAppBinaryChecksumViewValue().Value() == 4141);
	REQUIRE(update.PostAutomatchPollIdViewValue().Value() == -1);
	REQUIRE(update.PostDatachecksumViewValue().Value() == -777);
	REQUIRE(update.PostDescriptionViewValue().Value() == ToVector("SESSION_MATCH_KEY"));
	REQUIRE(update.PostHostIdViewValue().Value() == 1);
	REQUIRE(update.PostMapNameViewValue().Value() == ToVector("no_map"));
	REQUIRE(update.PostMatchTypeViewValue().Value() == 19);
	REQUIRE(update.PostMaxPlayersViewValue().Value() == 8);
	REQUIRE(update.PostOptionsViewValue().Value() == ToVector("opts"));
	REQUIRE(update.PostSlotInfoViewValue().Value() == ToVector("slot"));
	REQUIRE(update.PostStateViewValue().Value() == -1);
	REQUIRE(update.PostVersionFlagsViewValue().Value() == 0);
	REQUIRE(update.PostVisibleViewValue().Value() == 0);
}

TEST_CASE("View Update Platform Lobby Id") {

	auto httpRequest{ MakeRequestFromFile("requests/updatePlatformLobbyID.log") };
	auto updatePlatformLobbyId{ PostUpdatePlatformLobbyIdView(httpRequest) };

	CompareConnectionInfo(updatePlatformLobbyId.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(updatePlatformLobbyId.PostMatchId2ViewValue().Value() == 555);
	REQUIRE(updatePlatformLobbyId.PostPlatformLobbyIdViewValue().Value() == ToVector("1"));
}

TEST_CASE("View Update Progress Batched") {

	auto httpRequest{ MakeRequestFromFile("requests/updateProgressBatched.log") };
	auto updateProgressBatched{ PostUpdateProgressBatchedView(httpRequest) };

	CompareConnectionInfo(updateProgressBatched.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(updateProgressBatched.PostProgressIdsViewValue().Value() == ToVector("%5B999%5D"));
	REQUIRE(updateProgressBatched.PostUpdateAmountsViewValue().Value() == ToVector("%5B1%5D"));
}

TEST_CASE("View Update State") {

	auto httpRequest{ MakeRequestFromFile("requests/updateState.log") };
	auto updateState{ PostUpdateStateView(httpRequest) };

	CompareConnectionInfo(updateState.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(updateState.PostAdvertisementIdViewValue().Value() == 1);
	REQUIRE(updateState.PostStateViewValue().Value() == 1);
}

TEST_CASE("View Update Status") {

	auto httpRequest{ MakeRequestFromFile("requests/updateStatus.log") };
	auto updateStatus{ PostUpdateStatusView(httpRequest) };

	CompareConnectionInfo(updateStatus.PostConnectionInfoViewValue(), 123, "ccc", 111, "zzz");
	REQUIRE(updateStatus.PostMatchId2ViewValue().Value() == 555);
	REQUIRE(updateStatus.PostResultViewValue().Value() == 1);
	REQUIRE(updateStatus.PostResultCodeViewValue().Value() == 0);
}

TEST_CASE("Parse GET Request") {

	auto httpRequest{ MakeRequestFromFile("requests/dummyGet.log") };

	REQUIRE(httpRequest.HttpType() == "GET");
	REQUIRE(httpRequest.Path() == "/game/Achievement/getAvailableAchievements?");
	REQUIRE(httpRequest.QueryParameters() == ToVector("param1=1"));
	REQUIRE(httpRequest.Version() == "HTTP/1.1");
	const auto& headers = httpRequest.Headers();
	REQUIRE(headers.find("Cookie")->second == "ApplicationGatewayAffinity=0;ApplicationGatewayAffinityCORS=1;reliclink=2;");
	REQUIRE(headers.find("Host")->second == "aoe-api.reliclink.com");
	REQUIRE(headers.find("Accept-Encoding")->second == "identity");
	REQUIRE(headers.find("Accept")->second == "*/*");
	REQUIRE(headers.find("Pragma")->second == "no-cache");
	REQUIRE(headers.find("Content-Type")->second == "application/x-www-form-urlencoded; charset=UTF-8");
	REQUIRE(headers.find("Cache-Control")->second == "no-store");
	REQUIRE(httpRequest.Content().size() == 0);
}

TEST_CASE("Parse POST Request") {

	auto httpRequest{ MakeRequestFromFile("requests/dummyPost.log") };

	REQUIRE(httpRequest.HttpType() == "POST");
	REQUIRE(httpRequest.Path() == "/game/item/signItems");
	REQUIRE(httpRequest.QueryParameters() == ToVector(""));
	REQUIRE(httpRequest.Version() == "HTTP/1.1");
	const auto& headers = httpRequest.Headers();
	REQUIRE(headers.find("Cookie")->second == "ApplicationGatewayAffinity=0;ApplicationGatewayAffinityCORS=1;reliclink=2;");
	REQUIRE(headers.find("Host")->second == "aoe-api.reliclink.com");
	REQUIRE(headers.find("Accept-Encoding")->second == "identity");
	REQUIRE(headers.find("Accept")->second == "*/*");
	REQUIRE(headers.find("Content-Length")->second == "127");
	REQUIRE(headers.find("Pragma")->second == "no-cache");
	REQUIRE(headers.find("Content-Type")->second == "application/x-www-form-urlencoded; charset=UTF-8");
	REQUIRE(headers.find("Cache-Control")->second == "no-store");
	REQUIRE(httpRequest.Content() == ToVector("callNum=123&connect_id=ccc&crc=888&lastCallTime=111&sessionID=zzz"));
}
