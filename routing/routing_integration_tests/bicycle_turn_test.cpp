#include "testing/testing.hpp"

#include "routing/routing_callbacks.hpp"

#include "routing/routing_integration_tests/routing_test_tools.hpp"

#include "routing/route.hpp"

namespace bicycle_turn_test
{
using namespace routing;
using namespace routing::turns;

UNIT_TEST(RussiaMoscowSevTushinoParkBicycleWayTurnTest)
{
  TRouteResult const routeResult = integration::CalculateRoute(
      integration::GetVehicleComponents(VehicleType::Bicycle),
      mercator::FromLatLon(55.87467, 37.43658), {0.0, 0.0}, mercator::FromLatLon(55.8719, 37.4464));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 3 /* expectedTurnCount */);
  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnSlightRight);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 2).TestValid().TestDirection(CarDirection::TurnSlightRight);

  integration::TestRouteLength(route, 753.0);
}

UNIT_TEST(SpainTenerifeSlightTurnMain_TurnTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(28.09214, -16.73121), {0.0, 0.0},
                                  mercator::FromLatLon(28.09227, -16.7303));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 1 /* expectedTurnCount */);
  // Turn is needed because the route goes to the one of symmetric ways.
  // It's complicated since route way has tag tertiary and alternative way - residential.
  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnSlightRight);
}

UNIT_TEST(RussiaMoscowGerPanfilovtsev22BicycleWayTurnTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.85630, 37.41004), {0.0, 0.0},
                                  mercator::FromLatLon(55.85717, 37.41052));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 2 /* expectedTurnCount */);

  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnLeft);
}

UNIT_TEST(RussiaMoscowSalameiNerisPossibleTurnCorrectionBicycleWayTurnTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.85854, 37.36795), {0.0, 0.0},
                                  mercator::FromLatLon(55.85364, 37.37318));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 3 /* expectedTurnCount */);
  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 2).TestValid().TestDirection(CarDirection::TurnSlightLeft);
}

UNIT_TEST(Russia_Moscow_SalameiNerisNoUTurnBicycleWay_TurnTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.85854, 37.36795), {0.0, 0.0},
                                  mercator::FromLatLon(55.85765, 37.36793));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  /// @note This route goes not as expected after adding surface=ground here:
  /// https://www.openstreetmap.org/way/605548369.

  // Test for unexpected but factual route.
  integration::TestTurnCount(route, 3 /* expectedTurnCount */);
  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 2).TestValid().TestDirection(CarDirection::TurnRight);
  // Test for expected but not factual route.
  /*
  integration::TestTurnCount(route, 2);
  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnLeft);
  */
}

UNIT_TEST(RussiaMoscowSevTushinoParkBicycleOnePointOnewayRoadTurnTest)
{
  m2::PointD const point = mercator::FromLatLon(55.8719, 37.4464);
  TRouteResult const routeResult = integration::CalculateRoute(
      integration::GetVehicleComponents(VehicleType::Bicycle), point, {0.0, 0.0}, point);

  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());
}

UNIT_TEST(RussiaMoscowSevTushinoParkBicycleOnePointTwowayRoadTurnTest)
{
  m2::PointD const point = mercator::FromLatLon(55.87102, 37.44222);
  TRouteResult const routeResult = integration::CalculateRoute(
      integration::GetVehicleComponents(VehicleType::Bicycle), point, {0.0, 0.0}, point);

  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());
}

UNIT_TEST(Russia_Moscow_TatishchevaOnewayCarRoad_TurnTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.71566, 37.61568), {0.0, 0.0},
                                  mercator::FromLatLon(55.71519, 37.61566));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 4 /* expectedTurnCount */);

  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 2).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 3).TestValid().TestDirection(CarDirection::TurnRight);

  integration::TestRouteLength(route, 320.0);
}

UNIT_TEST(Russia_Moscow_SvobodiOnewayBicycleWay_TurnTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.87277, 37.44002), {0.0, 0.0},
                                  mercator::FromLatLon(55.87362, 37.43853));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 5 /* expectedTurnCount */);

  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnSlightRight);
  integration::GetNthTurn(route, 2).TestValid().TestOneOfDirections(
      {CarDirection::TurnSlightLeft, CarDirection::TurnLeft});
  integration::GetNthTurn(route, 3).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 4).TestValid().TestDirection(CarDirection::TurnLeft);

  integration::TestRouteLength(route, 768.0);
}

UNIT_TEST(TurnsNearAltufievskoeShosseLongFakeSegmentTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.91569, 37.58972), {0.0, 0.0},
                                  mercator::FromLatLon(55.91608, 37.58614));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 3 /* expectedTurnCount */);

  // Complicated case.
  // RoutingEngineResult::GetPossibleTurns at (turn_m_index == 3)
  // return nodes with isCandidatesAngleValid and 2 candidates with m_angle == 0
  // In fact they are -90 and +90, but we don't know it.
  // But this should not prevent from proper directions.
  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 2).TestValid().TestDirection(CarDirection::TurnRight);

  /// @todo Check how end point snapping on "nearest" edge works. Visually, closest road is on North (now on South).
  integration::TestRouteLength(route, 279.0);
}

UNIT_TEST(TurnsNearMoscowRiverShortFakeSegmentTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.71484, 37.54868), {0.0, 0.0},
                                  mercator::FromLatLon(55.71586, 37.54594));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  // Closest snapping road is a footway on East, and there are 2 turns, obviously.
  integration::TestTurnCount(route, 2 /* expectedTurnCount */);

  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnRight);

  integration::TestRouteLength(route, 401.2);
}

UNIT_TEST(TurnsNearMKAD85kmShortFakeSegmentTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.91788, 37.58603), {0.0, 0.0},
                                  mercator::FromLatLon(55.91684, 37.57884));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 9 /* expectedTurnCount */);
  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 2).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 3).TestValid().TestDirection(CarDirection::EnterRoundAbout);
  integration::GetNthTurn(route, 4).TestValid().TestDirection(CarDirection::LeaveRoundAbout);
  integration::GetNthTurn(route, 5).TestValid().TestDirection(CarDirection::EnterRoundAbout);
  integration::GetNthTurn(route, 6).TestValid().TestDirection(CarDirection::LeaveRoundAbout);
  integration::GetNthTurn(route, 7).TestValid().TestDirection(CarDirection::TurnRight);
  integration::GetNthTurn(route, 8).TestValid().TestDirection(CarDirection::TurnLeft);

  integration::TestRouteLength(route, 1704.21);
}

UNIT_TEST(TurnsNearKhladkombinatTest)
{
  TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Bicycle),
                                  mercator::FromLatLon(55.86973, 37.45825), {0.0, 0.0},
                                  mercator::FromLatLon(55.87020, 37.46011));

  Route const & route = *routeResult.first;
  RouterResultCode const result = routeResult.second;
  TEST_EQUAL(result, RouterResultCode::NoError, ());

  integration::TestTurnCount(route, 2 /* expectedTurnCount */);

  integration::GetNthTurn(route, 0).TestValid().TestDirection(CarDirection::TurnLeft);
  integration::GetNthTurn(route, 1).TestValid().TestDirection(CarDirection::TurnRight);

  integration::TestRouteLength(route, 484.3);
}
} // namespace bicycle_turn_test
