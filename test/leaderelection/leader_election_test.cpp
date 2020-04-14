/*
 * Project: curve
 * Created Date: 20190709
 * Author: lixiaocui1
 * Copyright (c) 2018 netease
 */

#include <fiu-control.h>
#include <gtest/gtest.h>
#include <memory>
#include "src/leader_election/leader_election.h"
#include "src/common/namespace_define.h"
#include "test/mds/mock/mock_etcdclient.h"
#include "src/mds/nameserver2/helper/namespace_helper.h"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;

using ::curve::common::LEADERCAMPAIGNNPFX;

namespace curve {
namespace mds {

using ::curve::election::LeaderElection;
using ::curve::election::LeaderElectionOptions;

TEST(TestLeaderElection, test_leader_election) {
    auto client = std::make_shared<MockEtcdClient>();
    LeaderElectionOptions opts;
    opts.etcdCli = client;
    opts.leaderUniqueName = "leader1";
    opts.sessionInterSec = 1;
    opts.electionTimeoutMs = 0;
    opts.campaginPrefix = "hello";
    auto leaderElection = std::make_shared<LeaderElection>(opts);
    fiu_init(0);
    fiu_enable("src/mds/leaderElection/observeLeader", 1, nullptr, 0);

    std::string realPrefix = LEADERCAMPAIGNNPFX + opts.campaginPrefix;
    EXPECT_CALL(*client, CampaignLeader(
        realPrefix,
        opts.leaderUniqueName,
        opts.sessionInterSec,
        opts.electionTimeoutMs,
        _))
        .WillOnce(DoAll(SetArgPointee<4>(1),
        Return(EtcdErrCode::EtcdCampaignLeaderSuccess)));
    ASSERT_EQ(0, leaderElection->CampaginLeader());

    EXPECT_CALL(*client, CampaignLeader(
        realPrefix,
        opts.leaderUniqueName,
        opts.sessionInterSec,
        opts.electionTimeoutMs,
        _))
        .WillOnce(Return(EtcdErrCode::EtcdCampaignInternalErr));
    ASSERT_EQ(-1, leaderElection->CampaginLeader());

    EXPECT_CALL(*client, LeaderResign(1, 1000 * opts.sessionInterSec))
        .WillOnce(Return(EtcdErrCode::EtcdLeaderResiginSuccess));
    ASSERT_EQ(0, leaderElection->LeaderResign());

    EXPECT_CALL(*client, LeaderResign(1, 1000 * opts.sessionInterSec))
        .WillOnce(Return(EtcdErrCode::EtcdLeaderResignErr));
    ASSERT_EQ(-1, leaderElection->LeaderResign());

    EXPECT_CALL(*client, LeaderObserve(1, opts.leaderUniqueName))
        .WillRepeatedly(Return(EtcdErrCode::EtcdObserverLeaderInternal));
    ASSERT_EQ(-1, leaderElection->ObserveLeader());

    fiu_disable("src/mds/leaderElection/observeLeader");
}
}  // namespace mds
}  // namespace curve


